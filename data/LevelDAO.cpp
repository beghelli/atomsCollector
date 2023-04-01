#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "constants.h"
#include "LevelDAO.h"

using namespace std;
using namespace Data;

unordered_map<string, LevelData> Data::LevelDAO::levelDataRepository;

LevelData Data::LevelDAO::getById(string id)
{
	return levelDataRepository[id];
}

bool Data::LevelDAO::loadData()
{
	const string filename = "." + PATH_SEPARATOR + DATA_FOLDER + PATH_SEPARATOR + "levels.csv"; 
	fstream levelDataFile(filename, ios::in);

	if (! levelDataFile.is_open())
	{
		return false;
	}

	int lineIndex = 1;
	string line, data;
	while (getline(levelDataFile, line))
	{
		if (lineIndex > 1)
		{
			LevelData levelData;
			stringstream lineStream(line);
			
			getline(lineStream, data, CSV_SEPARATOR);		
			levelData.id = data;

			getline(lineStream, data, CSV_SEPARATOR);
			levelData.title = data;

			getline(lineStream, data, CSV_SEPARATOR);
			levelData.desiredMoleculeId = data;

			getline(lineStream, data, CSV_SEPARATOR);
			levelData.desiredAtomsAppearanceChance = stoi(data);

			levelDataRepository[levelData.id] = levelData;
		}

		lineIndex++;
	}

	if (DEBUG)
	{
		for (auto pair: levelDataRepository)
		{
			auto data = pair.second;
			cout << "ID: " << data.id << endl;
			cout << "Title: " << data.title << endl;
			cout << "Desired Molecule: " << data.desiredMoleculeId << endl;
			cout << "Desired Atoms Appearance Chance: " << data.desiredAtomsAppearanceChance << endl;

			cout << "#########################" << endl;
		}
	}

	return true;
}
