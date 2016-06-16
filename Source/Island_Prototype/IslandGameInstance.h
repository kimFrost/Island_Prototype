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

	// Sets default values for this's properties
	UIslandGameInstance(const FObjectInitializer &ObjectInitializer);

	//~~ RESOURCES ~~//

	TMap<FString, FST_Item> StoredItems;



	//~~ Data ~~//

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	UDataTable* DATA_Items;

	UFUNCTION(BlueprintCallable, Category = "Data")
	void ReadTables();

	UFUNCTION(BlueprintCallable, Category = "Resources")
	float GetTotalResourceStored(FString Id);

	bool HasItemsAvailable(TMap<FString, float>& Request, bool bTagSearch, bool bUseProvides);

	bool HasResourcesAvailable(TMap<FString, float>& Request);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	FST_Item GetRandItem();

	UFUNCTION(BlueprintCallable, Category = "Resources", Meta = (ExpandEnumAsExecs = "Branches"))
	TArray<FST_Item> RequestItem(FString Id, int32 Quantity, bool bTagSearch, bool bUseProvides, TEnumAsByte<ERequestMetGateEnum>& Branches);
	
	UFUNCTION(BlueprintCallable, Category = "Resources", Meta = (ExpandEnumAsExecs = "Branches"))
	TArray<FST_Item> RequestResource(FString Id, float Quantity, TEnumAsByte<ERequestMetGateEnum>& Branches);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	FST_Item StoreItem(FString Id, int Quantity);
	
	UFUNCTION(BlueprintCallable, Category = "Resources")
	TArray<FST_Item> GetStoredItems();



};
