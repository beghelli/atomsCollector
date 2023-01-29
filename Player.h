#include <SDL2/SDL.h>

class Player
{

private:
	int x;
	int y;
	float xv;
	float yv;
	bool isAcceleratingX;
	bool isAcceleratingY;

public:
	Player(int x, int y);

	bool load(SDL_Renderer* renderer);
	void applyInputs(const unsigned char* keys, SDL_Point mousePosition);
	void render(SDL_Renderer* renderer);
	void destroy();
};
