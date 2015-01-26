// Fill out your copyright notice in the Description page of Project Settings.

#include "Noraneko.h"
#include "HidingPlace.h"

AHidingPlace::AHidingPlace(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	BaseCollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));

	RootComponent = BaseCollisionComponent;

	HidingPlaceMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("HidingPlaceMesh"));

	HidingPlaceMesh->SetSimulatePhysics(true); 

	HidingPlaceMesh->AttachTo(RootComponent);

	

}


