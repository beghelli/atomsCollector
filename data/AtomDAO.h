#pragma once
#include <vector>
#include <string>
#include <SDL2/SDL.h>

namespace Data
{
	typedef struct AtomData {
		string id;
		int atomicNumber;
		int atomicMass;
		string acronym;
		SDL_Color color;
		string name;
		string description;
		string textureFilename;
	} AtomData;

	class AtomDAO
	{

		public:
			static unordered_map<string, AtomData> atomDataRepository;

			AtomData getById(string id);
			AtomData getRandomBut(vector<string> excludeIds);
			static bool loadData();
	};
}
