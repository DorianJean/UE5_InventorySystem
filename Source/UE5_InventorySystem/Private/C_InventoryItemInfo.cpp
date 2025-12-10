// Copyright (C) 2025 Dorian Kupfernagel. All Rights Reserved.


#include "C_InventoryItemInfo.h"

bool UC_InventoryItemInfo::isStackable()
{

	return MaxQuantity > 1;
}

FName UC_InventoryItemInfo::GetItemID_Implementation()
{
	return Name;
}

FStackableResult UC_InventoryItemInfo::IsItemStackable_Implementation()
{
	FStackableResult Result;
	Result.isStackable = isStackable();
	Result.StackSize = MaxQuantity;

	return Result;
}

UC_InventoryItemInfo* UC_InventoryItemInfo::GetItemAsset_Implementation()
{
	return this;
}
