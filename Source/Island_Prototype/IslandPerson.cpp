// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandGameInstance.h"
#include "IslandDataHolder.h"
#include "IslandPlayerControllerBase.h"
#include "IslandTile.h"
#include "IslandPath.h"
#include "IslandPerson.h"


// Sets default values
AIslandPerson::AIslandPerson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstName = "";
	LastName = "";

	UselessIndex = 0;

	MaxHP = 3;
	HP = 3;

	bEatenThisTurn = false;

	MovePointsLeft = 2;
	bIsSelected = false;

	OnClicked.AddDynamic(this, &AIslandPerson::PersonClicked);

	TilePlacedOn = nullptr;

	MoveTimeLine.SetTimelineLength(1);
	//~~ Timeline tick update ~~//
	FOnTimelineFloat MoveTimeFloatDelegate = FOnTimelineFloat();
	MoveTimeFloatDelegate.BindUFunction(this, "TimelineUpdate");
	//~~ Timeline post update event ~~//
	FOnTimelineEvent MoveTimeEventUpdate = FOnTimelineEvent();
	MoveTimeEventUpdate.BindUFunction(this, "MoveEnded");
	MoveTimeLine.SetTimelineFinishedFunc(MoveTimeEventUpdate);
	//~~ Animation curve ~~//
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveObj(TEXT("CurveFloat'/Game/Island/Util/Curves/MoveAnimCurve.MoveAnimCurve'"));
	if (CurveObj.Succeeded())
	{
		MoveCurve = CurveObj.Object;
		MoveTimeLine.AddInterpFloat(MoveCurve, MoveTimeFloatDelegate, FName("Percentage_Complete"));
	}
}



/******************** Eat *************************/
void AIslandPerson::Eat()
{
	bEatenThisTurn = true;
}

/******************** Die *************************/
void AIslandPerson::Die(ECause Cause)
{
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		FString CauseString;

		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECause"), true);
		if (!EnumPtr) CauseString = FString("Invalid");
		CauseString = EnumPtr->GetEnumName((int32)Cause);

		//~~ Remove self from asigned slot on station ~~//
		// I have no ref to station slot here...! What to do? I have a temp fix in blueprint binding to onDestroyed.

		// Remove from list of people // Or maybe just give them a death state
		GameInstance->People.Remove(this);
		GameInstance->AddTaskDone("%FIRSTNAME% dies from " + CauseString, this, EUsefulRating::Neutral, ETaskType::Work);
		this->Destroy();
	}
}

/******************** TakeDamage *************************/
void AIslandPerson::TakeDamage(ECause Cause, int32 Amount)
{
	HP -= Amount;
	if (HP <= 0)
	{
		HP = 0;
		Die(Cause);
	}
}

/******************** RegainHealth *************************/
void AIslandPerson::RegenHP(ERegenCause Cause, int32 Amount)
{
	HP += Amount;
	if (HP > MaxHP) HP = MaxHP;
}


/******************** ProcessStates *************************/
void AIslandPerson::ProcessStates()
{
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		if (bEatenThisTurn)
		{
			if (States.Contains(EPersonState::Starving))
			{
				States.Remove(EPersonState::Starving);
				States.Add(EPersonState::Hungry);
			}
			else if (States.Contains(EPersonState::Hungry))
			{
				States.Remove(EPersonState::Hungry);
			}
			else
			{
				RegenHP(ERegenCause::Satiated, 1);
			}
		}
		else
		{
			if (States.Contains(EPersonState::Starving))
			{
				TakeDamage(ECause::Stavation, 2);
				GameInstance->AddNotification("%FIRSTNAME% is starving!", this, ENotificationType::Warning);
			}
			else if (States.Contains(EPersonState::Hungry))
			{
				TakeDamage(ECause::Stavation, 1);
				States.Remove(EPersonState::Hungry);
				States.Add(EPersonState::Starving);
				GameInstance->AddNotification("%FIRSTNAME% is now starving", this, ENotificationType::Warning);
			}
			else
			{
				States.Add(EPersonState::Hungry);
				GameInstance->AddNotification("%FIRSTNAME% is hungry", this, ENotificationType::Warning);
			}
			if (HP <= 0)
			{
				Die(ECause::Stavation);
			}
		}
	}
}



