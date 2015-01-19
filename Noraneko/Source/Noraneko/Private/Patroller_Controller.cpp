// Fill out your copyright notice in the Description page of Project Settings.

#include "Noraneko.h"
#include "Patroller_Controller.h"
#include "Patroller.h"
#include "NoranekoCharacter.h"

APatroller_Controller::APatroller_Controller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
	BehaviorTreeComp = ObjectInitializer.CreateDefaultSubobject <  UBehaviorTreeComponent >(this, TEXT("BehaviorComp"));

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

		BehaviorTreeComp->StartTree(*(Patroller->PatrollerBehavior));
	}

}

void APatroller_Controller::SearchForEnemy()
{
	APawn* MyPatroller = GetPawn();
	if (MyPatroller == NULL)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Dialog message")));

		return;
	}

	const FVector MyLoc = MyPatroller->GetActorLocation();
	float BestDistSq = MAX_FLT;
	ANoranekoCharacter* BestPawn = NULL; 

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		ANoranekoCharacter* TestPawn = Cast<ANoranekoCharacter>(*It);
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