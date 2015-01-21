// Fill out your copyright notice in the Description page of Project Settings.

#include "Noraneko.h"
#include "Patroller_Controller.h"
#include "Patroller.h"

APatroller_Controller::APatroller_Controller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), Index{0}
{
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
	BehaviorTreeComp = ObjectInitializer.CreateDefaultSubobject <  UBehaviorTreeComponent >(this, TEXT("BehaviorComp"));
	PatrollerSensor = ObjectInitializer.CreateDefaultSubobject<UPawnSensingComponent>(this, TEXT("Pawn Sensor"));
	PatrollerSensor->SensingInterval = .25f; // 4 times per second
	PatrollerSensor->bOnlySensePlayers = false;
	PatrollerSensor->SetPeripheralVisionAngle(85.f);
}

void  APatroller_Controller::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	APatroller* Patroller = Cast<APatroller>(InPawn);	

	if (Patroller && Patroller->PatrollerBehavior)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Dialog message")));		
		BlackboardComp->InitializeBlackboard(Patroller->PatrollerBehavior->BlackboardAsset);
		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyLocationID = BlackboardComp->GetKeyID("Destination");
		TargetLocationID = BlackboardComp->GetKeyID("Destination");

		BehaviorTreeComp->StartTree(*(Patroller->PatrollerBehavior));
	}

}

void APatroller_Controller::SearchForEnemy()
{
	auto MyPatroller = GetPawn();
	if (MyPatroller == NULL)
	{

		return;
	}

	const FVector MyLoc = MyPatroller->GetActorLocation();
	float BestDistSq = MAX_FLT;
	ANoranekoCharacter* BestPawn = NULL; 

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		auto TestPawn = Cast<ANoranekoCharacter>(*It);
		if (TestPawn)
		{
			const float DistSq = FVector::Dist(TestPawn->GetActorLocation(), MyLoc);
			if (DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestPawn = TestPawn;
			}
		}
	}
	if (BestPawn)
	{
		SetEnemy(BestPawn);
	}
}

void APatroller_Controller::SetEnemy(class APawn *InPawn)
{
	BlackboardComp->SetValueAsObject(EnemyKeyID, InPawn);
	BlackboardComp->SetValueAsVector(EnemyLocationID, InPawn->GetActorLocation());
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
	auto Player = Cast<ANoranekoCharacter>(OtherPawn);
	if (Player)
	{
		FString message = TEXT("Saw Actor ") + OtherPawn->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
	}

}

void APatroller_Controller::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PatrollerSensor->OnSeePawn.AddDynamic(this, &APatroller_Controller::OnSeePawn);
	PatrollerSensor->OnHearNoise.AddDynamic(this, &APatroller_Controller::OnHearNoise);
}
