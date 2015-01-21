// Fill out your copyright notice in the Description page of Project Settings.

#include "Noraneko.h"
#include "Patroller.h"


APatroller::APatroller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MeshPatroller = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PatrollerMesh"));
	MeshPatroller->SetSimulatePhysics(true);
	MeshPatroller->AttachTo(RootComponent);
}
