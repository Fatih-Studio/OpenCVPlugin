	#pragma once
	
	#include "PreOpenCVLib.h"
	#include <opencv2/opencv.hpp>
	#include <opencv2/aruco.hpp>
	#include <opencv2/objdetect/aruco_dictionary.hpp>
	#include <opencv2/core/cuda.hpp>
	#include <opencv2/cudaimgproc.hpp>
	#include <opencv2/cudaarithm.hpp>
	#include <opencv2/cudawarping.hpp>
	#include "PostOpenCVLib.h"
	
	#include "OpenCVCamera.h"
	
	#include "Kismet/BlueprintFunctionLibrary.h"
	#include "OpenCVBlueprintLibrary.generated.h"
	
	UCLASS()
	class OPENCVPLUGIN_API UOpenCVBlueprintLibrary : public UBlueprintFunctionLibrary
	{
		GENERATED_BODY()
	
	public:
	
		UFUNCTION(BlueprintCallable, Category = "OpenCV")
		static UOpenCVCamera* OpenCamera(int32 CameraID);
		
		UFUNCTION(BlueprintCallable, Category = "OpenCV")
		static void CloseCamera(UOpenCVCamera* Camera);
		
		UFUNCTION(BlueprintCallable, Category = "OpenCV")
		static void DetectArucoMarkers(UOpenCVCamera* Camera, EOpenCVArucoDict Dictionary, EOpenCVArucoDictSize Size, TArray<int32>& MarkerIds, bool& bDetected);
		
	private:
		static cv::aruco::PredefinedDictionaryType GetArucoDictionary(EOpenCVArucoDict Dictionary, EOpenCVArucoDictSize Size);
		
		cv::Mat ExtractCandidateCUDA(const cv::cuda::GpuMat& GPUFrame, int32 Index);
		
		bool DetectOnAllCandidate(const cv::Mat& GPUFrame);
		
	public:
	
		
	private:
	
		
		
	};