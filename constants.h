#include <filesystem>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

const int DEBUG = false;
const int DEBUG_KEY = SDL_SCANCODE_B;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;
const string ASSETS_FOLDER = "assets";

static const string PATH_SEPARATOR(1, filesystem::path::preferred_separator);
