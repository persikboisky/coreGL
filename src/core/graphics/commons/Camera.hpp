#include <glm/glm.hpp>
#include <glm/ext.hpp>

enum CAM_MODE
{
    DYNAMIC,
    STATIC
};

class Camera
{
private:
    glm::vec3 startUP = glm::vec3(0, 1, 0);
    glm::vec3 startTARGET = glm::vec3(0, 0, -1);

    glm::vec3 up;
    glm::vec3 target;
    glm::vec3 pos;

    glm::mat4 rot = glm::mat4(1.0f);

    float fov;  
    float distance;

    CAM_MODE mode;

public:
    Camera(float posX, float posY, float posZ, float fov, float distance);

    void setMode(CAM_MODE mode);

    void rotate(float x, float y, float z);
    void resetRotate();
    void move(float x, float y, float z);

    void setPos3f(glm::vec3 pos);
    void setPos(float x, float y, float z);

    void setTarget(float x, float y, float z);
    void setTarget3f(glm::vec3 target);

    void getPos3f(glm::vec3 &pos) const;
    void getPos(float &x, float &y, float &z) const;

    glm::mat4 getProj(int width, int height) const;
    glm::mat4 getView() const;
};