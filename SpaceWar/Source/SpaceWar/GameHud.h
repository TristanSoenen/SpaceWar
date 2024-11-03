// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHud.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;
UCLASS()
class SPACEWAR_API UGameHud : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION()
    void ChangeScoreHud(int Score);
    UFUNCTION()
    void SetHealthHud(int Health);
    UFUNCTION()
    void NativeConstruct() override;
    UFUNCTION()
    void ShowGameHud();
private:
   UFUNCTION()
   void PlayAgainButtonClicked();
   UFUNCTION()
   void QuitButtonClicked();

   UPROPERTY(meta = (BindWidget))
   UTextBlock* m_ScoreTextNum;
   UPROPERTY(meta = (BindWidget))
   UTextBlock* m_HealthTextNum;
   UPROPERTY(meta = (BindWidget))
   UTextBlock* m_ScoreText;
   UPROPERTY(meta = (BindWidget))
   UTextBlock* m_HealthText;
   UPROPERTY(meta = (BindWidget))
   UButton*    m_PlayAgainButton;
   UPROPERTY(meta = (BindWidget))
   UButton*    m_QuitButton;
  
   const FName m_LevelToLoad = "Main";
};
