#include "OpenCVCamera.h"
#include "Async/Async.h"

void UOpenCVCamera::BeginDestroy()
{
	Super::BeginDestroy();
}

void UOpenCVCamera::FinishDestroy()
{
	if (Wrapper)
	{
		if (Wrapper->Capture.isOpened())
		{
			Wrapper->Capture.release();
		}
		delete Wrapper;
		Wrapper = nullptr;
	}
	
	Super::FinishDestroy();
}
