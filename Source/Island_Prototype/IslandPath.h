// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "IslandPath.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class AIslandTile;



UCLASS()
class ISLAND_PROTOTYPE_API AIslandPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIslandPath();

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	AIslandTile* TileA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	AIslandTile* TileB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	int32 NumOfIntersections;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	bool bOneWay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	bool bSecret;

	UPROPERTY(BlueprintReadOnly, Category = "Path")
	bool bVisible;


	//UFUNCTION(BlueprintNativeEvent, Category = "Path")
	UFUNCTION(BlueprintImplementableEvent, Category = "Path")
	void SetPathVisibility(bool Visible);
	virtual void SetPathVisibility_Implementation(bool Visible);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void PreEditChange(UProperty* PropertyThatWillChange) override;
	
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	virtual void OnConstruction(const FTransform& Transform) override;


};
