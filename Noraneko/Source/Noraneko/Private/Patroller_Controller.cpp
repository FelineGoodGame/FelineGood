// Fill out your copyright notice in the Description page of Project Settings.

#include "Noraneko.h"
#include "Patroller_Controller.h"
#include "Patroller.h"

APatroller_Controller::APatroller_Controller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), Index{ 0 }, Player{nullptr}
{
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
	BehaviorTreeComp = ObjectInitializer.CreateDefaultSubobject <  UBehaviorTreeComponent >(this, TEXT("BehaviorComp"));

	PatrollerSensor = ObjectInitializer.CreateDefaultSubobject<UPawnSensingComponent>(this, TEXT("Pawn Sensor"));
	PatrollerSensor->SensingInterval = .25f; // 4 times per second
	PatrollerSensor->bOnlySensePlayers = false;
	PatrollerSensor->SetPeripheralVisionAngle(45.f);

}

void  APatroller_Controller::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	APatroller* Patroller = Cast<APatroller>(InPawn);	

	if (Patroller && Patroller->PatrollerBehavior)
	{
		BlackboardComp->InitializeBlackboard(Patroller->PatrollerBehavior->BlackboardAsset);

		TargetKeyID = BlackboardComp->GetKeyID("Target");
		TargetLocationID = BlackboardComp->GetKeyID("Destination");
		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");

		BehaviorTreeComp->StartTree(*(Patroller->PatrollerBehavior));
	}

}

void APatroller_Controller::SearchForEnemy()
{

	if (Player)
	{
		if (!PatrollerSensor->HasLineOfSightTo(Player))
		{
			BlackboardComp->SetValueAsObject(EnemyKeyID, NULL);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Enemy lost")));
			Player = nullptr;
		}
	}
}

void APatroller_Controller::SetEnemy(class APawn *InPawn)
{
	BlackboardComp->SetValueAsVector(TargetLocationID, InPawn->GetActorLocation());
}

void APatroller_Controller::GetNextLocation()
{
	auto MyPawn = GetPawn();
	if (MyPawn == NULL)
	{
		return;
	}

	auto MyPatroller = Cast<APatroller>(MyPawn);
	if (MyPatroller)
	{
		auto& NodeList = MyPatroller->WayPoints;
		auto Nb =  NodeList.Num();
		Index = (Index + 1) % Nb;

		//get random location from the list
		BlackboardComp->SetValueAsVector(TargetLocationID, NodeList[Index]->GetActorLocation());
		BlackboardComp->SetValueAsObject(TargetKeyID, NodeList[Index]);
	}
}
 
void APatroller_Controller::OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume)
{
	const FString VolumeDesc = FString::Printf(TEXT(" at volume %f"), Volume);
	FString message = TEXT("Heard Actor ") + OtherActor->GetName() + VolumeDesc;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
}

void APatroller_Controller::OnSeePawn(APawn* OtherPawn)
{
	auto Enemy = Cast<ARembrandt>(OtherPawn);
	if (Enemy)
	{
		Player = Enemy;
		if (Player->GetState() != EState::Hidden)
		{
			BlackboardComp->SetValueAsVector(TargetLocationID, Enemy->GetActorLocation());
			BlackboardComp->SetValueAsObject(EnemyKeyID, Enemy);
		}
		
	}
}

void APatroller_Controller::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PatrollerSensor->OnSeePawn.AddDynamic(this, &APatroller_Controller::OnSeePawn);
	PatrollerSensor->OnHearNoise.AddDynamic(this, &APatroller_Controller::OnHearNoise);
}
