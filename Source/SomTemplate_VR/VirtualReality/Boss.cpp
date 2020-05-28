// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "Boss.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "ConstructorHelpers.h"
#include "Projectile.h"
#include "Math/UnrealMathUtility.h"
#include "UserConstant.h"

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
		Body->SetRelativeLocation(FVector(0.0f, 0.0f, 10000.0f));
		Body->SetWorldScale3D(FVector(5.f));
	}

	Boss_MaxHP = 10000;
	Boss_CurrentHP = 10000;

	Pattern_1_timer = 0.0;
	Pattern_2_timer = 0.0;
	Pattern_3_timer = 0.0;
	Pattern_4_timer = 0.0;

	Pattern_2_Windmill_Rotation = 10;

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
	Pattern_1_timer += DeltaTime;
	Pattern_2_timer += DeltaTime;
	Pattern_3_timer += DeltaTime;
	Pattern_4_timer += DeltaTime;
	/*
	if (Boss_CurrentHP > 7000 && Pattern_1_timer > 1)
	{
		Pattern_1();
		Pattern_1_timer = 0.0;
	}*/

	if (Boss_CurrentHP > 7000 && Pattern_2_timer > 0.3)
	{
		Pattern_2();
		Pattern_2_timer = 0.0;
	}
		
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
	UE_LOG(LogTemp, Warning, TEXT("Boss Pattern_1 start"));
	FActorSpawnParameters SpawnParams;


	if (Pattern_1_Projectile)
	{
		FVector MuzzleLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(Offset);

		UWorld* World = GetWorld();
		if (World)
		{
			AProjectile* Projectile[PATTERN_1_PROJECTILE_NUM * PATTERN_1_PROJECTILE_NUM];
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			for (int i = 0; i < PATTERN_1_PROJECTILE_NUM; i++)
			{
				for (int j = 0; j < PATTERN_1_PROJECTILE_NUM; j++)
				{
					if (!(i == 0 && (j == 0 || j == 7)))
					{
						Projectile[i * 8 + j] = World->SpawnActor<AProjectile>(Pattern_1_Projectile, MuzzleLocation, GetActorRotation() + FRotator(45.0f * i, 360.0f / PATTERN_1_PROJECTILE_NUM * j, 0.0f), SpawnParams);
						if (Projectile[i * 8 + j])
						{
							FVector LaunchDirection = Projectile[i * PATTERN_1_PROJECTILE_NUM + j]->GetActorRotation().Vector();
							Projectile[i * PATTERN_1_PROJECTILE_NUM + j]->FireInDirection(LaunchDirection);
						}
					}
				}
			}
			
		} // if (World)
	}

}

void ABoss::Pattern_2()
{
	UE_LOG(LogTemp, Warning, TEXT("Boss Pattern_2 start"));
	FActorSpawnParameters SpawnParams;


	// Rain Pattern
	if (Pattern_2_Rain_Projectile)
	{
		//FVector MuzzleLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(Offset);

		UWorld* World = GetWorld();
		if (World)
		{
			AProjectile* Rain_Projectile[PATTERN_2_RAIN_PROJECTILE_NUM];
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			

			for (int i = 0; i < PATTERN_2_RAIN_PROJECTILE_NUM; i++)
			{	
				int Rain_x = FMath::RandRange(-20000, 20000);
				int Rain_y = FMath::RandRange(-20000, 20000);
				Rain_Projectile[i] = World->SpawnActor<AProjectile>(Pattern_2_Rain_Projectile, FVector(Rain_x, Rain_y, 20000.0f), GetActorRotation() + FRotator(-90.0f, 0.0f, 0.0f), SpawnParams);
				if (Rain_Projectile[i])
				{
					FVector LaunchDirection = Rain_Projectile[i]->GetActorRotation().Vector();
					Rain_Projectile[i]->FireInDirection(LaunchDirection);
				}
			}

		} // if (World)

		UE_LOG(LogTemp, Warning, TEXT("Boss Rain Projectile fire"));
	}


	// Windmill Pattern
	if (Pattern_2_Projectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boss Pattern_2 Windmill start"));
		FVector MuzzleLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(Offset);

		UWorld* World = GetWorld();
		if (World)
		{
			AProjectile* Projectile[PATTERN_2_WINDMILL_LAYER * PATTERN_2_WINDMILL_PROJECTILE_NUM];
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			for (int n = 0; n < PATTERN_2_WINDMILL_LAYER; n++)
			{
				for (int i = 0; i < PATTERN_2_WINDMILL_PROJECTILE_NUM; i++)
				{
					Projectile[i] = World->SpawnActor<AProjectile>
						(Pattern_2_Projectile,
							MuzzleLocation + FVector(0.0f, 0.0f, PATTERN_2_WINDMILL_FIRSTLAYER_HEIGHT - ((PATTERN_2_WINDMILL_FIRSTLAYER_HEIGHT / 3) * n)),
							GetActorRotation() + FRotator(
								0.0f,
								360.0f / PATTERN_2_WINDMILL_PROJECTILE_NUM * i + Pattern_2_Windmill_Rotation,
								0.0f),
							SpawnParams);
					if (Projectile[i])
					{
						FVector LaunchDirection = Projectile[i]->GetActorRotation().Vector();
						Projectile[i]->FireInDirection(LaunchDirection);
					}
				}
			}
			

		} // if (World)

		Pattern_2_Windmill_Rotation += 10;
	}
}

void ABoss::Pattern_3()
{
}

void ABoss::Pattern_4()
{
}

void ABoss::Test()
{
	UE_LOG(LogTemp, Warning, TEXT("Boss Current Hp: %d\n"), Boss_CurrentHP);
}

