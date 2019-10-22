// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Runtime/Core/Public/HAL/Runnable.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "DigitArchType.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

DECLARE_LOG_CATEGORY_EXTERN(DigitThread, Log, All);

class DIGITARCH_API DigitArchThread : public FRunnable
{
public:

	DigitArchThread();

	// Write data to struct
	void WriteDataPoint();

	// Convert data to Json
	void GetJson(FString& json_string);

	// Start function SetPoint
	bool bPositionActive = false;

	// Source data
	TArray<FPointVariable> point_variables;

	FString GetURI();

	bool Log;
	bool Send;
	bool GoNextFrame;

	FString FileName;

private:

	uint32 Run() override;
	void Exit() override;
	void Stop() override;

	// Frame
	int32 point_frame = 1;

	//File
	int32 file_count = 0;

	// Struct data
	FArrayPoints PointsArray;

	// Start Thread
	bool working = true;

	const FString ProjectDir = FPaths::ProjectDir() / "Log";
	const FString fileName = "points";
	const FString fileFormat = ".json";

	int32 file_part = 1;
};
