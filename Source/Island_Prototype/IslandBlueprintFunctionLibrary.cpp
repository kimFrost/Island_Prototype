// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandBlueprintFunctionLibrary.h"




/******************** NotNull *************************/
void UIslandBlueprintFunctionLibrary::NotNull(UObject* Object, TEnumAsByte<EBoolGateEnum>& Branches)
{
	if (Object != nullptr)
	{
		Branches = EBoolGateEnum::Exits;
	}
	else
	{
		Branches = EBoolGateEnum::Null;
	}
}
