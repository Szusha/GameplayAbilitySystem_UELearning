// Copyright Szusha


#include "AbilitySystem/Abilities/AuraFireBlast.h"
#include "Actors/AuraFireBall.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"

FString UAuraFireBlast::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float Manacost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		// Title
		"<Title>FIRE BLAST</>\n\n"

		// Details
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//Description
		"<Default>Launches %d </>"
		"<Default>fire balls in all directions, each coming back and </>"
		"<Default>exploding upon return, causing </>"
		"<Damage>%d</><Default> radial fire damage with a chance to burn</>"),

		// Values
		Level, Manacost, Cooldown, NumFireBalls, ScaledDamage);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 NextLevel)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(NextLevel);
	const float Manacost = FMath::Abs(GetManaCost(NextLevel));
	const float Cooldown = GetCooldown(NextLevel);

	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL</>\n\n"

		// Details
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//Description
		"<Default>Launches %d </>"
		"<Default>fire balls in all directions, each coming back and </>"
		"<Default>exploding upon return, causing </>"
		"<Damage>%d</><Default> radial fire damage with a chance to burn</>"),

		// Values
		NextLevel, Manacost, Cooldown, NumFireBalls, ScaledDamage);
}

TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBalls()
{
	TArray<AAuraFireBall*> FireBalls;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFireBalls);

	for (const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());

		AAuraFireBall* FireBall = GetWorld()->SpawnActorDeferred<AAuraFireBall>(
			FireBallClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		FDamageEffectParams Params = MakeDamageEffectParamsFromClassDefaults();
		FireBall->DamageEffectParams = Params;

		FireBalls.Add(FireBall);

		FireBall->FinishSpawning(SpawnTransform);
	}

	return FireBalls;
}
