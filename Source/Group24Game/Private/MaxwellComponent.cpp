// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellComponent.h"

UMaxwellComponent::UMaxwellComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMaxwellComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UMaxwellComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FTransform Transform = PrimaryComponentTick.Target->GetOwner()->GetTransform();
	const UE::Math::TRotator Rotator = Transform.Rotator().Add(0,RotationSpeed*DeltaTime,0);
	Transform.SetRotation(Rotator.Quaternion());
	PrimaryComponentTick.Target->GetOwner()->SetActorTransform(Transform);
}

