#include <string>
#include <vector>

namespace ENGINE::CORE {
	class Scene;
}


std::vector<std::string> splitString(const std::string& str);
void LoadScene(const char* path, ENGINE::CORE::Scene& scene);
void UnloadTextures();
