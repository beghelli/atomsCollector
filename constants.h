#include <filesystem>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

const int DEBUG = false;
const int DEBUG_KEY = SDL_SCANCODE_B;

// Game only works well with aspect ratio equals to 16:9. So we should only use dimensions like:
// 1920w x 1080h
// 1600w x 900h
// 1280w x 720h
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const bool FULLSCREEN = false;

const string ASSETS_FOLDER = "assets";
const string DATA_FOLDER = "data";
const char CSV_SEPARATOR = ';';

static const string PATH_SEPARATOR(1, filesystem::path::preferred_separator);
