#include "Volumen.h"
#include "Vector3D.h"
#include "Plane.h"

#ifndef RAYSETUPDEF
#define RAYSETUPDEF

class RaySetup
{
public:
	RaySetup(Volumen &vol, Plane ViewPlane, double SampleWgt, int XSize, int YSize);
	void Render();
	bool SavePic(const char* FileName);
	~RaySetup(void);
protected:
	Volumen &m_Vol;
   Plane m_ViewPlane;
	Vector3D m_StepX;
	Vector3D m_StepY;
	int m_XSize;
	int m_YSize;
	char* m_PicBuf;
	double m_SampleWgt;
	Vector3D Cast(Vector3D ActRayPos,Vector3D Dir);
	int SendRay(Vector3D Origin, Vector3D Dir,Vector3D Schnitt1,Vector3D Schnitt2);
};

#endif