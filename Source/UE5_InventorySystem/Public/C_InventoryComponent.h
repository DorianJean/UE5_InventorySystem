// Copyright (C) 2025 Dorian Kupfernagel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_InventoryItemInfo.h"
#include "C_InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItemTypes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item Type")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	int32 SlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item Type")
	TSoftObjectPtr<UC_InventoryItemInfo> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	UC_InventoryComponent* InventoryRef;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotChanged, FInventoryItemTypes, Slot);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_INVENTORYSYSTEM_API UC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_InventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaxInventoryAmount = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryItemTypes> InventoryItemList;


	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnSlotChanged OnSlotChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	bool C_IsSlotEmpty(FInventoryItemTypes Slot);

	UFUNCTION(BlueprintPure)
	bool C_IsSlotNotEmpty(FInventoryItemTypes Slot);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory|Getter / Setter")
	FInventoryItemTypes SetQuantityAtSlot(FInventoryItemTypes TargetSlot, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory|Getter / Setter")
	void SetItem(FInventoryItemTypes TargetSlot, FInventoryItemTypes Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory|Transfer")
	void SwapIndexes(FInventoryItemTypes Slot, FInventoryItemTypes SwapWithSlot);

	UFUNCTION(BlueprintPure, Category = "Inventory|Getter / Setter")
	bool GetSlotIndex(int32 Index, FInventoryItemTypes& Slot);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void NotifySlotChanged(FInventoryItemTypes Slot);


	UFUNCTION(BlueprintCallable, Category = "Inventory|Search")
	bool FindEmptySlot(FInventoryItemTypes& Slot, int32& Index);

	UFUNCTION(BlueprintCallable)
	void SetupSlots(int32 NewInventorySlots);

		
};
