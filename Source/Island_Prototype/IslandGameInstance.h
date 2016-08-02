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
	TurnSummery UMETA(DisplayName = "TurnSummery"),
	ProcessStations UMETA(DisplayName = "ProcessStations"),
	Exploring UMETA(DisplayName = "Exploring"),
	FoodConsumption UMETA(DisplayName = "FoodConsumption"),
	ProcessPeopleStates UMETA(DisplayName = "ProcessPeopleStates"),
	DoomEvent UMETA(DisplayName = "DoomEvent"),
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemAdded, FST_Item, Item);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIventoryUpdated);



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

	//~~ UTIL ~~//

	UFUNCTION(BlueprintCallable, Category = "Util")
	FString EnrichString(FString String, AIslandPerson* Person);

	UFUNCTION(BlueprintCallable, Category = "Util")
	float GetRoll(AIslandPerson* Person, TArray<FST_Modifier> Modifiers);

	UFUNCTION(BlueprintCallable, Category = "Util")
	FST_Outcome GetOutcome(TArray<FST_Outcome> Outcomes, AIslandPerson* Person, TArray<FST_Modifier> Modifiers);

	UFUNCTION(BlueprintCallable, Category = "Util")
	void ParseAction(ETarget TargetType, AIslandPerson* Person, EAction Action, float Amount, ECause Cause);

	UFUNCTION(BlueprintCallable, Category = "Util")
	void ParseOutcome(FST_Outcome Outcome, AIslandPerson* Person, ECause Cause, bool AddUpdate = true);

	//~~ TASKS + NOTIFICATIONS ~~//

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Task")
	TArray<FST_TaskDone> TasksDoneThisTurn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Notification")
	TArray<FST_Notification> Notifications;

	UFUNCTION(BlueprintCallable, Category = "Task")
	void AddTaskDone(FString Description, AIslandPerson* By, EUsefulRating Rating = EUsefulRating::Neutral, ETaskType TaskType = ETaskType::Work);

	UFUNCTION(BlueprintCallable, Category = "Task")
	void AddNotification(FString Msg, AIslandPerson* Concerning, ENotificationType Type);


	//~~ RESOURCES ~~//

	TMap<FString, FST_Item> StoredItems;


	//~~ PEOPLE ~~//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	TArray<AIslandPerson*> People;

	//~~ DATA ~~//

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

	UPROPERTY(BlueprintAssignable, Category = "Resources")
	FItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "Resources")
	FIventoryUpdated OnIventoryUpdated;

};
