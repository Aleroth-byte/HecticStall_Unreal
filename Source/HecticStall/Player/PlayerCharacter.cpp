#include "HecticStall/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "HecticStall/Pause/PauseMenuWidget.h"
#include "HecticStall/Food/FoodItem.h"
#include "HecticStall/Customer/FoodCustomer.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	HoldDistance = 150.f;
	HeldItem = nullptr;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnCamera", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &APlayerCharacter::DropHeldItem);


	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerCharacter::PauseGame);
}

void APlayerCharacter::MoveForward(float InputValue)
{
	AddMovementInput(GetActorForwardVector(), InputValue);
}

void APlayerCharacter::MoveRight(float InputValue)
{
	AddMovementInput(GetActorRightVector(), InputValue);
}

void APlayerCharacter::Turn(float InputValue)
{
	AddControllerYawInput(InputValue);
}

void APlayerCharacter::LookUp(float InputValue)
{
	AddControllerPitchInput(InputValue);
}

void APlayerCharacter::Interact()
{
	if (HeldItem)
	{
		TraceForCustomer(); // Try to give item to a customer
	}
	else
	{
		TraceForFood(); // Try to pick up food
	}
}

void APlayerCharacter::TraceForCustomer()
{
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetForwardVector() * 300.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		if (AFoodCustomer* Customer = Cast<AFoodCustomer>(Hit.GetActor()))
		{
			Customer->ReceiveFood(HeldItem);
			HeldItem->Destroy();
			HeldItem = nullptr;
		}
	}
}



void APlayerCharacter::TraceForFood()
{
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetForwardVector() * 300.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		if (AFoodItem* HitFood = Cast<AFoodItem>(Hit.GetActor()))
		{
			AttachFoodToCamera(HitFood);
		}
	}
}

void APlayerCharacter::AttachFoodToCamera(AFoodItem* FoodItem)
{
	if (!FoodItem || !Camera) return;

	FoodItem->AttachToComponent(Camera, FAttachmentTransformRules::SnapToTargetIncludingScale);
	FoodItem->SetActorRelativeLocation(FVector(HoldDistance, -10.f, -30.f)); // Slight downward tilt for realism
	HeldItem = FoodItem;

	UE_LOG(LogTemp, Warning, TEXT("Picked up Food ID: %d"), FoodItem->FoodID);
}

void APlayerCharacter::DropHeldItem()
{
	if (HeldItem)
	{
		// Detach from camera
		HeldItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		// Move it back to its original position
		HeldItem->SetActorTransform(HeldItem->OriginalTransform);

		// Make sure it's visible and has collision again
		HeldItem->SetActorHiddenInGame(false);
		HeldItem->SetActorEnableCollision(true);

		HeldItem = nullptr;
	}
}



void APlayerCharacter::PauseGame()
{
	APlayerController* PC = GetController<APlayerController>();
	if (!PC || PC->IsPaused()) return;

	PC->SetPause(true);
	PC->bShowMouseCursor = true;
	PC->SetInputMode(FInputModeUIOnly());

	if (PauseMenuWidgetClass)
	{
		PauseMenuInstance = CreateWidget<UPauseMenuWidget>(GetWorld(), PauseMenuWidgetClass);
		if (PauseMenuInstance)
		{
			PauseMenuInstance->AddToViewport();
		}
	}
}
