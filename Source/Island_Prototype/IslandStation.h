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
	AIslandStation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	FST_Station StationRowData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	FString RowId;

	//TMap<AIslandPerson*, FST_Task> WorkingTasks;
	//TMap<FST_Task, TArray<AIslandPerson*>> WorkingTasks;

	// Should a working task always be stored in TaskCache?? Yes, prop

	// Cache for task that can be shared across people. Used both for single- and multitasking. Etc building a product.
	TMap<FString, float> TaskCache;

	UFUNCTION(BlueprintCallable, Category = "Data")
	void LoadStationData();

	UFUNCTION(BlueprintCallable, Category = "Task")
	FST_Task GetTask(AIslandPerson* Person, FString TaskId);

	//float WorkTask(AIslandPerson* Person, float Amount); returns progress

	//void CompleteTask();

	//void CancelTask();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
