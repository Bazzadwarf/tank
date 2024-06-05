// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Engine/TriggerVolume.h"
#include "CameraVolume.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TANK_API ACameraVolume : public ATriggerVolume
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* DebugCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FollowPlayer = false;
	
private:

	UPROPERTY()
	bool IsActive = false;

	UPROPERTY()
	ATankPlayerCharacter* TankPlayerCharacter = nullptr;
	
public:
	
	ACameraVolume();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void MoveCameraToLocation();

	UFUNCTION()
	bool GetIsActive();

	UFUNCTION()
	void SetIsActive(bool bActive);

private:
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
