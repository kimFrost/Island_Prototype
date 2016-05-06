// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "IslandPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class ISLAND_PROTOTYPE_API AIslandPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
	
	
public:
	UFUNCTION(BlueprintPure, Category = "Hud")
	float GetObjectScreenRadius(AActor* InActor);

};
