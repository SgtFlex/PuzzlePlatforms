// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::Setup()
{
    this->AddToViewport();
    this->bIsFocusable = true;
    APlayerController* PlayerController = GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld());
    if (PlayerController==nullptr){return;}
    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = true;
}
void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
    Super::OnLevelRemovedFromWorld(InLevel, InWorld);
    Teardown();
}

void UMenuWidget::Teardown()
{
    UE_LOG(LogTemp, Warning, TEXT("Tearing down"));
    this->bIsFocusable = false;
    this->RemoveFromViewport();
    APlayerController* PlayerController = GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld());
    if (PlayerController==nullptr){return;}
    FInputModeGameOnly InputModeData;

    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = false;
}


void UMenuWidget::SetMenuInterface(IMenuInterface* _MenuInterface)
{
    this->MenuInterface = _MenuInterface;
}
