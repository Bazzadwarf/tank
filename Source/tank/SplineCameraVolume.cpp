// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineCameraVolume.h"

#include "Kismet/KismetMathLibrary.h"

ASplineCameraVolume::ASplineCameraVolume()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	SplineComponent->SetupAttachment(RootComponent);
	FollowPlayer = true;
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
		TankPlayerCharacter->CameraComponent->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(
			Location, TankPlayerCharacter->GetTransform().GetLocation()));
	}
}
