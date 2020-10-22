// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "PlatformTrigger.h"


AMovingPlatform::AMovingPlatform() 
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() 
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }

    GlobalStartLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::AddActiveTrigger()
{
    
}

void AMovingPlatform::RemoveActiveTrigger()
{
    
}

void AMovingPlatform::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    if (HasAuthority())
    {
        for (APlatformTrigger* TempTrigger : Triggers)
        {
            if (TempTrigger != nullptr)
            {
                if (TempTrigger->IsActivated())
                {
                    bActivated = true;
                    break;
                }
                bActivated = false;
            }
        }
        if (bActivated == true)
        {
            FVector Location = GetActorLocation();
            float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
            float JourneyTravelled = (Location - GlobalStartLocation).Size();

            if (JourneyTravelled > JourneyLength)
            {
                FVector Swap = GlobalStartLocation;
                GlobalStartLocation = GlobalTargetLocation;
                GlobalTargetLocation = Swap;
            }
            FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
            Location += MovingSpeed * DeltaTime * Direction;
            SetActorLocation(Location);
        }
    }
}
