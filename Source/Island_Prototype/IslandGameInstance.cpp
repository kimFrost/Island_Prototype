// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandGameInstance.h"




/******************** RequestResource *************************/
void UIslandGameInstance::RequestResource(FString Id, int32 Quantity, TEnumAsByte<ERequestMetGateEnum>& Branches)
{
	if (Id != "")
	{
		Branches = ERequestMetGateEnum::Met;
	}
	else
	{
		Branches = ERequestMetGateEnum::NotMet;
	}
}
