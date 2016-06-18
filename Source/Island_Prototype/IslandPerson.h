// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "IslandDataHolder.h"
#include "IslandPerson.generated.h"


UCLASS()
class ISLAND_PROTOTYPE_API AIslandPerson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIslandPerson();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	TArray<EPersonState> States;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TArray<FST_Item> Backpack;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
