// Fill out your copyright notice in the Description page of Project Settings.

#include "DigitArchCore.h"

UDigitArchCore::~UDigitArchCore()
{
	if (Thread != nullptr) {
		Thread->Kill();
		Thread->WaitForCompletion();
	}
}

UDigitArchCore* UDigitArchCore::CreateDigitArchCore(CameraType camera_type)
{
	const auto obj = NewObject<UDigitArchCore>();
	obj->DigitThread = new DigitArchThread(camera_type);
	obj->Thread = FRunnableThread::Create(obj->DigitThread, TEXT("DigitArchThread"));
	return obj;
}

void UDigitArchCore::SetPoint(TArray<FPointVariable> Points, bool log_to_file)
{
	if (DigitThread && Thread) {
		
		DigitThread->point_variables = Points;
		DigitThread->bPositionActive = true;
		DigitThread->Log = log_to_file;
	}
}