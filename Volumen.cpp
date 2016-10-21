#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Volumen.h"
#include "Plane.h"

#pragma warning(disable : 4996)

Volumen::Volumen()
{

}
Volumen::Volumen(const char* FileName, int xSize,int ySize,int zSize,unsigned int Bits)
{
	m_FileName = FileName;
	m_XSize = xSize;
	m_YSize = ySize;
	m_ZSize = zSize;
	m_Bits = Bits;
	m_DistX = 1.0;
	m_DistY = 1.0;
	m_DistZ = 1.0;
	m_Object = NULL;
	m_StartPos = Vector3D(0.0,0.0,0.0);
	m_Edge1 = m_StartPos;
	m_Edge2 = m_StartPos + Vector3D(m_DistX*m_XSize,0,0);
	m_Edge3 = m_StartPos + Vector3D(0,m_DistY*m_YSize,0);
	m_Edge4 = m_StartPos + Vector3D(0,0,m_DistZ*m_ZSize);
	m_Edge5 = m_StartPos + Vector3D(m_DistX*m_XSize,m_DistY*m_YSize,0);
	m_Edge6 = m_StartPos + Vector3D(m_DistX*m_XSize,0,m_DistZ*m_ZSize);
	m_Edge7 = m_StartPos + Vector3D(0,m_DistY*m_YSize,m_DistZ*m_ZSize);
	m_Edge8 = m_StartPos + Vector3D(m_DistX*m_XSize,m_DistY*m_YSize,m_DistZ*m_ZSize);
	m_Plane1 = Plane(m_Edge1,m_Edge2,m_Edge3);
	m_Plane2 = Plane(m_Edge1,m_Edge2,m_Edge4);
	m_Plane3 = Plane(m_Edge1,m_Edge3,m_Edge4);
	m_Plane4 = Plane(m_Edge8,m_Edge5,m_Edge7);
	m_Plane5 = Plane(m_Edge8,m_Edge5,m_Edge6);
	m_Plane6 = Plane(m_Edge8,m_Edge7,m_Edge6);
}

bool Volumen::Init()
{
	size_t items = m_XSize*m_YSize*m_ZSize;
	m_Object = new char[items];
	FILE* f = fopen(m_FileName,"rb");
	if(f!=NULL)
	{
		size_t rd = fread(m_Object,1,items,f);
		fclose(f);
		if(rd==items)
		{
			return true;
		}
	}
	return false;
}

int Volumen::GetVolumeVal(Vector3D vec)
{
   double x = vec.getX() / m_DistX;
   double y = vec.getY() / m_DistY;
   double z = vec.getZ() / m_DistZ;
   int val = GetVolumeVal((int)x,(int)y,(int)z);
   return (val<0) ? 0 : val;
}

int Volumen::GetVolumeVal(int x,int y,int z)
{
	if(x<m_XSize&&y<m_YSize&&z<m_ZSize)
	{
		int Pos = m_XSize*m_YSize*z + m_XSize*y + x;
		return m_Object[Pos];
	}
	else
	{
		return -1;
	}
}
Vector3D Volumen::GetVolumeVecPos(int x,int y,int z)
{
	Vector3D ret;
	if(x<m_XSize&&y<m_YSize&&z<m_ZSize)
	{
		ret = Vector3D(	x*m_DistX+m_StartPos.getX(),
						y*m_DistY+m_StartPos.getY(),
						z*m_DistZ+m_StartPos.getZ());
	}
	return ret;
}

bool Volumen::IsInsideVolume(Vector3D Origin,Vector3D ActPnt,Vector3D RaySchnitt1,Vector3D RaySchnitt2)
{
   double distOrigSn1 = (RaySchnitt1 - Origin).length();
   double distOrigSn2 = (RaySchnitt2 - Origin).length();
   double distOrigPnt = (ActPnt      - Origin).length();

   if((distOrigSn1<distOrigSn2 && distOrigPnt <= distOrigSn2 && distOrigPnt >= distOrigSn2) ||
      (distOrigSn1>distOrigSn2 && distOrigPnt >= distOrigSn2 && distOrigPnt <= distOrigSn2) )
      return true;

	return false;	
}

