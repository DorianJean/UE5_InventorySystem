// Copyright (C) 2025 Dorian Kupfernagel. All Rights Reserved.


#include "C_InventoryItem.h"

// Sets default values
AC_InventoryItem::AC_InventoryItem()
{
	PrimaryActorTick.bCanEverTick = false;

	// Static Mesh Setup
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	// Skeletal Mesh Setup
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(StaticMesh);
}

void AC_InventoryItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_InventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

