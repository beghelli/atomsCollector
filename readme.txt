ATOMS COLLECTOR
It is a game where the player has to collect atoms to produce a desired number of an specific molecule. In order to collect the atoms, the player has to touch them in an specific way. The stage is full of different types of atoms that keep moving in different speeds and that are identified them by their atomic number (isotopes of the same atom will be identified by their atomic mass). The player has some passive and active abilities that will help collecting the atoms.

LEARNING OBJECTIVES
We hope that the game will help students learning / memorizing:
- atoms and their basic particles
- isotopes
- periodic table, atomic mass, atomic number
- molecules and molecular formula
- fission and fusion reactions

PLAYER ABILITIES
The player can:
- move into any direction on the stage
	- use A W S D keys to move left, up, right and down. Use two directional keys to move diagonally.
- run
	- while moving, holds SHIFT key to run
- shoot a neutron into any direction
	- aim using the mouse and shoot by clicking any mouse button. Holding the mouse button will charge the neutron with more energy and releasing the button will shoot the neutron charged with extra energy.
- collect atoms it touches
	- move close to an atom until it touches the front part of the player while holding SPACE key. A player and atom collision will happen if:
		- the player doesn't hold the SPACE key while touching the atom
		- or the atom touches the back part of the player
		- player has no room in the atom containers to contain the touched atom

ATOM CONTAINERS
The player has containers that will hold the collected atoms. On each stage the player will have available a number of containers sufficient to hold all the atoms that form the molecule plus one. The extra one will contain atoms that the player collects but are not part of the molecule.

ATOM AND PLAYER COLLISION
If an atom touches the player while it is not holding the SPACE key, the atom and the player will collide. The atom will move to an opposite direction and the player will consume energy to absorb the impact. The higher the atomic mass and or atom velocity, the higher energy the player will have to spend to survive the collision.

REUSING ATOMS
The collected atoms that are not part of the desired molecule can be reused to:
- fuel the energy generator (for simplicity we can assume fission and fusion processes can easily happen with any type of atom, a more realistic approach to the energy generation can be a future expansion of the game)
- provide neutrons for the player to shoot

ENERGY
To perform any ability and to defend itself from atoms collisions, the player consumes energy. An energy bar is displayed to the player so it knows how much energy left it has to complete the atoms collection.

The energy generator can be fueled by the collected atoms that are not part of the desired molecule. It will slowly produce more energy for the player to consume, filling the energy bar while it consumes atoms (therefore emptying the other atoms container).

The player can also fill the energy bar (a high amount) if it can collect, in a short period of time, 3 hidrogen atoms in sequece:
- hidrogen
- deuterium
- tritium
The collection combo will trigger a fusion process that will generate an atom of helium (that will appear in the stage coming out from the player position) and a lot of energy (filling the energy bar). The fusion process will only happen if the player has enough energy to trigger it after the 3 atoms are collected.

ATOMS INTERACTION
Using the neutron shot, the player can interact with atoms that are on the stage to:
- change the atom direction
- create isotopes by adding neutrons to their nucleous
- fission an atom into two
The amount of energy required for each operation increases and the player can adjust the shot energy level, limited only by the amount of available energy it has.

These 3 atoms interactions help the player to reach the goal of collecting the correct atoms that will produce the desired molecule. For example:
- the molecule to build is water
- the player didn't collect many hydrogens yet
- the stage only has a few Helium atoms and lots of other atoms
In this scenario, the player can collect enough atoms to produce energy and, when it has enough energy, shoot a high energized neutron into a Helium atom to break it into two hydrogen (very simplistic fission, but necessary to make the game fun as well) and then collect the resulting hydrogens. The energy released by the fission will speed up nearby atoms and the player might have to "defend" itself from them using the neutron shot to change their direction.

Another scenario is when there are lots of available atoms of hydrogen and the player wants to produce a lot of energy, it can shoot neutrons at the hydronge atom to create isotopes and then collect them sequentially to produce energy from fusion.

ATOMS COLLECTION COMBO
Players can also directly produce the desired molecules if they collect atoms in the correct order of the molecule formula during a certain small period of time. Using the water molecule example, the player would have to collect 2 hydrogen and 1 oxygen sequentially to directly produce the molecule. When that happens, the collected atoms don't fill the containers, they are directly used to produce the molecule. This allows skilled players to produce more molecules then what their containers capacity can hold in atoms.

WHEN THE GAME IS OVER
When the player runs out of energy or when the containers to hold the desired atom containers are full. Either way, the player will receive its score based on the number of molecules it was able to produce.

COMPILE (REFERENCE DEPENDENCIES, DEV)
g++ -o game main.cpp .\engine\Core.cpp .\engine\Entity.cpp .\engine\MetricManager.cpp MyGame.cpp .\engine\GameEntity.cpp .\engine\Game.cpp .\gameEntities\Atom.cpp .\gameEntities\Player.cpp .\gameEntities\Bullet.cpp .\UIEntities\ScoreBoard.cpp .\engine\support\EntityRepository.cpp .\engine\support\CollisionDetector.cpp .\engine\support\ScreenWriter.cpp .\engine\support\Message.cpp .\engine\support\EventsManager.cpp .\engine\support\Event.cpp .\events\PlayerAndAtomCollided.cpp .\scenes\HuntAtoms.cpp -IC:\dev\SDL2-2.26.3\x86_64-w64-mingw32\include -LC:\dev\SDL2-2.26.3\x86_64-w64-mingw32\lib -LC:\dev\SDL2_ttf-2.20.2\x86_64-w64-mingw32\lib -I.\gameEntities\ -I.\UIEntities\ -I.\events\ -I.\engine\support\ -I.\engine -I. -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

COMPILE AND LINKER COMMAND (STATICALLY INCLUDE DEPENDENCIES, PRODUCTION)
g++ -o game main.cpp .\engine\Core.cpp .\engine\Entity.cpp .\engine\MetricManager.cpp MyGame.cpp .\engine\GameEntity.cpp .\engine\Game.cpp .\gameEntities\Atom.cpp .\gameEntities\Player.cpp .\gameEntities\Bullet.cpp .\UIEntities\ScoreBoard.cpp .\engine\support\EntityRepository.cpp .\engine\support\CollisionDetector.cpp .\engine\support\ScreenWriter.cpp .\engine\support\Message.cpp .\engine\support\EventsManager.cpp .\engine\support\Event.cpp .\events\PlayerAndAtomCollided.cpp .\scenes\HuntAtoms.cpp -IC:\dev\SDL2-2.26.3\x86_64-w64-mingw32\include -LC:\dev\SDL2-2.26.3\x86_64-w64-mingw32\lib -LC:\dev\SDL2_ttf-2.20.2\x86_64-w64-mingw32\lib -I.\gameEntities\ -I.\UIEntities\ -I.\events\ -I.\engine\support\ -I.\engine -I. -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lrpcrt4 -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static
