#include "FoodCustomer.h"
#include "HecticStall/Food/FoodItem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/TextRenderComponent.h"

UPROPERTY(VisibleAnywhere)
class UTextRenderComponent* CustomerText;

AFoodCustomer::AFoodCustomer()
{
	PrimaryActorTick.bCanEverTick = false;

	CustomerText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CustomerText"));
	CustomerText->SetupAttachment(RootComponent);
	CustomerText->SetText(FText::FromString("Waiting..."));
	CustomerText->SetHorizontalAlignment(EHTA_Center);
	CustomerText->SetWorldSize(50.f);
	CustomerText->SetRelativeLocation(FVector(0, 0, 120)); // make sure it's above the mesh
}

void AFoodCustomer::ReceiveFood(AFoodItem* GivenFood)
{
	if (!GivenFood) return;

	if (GivenFood->FoodID == DesiredFoodID)
	{
		if (CustomerText)
			CustomerText->SetText(FText::FromString("Thank you!"));

		UE_LOG(LogTemp, Warning, TEXT("Thank you!"));

		GivenFood->Destroy();
	}
	else
	{
		if (CustomerText)
			CustomerText->SetText(FText::FromString("That's not what I want!"));

		UE_LOG(LogTemp, Warning, TEXT("That's not what I want!"));
	}
}