bool Volumen::InsideRect(Plane pl,Vector3D CrossVec)
{
   Vector3D otherPnt = pl.getSpann1() + pl.getSpann2() + pl.getStuetz();
   double x0 = CrossVec.getX();
   double y0 = CrossVec.getY();
   double z0 = CrossVec.getZ();
   double x1 = pl.getStuetz().getX();
   double y1 = pl.getStuetz().getY();
   double z1 = pl.getStuetz().getZ();
   double x2 = otherPnt.getX();
   double y2 = otherPnt.getY();
   double z2 = otherPnt.getZ();

   if((x1<=x2 && x0<=x2 && x0>=x1) || (x1>x2 && x0<=x1 && x0>=x2))
   {
      if((y1<=y2 && y0<=y2 && y0>=y1) || (y1>y2 && y0<=y1 && y0>=y2))
      {
         if((z1<=z2 && z0<=z2 && z0>=z1) || (z1>z2 && z0<=z1 && z0>=z2))
         {
            return true;
         }
      }
   }
   return false;
}
bool Volumen::IntersectVolumen(Vector3D Origin, Vector3D dir, Vector3D &RaySchnitt1, Vector3D &RaySchnitt2)
{
   bool b_cr1 = false;
   bool b_cr2 = false;

   if(m_Plane1.IntersectRay(Origin,dir)) 
   {
      Vector3D vec = m_Plane1.GetIntersectPnt(Origin,dir);
      if(InsideRect(m_Plane1,vec))
      {
         if(!b_cr1)
         {
            RaySchnitt1=vec;
            b_cr1=true;
         }
         else
         {
            RaySchnitt2=vec;
            b_cr2=true;
         }
      }
   }
	if(m_Plane2.IntersectRay(Origin,dir))
   {
      Vector3D vec = m_Plane2.GetIntersectPnt(Origin,dir);
      if(InsideRect(m_Plane2,vec))
      {
         if(!b_cr1)
         {
            RaySchnitt1=vec;
            b_cr1=true;
         }
         else
         {
            RaySchnitt2=vec;
            b_cr2=true;
         }
      }
   }
	if(m_Plane3.IntersectRay(Origin,dir))
   {
      Vector3D vec = m_Plane3.GetIntersectPnt(Origin,dir);
      if(InsideRect(m_Plane3,vec))
      {
         if(!b_cr1)
         {
            RaySchnitt1=vec;
            b_cr1=true;
         }
         else
         {
            RaySchnitt2=vec;
            b_cr2=true;
         }
      }
   }
	if(m_Plane4.IntersectRay(Origin,dir))
   {
      Vector3D vec = m_Plane4.GetIntersectPnt(Origin,dir);
      if(InsideRect(m_Plane4,vec))
      {
         if(!b_cr1)
         {
            RaySchnitt1=vec;
            b_cr1=true;
         }
         else
         {
            RaySchnitt2=vec;
            b_cr2=true;
         }
      }
   }
	if(m_Plane5.IntersectRay(Origin,dir))
   {
      Vector3D vec = m_Plane5.GetIntersectPnt(Origin,dir);
      if(InsideRect(m_Plane5,vec))
      {
         if(!b_cr1)
         {
            RaySchnitt1=vec;
            b_cr1=true;
         }
         else
         {
            RaySchnitt2=vec;
            b_cr2=true;
         }
      }
   }
	if(m_Plane6.IntersectRay(Origin,dir)) 
   {
      Vector3D vec = m_Plane6.GetIntersectPnt(Origin,dir);
      if(InsideRect(m_Plane6,vec))
      {
         if(!b_cr1)
         {
            RaySchnitt1=vec;
            b_cr1=true;
         }
         else
         {
            RaySchnitt2=vec;
            b_cr2=true;
         }
      }
   }

   return b_cr1 && b_cr2;
}

Volumen::~Volumen(void)
{
	if(m_Object!=NULL)
   {
      delete m_Object;
      m_Object = NULL;
   }
}
