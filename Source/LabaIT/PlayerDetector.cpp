// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDetector.h"

// Sets default values for this component's properties
UPlayerDetector::UPlayerDetector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerDetector::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerDetector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (Player)
	{
		FVector OwnerLocation = GetOwner()->GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();
		float DistanceToPlayer = FVector::Distance(OwnerLocation, PlayerLocation);

		

		if (DistanceToPlayer <= DetectionRange)
		{
			UE_LOG(LogTemp, Warning, TEXT("UPlayerDetector::TickComponent - Player in Detection Range"));
			FHitResult Seen;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(GetOwner());
			bool bHit = GetWorld()->LineTraceSingleByChannel(Seen, OwnerLocation, PlayerLocation, ECollisionChannel::ECC_Pawn, Params);

			//for debugging purpouses
			DrawDebugLine(GetWorld(), OwnerLocation, PlayerLocation, FColor::Red, false, 0, 0, 2);
			if (bHit) { UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), *Seen.GetActor()->GetName()); }
			//*********


			if (bHit && Seen.GetActor() == Player)
			{
				//for debugging purpouses
				UE_LOG(LogTemp, Warning, TEXT("UPlayerDetector::TickComponent - Player Visible"));
				DrawDebugLine(GetWorld(), OwnerLocation, PlayerLocation, FColor::Green, false, 0, 0, 2);
				//*********

				FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, PlayerLocation);

				FRotator CurrentRotation = GetOwner()->GetActorRotation();
				FRotator TargetZRotation = FRotator(0.f, TargetRotation.Yaw, 0.f); //Yaw - Z, Pitch - Y, Roll - X
				FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetZRotation, DeltaTime, RotationSpeed);

				GetOwner()->SetActorRotation(NewRotation);
			}
		}

	}


}

