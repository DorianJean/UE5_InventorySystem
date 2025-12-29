// Copyright (C) 2025 Dorian Kupfernagel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_InventoryItemInfo.h"
#include "C_InventoryComponent.generated.h"

// Struct representing a single inventory slot and its contents.
USTRUCT(BlueprintType)
struct FInventoryItemTypes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item Type")
	FName ItemID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	int32 Quantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	int32 SlotIndex = INDEX_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item Type")
	TSoftObjectPtr<UC_InventoryItemInfo> Item = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	UC_InventoryComponent* InventoryRef = nullptr;

};

// Delegate broadcast whenever an inventory slot changes.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotChanged, FInventoryItemTypes, Slot);

// Inventory component that manages item slots, quantities and slot - based item interactions.
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_INVENTORYSYSTEM_API UC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_InventoryComponent();

	// Maximum number of slots available in the inventory.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaxInventoryAmount = 20;

	// List containing all inventory slots and their data.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryItemTypes> InventoryItemList;

	// Event triggered when a slot changes.
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnSlotChanged OnSlotChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Checks whether a slot is empty.
	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool C_IsSlotEmpty(FInventoryItemTypes Slot);

	// Checks whether a slot is not empty.
	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool C_IsSlotNotEmpty(FInventoryItemTypes Slot);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	/** Sets the quantity of an item at a specific slot.
	 *  Returns the updated slot data.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Getter / Setter")
	FInventoryItemTypes SetQuantityAtSlot(FInventoryItemTypes TargetSlot, int32 Quantity);

	// Assigns an item to a slot.
	UFUNCTION(BlueprintCallable, Category = "Inventory|Getter / Setter")
	void SetItem(FInventoryItemTypes TargetSlot, FInventoryItemTypes Item);

	// Swaps the contents of two slots.
	UFUNCTION(BlueprintCallable, Category = "Inventory|Transfer")
	void SwapIndexes(FInventoryItemTypes Slot, FInventoryItemTypes SwapWithSlot);

	/** Retrieves the slot data at the given index.
	 *  Returns true if the index is valid.
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory|Getter / Setter")
	bool GetSlotIndex(int32 Index, FInventoryItemTypes& Slot);

	// Notifies listeners that a slot has changed.
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void NotifySlotChanged(FInventoryItemTypes Slot);

	// Finds the first empty slot in the inventory.
	UFUNCTION(BlueprintCallable, Category = "Inventory|Search")
	bool FindEmptySlot(FInventoryItemTypes& Slot, int32& Index);

	/** Initializes the inventory with a given number of slots.
	 *  Clears existing inventory data.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetupSlots(int32 NewInventorySlots);

	// Removes the item from the given slot index.
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItemFromIndex(int32 Index);

		
};
