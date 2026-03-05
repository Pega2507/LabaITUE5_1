// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGrabber.h"

// Sets default values for this component's properties
UPlayerGrabber::UPlayerGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle missing"));
	}


	APlayerController* PC = GetWorld()->GetFirstPlayerController();



	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PC->InputComponent)) //sprawdzenie czy cast sie udal
	{

		if (GrabAction)
		{
			EIC->BindAction(GrabAction, ETriggerEvent::Started, this, &UPlayerGrabber::Use);
		}

	}

}


// Called every frame
void UPlayerGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector Start;
		FVector End;
		FRotator CamerRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, CamerRotation);
		End = Start + CamerRotation.Vector() * GrabRange;

		PhysicsHandle->SetTargetLocationAndRotation(End, CamerRotation);


	}

	// ...
}

void UPlayerGrabber::Use()
{
	if (PhysicsHandle)
	{
		if (PhysicsHandle->GetGrabbedComponent())
		{
			Release();
		}
		else
		{
			Grab();
		}
	}

}

void UPlayerGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("UPlayerGrabber::Grab"));

	FVector Start;
	FVector End;
	FRotator CamerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, CamerRotation);
	End = Start + CamerRotation.Vector() * 200.0f;

	FHitResult Result;
	GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECollisionChannel::ECC_Visibility); 

	//DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 5.0f, 0, 5.0f); //dla debugowania

	if (UPrimitiveComponent* PC = Result.GetComponent())
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabbed: %s"), *PC->GetName());

		if (PhysicsHandle)
		{
			//PC->GetComponentLocation() - lapie za pivot point na meshu, Result.Location za miejsce na ktore patrzymy
			PhysicsHandle->GrabComponentAtLocationWithRotation(PC, NAME_None, Result.Location, CamerRotation);
		}
	}

}

void UPlayerGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();



}
