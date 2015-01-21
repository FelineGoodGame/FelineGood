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

protected:
	/** Variable that use the blackboard*/
	uint8 TargetKeyID;
	uint8 TargetLocationID;
	uint8 EnemyKeyID;
	ANoranekoCharacter* Player;
	uint8 Index;

public:
	/**constructor of the patroller controller*/
	APatroller_Controller(const FObjectInitializer& ObjectInitializer);
	

	/**Component that allow Patroller see and hear the player*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Awareness)
	UPawnSensingComponent* PatrollerSensor;

	/** Blackboard that contains all the variables that'll be used in the behavior tree*/
	UPROPERTY(transient)
	class UBlackboardComponent* BlackboardComp;

	/** The State Machine that ruled the behavior of the patroller*/
	UPROPERTY(transient)
	class UBehaviorTreeComponent* BehaviorTreeComp;


	/** function that'll be called in the blueprint to seek for ennemy*/
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SearchForEnemy();

	/** function that'll be called in blueprint to get the next Location to go*/
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void GetNextLocation();

	/** function to call onHearNoise Event*/
	UFUNCTION()
	void OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume);

	/** function to call onSeePawn Event*/
	UFUNCTION()
	void OnSeePawn(APawn *OtherPawn);


	/**Register the delegate functions*/
	virtual void PostInitializeComponents();

	/** Set the controller for the patroller on possess*/
	virtual void Possess(class APawn * InPawn);

	/** Set the ennemy to follow*/
	void SetEnemy(class APawn* InPawn);

	
};
