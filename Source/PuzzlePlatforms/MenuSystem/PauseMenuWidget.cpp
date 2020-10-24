// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Components/Button.h"

bool UPauseMenuWidget::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    if (QuitButton==nullptr) return false;
    QuitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::QuitServer);

    if (ResumeButton==nullptr) return false;
    ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Cancel);

    return true;
}

void UPauseMenuWidget::QuitServer()
{
    if (MenuInterface==nullptr) return;
    MenuInterface->QuitLevel();
}

void UPauseMenuWidget::Cancel()
{
    Teardown();
}
