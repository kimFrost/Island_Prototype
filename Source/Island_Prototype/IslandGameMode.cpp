// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandPerson.h"
#include "IslandGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "IslandPlayerControllerBase.h"

// Sets default values
AIslandGameMode::AIslandGameMode(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	TimeOfDay = 0.f;
	DayLength = 300.f;
	TimeTicking = false;
	TimeSpeed = 1.f;

	//~~ Set the default PlayerController ~~ //
	PlayerControllerClass = AIslandPlayerControllerBase::StaticClass();
}


void AIslandGameMode::SetTimeRate(float Rate)
{
	TimeSpeed = Rate;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), Rate);
	CustomTimeDilation = Rate;
}


void AIslandGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get every person
	bool AnyNotWorking = false;
	for (TActorIterator<AIslandPerson> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr)
		{
			if (ActorItr->CurrentState != EPersonState::Working)
			{
				// If not unasigned to station
				AnyNotWorking = true;
			}
		}
		if (!AnyNotWorking)
		{
			TimeOfDay = TimeSpeed * DeltaTime + TimeOfDay;
			OnTimeUpdated.Broadcast(TimeOfDay, DeltaTime);
		}
	}
}


void AIslandGameMode::BeginPlay()
{
	Super::BeginPlay();

}