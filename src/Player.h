class Camera;

class Player
{
private:
	Camera *cam;
	void review(int w_width, int w_height, double mouseX, double mouseY); 

public:
	Player(float x, float y, float z, float fov);
	~Player();

	void move(bool keyArray[]);
	void render(const char* nameUniformView, const char* nameUniformProj, int w_width, int w_height, double mouseX, double mouseY);
};

