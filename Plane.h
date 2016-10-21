#include "Vector3D.h"

#ifndef PLANE_H
#define PLANE_H

class Plane {
protected:
	Vector3D	m_normale;
   Vector3D m_Stuetz;
   Vector3D m_Spann1;
   Vector3D m_Spann2;
	double	m_dist;
public:
   Plane();
	Plane(Vector3D Start,Vector3D v1,Vector3D v2);
   Plane &operator=(const Plane &pl);
   bool IntersectRay(Vector3D StartP, Vector3D LineDir);
   Vector3D GetIntersectPnt(Vector3D StartP, Vector3D LineDir);
	double getA();
	double getB();
	double getC();
	double getD();
   Vector3D getNormale();
   Vector3D getStuetz();
   Vector3D getSpann1();
   Vector3D getSpann2();
};

#endif

