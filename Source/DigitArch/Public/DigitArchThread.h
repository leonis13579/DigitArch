// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Runnable.h"
#include "DigitArchType.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

DECLARE_LOG_CATEGORY_EXTERN(DigitThread, Log, All);

class DIGITARCH_API DigitArchThread : public FRunnable
{
public:
	DigitArchThread();
	//~DigitArchThread();

	void SetPoint();
	void GetJson(FString& json_string);

	bool bPositionActive = false;
	FVector point;

	TArray<FPointVariable> point_variables;

private:

	uint32 Run() override;
	void Exit() override;
	void Stop() override;

	int32 point_frame = 1;


	FPoints Points;

	bool working = true;

};
