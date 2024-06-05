// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraVolume.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CameraManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API UCameraManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<ACameraVolume*> CameraVolumeQueue;

	UPROPERTY()
	ACameraVolume* CurrentCameraVolume = nullptr;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void SetCurrentCameraVolume(ACameraVolume* CameraVolume);

	UFUNCTION(BlueprintCallable)
	void RemoveCameraVolume(ACameraVolume* CameraVolume);

private:
	UFUNCTION(BlueprintCallable)
	void QueueCameraVolume(ACameraVolume* CameraVolume);

	UFUNCTION(BlueprintCallable)
	void DequeueCameraVolume(ACameraVolume* CameraVolume);
};
