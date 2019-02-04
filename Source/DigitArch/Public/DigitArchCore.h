// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RunnableThread.h"
#include "DigitArchThread.h"
#include "DigitArchCore.generated.h"



UCLASS(Blueprintable, BlueprintType)
class DIGITARCH_API UDigitArchCore : public UObject
{
	GENERATED_BODY()

public:

	UDigitArchCore();
	~UDigitArchCore();

	UFUNCTION(BlueprintPure, meta = (HidePin = "owner", DefaultToSelf = "owner"))
	static UDigitArchCore* CreateDigitArchCore(UObject* owner);

	UFUNCTION(BlueprintCallable)
	void SetPoint(PointMode point, FVector position);

	//UFUNCTION(BlueprintPure)
	//	void GetJson(PointMode point, FString& json_string);

private:

	FVector* test;

	DigitArchThread* DigitThread;
	FRunnableThread* Thread;
};
