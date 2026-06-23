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

#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "RenderingThread.h"
#include "RHICommandList.h"
#include "RHIResources.h"

void UOpenCVCamera::InitCameraTexture(int32 Width, int32 Height)
{
	CameraTexture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
	if (!CameraTexture) return;
	
	CameraTexture->MipGenSettings = TMGS_NoMipmaps;
	CameraTexture->NeverStream = true;
	CameraTexture->SRGB = 0;
	CameraTexture->Filter = TF_Bilinear;
	CameraTexture->UpdateResource();
}

void UOpenCVCamera::UpdateTextureFromMat(const cv::Mat& Image)
{
	if (!CameraTexture || Image.empty()) return;

	FTextureResource* TextureResource = CameraTexture->GetResource();
	if (!TextureResource) return;

	const int32 DataSize = Image.cols * Image.rows * 4;
	const int32 Width    = Image.cols;
	const int32 Height   = Image.rows;
	const int32 Pitch    = Image.cols * 4;

	TArray<uint8> PixelData;
	PixelData.SetNumUninitialized(DataSize);
	FMemory::Memcpy(PixelData.GetData(), Image.data, DataSize);

	ENQUEUE_RENDER_COMMAND(UpdateCameraTexture)(
		[TextureResource, PixelData = MoveTemp(PixelData), Width, Height, Pitch]
		(FRHICommandListImmediate& RHICmdList)
		{
			FUpdateTextureRegion2D Region(0, 0, 0, 0, Width, Height);
			RHIUpdateTexture2D(TextureResource->GetTextureRHI(),0,Region,Pitch,PixelData.GetData());
		});
}
