// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "IslandGameInstance.generated.h"





UENUM(BlueprintType)
enum ERequestMetGateEnum
{
	Met,
	NotMet
};





/**
 * 
 */
UCLASS()
class ISLAND_PROTOTYPE_API UIslandGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Resources", Meta = (ExpandEnumAsExecs = "Branches"))
	static void RequestResource(FString Id, int32 Quantity, TEnumAsByte<ERequestMetGateEnum>& Branches);
	
	
	
};
