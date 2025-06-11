#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UPauseMenuWidget;
class AFoodItem;

UCLASS()
class HECTICSTALL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY()
	AFoodItem* HeldItem = nullptr;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float HoldDistance = 150.f;

	void MoveForward(float InputValue);
	void MoveRight(float InputValue);
	void Turn(float InputValue);
	void LookUp(float InputValue);
	void Interact();
	void PauseGame();
	void TraceForFood();
	void AttachFoodToCamera(AFoodItem* FoodItem);
	void DropHeldItem();
	void TraceForCustomer();


	UPROPERTY(EditAnywhere, Category = "Food")
	TSubclassOf<AFoodItem> HeldItemClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UPauseMenuWidget> PauseMenuWidgetClass;

private:
	UPROPERTY()
	UPauseMenuWidget* PauseMenuInstance;
};
