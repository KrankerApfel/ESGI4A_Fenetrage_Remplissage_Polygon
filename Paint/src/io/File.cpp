#include "File.h"
#include <fstream>
using namespace std;

string File::read(string path)
{
    ifstream fileStream(path, ios::in | ios::binary);
    if (fileStream)
    {
        string ctn;
        fileStream.seekg(0, ios::end);
        ctn.resize(fileStream.tellg());
        fileStream.seekg(0, ios::beg);
        fileStream.read(&ctn[0], ctn.size());
        fileStream.close();
        return ctn;
    }
    spdlog::error("Could not read file at {}", path);
    return "";


}
