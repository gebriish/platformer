#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>

#include <core/scene.h>
#include <renderer/texture.h>

#include "sceneloader.h"

using namespace ENGINE;

std::vector<std::string> splitString(const std::string& str) {
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string word;

    while (iss >> word) {
        result.push_back(word);
    }

    return result;

}

void loadEntity(std::vector<std::string> arg, CORE::Scene& scene)
{
	auto entity = scene.CreateEntity();

	f32 x = 0, y = 0;
	std::stringstream(arg[1]) >> x;
	std::stringstream(arg[2]) >> y;
	entity->Position = {x, y};

	x = y = 0;
	std::stringstream(arg[3]) >> x;
	std::stringstream(arg[4]) >> y;
	entity->Size = {x, y};

	x = y = 0;
	std::stringstream(arg[5]) >> x;
	std::stringstream(arg[6]) >> y;
	entity->UV0 = {x, y};

	x = y = 0;
	std::stringstream(arg[7])  >> x;
	std::stringstream(arg[8]) >> y;
	entity->UV1 = {x, y};

	entity->Tag = arg[9].c_str();
	if(arg[10] == "true")
		entity->Visible = true;
	else if(arg[10] == "false")
		entity->Visible = false;
	else {
		printf("%s: unidentified\n", arg[10].c_str());
	}

	int texture_id;
	std::stringstream(arg[11]) >> texture_id;

	if(texture_id < scene.GetNumTextures())
		entity->Texture = scene.GetTexture(texture_id);
	else
		entity->Texture = scene.GetTexture(0);


	int r, g, b, a;
	std::stringstream(arg[12]) >> r;
	std::stringstream(arg[13]) >> g;
	std::stringstream(arg[14]) >> b;
	std::stringstream(arg[15]) >> a;
	entity->Color = {(u8)r, (u8)g, (u8)b, (u8)a};


}

void loadTexture(std::vector<std::string> arg, CORE::Scene& scene)
{
	scene.LoadTexture(arg[1].c_str());
}

void LoadScene(const char* path, CORE::Scene& scene) {

    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }


	std::string line;
	int lineindex = 1;
	
	while(std::getline(file, line))
	{
		if(line.empty() || line.at(0) == '#')
		{
			lineindex++;
			continue;
		}

		std::vector<std::string> args = splitString(line);
		
		if(args[0] == "entity")
			loadEntity(args, scene);

		else if(args[0] == "texture")
			loadTexture(args, scene);

		else
		{
			printf(".scene file parsing error.\n");
			printf("\terror[%d, %d]: unidentified arg \'%s\'\n", lineindex, 0, args[0].c_str());
		}

		lineindex++;
	}

    file.close();
}
