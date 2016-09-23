// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "IslandDataHolder.h"
#include "Bar.generated.h"

/**
 * 
 */

//Blueprintable
//BlueprintType

UCLASS(Blueprintable, BlueprintType)
class ISLAND_PROTOTYPE_API UBar : public UObject
{
	GENERATED_BODY()

public:
	UBar();
	~UBar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FST_Bar Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Percent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Max;

	UFUNCTION(BlueprintCallable, Category = "Data")
	void AddValue(float _Value);

	UFUNCTION(BlueprintCallable, Category = "Data")
	void UpdatePercent();


};
