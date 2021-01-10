/*####################################################################################################################
#																													 #
#																													 #
#																													 #
#										Tom RAKOTOMANAMPISON and Lior DILER                                          #
#													   present                                                       #
#																													 #
#																													 #
#                           __________      .__          _________.__                                                #
#                           \______   \____ |  | ___.__./   _____/|  | _____  ___.__. ___________                    #
#                            |     ___/  _ \|  |<   |  |\_____  \ |  | \__  \<   |  |/ __ \_  __ \                   #
#                            |    |  (  <_> )  |_\___  |/        \|  |__/ __ \\___  \  ___/|  | \/                   #
#                            |____|   \____/|____/ ____/_______  /|____(____  / ____|\___  >__|                      #
#                           					 \/            \/           \/\/         \/                          #
#																													 #
#																													 #
#               					 ~ an OpenGL project to study polygon clipping ~                                 #
#																													 #
#																													 #
#																													 #
#																													 #
#																													 #
#                               	       4th grade 3D and Video Game engineering                                   #
#                                                    ESGI - 2020/2021                                                #																													 #
#																													 #
####################################################################################################################*/



#include "stdafx.h"
#include "src/rendering/Shader.h"
#include "src/rendering/Mesh.h"

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

static void glfw_error_callback(int error, const char* description)
{
	spdlog::error("Glfw Error {}: {}", error, description);
}
int main()
{

	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);

	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	ImGui_ImplOpenGL3_Init(glsl_version);
	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	float my_color[4];

	// shaders
	// -- 2D simple heart vertices and indices --
	vector<Vertex> vertices =
	{
		::Vertex { glm::vec3(-0.5f, 1.0f, 0.0f), },
		::Vertex { glm::vec3(0.0f, 0.3f, 0.0f),  },
		::Vertex { glm::vec3(0.5f, 1.0f, 0.0f),  },
		::Vertex { glm::vec3(1.0f, 0.3f, 0.0f),  },
		::Vertex { glm::vec3(0.0f, -1.0f, 0.0f), },
		::Vertex { glm::vec3(-1.0f, 0.3f, 0.0f), }
	};
	vector<unsigned int> indices = {
		0, 1, 5,
		1, 2, 3,
		3, 4, 1,
		1, 4, 5
	};
	Shader s("src\\resources\\vert.glsl", "src\\resources\\frag.glsl");
	Mesh m(vertices, indices);

	while (!glfwWindowShouldClose(window)) {

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		if (show_another_window)
		{
			// Create a window called "My First Tool", with a menu bar.
			ImGui::Begin("My First Tool", &show_another_window, ImGuiWindowFlags_MenuBar);
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
					if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
					if (ImGui::MenuItem("Close", "Ctrl+W")) { show_another_window = false; }
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			// Edit a color (stored as ~4 floats)
			ImGui::ColorEdit4("Color", my_color);

			// Plot some values
			const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
			ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

			// Display contents in a scrolling region
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
			ImGui::BeginChild("Scrolling");
			for (int n = 0; n < 50; n++)
				ImGui::Text("%04d: Some text", n);
			ImGui::EndChild();
			ImGui::End();
		}

		processInput(window);


		ImGui::Render();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		s.use();
		m.draw(s);
		glfwPollEvents();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(window);


	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	//test


	return 0;
}