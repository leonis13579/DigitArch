// Fill out your copyright notice in the Description page of Project Settings.

#include "DigitArchCore.h"


UDigitArchCore::UDigitArchCore()
{

}

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

void UDigitArchCore::SetPoint(TArray<FPointVariable> Points)
{
	if (DigitThread && Thread) {
		
		DigitThread->point_variables = Points;
		DigitThread->bPositionActive = true;
	}
}