// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "IslandPerson.h"
#include "IslandPath.h"
#include "IslandTile.generated.h"



//~~~~~ Delegates/Event dispatcher ~~~~~//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTileRevealed, AIslandTile*, Tile);


UCLASS()
class ISLAND_PROTOTYPE_API AIslandTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIslandTile(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	bool IsCamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	TArray<AIslandTile*> PathTo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Path")
	TArray<AIslandPath*> Paths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	TArray<AIslandTile*> HiddenPathTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	TArray<AIslandPerson*> PeopleOnTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	FVector PeopleLocationDisplacement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	bool bTileHidden;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	bool bTileExplored;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	bool TileCanBeBypassed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	bool Selected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	FST_Card TileCard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	TArray<FString> CompletedEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	TArray<FString> CardsAllowed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
	UStaticMeshComponent* MoveToIndicatorMesh;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
	//UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathing")
	int32 DistanceFromSelectedPerson;

	// Dynamic material for param

	// Food stored. 


	/*********** FUNCTIONS **************/

	UFUNCTION(BlueprintCallable, Category = "Person")
	FVector PlacePerson(AIslandPerson* Person, bool Teleport, bool StoreInTile);

	UFUNCTION(BlueprintCallable, Category = "Person")
	void RemovePerson(AIslandPerson* Person);

	UFUNCTION(BlueprintCallable, Category = "Person")
	void UpdatePersonPlacements();

	UFUNCTION(BlueprintCallable, Category = "Tile")
	TArray<FST_Action> GetTileAvailableActions(AIslandPerson* Person);

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void PerformTileAction(AIslandPerson* ByPerson, FST_Action Action);

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void ShowTile();

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void HideTile();

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void CheckTile();

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void SelectTile();

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void DeselectTile();

	//UFUNCTION(BlueprintNativeEvent, Category = "Tile")
	//void OnTileRevealed();
	//virtual void OnTileRevealed_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void TileClicked(AActor* TouchedActor, FKey ButtonPressed);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void TileHoverBegin(class UPrimitiveComponent* pComponent);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void TileHoverEnd(class UPrimitiveComponent* pComponent);


	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnAnyTileClicked(AIslandTile* Tile);

public:


	/*********** DELEGATES **************/

	UPROPERTY(BlueprintAssignable, Category = "Tile")
	FTileRevealed OnTileRevealed;


	/*********** OVERRIDES **************/

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// OnConstruction
	virtual void OnConstruction(const FTransform& Transform) override;


};
