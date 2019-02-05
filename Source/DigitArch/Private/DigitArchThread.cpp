// Fill out your copyright notice in the Description page of Project Settings.

#include "DigitArchThread.h"

DEFINE_LOG_CATEGORY(DigitThread)

#define MAX_FRAME 60

void DigitArchThread::WriteDataPoint()
{
	bPositionActive = false;

	if (point_frame > MAX_FRAME)
	{
		FString json_string;
		GetJson(json_string);

		// Careful with that
		//UE_LOG(DigitThread, Log, TEXT("%s"), *json_string); 

		point_frame = 1;
	}

	FPointParam point_param;
	FPointInfo point_info;
	for(int32 i = 0; i < point_variables.Num(); i++)
	{
		point_param.Type = point_variables[i].Type;
		point_info.Position = point_variables[i].Position;
		point_info.Frame = point_frame;

		for (int32 j = 0; j < Points.Data.Num(); j++)
		{
			if (Points.Data[j].Type != point_param.Type)
				continue;

			Points.Data[j].PointInfo.Add(point_info);
			goto stop;
		}

		point_param.PointInfo.Add(point_info);
		Points.Data.Add(point_param);
		point_param.PointInfo.Empty();

	stop:
		continue;
	}
		
	++point_frame;
}

void DigitArchThread::GetJson(FString& json_string)
{
	if (Points.Data.Num() == 0)
		return;

	FJsonObjectConverter::UStructToJsonObjectString(Points, json_string);


	// Write in file
	if(Log)
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		const FString ProjectDir = FPaths::ProjectDir() / "Log";
		const FString fileName = "points.json";
		if (PlatformFile.CreateDirectory(*ProjectDir))
		{
			const FString AbsoluteFilePath = ProjectDir / fileName;
			FPaths::GetProjectFilePath();

			FFileHelper::SaveStringToFile(json_string, *AbsoluteFilePath);
		}
	}

	Points.Data.Empty();
	
}

uint32 DigitArchThread::Run()
{
	while (working)
	{
		//FPlatformProcess::Sleep(0.01);
		if (bPositionActive)
			WriteDataPoint();
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
