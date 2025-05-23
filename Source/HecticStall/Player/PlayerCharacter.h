
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

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

	UPROPERTY(EditAnywhere) //Where the functions are
	class UCameraComponent* Camera; //where the camera is called/exists

	void MoveForward(float InputValue); // Called when the player provides input on the "MoveForward" axis.
	void MoveRight(float InputValue);// Called when the player provides input on the "MoveRight" axis.
	void Turn(float InputValue);// Rotates the character left or right (yaw).
	void LookUp(float InputValue);// Rotates the camera up or down (pitch).
	void Interact();// Currently just logs "Object picked up!" to the output log � placeholder for future interaction logic.

};
