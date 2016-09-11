// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "Kismet/GameplayStatics.h"
#include "IslandGameInstance.h"
#include "IslandPath.h"
#include "IslandPlayerControllerBase.h"
#include "IslandTile.h"


// Sets default values
AIslandTile::AIslandTile(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DistanceFromSelectedPerson = 0;

	
	OnClicked.AddDynamic(this, &AIslandTile::TileClicked);

	//OnReleased
	//OnBeginCursorOver.AddDynamic(this, &AIslandTile::TileHoverBegin); // Build error 4.12
	//OnEndCursorOver.AddDynamic(this, &AIslandTile::TileHoverEnd); // Build error 4.12

	PeopleLocationDisplacement = FVector(300, 300, 50);

	bTileExplored = false;
	bTileHidden = true;
	bIsStart = false;
	bIsExit = false;
	bTileCanBeBypassed = false;

	bSelected = false;

	PathTo = TArray<AIslandTile*>();

	USceneComponent* const TranslationComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	TranslationComp->Mobility = EComponentMobility::Static;
	RootComponent = TranslationComp;

	//~~ BaseMesh ~~//
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>BaseMeshObj(TEXT("StaticMesh'/Game/Island/Meshes/Tile/tile.tile'"));
	if (BaseMeshObj.Succeeded())
	{
		BaseMesh->SetStaticMesh(BaseMeshObj.Object);
		BaseMesh->SetupAttachment(RootComponent); 
	}
	//BaseMesh->AttachParent = RootComponent;

	//BaseMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	//~~ Indicator ~~//
	MoveToIndicatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MoveToIndicatorMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MoveToIndicatorMeshObj(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	if (MoveToIndicatorMeshObj.Succeeded())
	{
		MoveToIndicatorMesh->SetStaticMesh(MoveToIndicatorMeshObj.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>MoveToIndicatorMaterialObj(TEXT("Material'/Game/Island/Materials/Indicator/M_Indicator.M_Indicator'"));
	if (MoveToIndicatorMaterialObj.Succeeded())
	{
		MoveToIndicatorMesh->SetMaterial(0, MoveToIndicatorMaterialObj.Object);
		MoveToIndicatorMesh->SetupAttachment(RootComponent);
	}

	MoveToIndicatorMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	MoveToIndicatorMesh->SetRelativeRotation(FRotator(180.f, 0.f, 0.f));
	MoveToIndicatorMesh->RelativeLocation = FVector(0, 0, 260);
	//MoveToIndicatorMesh->AttachParent = RootComponent;
	MoveToIndicatorMesh->SetVisibility(false);
	MoveToIndicatorMesh->SetCastShadow(false);
}


/******************** PlacePerson *************************/
FVector AIslandTile::PlacePerson(AIslandPerson* Person, bool Teleport, bool StoreInTile)
{
	int32 Index;
	FVector NewLocation;
	if (Person)
	{
		//~~ From from previous tile ~~//
		if (Person->TilePlacedOn)
		{
			Person->TilePlacedOn->RemovePerson(Person);
		}
		//~~ Add to new tile ~~//
		if (StoreInTile)
		{
			Index = PeopleOnTile.Add(Person);
			NewLocation = this->GetActorLocation() + (FVector(0, 500, 0) * Index) + PeopleLocationDisplacement;
			if (Teleport)
			{
				Person->SetActorLocation(NewLocation);
			}
			Person->TilePlacedOn = this;

		}
		// Get all steps/tiles pathto?
	}
	//return Index;
	return NewLocation;
}


/******************** ShowTile *************************/
void AIslandTile::ShowTile()
{
	if (bTileHidden)
	{
		RootComponent->SetVisibility(true, true);
		bTileHidden = false;

		OnTileRevealed.Broadcast(this);

		UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->OnTileRevealed.Broadcast(this);
		}

		//Paths.Num() // remove trees along path
	}
}


/******************** HideTile *************************/
void AIslandTile::HideTile()
{
	if (!bTileHidden)
	{
		RootComponent->SetVisibility(false, true);
		bTileHidden = true;
	}
}



/******************** OnTileRevealed *************************/
/*
void AIslandTile::OnTileRevealed_Implementation()
{
	// No logic here. Used for blueprint event binding
}
*/


/******************** CheckTile *************************/
void AIslandTile::CheckTile()
{
	if (!bTileExplored)
	{
		bTileExplored = true;
		ShowTile();

		for (int32 i = 0; i < Paths.Num(); i++)
		{
			AIslandPath* Path = Paths[i];
			if (Path)
			{
				Path->SetPathVisibility_Implementation(true);
				//Path->SetPathVisibility(true); //!! Won't work apparently
			}
		}
	}
}


/******************** RemovePerson *************************/
void AIslandTile::RemovePerson(AIslandPerson* Person)
{
	PeopleOnTile.Remove(Person);
	UpdatePersonPlacements();
}


/******************** UpdatePersonPlacements *************************/
void AIslandTile::UpdatePersonPlacements()
{
	for (int32 i = 0; i < PeopleOnTile.Num(); i++)
	{
		AIslandPerson* Person = PeopleOnTile[i];
		if (Person)
		{
			FVector NewLocation = this->GetActorLocation() + (FVector(50, 0, 0) * i) + PeopleLocationDisplacement;
			Person->SetActorLocation(NewLocation);
		}
	}
}


/******************** GetTileAvailableActions *************************/
TArray<FST_Action> AIslandTile::GetTileAvailableActions(AIslandPerson* Person)
{
	TArray<FST_Action> Actions;
	for (auto& Action : TileCard.Actions)
	{
		
	}

	Actions = TileCard.Actions;

	//?? Hidden path search? ??//


	// TileCard.Conditions

	// TileCard.NotConditions


	//CompletedEvents


	//~~ Parse string parameters $name etc. ~~//
	for (auto& Action : Actions)
	{
		for (auto& Event : Action.Events)
		{
			
		}
		//Action.Title.Replace();
	}

	return Actions;
}

/******************** PerformTileAction *************************/
void AIslandTile::PerformTileAction(AIslandPerson* ByPerson, FST_Action Action)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "AIslandTile:PerformTileAction");



	for (auto& Event : Action.Events)
	{
		//~~ Pick and find event in event datatable ~~//

		//~~ Parse string parameters $name etc. ~~//
	}

	/*
	switch (Action)
	{
		case ETileActions::DoNothing:
		{
			break;
		}
		case ETileActions::Explore:
		{
			// Items
			// Artifacts
			// Events
			// Hidden paths

			break;
		}
	}
	*/
}


