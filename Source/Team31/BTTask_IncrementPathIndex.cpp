// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "BTTask_IncrementPathIndex.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer) :
	UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Increment Path Index");
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Try and get the AI controller
	if (auto* const Cont = Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		// Try and get the NPC
		if (auto* const NPC = Cast<ANPC>(Cont->GetPawn()))
		{
			// Try and get the blackboard
			if(auto* const BC = OwnerComp.GetBlackboardComponent())
			{
				// Get number of patrol points and min and max indices
				auto const NoOfPoints = NPC->GetPatrolPath()->Num();
				auto const MinIndex = 0;
				auto const MaxIndex = NoOfPoints - 1;
				auto Index = BC->GetValueAsInt(GetSelectedBlackboardKey());

				// Change direction if we reach the last or the first patrol point if we are in bidirectional mode
				if(bBiDirectional)
				{
					if (Index >= MaxIndex && Direction == EDirectionType::Forward)
					{
						Direction = EDirectionType::Reverse;
					}
					else if(Index == MinIndex && Direction == EDirectionType::Reverse)
					{
						Direction = EDirectionType::Forward;
					}
				}

				// Set new value of index to the blackboard
				BC->SetValueAsInt(GetSelectedBlackboardKey(),
					(Direction == EDirectionType::Forward ? ++Index : --Index) % NoOfPoints);

				// Finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	// Something went wrong
	return EBTNodeResult::Failed;
}
