#include "MainMenuWidget3.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget3::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget3::OnPlayClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget3::OnQuitClicked);
	}
}

void UMainMenuWidget3::OnPlayClicked()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		// Switch to game-only input mode
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}

	// Load the level
	UGameplayStatics::OpenLevel(this, "GameMap");
}

void UMainMenuWidget3::OnQuitClicked()
{
	FGenericPlatformMisc::RequestExit(false);
}
