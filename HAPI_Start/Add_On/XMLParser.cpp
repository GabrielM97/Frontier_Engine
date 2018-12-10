#include "XMLParser.h"

namespace GM
{
	XMLParser::XMLParser(std::string path) : xmlFile(path)
	{
		if (xmlFile.GetRootNode() == nullptr)
		{
			std::cerr << "Error, could not load XML file!" << std::endl;
			return;
		}
	}

	XMLParser::~XMLParser()
	{
	}
}




