// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandDataHolder.h"
#include "IslandPerson.h"
#include "IslandGameInstance.h"
#include "IslandStation.h"


// Sets default values
AIslandStation::AIslandStation()
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
FST_Task AIslandStation::GetTask(AIslandPerson* Person, FString TaskId)
{
	FST_Task Task = StationRowData.Task;
	if (TaskCache.Contains(TaskId) && Task.bIsShareable)
	{
		Task.Progress = TaskCache[TaskId];
		return Task;
	}
	else
	{
		return StationRowData.Task;
	}
}


// Called when the game starts or when spawned
void AIslandStation::BeginPlay()
{
	Super::BeginPlay();
	
	LoadStationData();
}

// Called every frame
void AIslandStation::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

