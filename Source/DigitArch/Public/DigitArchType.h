#pragma once

#include "CoreMinimal.h"
#include "DigitArchType.generated.h"

UENUM(BlueprintType)
enum class PointType : uint8
{
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Eleven,
	Twelve,
	Thirteen,
	Fourteen,
	Fifteen,
	Sixteen
};

UENUM(BlueprintType)
enum class CameraType : uint8
{
	Kinect,
	OptiTrack,
	Vive 
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
struct DIGITARCH_API FPointParam
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadOnly)
		PointType Type;

	UPROPERTY(BlueprintReadOnly)
		TArray<FPointInfo> PointInfo;
};

USTRUCT(BlueprintType)
struct DIGITARCH_API FCameraDigit
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadOnly)
		int32 CameraAt;

	UPROPERTY(BlueprintReadOnly)
		TArray<FPointParam> Data;
};

USTRUCT(BlueprintType)
struct DIGITARCH_API FPoints
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		CameraType DeviceType;

	UPROPERTY(BlueprintReadOnly)
		TArray<FCameraDigit> DeviceData;
};

USTRUCT(BlueprintType)
struct DIGITARCH_API FPointVariable
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		int32 CameraAt;
		UPROPERTY(BlueprintReadWrite)
		PointType Type;
	UPROPERTY(BlueprintReadWrite)
		FVector Position;
};
