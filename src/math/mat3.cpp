#include "mat3.h"


mat3::mat3()
	: mat3(1.0)
{}

mat3::mat3(float s)
{
	for(int i=0; i<9; i++)
	{
		if(i / 3 == i % 3)
			m_Data[i] = s;
		else
			m_Data[i] = 0.0;
	}
}

mat3::mat3(const mat3& c)
{
	for(int i=0; i<9; i++)
		m_Data[i] = c.m_Data[i];
}
