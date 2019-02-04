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

	UFUNCTION(BlueprintPure)
	static UDigitArchCore* CreateDigitArchCore(PointMode point);

	UFUNCTION(BlueprintCallable)
	void SetPoint(FVector position);

	//UFUNCTION(BlueprintPure)
	//	void GetJson(PointMode point, FString& json_string);

private:

	DigitArchThread* DigitThread;
	FRunnableThread* Thread;
};
