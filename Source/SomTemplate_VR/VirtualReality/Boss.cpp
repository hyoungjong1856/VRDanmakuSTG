// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "Boss.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "ConstructorHelpers.h"
#include "Projectile.h"

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

	Boss_MaxHP = 10000;
	Boss_CurrentHP = 10000;

	// Test Input
	//InputComponent->BindAction("Test", IE_Pressed, this, &ABoss::Test);
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
/*
void ABoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}*/

int ABoss::GetBossMaxHp()
{
	return Boss_MaxHP;
}

int ABoss::GetBossCurrentHp()
{
	return Boss_CurrentHP;
}

void ABoss::SetBossCurrentHp(int hp)
{
	Boss_CurrentHP = hp;
}

void ABoss::Pattern_1()
{
	
	FActorSpawnParameters SpawnParams;


	if (ProjectileClass)
	{
		FVector MuzzleLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(Offset);
		FRotator MuzzleRotation = GetActorRotation();

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
				UE_LOG(LogTemp, Warning, TEXT("x:%f, y:%f, z:%f"), LaunchDirection.X, LaunchDirection.Y, LaunchDirection.Z);
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("Boss Normal Projectile fire"));
	}
}

void ABoss::Test()
{
	UE_LOG(LogTemp, Warning, TEXT("Boss Current Hp: %d\n"), Boss_CurrentHP);
}

