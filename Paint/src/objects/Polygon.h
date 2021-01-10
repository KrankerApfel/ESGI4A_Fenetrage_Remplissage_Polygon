#pragma once

#include <glm/glm.hpp>
#include "Point.h"
#include "../rendering/Mesh.h"
#include <vector>
#include "../../../stdafx.h"
using namespace std;
namespace PaintSlayer {


	class Polygon {

	public:
		Polygon();
		Polygon(vector<Point>& );
		std::array<float, 4> getColor() const;
		void setColor(std::array<float, 4>);
		vector<Point> getPoints() const;
		void addPoint(double x, double y);
		void removePoint();
		void draw(Shader& shader);
	private:
		vector<Point> points;
		Mesh mesh;
		std::array<float, 4> color;

	};
}