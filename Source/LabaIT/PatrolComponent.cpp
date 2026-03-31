// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolComponent.h"

// Sets default values for this component's properties
UPatrolComponent::UPatrolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPatrolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UPatrolComponent::GetPoint()
{
	AActor* Point;
	if (!(CurrentPointIndex > (PatrolPoints.Num() - 1)))
	{
		Point = PatrolPoints[CurrentPointIndex];
		CurrentPointIndex = (CurrentPointIndex + 1);
		
	}
	else
	{
		CurrentPointIndex = 0;
		Point = PatrolPoints[CurrentPointIndex];
	}
	
	return Point;
}

FVector UPatrolComponent::GetPointLocation()
{
	AActor* Point = GetPoint();
	if (!Point)
	{
		UE_LOG(LogTemp, Warning, TEXT("PatrolComponent: Point is null"));
		return FVector::ZeroVector;
	}
	return Point->GetActorLocation();
}
