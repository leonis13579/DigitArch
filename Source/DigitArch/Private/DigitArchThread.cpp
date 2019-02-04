// Fill out your copyright notice in the Description page of Project Settings.

#include "DigitArchThread.h"

#define MAX_FRAME 60

DigitArchThread::DigitArchThread(PointMode mode)
{
	Points.TypePoint = mode;
}

void DigitArchThread::SetPoint()
{
	bPositionActive = false;

	if (point_frame >= MAX_FRAME)
	{
		FString json_string;
		GetJson(json_string);
		//UE_LOG(LogTemp, Log, TEXT("%s"), *json_string);

		point_frame = 0;
	}

	FPointInfo point_info;
	point_info.Position = point;
	point_info.Frame = ++point_frame;

	/*if (!Point.Contains(PointMode::One))
	{
		FPoints points;
		points.PointPosition.Add(point_info);
		Point.Add(PointMode::One, points);

		return;
	}

	Point[PointMode::One].PointPosition.Add(point_info);*/

	Points.PointPosition.Add(point_info);
}

void DigitArchThread::GetJson(FString& json_string)
{
	if (Points.PointPosition.Num() == 0)
		return;

	FJsonObjectConverter::UStructToJsonObjectString(Points, json_string);

	Points.PointPosition.Empty();
	
}

uint32 DigitArchThread::Run()
{
	while (working)
	{
		//FPlatformProcess::Sleep(0.01);
		if (bPositionActive)
			SetPoint();
	}
	return 0;
}

void DigitArchThread::Exit()
{
}

void DigitArchThread::Stop()
{
	working = false;
}
