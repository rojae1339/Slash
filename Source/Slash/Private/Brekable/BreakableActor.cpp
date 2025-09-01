// Fill out your copyright notice in the Description page of Project Settings.


#include "Brekable/BreakableActor.h"

#include "GeometryCollection/GeometryCollectionComponent.h"


// Sets default values
ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	SetRootComponent(GeometryCollection);
	GeometryCollection->SetGenerateOverlapEvents(true);
	GeometryCollection->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

void ABreakableActor::GetHit_Implementation(const FVector& ImpactPoint)
{
	
}

void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

