#include <math.h>
#include "Vector3D.h"

Vector3D::Vector3D(void)
{
	for(int i=0;i<3;i++)
	{
		m_vector[i] = 0.0;
	}
}

Vector3D::Vector3D(const Vector3D &vec)
{
	for(int i=0;i<3;i++)
	{
		m_vector[i] = vec.m_vector[i];
	}
}
Vector3D::Vector3D(double x,double y,double z)
{
	m_vector[0] = x;
	m_vector[1] = y;
	m_vector[2] = z;
}
const double &Vector3D::operator[](int i) const 
{
	return m_vector[i];
}

double &Vector3D::operator[](int i)       
{
	return m_vector[i];
}	

Vector3D &Vector3D::operator=(const Vector3D &vec)
{
	for(int i=0;i<3;i++)
	{
		m_vector[i] = vec.m_vector[i];
	}
	return (*this);
}

Vector3D Vector3D::operator+(const Vector3D &vec) const
{
	Vector3D ret;
	for(int i=0;i<3; i++)
	{
		ret[i] = m_vector[i] + vec.m_vector[i];
	}
	return ret;
}

Vector3D Vector3D::operator-(const Vector3D &vec) const
{
	Vector3D ret;
	for(int i=0;i<3; i++)
	{
		ret[i] = m_vector[i] - vec.m_vector[i];
	}
	return ret;
}

Vector3D &Vector3D::operator+=(const Vector3D &vec)
{
	for(int i=0;i<3; i++)
	{
		m_vector[i] += vec.m_vector[i];
	}
	return (*this);
}

Vector3D &Vector3D::operator-=(const Vector3D &vec)
{
	for(int i=0;i<3; i++)
	{
		m_vector[i] -= vec.m_vector[i];
	}
	return (*this);
}

Vector3D Vector3D::operator*(double x) const
{
	Vector3D ret;
	for(int i=0;i<3;i++)
	{
		ret[i] = m_vector[i]*x;
	}
	return ret;
}

Vector3D Vector3D::operator/(double x) const
{
	Vector3D ret;
	for( int i=0; i<3; i++ )
	{
		ret[i] = m_vector[i]/x;
	}
	return ret;
}

double Vector3D::length(void) const
{
	double l = 0.0;
	for(int i=0;i<3;i++)
	{
		l += m_vector[i] * m_vector[i];
	}
	return sqrt(l);
}

Vector3D Vector3D::norm(void) const
{
	return (*this) / length();
}

Vector3D Vector3D::cross(const Vector3D &vec ) const
{
	Vector3D ret;
	ret = Vector3D(	m_vector[1]*vec.m_vector[2] - m_vector[2]*vec.m_vector[1],
					m_vector[2]*vec.m_vector[0] - m_vector[0]*vec.m_vector[2],
					m_vector[0]*vec.m_vector[1] - m_vector[1]*vec.m_vector[0] );
	return ret;
}

double Vector3D::dot(const Vector3D &vec) const
{
	double ret = 0.0;
	for(int i=0;i<3;i++)
	{
		ret += m_vector[i] * vec.m_vector[i];
	}
	return ret;
}

double Vector3D::getX()
{
	return m_vector[0];
}
double Vector3D::getY()
{
	return m_vector[1];
}

double Vector3D::getZ()
{
	return m_vector[2];
}

Vector3D::~Vector3D(void)
{
}
