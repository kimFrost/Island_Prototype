// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "IslandGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ISLAND_PROTOTYPE_API AIslandGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	// Sets default values for this's properties
	AIslandGameMode(const FObjectInitializer &ObjectInitializer);

	//~~ TIME ~~//

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	float TimeOfDay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	float DayLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	bool TimeTicking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	float TimeSpeed;
	
	//~~ Overrides ~~//

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

};
