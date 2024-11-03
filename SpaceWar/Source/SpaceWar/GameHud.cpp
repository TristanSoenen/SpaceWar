// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceWar/GameHud.h"

#include "PlayerSpaceCraft.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameHud::NativeConstruct()
{
    m_PlayAgainButton->OnClicked.AddDynamic(this, &UGameHud::PlayAgainButtonClicked);
    m_QuitButton->OnClicked.AddDynamic(this, &UGameHud::QuitButtonClicked);

    m_PlayAgainButton->SetVisibility(ESlateVisibility::Hidden);
    m_QuitButton->SetVisibility(ESlateVisibility::Hidden);

    m_ScoreTextNum->SetText(FText::AsNumber(0));
    m_ScoreText->SetText(FText::FromString("Hp: "));
    m_HealthTextNum->SetText(FText::AsNumber(100));
    m_HealthText->SetText(FText::FromString("PTS: "));

    APlayerSpaceCraft* player = Cast<APlayerSpaceCraft>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    player->m_OnHealthChanged.AddDynamic(this, &UGameHud::SetHealthHud);
    player->m_OnScoreChanged.AddDynamic(this, &UGameHud::ChangeScoreHud);
    player->m_OnPlayerDeath.AddDynamic(this, &UGameHud::ShowGameHud);
}

void UGameHud::ChangeScoreHud(int Score)
{
    m_ScoreTextNum->SetText(FText::AsNumber(Score));
}

void UGameHud::SetHealthHud(int Health)
{
    m_HealthTextNum->SetText(FText::AsNumber(Health));
}

void UGameHud::ShowGameHud()
{
    m_PlayAgainButton->SetVisibility(ESlateVisibility::Visible);
    m_QuitButton->SetVisibility(ESlateVisibility::Visible);
    m_ScoreTextNum->SetVisibility(ESlateVisibility::Hidden);
    m_ScoreText->SetVisibility(ESlateVisibility::Hidden);
    m_HealthTextNum->SetVisibility(ESlateVisibility::Hidden);
    m_HealthText->SetVisibility(ESlateVisibility::Hidden);

    APlayerController* controller = GetWorld()->GetFirstPlayerController();
    controller->bShowMouseCursor = true;
    controller->bEnableClickEvents = true;
}


void UGameHud::PlayAgainButtonClicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), m_LevelToLoad);


}

void UGameHud::QuitButtonClicked()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
