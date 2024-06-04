// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerCharacter.h"

#include "TankPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
ATankPlayerCharacter::ATankPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));	
}

// Called when the game starts or when spawned
void ATankPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankPlayerController->GetLocalPlayer()))
		{
			if (!InputMappingContext.IsNull())
			{
				InputSystem->AddMappingContext(InputMappingContext.LoadSynchronous(), 0);
			}	
		}
	}

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MovementAction)
		{
			Input->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ATankPlayerCharacter::MovementCallback);
		}

		if (YawAction)
		{
			Input->BindAction(YawAction, ETriggerEvent::Triggered, this, &ATankPlayerCharacter::RotationCallback);
		}	
	}
}

void ATankPlayerCharacter::MovementCallback(const FInputActionInstance& Instance)
{
	float Movement = Instance.GetValue().Get<float>();
	AddMovementInput(GetActorForwardVector(), Movement);
}

void ATankPlayerCharacter::RotationCallback(const FInputActionInstance& Instance)
{
	float Rotation = Instance.GetValue().Get<float>();
	AddControllerYawInput(Rotation);
}

