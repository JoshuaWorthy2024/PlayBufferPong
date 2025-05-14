#include "CustomMap.h"

bool CustomMap::Add(int x, int y)
{
	// check if already added
	if (DoesExist(x, y))
	{
		return false;
	}
	
	m_Data.push_back(new CustomMapInsert(x, y, false));
	return true;
}

bool CustomMap::Add(int x, int y, bool value)
{
	m_Data.push_back(new CustomMapInsert(x, y, value));
	return true;
}

bool CustomMap::DoesExist(int x, int y)
{
	for (vector<CustomMapInsert*>::iterator it = m_Data.begin(); it != m_Data.end(); it++)
	{
		if ((*it)->IsEqual(x, y))
		{
			return true;
		}
	}
	return false;
}

CustomMapInsert* CustomMap::GetMapInsert(int x, int y)
{
	for (vector<CustomMapInsert*>::iterator it = m_Data.begin(); it != m_Data.end(); it++)
	{
		if ((*it)->IsEqual(x, y))
		{
			return (*it);
		}
	}
	return nullptr;
}

bool CustomMap::Update(int x, int y, bool value)
{
	CustomMapInsert* mapInsert = GetMapInsert(x, y);
	if (mapInsert)
	{
		mapInsert->SetValue(value);
		return true;
	}

	return false;
}

