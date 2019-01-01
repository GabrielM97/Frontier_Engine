#pragma once
#include<iostream>
#include <vector>

using namespace std;


namespace GM
{
	class StringHandler
	{
	public:
		StringHandler();
		~StringHandler();

		vector<string> SplitString(string str, int sizeAlloc, char splitAt = ' ');


	};
}


