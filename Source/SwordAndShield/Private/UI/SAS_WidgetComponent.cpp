// Copyright Gift Wrapped Odity


#include "UI/SAS_WidgetComponent.h"

#include "AbilitySystem/SAS_AbilitySystemComponent.h"
#include "AbilitySystem/SAS_AttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/SAS_BaseCharacter.h"
#include "UI/SAS_AttributeWidget.h"

void USAS_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	// Set Weak pointers, but it's possible that instances are not yet initialized correctly
	InitAbilitySystemData();
	
	if (!IsASCInitialized())
	{
		//Bind to delegate and set callback
		SasCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
		return;
	}
	
	InitializeAttributeDelegate();
}

void USAS_WidgetComponent::InitAbilitySystemData()
{
	SasCharacter = Cast<ASAS_BaseCharacter>(GetOwner());
	AbilitySystemComponent = Cast<USAS_AbilitySystemComponent>(SasCharacter->GetAbilitySystemComponent());
	AttributeSet = Cast<USAS_AttributeSet>(SasCharacter->GetAttributeSet());
}

bool USAS_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void USAS_WidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributesInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanges);
	} else
	{
		BindToAttributeChanges();
	}
}


/**
 * Dynamic callback for when ASC has been initialized by characters (@SAS_BaseCharacter)
 * @param ASC 
 * @param AS 
 */
void USAS_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<USAS_AbilitySystemComponent>(ASC);
	AttributeSet = Cast<USAS_AttributeSet>(AS);
	
	if (!IsASCInitialized()) return;
	InitializeAttributeDelegate();
}

/**
 * Listens for changes for any attribute in AttributeSet
 */
void USAS_WidgetComponent::BindToAttributeChanges()
{
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair); // for checking the owned widget object
		
		// Case where we need to loop over child widget instances
		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanges(ChildWidget, Pair);
		});
	}
}

/**
 * Util to find a matching custom Widget and bind it to attribute changes
 * 
 * @param WidgetObject 
 * @param Pair 
 */
void USAS_WidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	USAS_AttributeWidget* AttributeWidget = Cast<USAS_AttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget)) return; // We only care about SAS Attribute Widgets
	if (!AttributeWidget->MatchesAttributes(Pair)) return; // Only subscribe for mathcing attributes
	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get()); // for Initial values
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, &Pair](const FOnGameplayAttributeValueChange& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get()); // for attribute updates during the game
	});
}




