#include "CustomMapInsert.h"

CustomMapInsert::CustomMapInsert(Play::Vector2D vec, bool value)
{
	m_Vec = vec;
	m_Value = value;
}

CustomMapInsert::CustomMapInsert(int x, int y, bool value)
{
	m_Vec = Play::Vector2D(x, y);
	m_Value = value;
}

bool CustomMapInsert::IsEqual(int x, int y)
{
	return m_Vec.x == x && m_Vec.y == y;
}

void CustomMapInsert::SetValue(bool value)
{
	m_Value = value;
}
