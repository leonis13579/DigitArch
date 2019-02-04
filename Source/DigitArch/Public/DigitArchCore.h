// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "DigitArchCore.generated.h"

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



UCLASS(Blueprintable, BlueprintType)
class DIGITARCH_API UDigitArchCore : public UObject
{
	GENERATED_BODY()

public:

	UDigitArchCore();

	UFUNCTION(BlueprintPure)
	static UDigitArchCore* CreateDigitArchCore();

	UFUNCTION(BlueprintCallable)
	void SetPoint(PointMode point, FVector position);

	UFUNCTION(BlueprintPure)
		void GetJson(PointMode point, FString& json_string);

	UFUNCTION(BlueprintPure)
	TMap<PointMode, FPoints> GetPoint();

private:
	int32 point_frame;
	TMap<PointMode, FPoints> Point;

	FString json_string;
};
