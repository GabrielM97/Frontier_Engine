#include "StringHandler.h"


namespace GM
{
	StringHandler::StringHandler()
	{
	}


	vector<string>StringHandler::SplitString(string str, int sizeAlloc, char splitAt)
	{
		vector<string> splitString;
		int id = 0;
		splitString.resize(sizeAlloc);
		for each (auto& var in str)
		{

			if (var == splitAt)
				id++;
			else if (var == '\n' || var == ' ')
			{

			}
			else
				splitString[id] += var;
		}

		for (auto& v : splitString)
		{
			if (v == "")
				splitString.pop_back();
		}

		return splitString;
	}

	StringHandler::~StringHandler()
	{
	}
}

