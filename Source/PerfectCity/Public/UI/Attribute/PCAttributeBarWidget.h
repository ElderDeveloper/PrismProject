// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PCAttributeBarWidget.generated.h"


UCLASS()
class PERFECTCITY_API UPCAttributeBarWidget : public UUserWidget
{
	GENERATED_BODY()

	void SetupWidget(AActor* NewOwner);

protected:
	UPROPERTY()
	AActor* AttributeOwner;

	virtual void NativeConstruct() override;
};
