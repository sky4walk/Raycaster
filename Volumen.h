#include "Vector3D.h"
#include "Plane.h"

#ifndef VOLUMENDEF
#define VOLUMENDEF

class Volumen
{
public:
	Volumen();
	Volumen(const char* FileName, int xSize,int ySize,int zSize,unsigned int Bits);
	Vector3D GetVolumeVecPos(int x,int y,int z);
	bool Init();
   bool IsInsideVolume(Vector3D Origin,Vector3D ActPnt,Vector3D RaySchnitt1,Vector3D RaySchnitt2);
   bool IntersectVolumen(Vector3D Origin, Vector3D dir, Vector3D &RaySchnitt1, Vector3D &RaySchnitt2);
   int GetVolumeVal(Vector3D vec);
	~Volumen(void);
protected:
	int GetVolumeVal(int x,int y,int z);
   bool InsideRect(Plane pl,Vector3D vec);
	const char* m_FileName;
	char* m_Object;
	unsigned int m_Bits;
	int m_XSize;
	int m_YSize;
	int m_ZSize;
	double m_DistX;
	double m_DistY;
	double m_DistZ;
	Vector3D m_StartPos;
	Vector3D m_Edge1;
	Vector3D m_Edge2;
	Vector3D m_Edge3;
	Vector3D m_Edge4;
	Vector3D m_Edge5;
	Vector3D m_Edge6;
	Vector3D m_Edge7;
	Vector3D m_Edge8;
	Plane m_Plane1;
	Plane m_Plane2;
	Plane m_Plane3;
	Plane m_Plane4;
	Plane m_Plane5;
	Plane m_Plane6;
};

#endif