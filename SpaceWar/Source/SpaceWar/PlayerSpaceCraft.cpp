// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceWar/PlayerSpaceCraft.h"
#include "Bullet.h"
#include "BulletData.h"
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
	//Add mapping context
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	Subsystem->AddMappingContext(InputMapping, 1);
	const FString contextWarning ={"Row not Found in data Table" };
	m_Data = m_DataTable->FindRow<FAllBulletAndEnemyData>("Player", contextWarning, true);
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
	if (value.Get<bool>() == false || m_CanFire == false)
		return;

	m_CanFire = false;
	FTransform spawnPoint;
	spawnPoint.SetLocation( GetActorLocation() +  GetActorUpVector() * 150);
	
	if(auto bullet = GetWorld()->SpawnActorDeferred<ABullet>(m_BPBullet, spawnPoint))
	{
		FVector direction = GetActorUpVector();
		bullet->InitializeBullet( true, m_Data->Speed, direction, m_Data->Damage);
		bullet->FinishSpawning(spawnPoint);
		bullet->SetBulletMaterial();
	}

	GetWorld()->GetTimerManager().SetTimer(m_FireTimer, this, &APlayerSpaceCraft::ResetFireTimer, m_Data->SpawnDelay, false);
}

void APlayerSpaceCraft::MovePlayerYZ(const FInputActionValue &value)
{
	FVector2D inputVector = value.Get<FVector2D>();
	FVector nextLocation = GetActorLocation();
	float deltaTime = GetWorld()->GetDeltaSeconds();
	nextLocation += FVector(0.0f, inputVector.X * m_Data->UnitMoveSpeed * deltaTime, inputVector.Y * m_Data->UnitMoveSpeed * deltaTime);
	SetActorLocation(nextLocation);
}

void APlayerSpaceCraft::ReduceHealth(int damage)
{
	m_Health -= damage;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Health Changed");
	if(m_Health < 0)
		Destroy();
}

void APlayerSpaceCraft::IncrementScore(int score)
{
	m_Score += score;
}

void APlayerSpaceCraft::ResetFireTimer()
{
	m_CanFire = true;
	GetWorld()->GetTimerManager().ClearTimer(m_FireTimer);
}
