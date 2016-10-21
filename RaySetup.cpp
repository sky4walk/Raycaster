#include <stdio.h>
#include <windows.h>
#include "RaySetup.h"

#pragma warning(disable : 4996)

RaySetup::RaySetup(Volumen& vol, Plane ViewPlane, double SampleWgt, int XSize, int YSize)
: m_Vol ( vol )
{
	m_XSize = XSize;
	m_YSize = YSize;
   m_ViewPlane = ViewPlane;
	m_SampleWgt = SampleWgt;
	m_PicBuf = new char[m_XSize*m_YSize];
}

void RaySetup::Render()
{
	Vector3D actPosY;
   Vector3D PlaneDirXStep  = m_ViewPlane.getSpann1() / m_XSize;
   Vector3D PlaneDirYStep  = m_ViewPlane.getSpann2() / m_YSize;
   Vector3D CastLen        = m_ViewPlane.getNormale() * m_SampleWgt;

	for(int y=0;y<m_YSize;y++)
	{
      Vector3D actPosX;
		for(int x=0;x<m_XSize;x++)
		{
         Vector3D actPos = m_ViewPlane.getStuetz()+actPosX+actPosY;
         Vector3D Schnitt1;
         Vector3D Schnitt2;
         if(m_Vol.IntersectVolumen(actPos,CastLen,Schnitt1,Schnitt2))
         {
			   int Sum = SendRay(actPos,CastLen,Schnitt1,Schnitt2);
            if(Sum>0)
            {
               Sum = 0;
            }
         }
         else
         {
            m_PicBuf[m_XSize*y+x] = 0;
         }
			actPosX += PlaneDirXStep;
		}
		actPosY += PlaneDirYStep;
	}
}

int RaySetup::SendRay(Vector3D Origin, Vector3D CastLen,Vector3D Schnitt1,Vector3D Schnitt2)
{
   int RayState = 0;
   int RaySum = 0;
   Vector3D ActPos = Origin;
   while(RayState<2)
   {
      if(m_Vol.IsInsideVolume(Origin,ActPos,Schnitt1,Schnitt2))
      {
         int val = m_Vol.GetVolumeVal(ActPos);
         RaySum += val;
         if(RayState==0)
            RayState=1;
      }
      else
      {
         if(RayState==1)
            RayState=2;
      }
      ActPos += CastLen;
   }
   return RaySum;
}

Vector3D RaySetup::Cast(Vector3D ActRayPos,Vector3D Dir)
{
	return ActRayPos + Dir;
}

bool RaySetup::SavePic(const char* FileName)
{
	FILE* f_h = fopen(FileName,"wb");
	if(f_h!=NULL)
	{
		BITMAPINFOHEADER infoheader;
		infoheader.biSize=sizeof(infoheader);
		infoheader.biWidth=m_XSize;
		infoheader.biHeight=m_YSize;
		infoheader.biPlanes=1;
		infoheader.biBitCount=32;
		infoheader.biCompression=0;
		infoheader.biSizeImage=0; 
		infoheader.biXPelsPerMeter=0;
		infoheader.biYPelsPerMeter=0;
		infoheader.biClrUsed=0; 
		infoheader.biClrImportant=0; 

		int size = infoheader.biWidth*infoheader.biHeight*infoheader.biBitCount/8;

		BITMAPFILEHEADER fileheader;
		fileheader.bfType=19778;
		fileheader.bfSize=size+sizeof(infoheader)+sizeof(fileheader);
		fileheader.bfReserved1=0;
		fileheader.bfReserved2=0;
		fileheader.bfOffBits=(DWORD)(sizeof(fileheader)+sizeof(infoheader));

		int sz = (int)fwrite(&fileheader,1,sizeof(fileheader),f_h);
		if(sz!=sizeof(fileheader))
		{
		}
		sz = (int)fwrite(&infoheader,1,sizeof(infoheader),f_h);
		if(sz!=sizeof(infoheader))
		{
		}
		sz = (int)fwrite(m_PicBuf,1,size,f_h);
		if(sz!=size)
		{
		}

		fflush(f_h);
		fclose(f_h);
	}
	else
		return false;
	return true;
}

RaySetup::~RaySetup(void)
{
   if(m_PicBuf!=NULL)
   {
	   delete m_PicBuf;
      m_PicBuf = NULL;
   }
}
