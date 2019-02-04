// Fill out your copyright notice in the Description page of Project Settings.

#include "DigitArchCore.h"

#define MAX_FRAME 60

UDigitArchCore::UDigitArchCore()
{
	point_frame = 0;
}

UDigitArchCore* UDigitArchCore::CreateDigitArchCore()
{
	const auto obj = NewObject<UDigitArchCore>();
	return obj;
}

void UDigitArchCore::SetPoint(PointMode point, FVector position)
{
	if (point_frame >= MAX_FRAME)
	{
		GetJson(point, json_string);
		point_frame = 0;

		UE_LOG(LogTemp, Log, TEXT("%s"), *json_string);
	}

	FPointInfo point_info;
	point_info.Position = position;
	point_info.Frame = ++point_frame;

	if (!Point.Contains(point))
	{
		FPoints points;
		points.PointPosition.Add(point_info);
		Point.Add(point, points);

		return;
	}

	Point[point].PointPosition.Add(point_info);
}

void UDigitArchCore::GetJson(PointMode point, FString& json_string)
{
	if (!Point.Contains(point))
		return;

	FJsonObjectConverter::UStructToJsonObjectString(Point[point], json_string);
}

TMap<PointMode, FPoints> UDigitArchCore::GetPoint()
{
	return Point;
}
