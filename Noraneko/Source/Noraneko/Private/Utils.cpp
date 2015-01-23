// Fill out your copyright notice in the Description page of Project Settings.

#include "Noraneko.h"
#include "Utils.h"

Message::~Message()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString{ Text.str().c_str() });
	Text.str("");
	Text.clear();
}