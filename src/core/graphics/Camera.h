#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera
{
private:
    glm::vec3 x;
    glm::vec3 y;
    glm::vec3 z;
    glm::vec3 pos;

    glm::mat4 rot = glm::mat4(1.0f);

    float fov;

public:
    Camera(float posX, float posY, float posZ, float fov);

    void rotate(float x, float y, float z);
    void resetRotate();
    void move(float x, float y, float z);

    glm::mat4 getProj(int width, int height);
    glm::mat4 getView();
};