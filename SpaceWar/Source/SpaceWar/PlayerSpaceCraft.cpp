// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceCraft.h"
#include "EnhancedInputSubsystems.h"
#include "Components/WidgetInteractionComponent.h"

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
	//Add mapping context
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	Subsystem->AddMappingContext(InputMapping, 1);
}

// Called every frame
void APlayerSpaceCraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerSpaceCraft::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//Binding actions
	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	input->BindAction(m_PlayerMoveAction, ETriggerEvent::Triggered, this, &APlayerSpaceCraft::MovePlayerYZ);
	input->BindAction(m_ShootAction, ETriggerEvent::Triggered, this, &APlayerSpaceCraft::Shoot);
}

void APlayerSpaceCraft::Shoot(const FInputActionValue& value)
{
	if (value.Get<bool>() == false)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Shoot");
}

void APlayerSpaceCraft::MovePlayerYZ(const FInputActionValue &value)
{
	FVector2D inputVector = value.Get<FVector2D>();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, inputVector.ToString());
	FVector nextLocation = GetActorLocation();
	float deltaTime = GetWorld()->GetDeltaSeconds();
	nextLocation += FVector(0.0f, inputVector.X * 1000.0f * deltaTime, inputVector.Y * 1000.0f * deltaTime);
	SetActorLocation(nextLocation);
}