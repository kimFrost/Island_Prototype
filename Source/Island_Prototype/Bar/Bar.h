// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Bar.generated.h"

/**
 * 
 */

UCLASS()
class ISLAND_PROTOTYPE_API UBar : public UObject
{
	GENERATED_BODY()

public:
	UBar();
	~UBar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString BarValue;
};
