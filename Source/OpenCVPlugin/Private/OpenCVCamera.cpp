#include "OpenCVCamera.h"

void UOpenCVCamera::BeginDestroy()
{
	if (Capture)
	{
		delete Capture;
		Capture = nullptr;
	}
	
	Super::BeginDestroy();
}
