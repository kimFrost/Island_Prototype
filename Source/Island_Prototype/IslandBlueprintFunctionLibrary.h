// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "IslandBlueprintFunctionLibrary.generated.h"



UENUM(BlueprintType)
enum EBoolGateEnum
{
	Exits,
	Null
};



UCLASS()
class ISLAND_PROTOTYPE_API UIslandBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Util", Meta = (ExpandEnumAsExecs = "Branches"))
	static void NotNull(AActor* Actor, TEnumAsByte<EBoolGateEnum>& Branches);
	
};
