#pragma once
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

namespace Data
{

	typedef struct MolecularFormulaItem
	{
		string atomId;
		int quantity;
	} MolecularFormulaItem;

	typedef struct MoleculeData
	{
		string id;
		string name;
		string description;
		vector<MolecularFormulaItem> formula;
		int totalAtomsCount;
	} MoleculeData;

	class MoleculeDAO
	{
		public:
			static unordered_map<string, MoleculeData> moleculeDataRepository;

			MoleculeData getById(string id);
			static bool loadData();
	};

}
