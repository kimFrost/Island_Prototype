// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "IslandDataHolder.h"
#include "Bar/Bar.h"
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
	AIslandPerson(const FObjectInitializer &ObjectInitializer);

	//~~ DATA ~~//

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString FirstName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString LastName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FST_TaskDone> TasksDoneThisTurn;

	// Task cache for personal tasks, that cannot be shared with other. Etc excerise, improving self. 
	//TMap<FString, float> TaskCache;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FST_Task> TaskCache;

	//~~ Bars ~~//

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	//FST_Bar Stress;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	//FST_Bar Entertainment;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Task")
	UBar* Stress;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Task")
	UBar* Entertainment;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	//FST_Task& TaskWorkingOn = FST_Task();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	bool bIsWorking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	EPersonState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	TArray<EPersonStateOld> States;

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
	void Die(ECause Cause);

	UFUNCTION(BlueprintCallable, Category = "Person")
	void TakeHPDamage(ECause Cause, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Person")
	void RegenHP(ERegenCause Cause, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Person")
	void ProcessStates();

	UFUNCTION(BlueprintCallable, Category = "Person")
	void AlterBar(EPersonBar Bar, float Value);


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
	void PersonClicked(AActor* TouchedActor, FKey ButtonPressed);

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

	virtual void OnConstruction(const FTransform& Transform) override;
	
	
};
