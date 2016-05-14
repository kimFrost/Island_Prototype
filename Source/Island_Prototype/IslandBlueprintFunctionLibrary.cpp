// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandBlueprintFunctionLibrary.h"




/******************** NotNull *************************/
void UIslandBlueprintFunctionLibrary::NotNull(AActor* Actor, TEnumAsByte<EBoolGateEnum>& Branches)
{
	if (Actor)
	{
		Branches = EBoolGateEnum::Exits;
	}
	else
	{
		Branches = EBoolGateEnum::Null;
	}
}
