#pragma once
#include <unordered_map>

using namespace std;

namespace Data
{
	typedef struct LevelData
	{
		string id;
		string title;
		string desiredMoleculeId;
		int desiredAtomsAppearanceChance;
	} LevelData;

	class LevelDAO
	{
		public:
			static unordered_map<string, LevelData> levelDataRepository;

			LevelData getById(string id);
			static bool loadData();
	};
}
