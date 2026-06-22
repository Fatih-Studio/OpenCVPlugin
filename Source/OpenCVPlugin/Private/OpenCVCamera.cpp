#include "OpenCVCamera.h"
#include "Async/Async.h"

void UOpenCVCamera::BeginDestroy()
{
	if (Capture)
	{
		cv::VideoCapture* CapToDestroy = Capture;
		Capture = nullptr;
		
		AsyncTask(ENamedThreads::GameThread, [CapToDestroy]()
		{
			if (CapToDestroy->isOpened())
			{
				CapToDestroy->release();
			}
			delete CapToDestroy;
		});
	}
	
	Super::BeginDestroy();
}
