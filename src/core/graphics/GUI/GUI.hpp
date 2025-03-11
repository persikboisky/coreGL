#include <vector>
#include <glm/glm.hpp>

class Window;
class VAO;
class Shader;

namespace GUI
{
	class Body;
}

class GUI::Body
{
private:
	Shader* shader = nullptr;
	VAO* vao = nullptr;

	std::vector<std::vector<float>> vertex;
	std::vector<int> id;

	//int currentIndexSettings = 0;
	int currentIndexElement = 0;

public:
	Body();
	~Body();

	void startCreate();
	//void addColor(float red, float green, float blue, float alhpa);
	//void addPng();
	void createButton(float x, float y, float width, float height, int id);
	void endCreate();

	void Render();
};