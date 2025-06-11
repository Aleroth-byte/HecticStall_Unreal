#include "FoodItem.h"

AFoodItem::AFoodItem()
{
	PrimaryActorTick.bCanEverTick = false;

	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FoodMesh"));
	RootComponent = FoodMesh;

	FoodID = -1; // default invalid
}

void AFoodItem::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetActorLocation();
	OriginalRotation = GetActorRotation();
	OriginalTransform = GetActorTransform();
}

