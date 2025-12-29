// Copyright (C) 2025 Dorian Kupfernagel. All Rights Reserved.


#include "C_InventoryComponent.h"

/**
 * Constructor.
 * Initializes the inventory component with default settings.
 * Disables ticking since the inventory does not require per-frame updates.
 */
UC_InventoryComponent::UC_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

/**
 * Called when the game starts.
 * Can be used to initialize runtime-only inventory logic.
 */
void UC_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

/**
 * Called every frame if ticking is enabled.
 * Currently unused as the inventory system is event-driven.
 */
void UC_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/**
 * Sets a new quantity for the given inventory slot.
 * Returns the updated slot data.
 */
FInventoryItemTypes UC_InventoryComponent::SetQuantityAtSlot(FInventoryItemTypes TargetSlot, int32 Quantity)
{
	if (Quantity == 0)
	{
		RemoveItemFromIndex(TargetSlot.SlotIndex);
		return InventoryItemList[TargetSlot.SlotIndex];
	}
	else
	{
		FInventoryItemTypes& Slot = InventoryItemList[TargetSlot.SlotIndex];
		Slot.Quantity = Quantity;

		NotifySlotChanged(Slot);
		return Slot;
	}
}


/**
 * Assigns an item to a specific inventory slot.
 * Automatically updates the slot index and inventory reference
 * and notifies listeners about the change.
 */
void UC_InventoryComponent::SetItem(FInventoryItemTypes TargetSlot, FInventoryItemTypes Item)
{
	InventoryItemList[TargetSlot.SlotIndex] = Item;

	FInventoryItemTypes NewItem = InventoryItemList[TargetSlot.SlotIndex];
	NewItem.SlotIndex = TargetSlot.SlotIndex;
	NewItem.InventoryRef = this;
	InventoryItemList[TargetSlot.SlotIndex] = NewItem;

	NotifySlotChanged(NewItem);
}

/**
 * Swaps the contents of two inventory slots.
 * Useful for drag-and-drop inventory interactions.
 */
void UC_InventoryComponent::SwapIndexes(FInventoryItemTypes Slot, FInventoryItemTypes SwapWithSlot)
{
	SetItem(Slot, SwapWithSlot);

	SwapWithSlot.InventoryRef->SetItem(SwapWithSlot, Slot);
}

// Checks whether the given slot is empty.
bool UC_InventoryComponent::C_IsSlotEmpty(FInventoryItemTypes Slot)
{
	return !Slot.Item.IsValid();
}

// Checks whether the given slot is not empty.
bool UC_InventoryComponent::C_IsSlotNotEmpty(FInventoryItemTypes Slot)
{
	return !C_IsSlotEmpty(Slot);
}

/**
 * Finds the first empty slot in the inventory.
 * Returns true if an empty slot was found.
 */
bool UC_InventoryComponent::FindEmptySlot(FInventoryItemTypes& Slot, int32& Index)
{
	for (int ItemStep = 0; ItemStep < InventoryItemList.Num(); ItemStep++)
	{
		if (C_IsSlotEmpty(InventoryItemList[ItemStep]))
		{
			Slot = InventoryItemList[ItemStep];
			Index = ItemStep;
			return true;
		}
	}
	return false;
}

/**
 * Broadcasts a slot change event.
 * Used to update UI or other systems listening for inventory changes.
 */
void UC_InventoryComponent::NotifySlotChanged(FInventoryItemTypes Slot)
{
	OnSlotChanged.Broadcast(Slot);
}

/**
 * Retrieves the slot data at the given index.
 * Returns true if the index is valid.
 */
bool UC_InventoryComponent::GetSlotIndex(int32 Index, FInventoryItemTypes& Slot)
{
	if (InventoryItemList.IsValidIndex(Index))
	{
		Slot = InventoryItemList[Index];
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * Initializes the inventory with a fixed number of empty slots.
 * Existing inventory data will be cleared.
 */
void UC_InventoryComponent::SetupSlots(int32 NewInventorySlots)
{
	MaxInventoryAmount = NewInventorySlots;

	InventoryItemList.Empty();

	for (int32 Slot = 0; Slot < MaxInventoryAmount; Slot++)
	{
		FInventoryItemTypes SlotToAdd;
		SlotToAdd.SlotIndex = Slot;
		SlotToAdd.InventoryRef = this;

		InventoryItemList.Add(SlotToAdd);
	}
}

/**
 * Removes the item at the specified slot index.
 * The slot will be reset to an empty state.
 */
bool UC_InventoryComponent::RemoveItemFromIndex(int32 Index)
{
	FInventoryItemTypes Slot;
	if (!GetSlotIndex(Index, Slot))
	{
		return false;
	}

	FInventoryItemTypes EmptyItem;
	EmptyItem.SlotIndex = Slot.SlotIndex;
	EmptyItem.InventoryRef = this;

	// Remove Item from Inventory Container
	SetItem(Slot, EmptyItem);

	return true;
}

