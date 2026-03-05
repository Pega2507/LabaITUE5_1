// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "PlayerGrabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABAIT_API UPlayerGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void Use();
	void Grab();
	void Release();

private:

	UPROPERTY(EditAnywhere, Category = "Grab")
	float GrabRange = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Grab")
	UInputAction* GrabAction;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
};
