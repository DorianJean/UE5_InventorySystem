// Copyright (C) 2025 Dorian Kupfernagel. All Rights Reserved.


#include "C_InventoryItem.h"

// Sets default values
AC_InventoryItem::AC_InventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_InventoryItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_InventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

