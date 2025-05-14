#pragma once
#include "vector"
#include "CustomMapInsert.h"

using std::vector;

class CustomMap
{
public:
	bool Add(int x, int y);
	bool Add(int x, int y, bool value);
	bool DoesExist(int x, int y);
	CustomMapInsert* GetMapInsert(int x, int y);
	bool Update(int x, int y, bool value);
private:
	vector<CustomMapInsert*> m_Data;
};

