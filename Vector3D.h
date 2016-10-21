#ifndef VECTOR3DDEF
#define VECTOR3DDEF

class Vector3D
{
public:
	Vector3D(void);
	Vector3D(const Vector3D &vec);
	Vector3D(double x,double y,double z);
	const double &operator[](int i) const;
	double &operator[](int i);
	Vector3D &operator=(const Vector3D &vec);
	Vector3D operator+(const Vector3D &vec) const;
	Vector3D operator-(const Vector3D &vec) const;
	Vector3D &operator+=(const Vector3D &vec);
	Vector3D &operator-=(const Vector3D &vec);
	Vector3D operator*(double x) const;
	Vector3D operator/(double x) const;
	double length(void) const;
	Vector3D norm(void) const;
	double dot(const Vector3D &vec) const;
	Vector3D cross(const Vector3D &vec ) const;
	double getX();
	double getY();
	double getZ();
	~Vector3D(void);
protected:
	double m_vector[3];
};

#endif
