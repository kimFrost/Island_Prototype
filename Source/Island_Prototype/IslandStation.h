// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "IslandDataHolder.h"
#include "IslandPerson.h"
#include "IslandStation.generated.h"

UCLASS()
class ISLAND_PROTOTYPE_API AIslandStation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIslandStation(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	TArray<AIslandPerson*> PeopleStationed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	FST_Station StationRowData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	FString RowId;

	//TMap<AIslandPerson*, FST_Task> WorkingTasks;
	//TMap<FST_Task, TArray<AIslandPerson*>> WorkingTasks;

	// Should a working task always be stored in TaskCache?? Yes, prop

	// Cache for task that can be shared across people. Used both for single- and multitasking. Etc building a product.
	//TMap<FString, float> TaskCache;0
	//TMap<FST_Task, float> TaskCache;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	//TArray<FST_Task> TaskCache;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	FST_Task CurrentTask;

	UFUNCTION(BlueprintCallable, Category = "Data")
	void LoadStationData();

	UFUNCTION(BlueprintCallable, Category = "Task")
	FST_Task GetTask(); // Only support one task for now

	UFUNCTION(BlueprintCallable, Category = "Task")
	float WorkTask(AIslandPerson* Person, float AmountTime); //returns progress

	UFUNCTION(BlueprintCallable, Category = "Task")
	void CompleteTask();

	UFUNCTION(BlueprintCallable, Category = "Task")
	void ResetTask();
	

	//void CompleteTask();

	//void CancelTask(); 


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
