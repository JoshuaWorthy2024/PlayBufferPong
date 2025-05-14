#pragma once
#include "Play.h"

class CustomMapInsert
{
public:
	CustomMapInsert(Play::Vector2D vec, bool value);
	CustomMapInsert(int x, int y, bool value);

	bool IsEqual(int x, int y);
	void SetValue(bool value);

	const bool GetValue() const { return m_Value; }
private:
	Play::Vector2D m_Vec;
	bool m_Value = false;
	
};

