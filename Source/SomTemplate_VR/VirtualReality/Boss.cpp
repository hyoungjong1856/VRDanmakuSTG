// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "Boss.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Body->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BossBodyAsset(TEXT
	("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));

	if (BossBodyAsset.Succeeded())
	{
		Body->SetStaticMesh(BossBodyAsset.Object);
		Body->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Body->SetWorldScale3D(FVector(5.f));
	}
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

