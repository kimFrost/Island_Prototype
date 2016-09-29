// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "IslandDataHolder.h"
#include "Task.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class AIslandPerson;


//Blueprintable
//BlueprintType

UCLASS(Blueprintable, BlueprintType)
class ISLAND_PROTOTYPE_API UTask : public UObject
{
	GENERATED_BODY()

public:
	UTask();
	~UTask();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FST_Task Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	float Progress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	float Timeleft;

	TArray<AIslandPerson*> PeopleWorkedOnTask;

	UFUNCTION(BlueprintCallable, Category = "Task")
	void ResetTask();

	UFUNCTION(BlueprintCallable, Category = "Task")
	float WorkTask(AIslandPerson* Person, float AmountTime);
	
	UFUNCTION(BlueprintCallable, Category = "Task")
	void CompleteTask();

};
