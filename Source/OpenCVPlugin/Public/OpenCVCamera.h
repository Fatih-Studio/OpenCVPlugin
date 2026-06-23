#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "PreOpenCVLib.h"
#include <opencv2/opencv.hpp>
#include "PostOpenCVLib.h"

#include "OpenCVCamera.generated.h"

// Dictionary Type
UENUM(BlueprintType)
enum class EOpenCVArucoDict : uint8
{
	Dict4x4      UMETA(DisplayName = "4x4"),
	Dict5x5      UMETA(DisplayName = "5x5"),
	Dict6x6      UMETA(DisplayName = "6x6"),
	Dict7x7      UMETA(DisplayName = "7x7"),
	DictOriginal UMETA(DisplayName = "Original")
};

// Dictionary Size
UENUM(BlueprintType)
enum class EOpenCVArucoDictSize : uint8
{
	DictSize50   UMETA(DisplayName = "50"),
	DictSize100  UMETA(DisplayName = "100"),
	DictSize250  UMETA(DisplayName = "250"),
	DictSize1000 UMETA(DisplayName = "1000")
};


struct FCameraWrapper
{
	cv::VideoCapture Capture;
};

UCLASS(BlueprintType)
class OPENCVPLUGIN_API UOpenCVCamera : public UObject
{
	GENERATED_BODY()

public:

	FCameraWrapper* Wrapper = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "OpenCV")
	class UTexture2D* CameraTexture = nullptr;

	virtual void BeginDestroy() override;
	virtual void FinishDestroy() override;
	
	void InitCameraTexture(int32 Width, int32 Height);
	void UpdateTextureFromMat(const cv::Mat& Image);
};