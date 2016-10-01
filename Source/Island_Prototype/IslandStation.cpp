// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandDataHolder.h"
#include "IslandPerson.h"
#include "Task/Task.h"
#include "IslandGameInstance.h"
#include "IslandStation.h"


// Sets default values
AIslandStation::AIslandStation(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//~~ Root component ~~//
	USceneComponent* const TranslationComp = CreateDefaultSubobject<USceneComponent>(TEXT("StationScene"));
	TranslationComp->Mobility = EComponentMobility::Movable;
	RootComponent = TranslationComp;

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
UTask* AIslandStation::GetTask()
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


/******************** WorkStation *************************/
float AIslandStation::WorkStation(AIslandPerson* Person, float AmountTime)
{
	float _Progress = 0.f;
	if (!CurrentTask)
	{
		ResetTask();
	}
	if (CurrentTask)
	{
		_Progress = CurrentTask->WorkTask(Person, AmountTime);
		if (_Progress >= 1)
		{
			CompleteTask();
		}
		else 
		{ 
			Person->CurrentState = EPersonState::Working;
			Person->bIsWorking = true;
		}
	}
	return _Progress;
}

/******************** CompleteTask *************************/
void AIslandStation::CompleteTask()
{
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		for (auto& Person : PeopleStationed)
		{
			if (Person)
			{
				Person->CurrentState = EPersonState::Awaiting;
				Person->bIsWorking = false;
			}
		}

		GameInstance->OnTaskCompleted.Broadcast(CurrentTask, this);
		
		//FST_Outcome Outcome = GameInstance->GetOutcome(CurrentTask, PeopleStationed, TArray<FST_Modifier>());

		ResetTask();


	}
	// Get new copy of base task
	//ResetTask() wait for modal choice to reset task
}

/******************** ResetTask *************************/
void AIslandStation::ResetTask()
{
	// Destroy task
	if (CurrentTask)
	{
		//CurrentTask->ConditionalBeginDestroy(); // Do I need this, or will the garbage collector notice that no now is reference to it?
		CurrentTask = nullptr;
	}
	// Make new
	CurrentTask = NewObject<UTask>();
	if (CurrentTask)
	{
		CurrentTask->Data = StationRowData.Task;
	}
}

// Called when the game starts or when spawned
void AIslandStation::BeginPlay()
{
	Super::BeginPlay();
	
	LoadStationData();
	ResetTask();
}

// Called every frame
void AIslandStation::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

