// Copyright (C) 2025 Dorian Kupfernagel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_InventoryAssetInterface.generated.h"

USTRUCT(BlueprintType)
struct FStackableResult
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isStackable = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StackSize = 1;

    FStackableResult() = default;

    FStackableResult(bool bStackable, int32 InSize)
        : isStackable(bStackable), StackSize(InSize)
    {}
};

// This class is used so that we can access the information from C_InventoryItemInfo without having to cast in Blueprints.
UINTERFACE(Blueprintable)
class UC_InventoryAssetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE5_INVENTORYSYSTEM_API IC_InventoryAssetInterface
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Asset Interface")
    FName GetItemID();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Asset Interface")
    FStackableResult IsItemStackable();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Asset Interface")
    UC_InventoryItemInfo* GetItemAsset();
};
