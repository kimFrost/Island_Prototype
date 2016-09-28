// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandDataHolder.h"
#include "IslandPerson.h"
#include "IslandGameInstance.h"
#include "IslandStation.h"


// Sets default values
AIslandStation::AIslandStation(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


/******************** LoadStationData *************************/
void AIslandStation::LoadStationData()
{
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		static const FString ContextString(TEXT("StationLookup"));
		FST_Station* StationData = GameInstance->DATA_Stations->FindRow<FST_Station>(FName(*RowId), ContextString);
		if (StationData)
		{
			StationRowData = *StationData;
		}
	}
}

/******************** GetTask *************************/
FST_Task AIslandStation::GetTask()
{
	return CurrentTask;

	/*
	if (StationRowData.Task.bIsShareable)
	{
		return CurrentTask;
		//return TaskCache[0];
		// Get Task from cache
		//TArray<FST_Task> Keys;
		//TaskCache.GenerateKeyArray(Keys);
		//return TaskCache; // temp. only support one task
	}
	else
	{
		// Create new task and put in cache
		FST_Task Task = StationRowData.Task;
		TaskCache.Add(Task);
		return Task;
	}
	*/
	/*
	if (TaskCache.Contains(TaskId) && Task.bIsShareable)
	{
		// Return task ref from cache
		Task.Progress = TaskCache[TaskId];
		return Task;
	}
	else
	{
		FST_Task Task = StationRowData.Task;
		// Create new task and put in cache
		TaskCache.Add(TaskId, 0.f);
		return StationRowData.Task;
	}
	*/
}


/******************** WorkTask *************************/
float AIslandStation::WorkTask(AIslandPerson* Person, float AmountTime)
{
	if (CurrentTask.Progress < 1)
	{
		CurrentTask.Progress += AmountTime / CurrentTask.WorkTime;
		if (CurrentTask.Progress >= 1)
		{
			CompleteTask();
		}
	}
	else
	{
		Person->CurrentState = EPersonState::Waiting;
		Person->bIsWorking = false;
		// Task is already completed.
	}
	return CurrentTask.Progress;
}

/******************** CompleteTask *************************/
void AIslandStation::CompleteTask()
{
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OnTaskCompleted.Broadcast(CurrentTask, this);

		FST_Outcome Outcome = GameInstance->GetOutcome(CurrentTask, PeopleStationed, TArray<FST_Modifier>());


	}
	// Get new copy of base task
	//ResetTask() wait for modal choice to reset task
}

/******************** ResetTask *************************/
void AIslandStation::ResetTask()
{
	CurrentTask = StationRowData.Task;
}

// Called when the game starts or when spawned
void AIslandStation::BeginPlay()
{
	Super::BeginPlay();
	
	LoadStationData();
	CurrentTask = StationRowData.Task;
}

// Called every frame
void AIslandStation::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

