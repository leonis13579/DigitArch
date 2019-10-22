// Fill out your copyright notice in the Description page of Project Settings.

#include "DigitArchCore.h"

UDigitArchCore::~UDigitArchCore()
{
	if (Thread != nullptr) {
		Thread->Kill();
		Thread->WaitForCompletion();
	}
}

UDigitArchCore* UDigitArchCore::CreateDigitArchCore()
{
	const auto obj = NewObject<UDigitArchCore>();
	obj->DigitThread = new DigitArchThread();
	obj->Thread = FRunnableThread::Create(obj->DigitThread, TEXT("DigitArchThread"));
	return obj;
}

void UDigitArchCore::SetPoint(TArray<FPointVariable> Points, FString file_name, bool send_to_server, bool log_to_file)
{
	if (DigitThread && Thread) {
		
		DigitThread->point_variables = Points;
		DigitThread->bPositionActive = true;
		DigitThread->FileName = file_name;
		DigitThread->Log = log_to_file;
		DigitThread->Send = send_to_server;
	}
}

void UDigitArchCore::NextFrame() {
	if (!DigitThread->GoNextFrame) {
		DigitThread->GoNextFrame = true;
	}
}