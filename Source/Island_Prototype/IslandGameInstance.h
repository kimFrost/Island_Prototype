// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "IslandDataHolder.h"
#include "IslandGameInstance.generated.h"



enum class EIslandPlayState : uint8 //** you can replace short with uint8 */
{
	EPlaying,
	EGameOver,
	EUnknown
};

UENUM(BlueprintType)
enum ERequestMetGateEnum
{
	Met,
	NotMet
};

UENUM(BlueprintType)
enum class EGameState : uint8
{
	BaseManagement UMETA(DisplayName = "BaseManagement"),
	ProcessStations UMETA(DisplayName = "ProcessStations"),
	Exploring UMETA(DisplayName = "Exploring"),
	FoodConsumption UMETA(DisplayName = "FoodConsumption"),
	ProcessPeopleStates UMETA(DisplayName = "ProcessPeopleStates"),
};


//~~~~~ Forward Declarations ~~~~~//
class AIslandTile;
class AIslandPerson;


//~~~~~ Delegates/Event dispatcher ~~~~~//
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurnSwitched, float, Turn);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewTurn, float, Turn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTileClicked, AIslandTile*, Tile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnyTileRevealed, AIslandTile*, Tile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPersonMoveEnded, AIslandPerson*, Person, AIslandTile*, Tile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPersonSelected, AIslandPerson*, Person);



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

	UFUNCTION(BlueprintCallable, Category = "Resources")
	FST_Item GetItem(FString Id, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Resources", Meta = (ExpandEnumAsExecs = "Branches"))
	TArray<FST_Item> RequestItem(FString Id, int32 Quantity, bool bTagSearch, bool bUseProvides, TEnumAsByte<ERequestMetGateEnum>& Branches);
	
	UFUNCTION(BlueprintCallable, Category = "Resources", Meta = (ExpandEnumAsExecs = "Branches"))
	TArray<FST_Item> RequestResource(FString Id, float Quantity, TEnumAsByte<ERequestMetGateEnum>& Branches);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	FST_Item StoreItem(FString Id, int Quantity);
	
	UFUNCTION(BlueprintCallable, Category = "Resources")
	TArray<FST_Item> GetStoredItems();

	/*********** DELEGATES **************/

	//UPROPERTY(BlueprintAssignable, Category = "Turn")
	//FTurnSwitched OnTurnSwitched;

	//UPROPERTY(BlueprintAssignable, Category = "Turn")
	//FNewTurn OnNewTurn;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FTileClicked OnTileClicked;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FAnyTileRevealed OnTileRevealed;

	//UPROPERTY(BlueprintAssignable, Category = "Input")
	FPersonMoveEnded OnPersonMoveEnded;

	//UPROPERTY(BlueprintAssignable, Category = "Input")
	FPersonSelected OnPersonSelected;

};
