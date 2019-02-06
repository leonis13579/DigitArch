// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Runtime/Core/Public/HAL/Runnable.h"
#include "DigitArchType.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

DECLARE_LOG_CATEGORY_EXTERN(DigitThread, Log, All);

class DIGITARCH_API DigitArchThread : public FRunnable
{
public:

	DigitArchThread(CameraType camera_type);

	// Write data to struct
	void WriteDataPoint();

	// Convert data to Json
	void GetJson(FString& json_string);

	// Start function SetPoint
	bool bPositionActive = false;

	// Source data
	TArray<FPointVariable> point_variables;

	bool Log;

private:

	uint32 Run() override;
	void Exit() override;
	void Stop() override;

	// Frame
	int32 point_frame = 1;

	// Struct data
	FPoints Points;

	// Start Thread
	bool working = true;

	const FString ProjectDir = FPaths::ProjectDir() / "Log";
	const FString fileName = "points.json";
};
