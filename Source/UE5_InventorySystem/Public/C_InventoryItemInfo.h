// Copyright (C) 2025 Dorian Kupfernagel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/StaticMesh.h"
#include "C_InventoryAssetInterface.h"
#include "C_InventoryItemInfo.generated.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common UMETA(DisplayName = "Common"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary")
};

UCLASS()
class UE5_INVENTORYSYSTEM_API UC_InventoryItemInfo : public UPrimaryDataAsset, public IC_InventoryAssetInterface
{

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	TSubclassOf<AActor> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	int32 MaxQuantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	EItemRarity ItemRarity;

public:

	UFUNCTION(BlueprintCallable)
	bool isStackable();

	virtual FName GetItemID_Implementation() override;
	virtual FStackableResult IsItemStackable_Implementation() override;
	virtual UC_InventoryItemInfo* GetItemAsset_Implementation() override;
};
