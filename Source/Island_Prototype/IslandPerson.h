// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "IslandDataHolder.h"
#include "IslandPerson.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class AIslandTile;


//~~~~~ ENUMS ~~~~~//


UCLASS()
class ISLAND_PROTOTYPE_API AIslandPerson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIslandPerson();

	//~~ DATA ~~//

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString FirstName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString LastName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FST_TaskDone> TasksDoneThisTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	TArray<EPersonState> States;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TArray<FST_Item> Backpack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	int32 UselessIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	int32 MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	bool bEatenThisTurn;

	UFUNCTION(BlueprintCallable, Category = "Person")
	void Eat();
	
	UFUNCTION(BlueprintCallable, Category = "Person")
	void Die(EDeathCause Cause);

	UFUNCTION(BlueprintCallable, Category = "Person")
	void TakeDamage(EDeathCause Cause, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Person")
	void RegenHP(ERegenCause Cause, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Person")
	void ProcessStates();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	bool bIsSelected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	AIslandTile* TilePlacedOn;

	TMap<int32, TArray<AIslandTile*>> TileRangeMap;

	FTimeline MoveTimeLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UCurveFloat* MoveCurve;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	FVector MoveFromLocation;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	FVector MoveToLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	int32 MovePointsLeft;

	UFUNCTION()
	void TimelineUpdate(float Value);
	
	UFUNCTION()
	void MoveEnded();

	TArray<AIslandTile*> PathToTake;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveTo(AIslandTile* Tile);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void PersonClicked();

	UFUNCTION(BlueprintCallable, Category = "Person")
	void SelectPerson();

	UFUNCTION(BlueprintCallable, Category = "Pathing")
	void UpdatePathingOptions();

	UFUNCTION(BlueprintCallable, Category = "Pathing")
	void UpdateShortestPath(AIslandTile* TargetTile);

	UFUNCTION(BlueprintCallable, Category = "Pathing")
	void ExecuteMoveAlongPath();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnAnyPersonSelected(AIslandPerson* Person);

	void TimerExpired();




	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
