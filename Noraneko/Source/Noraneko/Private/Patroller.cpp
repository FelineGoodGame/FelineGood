// Fill out your copyright notice in the Description page of Project Settings.

#include "Noraneko.h"
#include "Patroller_Controller.h"
#include "Patroller.h"


APatroller::APatroller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MeshPatroller = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PatrollerMesh"));
	MeshPatroller->SetSimulatePhysics(true);
	MeshPatroller->AttachTo(RootComponent);
	AIControllerClass = APatroller_Controller::StaticClass();

	PatrollerSensor = ObjectInitializer.CreateDefaultSubobject<UPawnSensingComponent>(this, TEXT("Pawn Sensor"));
	PatrollerSensor->SensingInterval = .25f; // 4 times per second
	PatrollerSensor->bOnlySensePlayers = false;
	PatrollerSensor->SetPeripheralVisionAngle(85.f);

}

void APatroller::OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume)
{
	const FString VolumeDesc = FString::Printf(TEXT(" at volume %f"), Volume);
	FString message = TEXT("Heard Actor ") + OtherActor->GetName() + VolumeDesc;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
}

void APatroller::OnSeePawn(APawn* OtherPawn)
{
	FString message = TEXT("Saw Actor ") + OtherPawn->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
}

void APatroller::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PatrollerSensor->OnSeePawn.AddDynamic(this, &APatroller::OnSeePawn);
	PatrollerSensor->OnHearNoise.AddDynamic(this, &APatroller::OnHearNoise);
}