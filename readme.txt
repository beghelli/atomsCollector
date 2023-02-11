COMPILE (REFERENCE DEPENDENCIES, DEV)
g++ -o demo2 demo.c GameEntity.cpp Player.cpp Bullet.cpp -IC:\dev\SDL2-2.26.3\x86_64-w64-mingw32\include -LC:\dev\SDL2-2.26.3\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2

COMPILE AND LINKER COMMAND (STATICALLY INCLUDE DEPENDENCIES, PRODUCTION)
g++ -o demo2 demo.c GameEntity.cpp Player.cpp Bullet.cpp -IC:\dev\SDL2-2.26.3\x86_64-w64-mingw32\include -LC:\dev\SDL2-2.26.3\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static