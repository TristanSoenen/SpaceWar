// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "PlayerSpaceCraft.generated.h"

UCLASS()
class SPACEWAR_API APlayerSpaceCraft : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerSpaceCraft();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	TObjectPtr<UInputAction> m_ShootAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	TObjectPtr<UInputAction> m_PlayerMoveAction;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	void Shoot(const FInputActionValue& value);
	void MovePlayerYZ(const FInputActionValue& value);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
