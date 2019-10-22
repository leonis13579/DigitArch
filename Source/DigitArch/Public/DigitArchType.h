#pragma once

#include "CoreMinimal.h"
#include "DigitArchType.generated.h"

UENUM(BlueprintType)
enum class PointType : uint8
{
	RightWrist,
	RightElbow,
	RightShoulder,
	Head,
	LeftWrist,
	LeftElbow,
	LeftShoulder,
	CenterOfShoulders,
	Spine,
	CenterOfHip,
	RightHip,
	RightKnee,
	RightAnkle,
	LeftHip,
	LeftKnee,
	LeftAnkle
};

UENUM(BlueprintType)
enum class CameraType : uint8
{
	Kinect,
	OptiTrack,
	Vive,
	PerceptionNeuron
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
		FString CameraAt;

	UPROPERTY(BlueprintReadOnly)
		TArray<FPointParam> CameraData;
};

USTRUCT(BlueprintType)
struct DIGITARCH_API FPoints
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		CameraType DeviceType;

	UPROPERTY(BlueprintReadOnly)
		TArray<FCameraDigit> DeviceData;

	bool Contains(CameraType device);
};

USTRUCT(BlueprintType)
struct DIGITARCH_API FArrayPoints {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		TArray<FPoints> Points;

	bool CheckIn(FPoints points) {
		for (int32 i = 0; i < Points.Num(); i++) {
			if (Points[i].DeviceType == points.DeviceType) {
				return true;
			}
		}
		return false;
	};
};

USTRUCT(BlueprintType)
struct DIGITARCH_API FPointVariable
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		CameraType DeviceType;
		UPROPERTY(BlueprintReadWrite)
		FString CameraAt;
		UPROPERTY(BlueprintReadWrite)
		PointType Type;
		UPROPERTY(BlueprintReadWrite)
		FVector Position;
};