/******************** TimelineUpdate *************************/
void AIslandPerson::TimelineUpdate(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, TEXT("EFFECT PROGRESS") + FString::SanitizeFloat(Value));
	FVector NewLocation = FMath::Lerp(MoveFromLocation, MoveToLocation, Value);
	SetActorLocation(NewLocation);
}


/******************** MoveEnded *************************/
void AIslandPerson::MoveEnded()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Timeline ended"));
	if (PathToTake.Num() > 0)
	{
		ExecuteMoveAlongPath();
	}
	else
	{
		if (TilePlacedOn)
		{
			TilePlacedOn->CheckTile();
			// Trigger tile modal
			UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
			if (GameInstance)
			{
				GameInstance->OnPersonMoveEnded.Broadcast(this, TilePlacedOn);
			}
		}
		UpdatePathingOptions(); // force update tiles in range
		//PersonState = EIslandPersonState::Idle;
	}
}


/******************** MoveTo *************************/
void AIslandPerson::MoveTo(AIslandTile* Tile) {
	if (Tile)
	{
		MoveFromLocation = GetActorLocation();
		//MoveToLocation = Tile->GetActorLocation();
		MoveToLocation = Tile->PlacePerson(this, false, true);
		//~~ Start animation timeline ~~//
		MoveTimeLine.PlayFromStart();
	}
}


/******************** PersonClicked *************************/
void AIslandPerson::PersonClicked(AActor* TouchedActor, FKey ButtonPressed) {
	//UE_LOG(LogTemp, Log, TEXT("pawn clicked"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "AIslandPerson:PersonClicked");
	/*
	AIslandPlayerController* PlayerController = Cast<AIslandPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
	PlayerController->CenterCameraAt(GetActorLocation());
	}
	*/
	if (TilePlacedOn)
	{
		TilePlacedOn->TileClicked(nullptr, ButtonPressed); // proberly not thre correct parameter
	}
	SelectPerson();
}


/******************** SelectPerson *************************/
void AIslandPerson::SelectPerson() {
	bIsSelected = true;
	UpdatePathingOptions();
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OnPersonSelected.Broadcast(this);
	}
	/*
	if (PersonMeshDynamicMaterial)
	{
		PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Yellow);
	}
	*/
}


