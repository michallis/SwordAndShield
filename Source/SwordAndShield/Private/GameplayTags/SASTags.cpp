#include "GameplayTags/SASTags.h"

namespace SASTags
{
	namespace SASAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "SASTags.SASAbilities.ActivateOnGiven", "Tag to activate ability when given")
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "SASTags.SASAbilities.Primary", "Tag for the Primary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "SASTags.SASAbilities.Secondary", "Tag for the Secondary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "SASTags.SASAbilities.Tertiary", "Tag for the Tertiary Ability")
	}
	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, "SASTags.Events.KillScored", "Tag for the KillScored Event")
		
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "SASTags.Events.Enemy.HitReact", "Tag for Enemy Hit React Event")
		}
	}
}

