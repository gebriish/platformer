#pragma once

struct mat3
{
public:
	mat3();
	mat3(float scalar);
	mat3(const mat3& c);

	mat3& operator=(const mat3& other) {
		if(this != &other)
			for(int i=0; i<9; i++)
				m_Data[i] = other.m_Data[i];
		return *this;
	}

	mat3 operator+(const mat3& other) const {
		mat3 result;
		for(int i=0; i<9; i++)
			result.m_Data[i] = m_Data[i] + other.m_Data[i];
		return result;
	}

	mat3 operator-(const mat3& other) const {
		mat3 result;
		for(int i=0; i<9; i++)
			result.m_Data[i] = m_Data[i] - other.m_Data[i];
		return result;
	}

	mat3& operator+=(const mat3& other) 
	{
		for(int i=0; i<9; i++)
			m_Data[i] += other.m_Data[i];
		return *this;
	}

	mat3& operator-=(const mat3& other) 
	{
		for(int i=0; i<9; i++)
			m_Data[i] -= other.m_Data[i];
		return *this;
	}

	mat3 operator*(float scalar) const {
        mat3 result(*this);
		result.m_Data[0] *= scalar;
		result.m_Data[4] *= scalar;
		result.m_Data[8] *= scalar;
		return result;
    }

    mat3& operator*=(float scalar) {
        m_Data[0] *= scalar;
		m_Data[4] *= scalar;
		m_Data[8] *= scalar;
		return *this;
    }

	bool operator==(const mat3& other) const {
        for(int i=0; i<9; i++)
			if(m_Data[i] != other.m_Data[i])
				return false;
	
		return true;
    }

	bool operator!=(const mat3& other) const {
        return !(*this == other);
    }

    mat3 operator-() const {
		mat3 result(*this);
		for(int i=0; i<9; i++)
			if(i / 3 == i % 3)
				result.m_Data[i] *= -1;
		return result;
    }

private:
	float m_Data[9];	// column-major order
};