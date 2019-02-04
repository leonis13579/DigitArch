// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Runnable.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "DigitArchThread.generated.h"

UENUM(BlueprintType)
enum class PointMode : uint8
{
	One,
	Two
};

USTRUCT(BlueprintType)
struct DIGITARCH_API FPointInfo
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadOnly)
		int32 Frame;

	UPROPERTY(BlueprintReadOnly)
		FVector Position;
};

USTRUCT(BlueprintType)
struct DIGITARCH_API FPoints
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FPointInfo> PointPosition;
};

class DIGITARCH_API DigitArchThread : public FRunnable
{
public:
	DigitArchThread();
	~DigitArchThread();

	void SetPoint();
	void GetJson(PointMode point, FString& json_string);

	bool bPositionActive = false;
	FVector point;

private:

	uint32 Run() override;
	void Exit() override;
	void Stop() override;

	int32 point_frame = 0;
	TMap<PointMode, FPoints> Point;


	bool working = true;

};
