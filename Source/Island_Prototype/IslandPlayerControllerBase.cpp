// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandPlayerControllerBase.h"




#if WITH_EDITOR
/* Get Screen Percentage */
static const auto CVarScreenPercentage = IConsoleManager::Get().FindTConsoleVariableDataFloat(TEXT("r.SCreenPercentage"));
#endif WITH_EDITOR

float AIslandPlayerControllerBase::GetObjectScreenRadius(AActor* InActor)
{
	float ScreenRadius;
	int32 Width, Height;
	FVector Viewlocation;
	FRotator ViewRotation; // Not Used, but required for Function call
	float CamFOV = 90.0f; //TODO: Replace With Function that returns camera FOV
#if WITH_EDITOR
	float ScreenPerc = CVarScreenPercentage->GetValueOnGameThread() / 100.0f;
#endif WITH_EDITOR

	/* Get the size of the viewport, and the player cameras location. */
	GetViewportSize(Width, Height);
	GetPlayerViewPoint(Viewlocation, ViewRotation);

#if WITH_EDITOR
	/* Factor in Screen Percentage & Quality Settings */
	Width *= ScreenPerc;
	Height *= ScreenPerc;
#endif WITH_EDITOR

	/* Easy Way To Return The Size, Create a vector and scale it. Alternative would be to use FMath::Max3 */
	float SRad = FVector2D(Width, Height).Size();

	/* Get Object Bounds (R) */
	float BoundingRadius = InActor->GetRootComponent()->Bounds.SphereRadius;
	float DistanceToObject = FVector(InActor->GetActorLocation() - Viewlocation).Size();

	/* Get Projected Screen Radius */
	ScreenRadius = FMath::Atan(BoundingRadius / DistanceToObject);
	ScreenRadius *= SRad / FMath::DegreesToRadians(CamFOV);

	return ScreenRadius;
}


FBox2D AIslandPlayerControllerBase::GetObjectScreenBounds(AActor* InActor)
{
	//The Actor Bounds Point Mapping
	const FVector BoundsPointMapping[8] =
	{
		FVector(1, 1, 1),
		FVector(1, 1, -1),
		FVector(1, -1, 1),
		FVector(1, -1, -1),
		FVector(-1, 1, 1),
		FVector(-1, 1, -1),
		FVector(-1, -1, 1),
		FVector(-1, -1, -1)
	};
	//Get Actor Bounds    casting to base class, checked by template in the .h
	const FBox EachActorBounds = InActor->GetComponentsBoundingBox(false); /* All Components */

	//Center
	const FVector BoxCenter = EachActorBounds.GetCenter();

	//Extents
	const FVector BoxExtents = EachActorBounds.GetExtent();

	// Build 2D bounding box of actor in screen spacesa
	FBox2D ActorBox2D(0);
	for (uint8 BoundsPointItr = 0; BoundsPointItr < 8; BoundsPointItr++)
	{
		// Project vert into screen space.
		//const FVector ProjectedWorldLocation = Project(BoxCenter + (BoundsPointMapping[BoundsPointItr] * BoxExtents));
		FVector2D ProjectedWorldLocation;
		ProjectWorldLocationToScreen(BoxCenter + (BoundsPointMapping[BoundsPointItr] * BoxExtents), ProjectedWorldLocation);

		// Add to 2D bounding box
		ActorBox2D += FVector2D(ProjectedWorldLocation.X, ProjectedWorldLocation.Y);
	}
	return ActorBox2D;
}