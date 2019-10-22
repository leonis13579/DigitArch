// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"
#include "DigitArchType.h"
#include "DigitArchThread.h"
#include "DigitArchCore.generated.h"


UCLASS(Blueprintable, BlueprintType)
class DIGITARCH_API UDigitArchCore : public UObject
{
	GENERATED_BODY()

public:

	~UDigitArchCore();

	//Create class
	UFUNCTION(BlueprintPure)
	static UDigitArchCore* CreateDigitArchCore();

	// Set data from point
	UFUNCTION(BlueprintCallable)
	void SetPoint(TArray<FPointVariable> Points, FString file_name, bool send_to_server, bool log_to_file);

	UFUNCTION(BlueprintCallable)
	void NextFrame();

private:

	//Class is thread
	DigitArchThread* DigitThread;

	//Thread function
	FRunnableThread* Thread;
};
