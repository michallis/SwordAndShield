#include "GameplayTags/SASTags.h"

namespace SASTags
{
	namespace SetByCaller 
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Projectile, "SASTags.SetByCaller.Projectile", "Tag for SetByCaller Magnitude for Projectiles")
	}
	namespace SASAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "SASTags.SASAbilities.ActivateOnGiven", "Tag to activate ability when given")
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "SASTags.SASAbilities.Primary", "Tag for the Primary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "SASTags.SASAbilities.Secondary", "Tag for the Secondary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "SASTags.SASAbilities.Tertiary", "Tag for the Tertiary Ability")

		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "SASTags.SASAbilities.Enemy.Attack", "Tag Enemy Attack")
		}
	}
	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, "SASTags.Events.KillScored", "Tag for the KillScored Event")
		
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "SASTags.Events.Enemy.HitReact", "Tag for Enemy Hit React Event")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(EndAttack, "SASTags.Events.Enemy.EndAttack", "Triggered immediately when attack has finished")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(MeleeTraceHits, "SASTags.Events.Enemy.MeleeTraceHits", "Tag for the Enemy Melee Trace Hit")
		}
	}
}

