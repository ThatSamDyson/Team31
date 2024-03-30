// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindPatrolPathPoint.h"
#include  "NPC.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrolPathPoint::UBTTask_FindPatrolPathPoint(FObjectInitializer const& ObjectInitializer) :
	UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Find Path Point");
}

EBTNodeResult::Type UBTTask_FindPatrolPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Attempt to get the NPC's controller
	if (auto* const cont = Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		// Attempt to get the blackboard component from the behaviour tree
		if(auto* const bc = OwnerComp.GetBlackboardComponent())
		{
			// Get the current patrol path index from the blackboard
			auto const Index = bc->GetValueAsInt((GetSelectedBlackboardKey()));

			// Get the NPC
			if (auto* npc = Cast<ANPC>(cont->GetPawn()))
			{
				// Get the current patrol pathing vector from the NPC - This is a local to the patrol path actor
				auto const Point = npc->GetPatrolPath()->GetPatrolPoint(Index);

				// Convert the local vector to a global point
				auto const GlobalPoint = npc->GetPatrolPath()->GetActorTransform().TransformPosition(Point);
				bc->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);

				// Finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
