// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "NPC_AIController.generated.h"

/**
 * 
 */
UCLASS()
class TEAM31_API ANPC_AIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit ANPC_AIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Search", meta=(AllowPrivateAccess="true"))
	float PeripheralVision = 270.f;
private:
	class UAISenseConfig_Sight* SightConfig;

	void SetupPerpectionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);
};