/******************** UpdatePathingOptions *************************/
void AIslandPerson::UpdatePathingOptions() {
	if (TilePlacedOn)
	{
		// Deselect all tile
		for (TActorIterator<AIslandTile> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			AIslandTile* Tile = *ActorItr;
			Tile->DeselectTile();
			Tile->DistanceFromSelectedPerson = 9999;
		}

		TileRangeMap.Empty();
		TArray<AIslandTile*> VisitedTiles;
		TArray<AIslandTile*> Frontier;
		Frontier.Add(TilePlacedOn);
		TileRangeMap.Add(0, Frontier); //~~ Add base for the start ~~//
		VisitedTiles.Add(TilePlacedOn); //~~ Add base to allready visited to prevent bounce back ~~//

		TilePlacedOn->DistanceFromSelectedPerson = 0; //~~ set person distance to zero on base tile ~~//

		for (int32 k = 0; k < MovePointsLeft; k++)
		{
			TArray<AIslandTile*> NewFrontier;
			TileRangeMap.Add(k + 1, NewFrontier);
			Frontier = TileRangeMap[k];
			//~~ Loop though all tiles in current frontier ~~//
			for (int32 m = 0; m < Frontier.Num(); m++)
			{
				AIslandTile* Tile = Frontier[m];

				//~~ If tile has a gate/trap then prevent travel any further until its is open/disarmed ~~//
				if (Tile->TileCard.bBlockPath) {
					continue; //~~ Skip Tile ~~//
				}

				//~~ Loop though all Paths connected to this tile to create the next frontier ~~//
				for (int32 l = 0; l < Tile->Paths.Num(); l++)
				{
					AIslandPath* Path = Tile->Paths[l];
					//~~ Error handing in path pointer ~~//
					if (!Path->TileA || !Path->TileB || !Path->bVisible)
					{
						continue; //~~ Skip path ~~//
					}

					// If not oneway or if oneway and This til is A (A=>B)
					if ((Path->bOneWay && Path->TileA == Tile) || !Path->bOneWay)
					{
						AIslandTile* NeighbourTile = nullptr;
						if (Path->TileA == Tile)
						{
							NeighbourTile = Path->TileB;
						}
						else if (Path->TileB == Tile)
						{
							NeighbourTile = Path->TileA;
						}
						if (NeighbourTile)
						{
							if (NeighbourTile && !VisitedTiles.Contains(NeighbourTile))
							{
								NeighbourTile->DistanceFromSelectedPerson = k + 1;
								TileRangeMap[k + 1].Add(NeighbourTile); //~~ Add Neighbor tile to the next frontier ~~//
								VisitedTiles.Add(NeighbourTile); //~~ Add to visited, so that neighbors don't overlap each other. ~~//
							}
						}
					}
				}
				/*
				//~~ Loop though all pathto to create the next frontier ~~//
				for (int32 l = 0; l < Tile->PathTo.Num(); l++)
				{
				AIslandTile* NeighbourTile = Tile->PathTo[l];
				//~~ Check if add to next frontier ~~//
				if (NeighbourTile && !VisitedTiles.Contains(NeighbourTile))
				{
				NeighbourTile->DistanceFromSelectedPerson = k + 1;
				TileRangeMap[k + 1].Add(NeighbourTile); //~~ Add Neighbor tile to the next frontier ~~//
				VisitedTiles.Add(NeighbourTile); //~~ Add to visited, so that neighbors don't overlap each other. ~~//
				}
				}
				*/
			}

		}

		// Select tiles in range
		for (auto& Tiles : TileRangeMap)
		{
			for (int32 i = 0; i < Tiles.Value.Num(); i++)
			{
				AIslandTile* Tile = Tiles.Value[i];
				Tile->SelectTile();
			}
		}
	}
}


/******************** UpdateShortestPath *************************/
void AIslandPerson::UpdateShortestPath(AIslandTile* TargetTile) {
	if (TilePlacedOn && TargetTile)
	{
		PathToTake.Empty();
		int32 ShortestPathLength = 0;
		for (auto& Tiles : TileRangeMap)
		{
			if (Tiles.Value.Find(TargetTile) != -1)
			{
				ShortestPathLength = Tiles.Key;
				break;
			}
		}
		AIslandTile* Tile = TargetTile;
		for (int32 steps = 0; steps < ShortestPathLength; steps++)
		{
			for (int32 i = 0; i < Tile->Paths.Num(); i++)
			{
				AIslandPath* Path = Tile->Paths[i];
				if (!Path->TileA || !Path->TileB)
				{
					continue; //~~ Skip path ~~//
				}
				if ((Path->bOneWay && Path->TileB == Tile) || !Path->bOneWay)
				{
					AIslandTile* NeighbourTile = nullptr;
					if (Path->TileA == Tile)
					{
						NeighbourTile = Path->TileB;
					}
					else if (Path->TileB == Tile)
					{
						NeighbourTile = Path->TileA;
					}
					if (NeighbourTile)
					{
						if (NeighbourTile->DistanceFromSelectedPerson < Tile->DistanceFromSelectedPerson)
						{
							if (Tile->DistanceFromSelectedPerson > 0)
							{
								PathToTake.Insert(Tile, 0);
								Tile = NeighbourTile;
								i = -1; // Reset neighbour loop for new current tile
							}
							else
							{
								PathToTake.Insert(Tile, 0);
								// We are there
								break;
							}
						}
					}
				}
			}
			/*
			for (int32 i = 0; i < Tile->PathTo.Num(); i++)
			{
			AIslandTile* NeighbourTile = Tile->PathTo[i];
			//~~ If neighbour tile distance from person is lower than current tile ~~//
			if (NeighbourTile->DistanceFromSelectedPerson < Tile->DistanceFromSelectedPerson)
			{
			if (Tile->DistanceFromSelectedPerson > 0)
			{
			PathToTake.Insert(Tile, 0);
			Tile = NeighbourTile;
			i = -1; // Reset neighbour loop for new current tile
			}
			else
			{
			PathToTake.Insert(Tile, 0);
			// We are there
			break;
			}
			}
			}
			*/
		}
	}
}


