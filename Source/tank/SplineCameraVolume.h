// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraVolume.h"
#include "Components/SplineComponent.h"
#include "SplineCameraVolume.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API ASplineCameraVolume : public ACameraVolume
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FollowPlayer = true;

	ASplineCameraVolume();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
