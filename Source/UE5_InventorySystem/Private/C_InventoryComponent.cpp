// Copyright (C) 2025 Dorian Kupfernagel. All Rights Reserved.


#include "C_InventoryComponent.h"

// Sets default values for this component's properties
UC_InventoryComponent::UC_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UC_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UC_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FInventoryItemTypes UC_InventoryComponent::SetQuantityAtSlot_Implementation(FInventoryItemTypes TargetSlot, int32 Quantity)
{
	FInventoryItemTypes SlotItem;
	return SlotItem;
}

void UC_InventoryComponent::SetItem(FInventoryItemTypes TargetSlot, FInventoryItemTypes Item)
{
	InventoryItemList[TargetSlot.SlotIndex] = Item;

	FInventoryItemTypes NewItem = InventoryItemList[TargetSlot.SlotIndex];
	NewItem.SlotIndex = TargetSlot.SlotIndex;
	NewItem.InventoryRef = this;
	InventoryItemList[TargetSlot.SlotIndex] = NewItem;

	NotifySlotChanged(NewItem);
}

void UC_InventoryComponent::SwapIndexes(FInventoryItemTypes Slot, FInventoryItemTypes SwapWithSlot)
{
	SetItem(Slot, SwapWithSlot);

	SwapWithSlot.InventoryRef->SetItem(SwapWithSlot, Slot);
}

bool UC_InventoryComponent::C_IsSlotEmpty(FInventoryItemTypes Slot)
{
	return !Slot.Item.IsValid();
}

bool UC_InventoryComponent::C_IsSlotNotEmpty(FInventoryItemTypes Slot)
{
	return !C_IsSlotEmpty(Slot);
}

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

void UC_InventoryComponent::NotifySlotChanged(FInventoryItemTypes Slot)
{
	OnSlotChanged.Broadcast(Slot);
}

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

