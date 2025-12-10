// Copyright (C) 2025 Dorian Kupfernagel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_InventoryComponent.h"
#include "C_InventoryItem.generated.h"

UCLASS()
class UE5_INVENTORYSYSTEM_API AC_InventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_InventoryItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	int32 Quantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	UC_InventoryItemInfo* Item;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
