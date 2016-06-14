// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "IslandDataHolder.h"
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

	// Resources
	TMap<FString, FST_Item> Items;


	UFUNCTION(BlueprintCallable, Category = "Resources", Meta = (ExpandEnumAsExecs = "Branches"))
	FST_Item RequestItem(FString Id, int32 Quantity, TEnumAsByte<ERequestMetGateEnum>& Branches);
	
	UFUNCTION(BlueprintCallable, Category = "Resources")
	void StoreItem();
	
	UFUNCTION(BlueprintCallable, Category = "Resources")
	void GetStoredItems();

};
