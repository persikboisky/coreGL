

class Shader;

struct fontsMesh
{

};

struct font
{
private:
	Shader* shader;

public:
	static void draw2D(const char* text, float x, float y);
};