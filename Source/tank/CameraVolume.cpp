// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraVolume.h"
#include "TankPlayerCharacter.h"

ACameraVolume::ACameraVolume()
{
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
}

void ACameraVolume::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ATankPlayerCharacter* PlayerCharacter = Cast<ATankPlayerCharacter>(OtherActor))
	{
		FTransform transform = PlayerCharacter->CameraComponent->GetComponentTransform();
		transform.SetLocation(ArrowComponent->GetComponentTransform().GetLocation());
		transform.SetRotation(ArrowComponent->GetComponentTransform().GetRotation());
		PlayerCharacter->CameraComponent->SetWorldTransform(transform);
	}
}
