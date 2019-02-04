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

UDigitArchCore* UDigitArchCore::CreateDigitArchCore(PointMode point)
{
	const auto obj = NewObject<UDigitArchCore>();
	obj->DigitThread = new DigitArchThread(point);
	obj->Thread = FRunnableThread::Create(obj->DigitThread, TEXT("DigitArchThread"));
	return obj;
}

void UDigitArchCore::SetPoint(FVector position)
{
	DigitThread->point = position;

	DigitThread->bPositionActive = true;
}