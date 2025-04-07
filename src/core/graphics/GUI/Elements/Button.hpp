#include <vector>
#include <string>

struct GUIstyle;
class VAO;

class Button
{
private:
	std::vector<std::string> vID;
	std::vector<GUIstyle> vStyle;
	std::vector<void(*)()> vFunction;
	std::vector<bool> vActive;
	std::vector<bool> vHover;

	unsigned int nButton = 0;

	VAO* vao = nullptr;

	void compileVAO();
	bool flagCompileVAO = false;

	unsigned int vaoID = 0;

public:
	Button();
	~Button();

	void add(
		GUIstyle style,
		void(*function)() = nullptr,
		std::string ID = "button"
	);

	void setStyle(std::string ID, GUIstyle style);
	//void setPos(std::string ID, float x, float y);

	void Delete(std::string ID);
	void DeleteALL();

	void update(double mouseX, double mouseY, bool LBM);
	void render();
};