// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Patroller_Controller.generated.h"

/**
 * 
 */
UCLASS()
class NORANEKO_API APatroller_Controller : public AAIController
{
	GENERATED_BODY()

	

protected:
	uint8 EnemyKeyID;
	uint8 EnemyLocationID;
	
public:
	APatroller_Controller(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(transient)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
	class UBehaviorTreeComponent* BehaviorTreeComp;

	virtual void Possess(class APawn * InPawn);

	void SetEnemy(class APawn* InPawn);

	UFUNCTION(BlueprintCallable, Category = Behavior)
		void SearchForEnemy();
};