/******************** ExecuteMoveAlongPath *************************/
void AIslandPerson::ExecuteMoveAlongPath()
{
	if (PathToTake.Num() > 0 && PathToTake[0])
	{
		//PersonState = EIslandPersonState::Moving;
		// Deselect all tile
		for (TActorIterator<AIslandTile> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			AIslandTile* Tile = *ActorItr;
			Tile->DeselectTile();
		}

		MoveFromLocation = GetActorLocation();
		MoveToLocation = PathToTake[0]->PlacePerson(this, false, true);
		PathToTake.RemoveAt(0);
		MovePointsLeft--; //~~ Decrease movement points per tile moved ~~//
		MoveTimeLine.PlayFromStart();
	}
}



/******************** OnAnyTileSelected *************************/
void AIslandPerson::OnAnyPersonSelected(AIslandPerson* Person)
{
	if (Person != this)
	{
		/*
		if (PersonMeshDynamicMaterial)
		{
			PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::White);
		}
		*/
		bIsSelected = false;
	}
}


/******************** OnNewTurn *************************/
/*
void AIslandPerson::OnNewTurn(float Turn)
{
	//~~ Parse person traits and their effects ~~//
	//ParseTraits();
	//UpdateStats();

	//~~ Reset needs ~~//

	//~~ Reset movement points ~~//
	MovePointsLeft = 2;


	if (bIsSelected)
	{
		UpdatePathingOptions();
	}
}
*/


void AIslandPerson::TimerExpired()
{
	if (TilePlacedOn)
	{
		TilePlacedOn->CheckTile();
	}
}


// Called when the game starts or when spawned
void AIslandPerson::BeginPlay()
{
	Super::BeginPlay();
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OnPersonSelected.AddDynamic(this, &AIslandPerson::OnAnyPersonSelected);
		//GameInstance->OnTurnSwitched.AddDynamic(this, &AIslandPerson::OnTurnSwitched);
		//GameInstance->OnNewTurn.AddDynamic(this, &AIslandPerson::OnNewTurn);
	}

	//~~ Timer used to prevent check being made before beginplay bidings is done on tile ~~//
	//FTimerHandle FuzeTimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AIslandPerson::TimerExpired, 1.f);
	/*
	if (TilePlacedOn)
	{
	TilePlacedOn->CheckTile();
	}
	*/

	//~~ Calc stats ~~//
	//ParseTraits();
	//UpdateStats();


	/*
	TimeLine.PlayFromStart();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AIslandPerson::TickTimeline, DELTATIME, true, 0.0f);
	*/
}



// Called every frame
void AIslandPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//~~ Tick timeline for movement ~~//
	if (MoveTimeLine.IsPlaying())
	{
		MoveTimeLine.TickTimeline(DeltaTime);
	}
}


// Called on spawn actor(PIE) and load actor
void AIslandPerson::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Warning, TEXT("AIslandPerson::PostInitializeComponents"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "AIslandPerson::PostInitializeComponents");
	/*
	if (PersonMeshMaterial)
	{
	PersonMeshDynamicMaterial = UMaterialInstanceDynamic::Create(PersonMeshMaterial, this);
	PersonMesh->SetMaterial(0, PersonMeshDynamicMaterial);
	PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Red);
	}
	*/
}

// Called to bind functionality to input
void AIslandPerson::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

