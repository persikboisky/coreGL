#include <vector>
#include <glm/glm.hpp>

class VAO;

namespace GUI
{
	class Style;

	class Body
	{
	private:
		VAO* vao;

		std::vector<unsigned int> id;
		std::vector<glm::vec4> cord_and_size;
		std::vector<GUI::Style*> style;

		unsigned int SelectID = 0;

		void addElement(int x, int y, float width, float height, GUI::Style* style);

	public:
		Body();
		~Body();

		void addButton(int x, int y, float width, float height, void* function = nullptr, GUI::Style* style = nullptr);
		void compile();
		void render();

		void DeleteElement(unsigned int id);
	};
}

