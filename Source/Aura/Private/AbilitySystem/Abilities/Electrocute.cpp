// Copyright Szusha


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float Manacost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>ELECTORCUTE</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//Description
			"<Default>Emits a beam of lightning, "
			"connecting with the target, repeatedly causing </>"
			"<Damage>%d</><Default> lightning damage with a chance to stun</>"),

			// Values
			Level, Manacost, Cooldown, ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>ELECTORCUTE</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//Description
			"<Default>Emits a beam of lightning, "
			"propagating to %d additional targets nearby, "
			"repeatedly causing </>"
			"<Damage>%d</><Default> lightning damage with a chance to stun</>"),

			// Values
			Level, Manacost, Cooldown, FMath::Min(Level, MaxNumShockTargets) - 1, ScaledDamage);
	}
}

FString UElectrocute::GetNextLevelDescription(int32 NextLevel)
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
		"<Default>Emits a beam of lightning, "
		"propagating to %d additional targets nearby, "
		"repeatedly causing </>"
		"<Damage>%d</><Default> lightning damage with a chance to stun</>"),

		// Values
		NextLevel, Manacost, Cooldown, FMath::Min(NextLevel, MaxNumShockTargets) - 1, ScaledDamage);
}
