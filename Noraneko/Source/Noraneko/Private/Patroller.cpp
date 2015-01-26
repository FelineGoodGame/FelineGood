// Fill out your copyright notice in the Description page of Project Settings.

#include "Noraneko.h"
#include "Patroller_Controller.h"
#include "Patroller.h"


APatroller::APatroller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bIsSeeing{false}
{
	AIControllerClass = APatroller_Controller::StaticClass();
}
