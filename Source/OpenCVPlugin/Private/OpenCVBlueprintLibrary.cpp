#include "OpenCVBlueprintLibrary.h"

#include "Kismet/KismetSystemLibrary.h"


UOpenCVCamera* UOpenCVBlueprintLibrary::OpenCamera(int32 CameraID)
{
	UOpenCVCamera* Camera = NewObject<UOpenCVCamera>();
	
	Camera->Capture = new cv::VideoCapture();
	if (Camera->Capture->open(CameraID))
	{
		return Camera;
	}
	delete Camera->Capture;
	Camera->Capture = nullptr;
	return nullptr;
}

void UOpenCVBlueprintLibrary::CloseCamera(UOpenCVCamera* Camera)
{
	if (Camera && Camera->Capture && Camera->Capture->isOpened())
	{
		try
		{
			Camera->Capture->release();
		}
		catch (...)
		{
			UKismetSystemLibrary::PrintString(nullptr, TEXT("Failed to release camera."), true, true, FLinearColor::Red, 2.0f);
		}
	}
}

cv::aruco::PredefinedDictionaryType UOpenCVBlueprintLibrary::GetArucoDictionary(EOpenCVArucoDict Dictionary, EOpenCVArucoDictSize Size)
{
	switch (Dictionary)
	{
	case EOpenCVArucoDict::Dict4x4:
		switch (Size)
		{
			case EOpenCVArucoDictSize::DictSize50:   return cv::aruco::DICT_4X4_50;
			case EOpenCVArucoDictSize::DictSize100:  return cv::aruco::DICT_4X4_100;
			case EOpenCVArucoDictSize::DictSize250:  return cv::aruco::DICT_4X4_250;
			case EOpenCVArucoDictSize::DictSize1000: return cv::aruco::DICT_4X4_1000;
		}
		break;

	case EOpenCVArucoDict::Dict5x5:
		switch (Size)
		{
			case EOpenCVArucoDictSize::DictSize50:   return cv::aruco::DICT_5X5_50;
			case EOpenCVArucoDictSize::DictSize100:  return cv::aruco::DICT_5X5_100;
			case EOpenCVArucoDictSize::DictSize250:  return cv::aruco::DICT_5X5_250;
			case EOpenCVArucoDictSize::DictSize1000: return cv::aruco::DICT_5X5_1000;
		}
		break;
	case EOpenCVArucoDict::Dict6x6:
		switch (Size)
		{
			case EOpenCVArucoDictSize::DictSize50:   return cv::aruco::DICT_6X6_50;
			case EOpenCVArucoDictSize::DictSize100:  return cv::aruco::DICT_6X6_100;
			case EOpenCVArucoDictSize::DictSize250:  return cv::aruco::DICT_6X6_250;
			case EOpenCVArucoDictSize::DictSize1000: return cv::aruco::DICT_6X6_1000;
		}
		break;
	case EOpenCVArucoDict::Dict7x7:
		switch (Size)
		{
			case EOpenCVArucoDictSize::DictSize50:   return cv::aruco::DICT_7X7_50;
			case EOpenCVArucoDictSize::DictSize100:  return cv::aruco::DICT_7X7_100;
			case EOpenCVArucoDictSize::DictSize250:  return cv::aruco::DICT_7X7_250;
			case EOpenCVArucoDictSize::DictSize1000: return cv::aruco::DICT_7X7_1000;
		}
		break;
	}
	return cv::aruco::DICT_4X4_50; // Default
}

void UOpenCVBlueprintLibrary::DetectArucoMarkers(UOpenCVCamera* Camera, EOpenCVArucoDict Dictionary, EOpenCVArucoDictSize Size, TArray<int32>& MarkerIds, bool& bDetected)
{
	MarkerIds.Empty();
	bDetected = false;	
	
	if (!IsValid(Camera))
	{
		UE_LOG(LogTemp, Error, TEXT("Camera UObject is invalid"));
		return;
	}
	
	cv::Mat Frame;
	
	if (!Camera->Capture || !Camera->Capture->read(Frame))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read frame"));
		return;
	}
	
	if (Frame.empty())
	{
		UE_LOG(LogTemp, Error, TEXT("Frame is empty"));
		return;
	}
	
	auto DictionaryType = GetArucoDictionary(Dictionary, Size);
	
	auto ArucoDictionary = cv::aruco::getPredefinedDictionary(DictionaryType);
	
	cv::aruco::ArucoDetector Detector(ArucoDictionary);
	
	auto* DetectedMarkerIds = new std::vector<int>();
	auto* MarkerCorners = new std::vector<std::vector<cv::Point2f>>();

	Detector.detectMarkers(Frame,*MarkerCorners,*DetectedMarkerIds);
	
	if (DetectedMarkerIds->size() > 0)
	{
		for (int Id : *DetectedMarkerIds)
		{
			MarkerIds.Add(Id);
		}
	}
	
	bDetected = MarkerIds.Num() > 0;
}
