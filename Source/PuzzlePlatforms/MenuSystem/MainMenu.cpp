// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"


bool UMainMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    if (HostButton==nullptr) return false;
    HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
    if (JoinButton==nullptr) return false;
    JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
    if (CancelButton==nullptr) return false;
    CancelButton->OnClicked.AddDynamic(this, &UMainMenu::CancelJoin);
    if (JoinServerButton==nullptr) return false;
    JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
    if (QuitGameButton==nullptr) return false;
    QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
    
    return true;
}







void UMainMenu::HostServer()
{
    if (MenuInterface==nullptr) return;
    MenuInterface->Host();
    
}

void UMainMenu::JoinServer()
{
    if (MenuInterface==nullptr) return;
    MenuInterface->Join(IPAddressField->GetText().ToString());
}

void UMainMenu::OpenJoinMenu()
{
    if (MenuSwitcher==nullptr) return;
    if (JoinMenu==nullptr) return;
    MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::CancelJoin()
{
    if (MenuSwitcher==nullptr) return;
    if (StartMenu==nullptr) return;
    MenuSwitcher->SetActiveWidget(StartMenu);
}

void UMainMenu::QuitGame()
{
    GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
