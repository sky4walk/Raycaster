// RayCaster.cpp : Defines the entry point for the console application.
#include "Volumen.h"
#include "RaySetup.h"

int main(int argc, char* argv[])
{
	Volumen Kugel("HohlKugel-64x64x64-8.raw",64,64,64,8);
   Plane ViewPlane(Vector3D(0,128,-128),Vector3D(128,128,-128),Vector3D(0,0,-128));

   Kugel.Init();

	RaySetup RayOne(Kugel,ViewPlane,.5,128,128);
   RayOne.Render();

	return 0;
}

