#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoodItem.generated.h"

UCLASS()
class HECTICSTALL_API AFoodItem : public AActor
{
	GENERATED_BODY()

public:
	AFoodItem();

public:
	FVector OriginalLocation;
	FRotator OriginalRotation;

	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food")
	int32 FoodID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Food")
	UStaticMeshComponent* FoodMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food")
	FString FoodName;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTransform OriginalTransform;


};
