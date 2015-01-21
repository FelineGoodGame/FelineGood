// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NoranekoCharacter.h"
#include "Classes/Perception/PawnSensingComponent.h"
#include "Patroller_Controller.generated.h"

/**
 * 
 */
UCLASS()
class NORANEKO_API APatroller_Controller : public AAIController
{
	GENERATED_BODY()

	uint8 Index;

protected:
	uint8 EnemyKeyID;
	uint8 EnemyLocationID;
	uint8 TargetLocationID;
	
public:
	/**constructor of the patroller controller*/
	APatroller_Controller(const FObjectInitializer& ObjectInitializer);
	
	virtual void PostInitializeComponents();
	
	/**Component that allow Patroller see and hear the player*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Awareness)
		UPawnSensingComponent* PatrollerSensor;

	/** Blackboard that contains all the variables that'll be used in the behavior tree*/
	UPROPERTY(transient)
	class UBlackboardComponent* BlackboardComp;

	/** The State Machine that ruled the behavior of the patroller*/
	UPROPERTY(transient)
	class UBehaviorTreeComponent* BehaviorTreeComp;

	/** Set the controller for the patroller on possessed*/
	virtual void Possess(class APawn * InPawn);

	/** Set the ennemy to follow*/
	void SetEnemy(class APawn* InPawn);

	/** function that'll be called in the blueprint to seek for ennemy*/
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SearchForEnemy();

	/** function that'll be called in blueprint to get the next Location to go*/
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void GetNextLocation();

	UFUNCTION()
		void OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume);

	UFUNCTION()
		void OnSeePawn(APawn *OtherPawn);
};
