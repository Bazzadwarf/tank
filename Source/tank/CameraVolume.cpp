// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraVolume.h"
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
	this->OnActorEndOverlap.AddDynamic(this, &ACameraVolume::ACameraVolume::OnEndOverlap);
}

void ACameraVolume::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsActive && FollowPlayer && TankPlayerCharacter)
	{
		TankPlayerCharacter->CameraComponent->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(
			ArrowComponent->GetComponentTransform().GetLocation(), TankPlayerCharacter->GetTransform().GetLocation()));
	}
}

void ACameraVolume::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ATankPlayerCharacter* PlayerCharacter = Cast<ATankPlayerCharacter>(OtherActor))
	{
		PlayerCharacter->CameraComponent->SetWorldLocation(ArrowComponent->GetComponentTransform().GetLocation());
		PlayerCharacter->CameraComponent->SetWorldRotation(ArrowComponent->GetComponentTransform().GetRotation());

		TankPlayerCharacter = PlayerCharacter;
		IsActive = true;
	}
}

void ACameraVolume::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	IsActive = false;
	TankPlayerCharacter = nullptr;
}
