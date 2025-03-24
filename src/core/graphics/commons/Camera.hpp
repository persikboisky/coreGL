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
    float distance;

public:
    Camera(float posX, float posY, float posZ, float fov, float distance);

    void rotate(float x, float y, float z);
    void resetRotate();
    void move(float x, float y, float z);

    void setPos3f(glm::vec3 pos);
    void setPos(float x, float y, float z);

    void getPos3f(glm::vec3 &pos) const;
    void getPos(float &x, float &y, float &z) const;

    glm::mat4 getProj(int width, int height) const;
    glm::mat4 getView() const;
};