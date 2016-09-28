// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "IslandDataHolder.h"
#include "IslandStation.h"
#include "IslandGameMode.generated.h"


//~~~~~ Delegates/Event dispatcher ~~~~~//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTimeUpdated, float, Time, float, TimeProgressed);



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

	//~~ TIME - var ~~//

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	float TimeOfDay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	float DayLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	bool TimeTicking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	float TimeSpeed;

	//~~ TIME - func ~~//

	UFUNCTION(BlueprintCallable, Category = "Time")
	void SetTimeRate(float Rate);

	//~~ TIME - delegates ~~//

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FTimeUpdated OnTimeUpdated;

	//~~ Overrides ~~//

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

};
