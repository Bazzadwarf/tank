// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraVolume.h"

#include "CameraManagerSubsystem.h"
#include "TankPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

ACameraVolume::ACameraVolume()
{
	PrimaryActorTick.bCanEverTick = true;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	ArrowComponent->SetupAttachment(RootComponent);

	DebugCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Debug Camera"));
	DebugCamera->SetupAttachment(ArrowComponent);
	DebugCamera->SetActive(false);
}

void ACameraVolume::BeginPlay()
{
	Super::BeginPlay();
	this->OnActorBeginOverlap.AddDynamic(this, &ACameraVolume::OnBeginOverlap);
	this->OnActorEndOverlap.AddDynamic(this, &ACameraVolume::OnEndOverlap);
}

void ACameraVolume::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsActive && LookAtPlayer && TankPlayerCharacter)
	{
		TankPlayerCharacter->CameraComponent->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(
			ArrowComponent->GetComponentTransform().GetLocation(), TankPlayerCharacter->GetTransform().GetLocation()));
	}
}

void ACameraVolume::MoveCameraToLocation()
{
	if (TankPlayerCharacter)
	{
		TankPlayerCharacter->CameraComponent->SetWorldLocation(ArrowComponent->GetComponentTransform().GetLocation());
		TankPlayerCharacter->CameraComponent->SetWorldRotation(ArrowComponent->GetComponentTransform().GetRotation());
	}
}

bool ACameraVolume::GetIsActive()
{
	return IsActive;
}

void ACameraVolume::SetIsActive(bool bActive)
{
	IsActive = bActive;
}

void ACameraVolume::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ATankPlayerCharacter* PlayerCharacter = Cast<ATankPlayerCharacter>(OtherActor))
	{
		TankPlayerCharacter = PlayerCharacter;
		IsActive = true;

		auto CameraManagerSubsystem = GetGameInstance()->GetSubsystem<UCameraManagerSubsystem>();
		CameraManagerSubsystem->SetCurrentCameraVolume(this);
	}
}

void ACameraVolume::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	IsActive = false;
	TankPlayerCharacter = nullptr;

	auto CameraManagerSubsystem = GetGameInstance()->GetSubsystem<UCameraManagerSubsystem>();
	CameraManagerSubsystem->RemoveCameraVolume(this);
}
