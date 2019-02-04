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

UDigitArchCore* UDigitArchCore::CreateDigitArchCore(UObject* owner)
{
	const auto obj = NewObject<UDigitArchCore>();
	obj->DigitThread = new DigitArchThread();
	obj->Thread = FRunnableThread::Create(obj->DigitThread, TEXT("DigitArchThread"));
	return obj;
}

void UDigitArchCore::SetPoint(PointMode point, FVector position)
{
	DigitThread->point = position;

	DigitThread->bPositionActive = true;
}
//
//void UDigitArchCore::GetJson(PointMode point, FString& json_string)
//{
//	DigitThread->GetJson(point, json_string);
//}
