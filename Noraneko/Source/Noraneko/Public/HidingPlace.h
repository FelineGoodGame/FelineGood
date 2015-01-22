// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "HidingPlace.generated.h"

/**
*
*/
UCLASS()
class NORANEKO_API AHidingPlace : public AActor
{
	GENERATED_BODY()
public:
	AHidingPlace(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = HidingPlace)
		USphereComponent* BaseCollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = HidingPlace)
		UStaticMeshComponent* HidingPlaceMesh;

};
