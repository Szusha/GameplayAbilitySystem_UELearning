// Coryright Szusha

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllers/AuraWidgetController.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "OverlayWidgetController.generated.h"


struct FAuraAbilityInfo;
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

class UAuraUserWidget;
class UAbilityInfo;
class UAuraAbilitySystemComponent;
struct FOnAttributeChangeData;


UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttrbuiteChangedSignature, float, NewValue);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature, const FAuraAbilityInfo&, Info);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttrbuiteChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttrbuiteChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttrbuiteChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttrbuiteChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FAbilityInfoSignature AbilityInfoDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|XP")
	FOnAttrbuiteChangedSignature OnXPPercentChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UAbilityInfo> AbilityInfo;

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

	void OnInitializeStartupAbilities(UAuraAbilitySystemComponent* AuraAbilitySystemComponent);

	void OnXPChanged(int32 NewXP);
};

template<typename T>
inline T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{ 
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
