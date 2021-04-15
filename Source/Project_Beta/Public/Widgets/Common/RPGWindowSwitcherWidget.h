// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "RPGTypes.h"
#include "RPGWindowSwitcherWidget.generated.h"

class URPGInventoryComponent;
class URPGCraftingComponent;
class URPGTabBaseWidget;
class URPGMainTabWidget;
class URPGVendorTabWidget;
class URPGStorageTabWidget;
class URPGLoadGameTabWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchWidgetTab, EWidgetType, TapToActivate);

UCLASS()
class PROJECT_BETA_API URPGWindowSwitcherWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	URPGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URPGCraftingComponent* CraftingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	UWidgetSwitcher* Tab_Switcher;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGMainTabWidget* MainTab_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGVendorTabWidget* VendorTab_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGStorageTabWidget* StorageTab_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true", BindWidget))
	URPGLoadGameTabWidget* LoadGameTab_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	EWidgetType ActiveTabType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	EWidgetType WidgetType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FLinearColor HoveredButtonColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FLinearColor UnHoveredButtonColor;

	UPROPERTY(BlueprintAssignable)
	FOnSwitchWidgetTab OnSwitchWidgetTab;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayConstructAnim();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopConstructAnim();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetActiveButtonStyle(const EWidgetType TabToActivate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SwitchWidgetTab(const EWidgetType TabToActivate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SwitchWidgetTo(const EWidgetType WidgetToActivate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemoveActiveWidget();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HoverButton(const EWidgetType WidgetToActivate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UnHoverButton(const EWidgetType WidgetToActivate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenNextWidget(const EWidgetType WidgetToActivate);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EventOnSwitchWidgetTab(const EWidgetType TabToActivate);

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	URPGTabBaseWidget* GetWidgetSwitcherPanel(const EWidgetType Index) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UButton* GetButtonByWidgetType(const EWidgetType CurrentWidget);
};
