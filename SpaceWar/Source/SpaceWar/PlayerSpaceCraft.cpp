// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceCraft.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
APlayerSpaceCraft::APlayerSpaceCraft()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerSpaceCraft::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerSpaceCraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerSpaceCraft::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);
	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (input)
	{
		input->BindAction(m_ShootAction, ETriggerEvent::Triggered, this, &APlayerSpaceCraft::Shoot);
	}

}

void APlayerSpaceCraft::Shoot(const FInputActionValue& value)
{
	if (value.Get<bool>() == false)
		return;

	UE_LOG(LogTemp, Warning, TEXT("Shoot"));
}