#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "constants.h"
#include "MoleculeDAO.h"

using namespace std;
using namespace Data;

unordered_map<string, MoleculeData> Data::MoleculeDAO::moleculeDataRepository;

MoleculeData Data::MoleculeDAO::getById(string id)
{
	return moleculeDataRepository[id];
}

bool Data::MoleculeDAO::loadData()
{
	if (moleculeDataRepository.size() == 0)
	{
		string filename = "." + PATH_SEPARATOR + DATA_FOLDER + PATH_SEPARATOR + "molecules.csv";
		fstream moleculesFile(filename, ios::in);

		if (! moleculesFile.is_open())
		{
			return false;
		}

		string line, data;
		int totalAtomsCount = 0;
		while (getline(moleculesFile, line))
		{
			MoleculeData moleculeData;
			stringstream str(line);

			getline(str, data, CSV_SEPARATOR);
			moleculeData.id = data;

			getline(str, data, CSV_SEPARATOR);
			moleculeData.name = data;

			getline(str, data, CSV_SEPARATOR);
			moleculeData.description = data;

			// Molecular formula.
			getline(str, data, CSV_SEPARATOR);
			string formulaItemData;
			stringstream formulaStream(data);
			getline(formulaStream, formulaItemData, ' ');

			while (formulaItemData.length())
			{
				MolecularFormulaItem formulaItem;
				string formulaItemAttributeValue;
				stringstream formulaItemStream(formulaItemData);
				getline(formulaItemStream, formulaItemAttributeValue, '-');

				if (formulaItemAttributeValue.length())
				{
					formulaItem.atomId = formulaItemAttributeValue;
				}

				getline(formulaItemStream, formulaItemAttributeValue, '-');
				if (formulaItemAttributeValue.length())
				{
					formulaItem.quantity = stoi(formulaItemAttributeValue);
					totalAtomsCount += formulaItem.quantity;
				}

				if (formulaItem.atomId.length() && formulaItem.quantity)
				{
					moleculeData.formula.push_back(formulaItem);
				}

				if (formulaStream.eof())
				{
					break;
				}
				getline(formulaStream, formulaItemData, ' ');
			}

			moleculeData.totalAtomsCount = totalAtomsCount;
			moleculeDataRepository[moleculeData.id] = moleculeData;
		}

		moleculesFile.close();
	}

	if (DEBUG)
	{
		for (auto pair: moleculeDataRepository)
		{
			auto data = pair.second;
			cout << "ID: " << data.id << endl;
			cout << "Name: " << data.name << endl;
			cout << "Desc: " << data.description << endl;

			for (auto item : data.formula)
			{
				cout << "Atom ID: " << item.atomId << "  ";
				cout << "Quantity: " << item.quantity << endl;
			}
			cout << "#########################" << endl;
		}
	}

	return true;
}

