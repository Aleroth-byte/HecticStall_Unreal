#include "MainMenuWidget2.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget2::NativeConstruct()
{
    Super::NativeConstruct();

    if (PlayButton)
    {
        PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget2::OnPlayClicked);
    }

    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget2::OnQuitClicked);
    }
}

void UMainMenuWidget2::OnPlayClicked()
{
    UGameplayStatics::OpenLevel(this, FName("GameLevel")); // Replace with your game level name
}

void UMainMenuWidget2::OnQuitClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
