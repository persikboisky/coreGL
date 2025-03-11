#include <glm/glm.hpp>

struct style
{
	glm::vec4 color_1; // основной цет
	glm::vec4 color_2; // цвет взаимодействия
	glm::vec4 color_3; // цвет контура
	glm::vec4 color_4; // цвет взаимодействия с контуром

	int mode;		   // 0 - спрайт, 1 - кнопка, 2 - текст
};