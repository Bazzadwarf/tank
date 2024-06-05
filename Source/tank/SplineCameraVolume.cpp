// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineCameraVolume.h"

#include "Kismet/KismetMathLibrary.h"

ASplineCameraVolume::ASplineCameraVolume()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	SplineComponent->SetupAttachment(RootComponent);
}

void ASplineCameraVolume::BeginPlay()
{
	Super::BeginPlay();
}

void ASplineCameraVolume::Tick(float DeltaSeconds)
{
	if (IsActive && FollowPlayer && TankPlayerCharacter)
	{
		FVector Location = SplineComponent->FindLocationClosestToWorldLocation(
			TankPlayerCharacter->GetTransform().GetLocation(), ESplineCoordinateSpace::World);

		TankPlayerCharacter->CameraComponent->SetWorldLocation(Location);
	}

	if (IsActive && LookAtPlayer && TankPlayerCharacter)
	{
		TankPlayerCharacter->CameraComponent->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(
			TankPlayerCharacter->CameraComponent->GetComponentToWorld().GetLocation(), TankPlayerCharacter->GetTransform().GetLocation()));
	}
}
