// Fill out your copyright notice in the Description page of Project Settings.

#include "DigitArchThread.h"

DEFINE_LOG_CATEGORY(DigitThread)

#define MAX_FRAME 60

DigitArchThread::DigitArchThread()
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	PlatformFile.DeleteDirectoryRecursively(*ProjectDir);
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

	FPoints points;
	FPointParam point_param;
	FPointInfo point_info;
	FCameraDigit camera;
	for(int32 i = 0; i < point_variables.Num(); i++)
	{
		points.DeviceType = point_variables[i].DeviceType;
		point_param.Type = point_variables[i].Type;
		point_info.Position = point_variables[i].Position;
		point_info.Frame = point_frame;
		camera.CameraAt = point_variables[i].CameraAt;
		//point_param.PointInfo.Add(point_info);
		//camera.Data.Add(point_param);
		for (int32 h = 0; h < PointsArray.Points.Num(); h++) 
		{
			if (PointsArray.Points[h].DeviceType == points.DeviceType)
			{
				for (int32 j = 0; j < PointsArray.Points[h].DeviceData.Num(); j++)
				{
					if (PointsArray.Points[h].DeviceData[j].CameraAt == camera.CameraAt)
					{
						for (int32 k = 0; k < PointsArray.Points[h].DeviceData[j].CameraData.Num(); k++)
						{
							if (PointsArray.Points[h].DeviceData[j].CameraData[k].Type != point_param.Type)
								continue;

							PointsArray.Points[h].DeviceData[j].CameraData[k].PointInfo.Add(point_info);
							goto stop1;
						}
						point_param.PointInfo.Add(point_info);
						PointsArray.Points[h].DeviceData[j].CameraData.Add(point_param);
						point_param.PointInfo.Empty();
						goto stop1;
					}
				}
				point_param.PointInfo.Add(point_info);
				camera.CameraData.Add(point_param);
				PointsArray.Points[h].DeviceData.Add(camera);
				point_param.PointInfo.Empty();
				camera.CameraData.Empty();
			}
		}
		point_param.PointInfo.Add(point_info);
		camera.CameraData.Add(point_param);
		points.DeviceData.Add(camera);
		if (!PointsArray.CheckIn(points)) {
			PointsArray.Points.Add(points);
		}
		point_param.PointInfo.Empty();
		camera.CameraData.Empty();
		points.DeviceData.Empty();
	stop1:

		continue;
	}
		
	if (GoNextFrame) {
		++point_frame;
		GoNextFrame = false;
	}
}

void DigitArchThread::GetJson(FString& json_string)
{
	if (PointsArray.Points.Num() == 0)
		return;

	FJsonObjectConverter::UStructToJsonObjectString(PointsArray, json_string);

	//UE_LOG(LogTemp, Log, TEXT("Work"));

	// Write in file
	if(Log)
	{
		//UE_LOG(LogTemp, Log, TEXT("Record"));

		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		if (PlatformFile.CreateDirectory(*ProjectDir))
		{
			const FString AbsoluteFilePath = ProjectDir / fileName + FString::FromInt(file_part) + fileFormat;
			FPaths::GetProjectFilePath();

			FFileHelper::SaveStringToFile(json_string, *AbsoluteFilePath);
		}
	}

	if (Send) {
		//UE_LOG(LogTemp, Log, TEXT("Send"));
		file_count++;
		TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
		Request->SetURL(GetURI() + "/api/File/upload/" + FileName + "/" + FString::FromInt(file_count));
		Request->SetVerb("POST");
		Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
		Request->SetContentAsString(json_string);
		Request->ProcessRequest();
	}

	++file_part;
	PointsArray.Points.Empty();
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

FString DigitArchThread::GetURI() {
	const FString JsonPath = FPaths::ProjectConfigDir() / "Settings.json";

	FString data;

	if (!FFileHelper::LoadFileToString(data, *JsonPath)) {
		UE_LOG(LogTemp, Error, TEXT("Not setting!"));
		return "";
	}

	const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(data);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	FString ServerUri;
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
		if (!JsonObject.Get()->TryGetStringField("ServerName", ServerUri)) {
			UE_LOG(LogTemp, Error, TEXT("Not parametr 'ServerName' !"));
			return "";
		}
	}
	return ServerUri;
}
