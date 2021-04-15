// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/RPGInventoryNotifyWidget.h"

void URPGInventoryNotifyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StopAnim();
	PlayAnim();
}

FText URPGInventoryNotifyWidget::UpdateMessage() const
{
	return Message;
}
