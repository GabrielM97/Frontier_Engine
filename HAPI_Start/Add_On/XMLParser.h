#pragma once
#include <HAPI_lib.h>
#include <iostream>

using namespace HAPISPACE;
using namespace std;


namespace GM
{
	class XMLParser
	{
	public:
		XMLParser() = default;

		XMLParser(std::string path);
		~XMLParser();

		template <class  T>
		T GetDataFromFile(std::string node, std::string attrib = "")
		{

			std::vector<CHapiXMLNode*> nodes;
			nodes = xmlFile.GetAllNodesWithName(node);

			if (attrib != "")
			{
				for (auto &n : nodes)
				{

					CHapiXMLAttribute attribute;
					if (!n->GetAttributeWithName(attrib, attribute))
						return (T)NULL;

					return (T&)attribute.AsString();
				}
			}
			return (T&)nodes;
		}


	private:
		CHapiXML xmlFile;





	};

}

