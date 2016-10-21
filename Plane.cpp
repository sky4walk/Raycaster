#include <math.h>
#include "Plane.h"

Plane &Plane::operator=(const Plane &pl)
{
	m_normale = pl.m_normale;
	m_dist = pl.m_dist;
   m_Stuetz = pl.m_Stuetz;
   m_Spann1 = pl.m_Spann1;
   m_Spann2 = pl.m_Spann2;
	return (*this);
}

Vector3D Plane::getNormale()
{
   return m_normale;
}
double Plane::getA()
{
	return m_normale.getX();
}
double Plane::getB()
{
	return m_normale.getY();
}
double Plane::getC()
{
	return m_normale.getZ();
}
double Plane::getD()
{
	return m_dist;
}
Vector3D Plane::getStuetz()
{
   return m_Stuetz;
}
Vector3D Plane::getSpann1()
{
   return m_Spann1;
}
Vector3D Plane::getSpann2()
{
   return m_Spann2;
}

Plane::Plane(Vector3D Start,Vector3D v1,Vector3D v2) 
{
   m_Stuetz   = Start;
   m_Spann1   = v1 - m_Stuetz;
   m_Spann2   = v2 - m_Stuetz;
   m_normale = m_Spann1.cross(m_Spann2).norm();
   m_dist    = - (m_normale.getX() * m_Stuetz.getX() + 
                  m_normale.getY() * m_Stuetz.getY() + 
                  m_normale.getZ() * m_Stuetz.getZ());
}
Plane::Plane()
{

}
bool Plane::IntersectRay(Vector3D StartP, Vector3D LineDir)
{
   double n =  LineDir.getX() * getA() + 
               LineDir.getY() * getB() + 
               LineDir.getZ() * getC();

   double z =  StartP.getX() * getA() + 
               StartP.getY() * getB() + 
               StartP.getZ() * getC() + getD();

   if(fabs(n) > 0.0001f)
   {
      double s = -z / n;
      if(fabs(s)>0.0001f)
      {
         return true;
      }
   }

   return false;
}

Vector3D Plane::GetIntersectPnt(Vector3D StartP, Vector3D LineDir)
{
   Vector3D IntPnt;

   double n =  LineDir.getX() * getA() + 
               LineDir.getY() * getB() + 
               LineDir.getZ() * getC();

   double z =  StartP.getX() * getA() + 
               StartP.getY() * getB() + 
               StartP.getZ() * getC() + getD();

   if(fabs(n) > 0.0001f)
   {
      double s = -z / n;
      if(fabs(s)>0.0001f)
      {
         IntPnt = StartP + LineDir * s;
      }
   }

   return IntPnt;
}
