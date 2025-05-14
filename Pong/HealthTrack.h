#pragma once
class HealthTrack
{
public:
	HealthTrack(int total);

	void Heal(int amount);
	void Hurt(int amount);
	void Reset();
	const int GetCurrent() const
	{
		return m_Current;
	}

	const int GetTotal() const
	{
		return m_Total;
	}
private:
	int m_Total;
	int m_Current;
};