/******************** SelectTile *************************/
void AIslandTile::SelectTile()
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue("Color", FLinearColor::Yellow);
		bSelected = true;
		MoveToIndicatorMesh->SetVisibility(true);
	}
}


/******************** DeselectTile *************************/
void AIslandTile::DeselectTile()
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue("Color", FLinearColor::Black);
		bSelected = false;
		MoveToIndicatorMesh->SetVisibility(false);
	}
}


/******************** TileClicked *************************/
void AIslandTile::TileClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "IslandTile::TileClicked");
	//UIslandGameInstance GameInstance = Cast<UIslandGameInstance>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		/*
		//~~ Select first person ~~//
		if (PeopleOnTile.Num() > 0)
		{
			GameInstance->OnPersonSelected.Broadcast(PeopleOnTile[0]);
			PeopleOnTile[0]->SelectPerson();
		}
		//~~ Else select nullptr ~~//
		else
		{
			GameInstance->OnPersonSelected.Broadcast(nullptr);
		}
		*/
		AIslandPlayerControllerBase* PlayerController = Cast<AIslandPlayerControllerBase>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			//PlayerController->CenterCameraAt(GetActorLocation());
		}
		GameInstance->OnTileClicked.Broadcast(this);
		SelectTile();
	}
}


/******************** TileHoverBegin *************************/
void AIslandTile::TileHoverBegin(UPrimitiveComponent* pComponent)
{

}


/******************** TileHoverEnd *************************/
void AIslandTile::TileHoverEnd(UPrimitiveComponent* pComponent)
{

}

/******************** OnAnyTileClicked *************************/
void AIslandTile::OnAnyTileClicked(AIslandTile* Tile)
{
	if (Tile != this)
	{
		DeselectTile();
	}
}


// Called when the game starts or when spawned
void AIslandTile::BeginPlay()
{
	Super::BeginPlay();
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OnTileClicked.AddDynamic(this, &AIslandTile::OnAnyTileClicked);
		//TileCard = GameInstance->GetRandCard(EIslandCardType::Tile);
	}
	//~~ Make the tile default hidden ~~//
	if (bTileHidden)
	{
		HideTile();
	}
	//~~ If any people placed on tile ~~//
	if (PeopleOnTile.Num() > 0)
	{
		CheckTile();
	}
}

// Called every frame
void AIslandTile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AIslandTile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UE_LOG(LogTemp, Warning, TEXT("Tile::OnConstruction"));


}