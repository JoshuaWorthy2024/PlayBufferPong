#include "HealthTrack.h"

HealthTrack::HealthTrack(int total)
{
	m_Total = total;
	m_Current = total;
}

void HealthTrack::Heal(int amount)
{
	if (m_Current + amount > m_Total)
	{
		m_Current = m_Total;
	}
	else
	{
		m_Current += amount;
	}
}

void HealthTrack::Hurt(int amount)
{
	if (m_Current - amount < 0)
	{
		m_Current = 0;
	}
	else
	{
		m_Current -= amount;
	}
}

void HealthTrack::Reset()
{
	m_Current = m_Total;
}
