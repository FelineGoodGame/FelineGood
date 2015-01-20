// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Engine/TargetPoint.h"
#include "Patroller.generated.h"

/**
 * 
 */
UCLASS()
class NORANEKO_API APatroller : public ACharacter
{
	GENERATED_BODY()
	
	public:
		/** Patroller constructor*/
		APatroller(const FObjectInitializer& ObjectInitializer);

		/** Behavior Tree that runs the patroller behavior*/
		UPROPERTY(EditAnywhere, Category =Behavior)
		class UBehaviorTree* PatrollerBehavior;

		/** Array of patrol points of the patroller*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Patrol)
			TArray<ATargetPoint*> WayPoints;
		
		/** The speed of the walk */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Patrol)
			float Speed;

		/** Static mesh of the patroller*/
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Patrol)
			UStaticMeshComponent* MeshPatroller;
	
};
