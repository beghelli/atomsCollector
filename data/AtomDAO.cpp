#include <string>
#include <fstream>
#include <sstream>
#include "constants.h"
#include "AtomDAO.h"
#include "Atom.h"

using namespace Data;

unordered_map<string, AtomData> Data::AtomDAO::atomDataRepository;

AtomData Data::AtomDAO::getById(string id)
{
	return atomDataRepository[id];
}

bool Data::AtomDAO::loadData()
{
	if (atomDataRepository.size() == 0)
	{
		string filename = "." + PATH_SEPARATOR + DATA_FOLDER + PATH_SEPARATOR + "atoms.csv";
		fstream atomsFile(filename, ios::in);

		if (! atomsFile.is_open())
		{
			return false;
		}

		string line, data;
		while (getline(atomsFile, line))
		{
			AtomData atomData;
			stringstream str(line);

			getline(str, data, CSV_SEPARATOR);
			atomData.id = data;

			getline(str, data, CSV_SEPARATOR);
			atomData.atomicNumber = stoi(data);

			getline(str, data, CSV_SEPARATOR);
			atomData.atomicMass = stoi(data);

			getline(str, data, CSV_SEPARATOR);
			atomData.acronym = data;

			// Color, get each value separated by space.
			getline(str, data, CSV_SEPARATOR);
			SDL_Color color;
			string rgbaData;
			stringstream rgbaDataStream(data);
			getline(rgbaDataStream, rgbaData, ' ');
			color.r = stoi(rgbaData);
			getline(rgbaDataStream, rgbaData, ' ');
			color.g = stoi(rgbaData);
			getline(rgbaDataStream, rgbaData, ' ');
			color.b = stoi(rgbaData);
			getline(rgbaDataStream, rgbaData, ' ');
			color.a = stoi(rgbaData);
			atomData.color = color;

			getline(str, data, CSV_SEPARATOR);
			atomData.name = data;

			getline(str, data, CSV_SEPARATOR);
			atomData.description = data;

			atomDataRepository[atomData.id] = atomData;
		}

		atomsFile.close();
	}

	return true;
}
