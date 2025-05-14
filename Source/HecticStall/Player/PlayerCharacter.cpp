
#include "HecticStall/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera")); //What the camera is going to do
	Camera->SetupAttachment(RootComponent); //Where the camera will go, to the player character
	Camera->bUsePawnControlRotation = true; //Enables the Pawn Control rotation of the camera in the blueprint class to true
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);


	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward); // When the player presses W or S, the input value is passed to MoveForward(), which moves the character forward or backward.
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);// When the player presses A or D, the input value is passed to MoveRight(), which moves the character left or right.
	PlayerInputComponent->BindAxis("TurnCamera", this, &APlayerCharacter::Turn);// This controls yaw rotation, allowing the player to turn left or right by moving the mouse horizontally.
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);// This controls pitch rotation, allowing the player to look up or down by moving the mouse vertically.

}

void APlayerCharacter::MoveForward(float InputValue)
{
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);//Pressing W will make the character move forward and S backwards according to the input value assigned in the project settings. (1.0, -1.0)
}

void APlayerCharacter::MoveRight(float InputValue)
{
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, InputValue);//Pressing D will make the character move right and A left according to the input value assigned in the project settings. (1.0, -1.0)
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
	UE_LOG(LogTemp, Warning, TEXT("Object picked up!"));
}
