// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManagerSubsystem.h"

void UCameraManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentCameraVolume = nullptr;
	CameraVolumeQueue.Empty();
}

void UCameraManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	CurrentCameraVolume = nullptr;
	CameraVolumeQueue.Empty();
}

void UCameraManagerSubsystem::SetCurrentCameraVolume(ACameraVolume* CameraVolume)
{

	if (CurrentCameraVolume != CameraVolume && !CameraVolumeQueue.Contains(CameraVolume))
	{
		if (CurrentCameraVolume)
		{
			CurrentCameraVolume->SetIsActive(false);
		}
		
		QueueCameraVolume(CameraVolume);
		CurrentCameraVolume = CameraVolume;
		CurrentCameraVolume->MoveCameraToLocation();
	}
}

void UCameraManagerSubsystem::RemoveCameraVolume(ACameraVolume* CameraVolume)
{
	if (CameraVolume == CurrentCameraVolume)
	{
		DequeueCameraVolume(CameraVolume);
		CurrentCameraVolume->SetIsActive(false);
		CurrentCameraVolume = nullptr;
	}

	if (CameraVolumeQueue.Num() > 0)
	{
		CurrentCameraVolume = CameraVolumeQueue.Last();
		CurrentCameraVolume->MoveCameraToLocation();
		CurrentCameraVolume->SetIsActive(true);
	}
}

void UCameraManagerSubsystem::QueueCameraVolume(ACameraVolume* CameraVolume)
{
	if (!CameraVolumeQueue.Contains(CameraVolume))
	{
		CameraVolumeQueue.Push(CameraVolume);
	}
}

void UCameraManagerSubsystem::DequeueCameraVolume(ACameraVolume* CameraVolume)
{
	if (CameraVolumeQueue.Contains(CameraVolume))
	{
		CameraVolumeQueue.Remove(CameraVolume);
	}
}
