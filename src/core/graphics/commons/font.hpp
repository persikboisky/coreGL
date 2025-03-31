#include <string>
#include <vector>

class Shader;
class Texture;

enum styleBillText
{

};

struct font 
{
	Texture* textureFont;

	float widthSymbol;
	float heightSymbol;

	font(const char* name = "standard");
	~font();
};

class BufferText2D
{
private:
	static Shader* shader2D;
	static unsigned int n_Buffer;
	font* Font;

	bool vaoCompile = true;
	std::vector<float> vertexes;

	unsigned int vao = 0;
	unsigned int n_vertex = 0;

public:
	BufferText2D();
	~BufferText2D();

	void linkFont(font &Font);
	void linkFont(font* &Font);

	void addText(
		std::string text = "Hello World",
		float x = -0.5, 
		float y = 0.5,
		float width = 1.0, 
		float height = 1.0,
		float c_red = 1.0, 
		float c_green = 1.0,
		float c_blue = 1.0,
		float c_alpha = 1.0
	);

	void DeleteText();

	void render();
};

class BufferText3D final
{
};