// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class TEAM31_API APickup : public AInteractable
{
	GENERATED_BODY()

public:

	APickup();

	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintNativeEvent)
		void Use();
	//virtual void Use_Implementation() override;

	UPROPERTY(EditAnywhere, Category = "Pickup Properties")
		UTexture2D* pickupThumbnail;

	UPROPERTY(EditAnywhere, Category = "Pickup Properties")
		FString itemName;

	UPROPERTY(EditAnywhere, Category = "Pickup Properties")
		int32 Value;
	
	/*this is called when the item is pickedup and needs to be cleaned up from the level*/
	void OnPickedUp();

};
