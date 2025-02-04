// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Attribute/PCAttributeBarWidget.h"

void UPCAttributeBarWidget::SetupWidget(AActor* NewOwner)
{
	AttributeOwner = NewOwner;
}

void UPCAttributeBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}
