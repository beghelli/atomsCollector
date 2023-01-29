#include <SDL2/SDL.h>

class Player
{

private:
	int x;
	int y;
	float xv;
	float yv;
	double zAngle;
	bool isAcceleratingX;
	bool isAcceleratingY;
	SDL_Texture* texture;

	void calculatePosition(const unsigned char* keys);
	void limitPositionToScreenSize();
	void calculateZAngle(SDL_Point mousePosition);
	void fire(bool isMouseDown);

public:
	Player(int x, int y);

	bool load(SDL_Renderer* renderer);
	void applyInputs(const unsigned char* keys, SDL_Point mousePosition, bool isMouseDown);
	void render(SDL_Renderer* renderer);
	void destroy();
};
