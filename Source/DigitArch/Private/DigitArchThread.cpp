// Fill out your copyright notice in the Description page of Project Settings.

#include "DigitArchThread.h"

DEFINE_LOG_CATEGORY(DigitThread)

#define MAX_FRAME 60

DigitArchThread::DigitArchThread(CameraType camera_type)
{
	Points.DeviceType = camera_type;
}

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
	FCameraDigit camera;
	for(int32 i = 0; i < point_variables.Num(); i++)
	{
		point_param.Type = point_variables[i].Type;
		point_info.Position = point_variables[i].Position;
		point_info.Frame = point_frame;
		//point_param.PointInfo.Add(point_info);
		//camera.Data.Add(point_param);

		if(point_variables[i].CameraAt <= 0)
		{
			camera.CameraAt = 1;
		} else
		{
			camera.CameraAt = point_variables[i].CameraAt;
		}

		for (int32 j = 0; j < Points.DeviceData.Num(); j++)
		{
			if (Points.DeviceData[j].CameraAt == camera.CameraAt)
			{
				for (int32 k = 0; k < Points.DeviceData[j].Data.Num(); k++)
				{
					if (Points.DeviceData[j].Data[k].Type != point_param.Type)
						continue;

					Points.DeviceData[j].Data[k].PointInfo.Add(point_info);
					goto stop1;
				}
				point_param.PointInfo.Add(point_info);
				Points.DeviceData[j].Data.Add(point_param);
				point_param.PointInfo.Empty();
				goto stop1;
			}
		}
	
		point_param.PointInfo.Add(point_info);
		camera.Data.Add(point_param);
		Points.DeviceData.Add(camera);
		point_param.PointInfo.Empty();
		camera.Data.Empty();
		stop1:

		continue;
	}
		
	++point_frame;
}

void DigitArchThread::GetJson(FString& json_string)
{
	if (Points.DeviceData.Num() == 0)
		return;

	FJsonObjectConverter::UStructToJsonObjectString(Points, json_string);

	// Write in file
	if(Log)
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		if (PlatformFile.CreateDirectory(*ProjectDir))
		{
			const FString AbsoluteFilePath = ProjectDir / fileName;
			FPaths::GetProjectFilePath();

			FFileHelper::SaveStringToFile(json_string, *AbsoluteFilePath);
		}
	}

	Points.DeviceData.Empty();
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
