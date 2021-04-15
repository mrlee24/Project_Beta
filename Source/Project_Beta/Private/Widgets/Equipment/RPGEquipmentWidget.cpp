// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Equipment/RPGEquipmentWidget.h"
#include "Widgets/Equipment/RPGEquipmentSlotWidget.h"
#include "Components/RPGInventoryComponent.h"
#include "Components/RPGEquipmentComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void URPGEquipmentWidget::CreateEquipment_Implementation()
{
	TArray<UUserWidget*> WidgetSlots;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), WidgetSlots, URPGEquipmentSlotWidget::StaticClass(), false);

	for (int32 Index = 0; Index < WidgetSlots.Num(); Index++)
	{
		URPGEquipmentSlotWidget* ItemSlot = Cast<URPGEquipmentSlotWidget>(WidgetSlots[Index]);

		if (EquipmentComponent->GetEquipmentData()->Contains(ItemSlot->GetItemSlot()))
			SetEquipmentSlot(ItemSlot, *EquipmentComponent->GetEquipmentData()->Find(ItemSlot->GetItemSlot()));
	}
}

void URPGEquipmentWidget::SetEquipmentSlot(URPGEquipmentSlotWidget* EquipmentSlot_Widget, const FRPGItemData ItemData)
{
	EquipmentSlot_Widget->SetEquipment_Widget(this);
	EquipmentSlot_Widget->SetItemData(ItemData);
	EquipmentSlot_Widget->GetItem_Image()->SetBrush(ItemData.Thumbnail);
}

void URPGEquipmentWidget::SetFocusToSlot(const FRPGItemSlot InSlot)
{
	if (InventoryComponent->GetFocusedWidget() == EWidgetType::Equipment)
	{
		if (GetWidgetSlotByItemSlot(InSlot))
		{
			LastFocusedSlot = InSlot;
			GetWidgetSlotByItemSlot(InSlot)->SetUserFocus(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		}
	}
}

URPGEquipmentSlotWidget* URPGEquipmentWidget::GetWidgetSlotByItemSlot(const FRPGItemSlot InSlot) const
{
	TArray<UUserWidget*> WidgetSlots;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), WidgetSlots, URPGEquipmentSlotWidget::StaticClass(), false);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), WidgetSlots.Num()));

	for (int32 Index = 0; Index < WidgetSlots.Num(); Index++)
	{
		URPGEquipmentSlotWidget* ItemSlot = Cast<URPGEquipmentSlotWidget>(WidgetSlots[Index]);

		if (ItemSlot->GetItemSlot() == InSlot)
			return ItemSlot;
	}

	return nullptr;
}
