#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoodCustomer.generated.h"

class AFoodItem;

UCLASS()
class HECTICSTALL_API AFoodCustomer : public AActor
{
	GENERATED_BODY()

public:
	AFoodCustomer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customer")
	int32 DesiredFoodID = 0;

	UFUNCTION()
	void ReceiveFood(AFoodItem* GivenFood);
};
