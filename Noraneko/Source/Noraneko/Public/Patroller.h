// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Patroller.generated.h"

/**
 * 
 */
UCLASS()
class NORANEKO_API APatroller : public ACharacter
{
	GENERATED_BODY()
	
	public:

		APatroller(const FObjectInitializer& ObjectInitializer);

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Patrol)
			TArray<float> WayPoints;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Patrol)
			float Speed;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Patrol)
			UStaticMeshComponent* MeshPatroller;
};
