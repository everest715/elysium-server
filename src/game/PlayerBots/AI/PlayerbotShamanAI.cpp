/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "PlayerbotShamanAI.h"
#include "../../Objects/Totem.h"
#include "../Spells/SpellAuras.h"

class PlayerbotAI;
PlayerbotShamanAI::PlayerbotShamanAI(Player* const master, Player* const bot, PlayerbotAI* const ai) : PlayerbotClassAI(master, bot, ai)
{
    // restoration
    CHAIN_HEAL               = m_ai->initSpell(CHAIN_HEAL_1);
    HEALING_WAVE             = m_ai->initSpell(HEALING_WAVE_1);
    LESSER_HEALING_WAVE      = m_ai->initSpell(LESSER_HEALING_WAVE_1);
    ANCESTRAL_SPIRIT         = m_ai->initSpell(ANCESTRAL_SPIRIT_1);
    EARTH_SHIELD             = m_ai->initSpell(EARTH_SHIELD_1);
    TREMOR_TOTEM             = m_ai->initSpell(TREMOR_TOTEM_1); // totems
    HEALING_STREAM_TOTEM     = m_ai->initSpell(HEALING_STREAM_TOTEM_1);
    MANA_SPRING_TOTEM        = m_ai->initSpell(MANA_SPRING_TOTEM_1);
    MANA_TIDE_TOTEM          = m_ai->initSpell(MANA_TIDE_TOTEM_1);
    CURE_DISEASE_SHAMAN      = m_ai->initSpell(CURE_DISEASE_SHAMAN_1);
    CURE_POISON_SHAMAN       = m_ai->initSpell(CURE_POISON_SHAMAN_1);
    NATURES_SWIFTNESS_SHAMAN = m_ai->initSpell(NATURES_SWIFTNESS_SHAMAN_1);
    // enhancement
    FOCUSED                  = 0; // Focused what?
    STORMSTRIKE              = m_ai->initSpell(STORMSTRIKE_1);
    BLOODLUST                = m_ai->initSpell(BLOODLUST_1);
    LIGHTNING_SHIELD         = m_ai->initSpell(LIGHTNING_SHIELD_1);
    ROCKBITER_WEAPON         = m_ai->initSpell(ROCKBITER_WEAPON_1);
    FLAMETONGUE_WEAPON       = m_ai->initSpell(FLAMETONGUE_WEAPON_1);
    FROSTBRAND_WEAPON        = m_ai->initSpell(FROSTBRAND_WEAPON_1);
    WINDFURY_WEAPON          = m_ai->initSpell(WINDFURY_WEAPON_1);
    STONESKIN_TOTEM          = m_ai->initSpell(STONESKIN_TOTEM_1); // totems
    STRENGTH_OF_EARTH_TOTEM  = m_ai->initSpell(STRENGTH_OF_EARTH_TOTEM_1);
    FROST_RESISTANCE_TOTEM   = m_ai->initSpell(FROST_RESISTANCE_TOTEM_1);
    FLAMETONGUE_TOTEM        = m_ai->initSpell(FLAMETONGUE_TOTEM_1);
    FIRE_RESISTANCE_TOTEM    = m_ai->initSpell(FIRE_RESISTANCE_TOTEM_1);
    GROUNDING_TOTEM          = m_ai->initSpell(GROUNDING_TOTEM_1);
    NATURE_RESISTANCE_TOTEM  = m_ai->initSpell(NATURE_RESISTANCE_TOTEM_1);
    WIND_FURY_TOTEM          = m_ai->initSpell(WINDFURY_TOTEM_1);
    STONESKIN_TOTEM          = m_ai->initSpell(STONESKIN_TOTEM_1);
    WRATH_OF_AIR_TOTEM       = m_ai->initSpell(WRATH_OF_AIR_TOTEM_1);
    EARTH_ELEMENTAL_TOTEM    = m_ai->initSpell(EARTH_ELEMENTAL_TOTEM_1);
	Grace_of_Air_Totem       = m_ai->initSpell(Grace_of_Air_Totem_1);
    // elemental
    LIGHTNING_BOLT           = m_ai->initSpell(LIGHTNING_BOLT_1);
    EARTH_SHOCK              = m_ai->initSpell(EARTH_SHOCK_1);
    FLAME_SHOCK              = m_ai->initSpell(FLAME_SHOCK_1);
    PURGE                    = m_ai->initSpell(PURGE_1);
    FROST_SHOCK              = m_ai->initSpell(FROST_SHOCK_1);
    CHAIN_LIGHTNING          = m_ai->initSpell(CHAIN_LIGHTNING_1);
    STONECLAW_TOTEM          = m_ai->initSpell(STONECLAW_TOTEM_1); // totems
    SEARING_TOTEM            = m_ai->initSpell(SEARING_TOTEM_1);
    FIRE_NOVA_TOTEM          = 0; // NPC only spell, check FIRE_NOVA_1
    MAGMA_TOTEM              = m_ai->initSpell(MAGMA_TOTEM_1);
    EARTHBIND_TOTEM          = m_ai->initSpell(EARTHBIND_TOTEM_1);
    FIRE_ELEMENTAL_TOTEM     = m_ai->initSpell(FIRE_ELEMENTAL_TOTEM_1);
    ELEMENTAL_MASTERY        = m_ai->initSpell(ELEMENTAL_MASTERY_1);

    RECENTLY_BANDAGED        = 11196; // first aid check

    // racial
    BLOOD_FURY               = m_ai->initSpell(BLOOD_FURY_ALL); // orc
    WAR_STOMP                = m_ai->initSpell(WAR_STOMP_ALL); // tauren
    BERSERKING               = m_ai->initSpell(BERSERKING_ALL); // troll

    // totem buffs
    STRENGTH_OF_EARTH_EFFECT    = m_ai->initSpell(STRENGTH_OF_EARTH_EFFECT_1);
    FLAMETONGUE_EFFECT          = m_ai->initSpell(FLAMETONGUE_EFFECT_1);
    MAGMA_TOTEM_EFFECT          = m_ai->initSpell(MAGMA_TOTEM_EFFECT_1);
    STONECLAW_EFFECT            = m_ai->initSpell(STONECLAW_EFFECT_1);
    FIRE_RESISTANCE_EFFECT      = m_ai->initSpell(FIRE_RESISTANCE_EFFECT_1);
    FROST_RESISTANCE_EFFECT     = m_ai->initSpell(FROST_RESISTANCE_EFFECT_1);
    GROUDNING_EFFECT            = m_ai->initSpell(GROUDNING_EFFECT_1);
    NATURE_RESISTANCE_EFFECT    = m_ai->initSpell(NATURE_RESISTANCE_EFFECT_1);
    STONESKIN_EFFECT            = m_ai->initSpell(STONESKIN_EFFECT_1);
    WINDFURY_EFFECT             = m_ai->initSpell(WINDFURY_EFFECT_1);
    WRATH_OF_AIR_EFFECT         = m_ai->initSpell(WRATH_OF_AIR_EFFECT_1);
    CLEANSING_TOTEM_EFFECT      = m_ai->initSpell(CLEANSING_TOTEM_EFFECT_1);
    MANA_SPRING_EFFECT          = m_ai->initSpell(MANA_SPRING_EFFECT_1);
    TREMOR_TOTEM_EFFECT         = m_ai->initSpell(TREMOR_TOTEM_EFFECT_1);
    STONECLAW_EFFECT            = m_ai->initSpell(STONECLAW_EFFECT_1);
    EARTHBIND_EFFECT            = m_ai->initSpell(EARTHBIND_EFFECT_1);
	Grace_of_Air_EFFECT         = m_ai->initSpell(Grace_of_Air_EFFECT_1);
}

PlayerbotShamanAI::~PlayerbotShamanAI() {}

CombatManeuverReturns PlayerbotShamanAI::DoFirstCombatManeuver(Unit* pTarget)
{
    // There are NPCs in BGs and Open World PvP, so don't filter this on PvP scenarios (of course if PvP targets anyone but tank, all bets are off anyway)
    // Wait until the tank says so, until any non-tank gains aggro or X seconds - whichever is shortest
    if (m_ai->GetCombatOrder() & PlayerbotAI::ORDERS_TEMP_WAIT_TANKAGGRO)
    {
        if (m_WaitUntil > m_ai->CurrentTime() && m_ai->GroupTankHoldsAggro())
        {
            if (PlayerbotAI::ORDERS_HEAL & m_ai->GetCombatOrder())
               return HealPlayer(GetHealTarget());
            else
                return RETURN_NO_ACTION_OK; // wait it out
        }
        else
        {
            m_ai->ClearGroupCombatOrder(PlayerbotAI::ORDERS_TEMP_WAIT_TANKAGGRO);
        }
    }

    if (m_ai->GetCombatOrder() & PlayerbotAI::ORDERS_TEMP_WAIT_OOC)
    {
        if (m_WaitUntil > m_ai->CurrentTime() && !m_ai->IsGroupInCombat())
            return RETURN_NO_ACTION_OK; // wait it out
        else
            m_ai->ClearGroupCombatOrder(PlayerbotAI::ORDERS_TEMP_WAIT_OOC);
    }

    switch (m_ai->GetScenarioType())
    {
        case PlayerbotAI::SCENARIO_PVP_DUEL:
        case PlayerbotAI::SCENARIO_PVP_BG:
        case PlayerbotAI::SCENARIO_PVP_ARENA:
        case PlayerbotAI::SCENARIO_PVP_OPENWORLD:
            return DoFirstCombatManeuverPVP(pTarget);
        case PlayerbotAI::SCENARIO_PVE:
        case PlayerbotAI::SCENARIO_PVE_ELITE:
        case PlayerbotAI::SCENARIO_PVE_RAID:
        default:
            return DoFirstCombatManeuverPVE(pTarget);
            break;
    }

    return RETURN_NO_ACTION_ERROR;
}

CombatManeuverReturns PlayerbotShamanAI::DoFirstCombatManeuverPVE(Unit* /*pTarget*/)
{   
    uint32 spec = m_bot->GetSpec();
	if (spec == SHAMAN_SPEC_RESTORATION && (m_ai->GetCombatOrder() & PlayerbotAI::ORDERS_NODISPEL) == 0)
		m_ai->SetCombatOrder(PlayerbotAI::ORDERS_HEAL);
    return RETURN_NO_ACTION_OK;
	
}

CombatManeuverReturns PlayerbotShamanAI::DoFirstCombatManeuverPVP(Unit* /*pTarget*/)
{
    return RETURN_NO_ACTION_OK;
}

CombatManeuverReturns PlayerbotShamanAI::DoNextCombatManeuver(Unit *pTarget)
{
    // Face enemy, make sure bot is attacking
    m_ai->FaceTarget(pTarget);

    switch (m_ai->GetScenarioType())
    {
        case PlayerbotAI::SCENARIO_PVP_DUEL:
        case PlayerbotAI::SCENARIO_PVP_BG:
        case PlayerbotAI::SCENARIO_PVP_ARENA:
        case PlayerbotAI::SCENARIO_PVP_OPENWORLD:
            return DoNextCombatManeuverPVP(pTarget);
        case PlayerbotAI::SCENARIO_PVE:
        case PlayerbotAI::SCENARIO_PVE_ELITE:
        case PlayerbotAI::SCENARIO_PVE_RAID:
        default:
            return DoNextCombatManeuverPVE(pTarget);
            break;
    }

    return RETURN_NO_ACTION_ERROR;
}

CombatManeuverReturns PlayerbotShamanAI::DoNextCombatManeuverPVE(Unit *pTarget)
{
    if (!m_ai)  return RETURN_NO_ACTION_ERROR;
    if (!m_bot) return RETURN_NO_ACTION_ERROR;

	uint32 spec = m_bot->GetSpec();

    // Make sure healer stays put, don't even melee (aggro) if in range.
    if (m_ai->IsHealer() || spec == SHAMAN_SPEC_ELEMENTAL)
        m_ai->SetCombatStyle(PlayerbotAI::COMBAT_RANGED);
    if (spec == SHAMAN_SPEC_ENHANCEMENT)
        m_ai->SetCombatStyle(PlayerbotAI::COMBAT_MELEE);
    
	usetrinkets();
	
	if (m_ai->GetDragFlg())
	{
		if (m_ai->GetHealthPercent() < 20)
		{
			m_ai->TryEmergency(nullptr);
		}
		if (m_ai->GetManaPercent() < 10)
	    {
        	Item* manaRegen = m_ai->FindManaRegenItem();
			if (manaRegen)
			m_ai->UseItem(manaRegen);
        }
	}
	//Used to determine if this bot is highest on threat
	Unit *newTarget = m_ai->FindAttacker((PlayerbotAI::ATTACKERINFOTYPE) (PlayerbotAI::AIT_VICTIMSELF | PlayerbotAI::AIT_HIGHESTTHREAT), m_bot);
	if (newTarget && m_ai->IsElite(newTarget) && m_ai->GetHealthPercent() < 80 && m_ai->GetFightFlg()) // TODO: && party has a tank
	{
		bool meleeReach = m_bot->CanReachWithMeleeAttack(newTarget);
		if (m_bot->getRace() == RACE_TAUREN && m_bot->IsSpellReady(WAR_STOMP) && meleeReach && m_ai->CastSpell(WAR_STOMP, *pTarget))
			return RETURN_CONTINUE;
		if (STONECLAW_TOTEM > 0 && m_ai->CastSpell(STONECLAW_TOTEM))
			return RETURN_CONTINUE;
        if (m_ai->IsHealer())
        {
            if (HealPlayer(m_bot) == RETURN_CONTINUE)
                return RETURN_CONTINUE;
        }
        else
        {
            bool inRaidGroup = m_bot->GetGroup() && m_bot->GetGroup()->isRaidGroup();
            if ((spec == 0 || spec == SHAMAN_SPEC_ENHANCEMENT || spec == SHAMAN_SPEC_ELEMENTAL) && !inRaidGroup)
            {
                if (Healothers(m_bot) == RETURN_CONTINUE)
                    return RETURN_CONTINUE;
            }
        }

		// TODO: Heal tank

		// We have aggro, don't need to heal self or tank, wait for aggro to subside
		//if (m_ai->IsHealer()) // Commented out: not necessary because of below. Leave code here in case below ever changes.
		//    return RETURN_NO_ACTION_OK;

		// We have no shoot spell; Assume auto-attack is on
		return RETURN_NO_ACTION_OK;
	}

	DropTotems();
	
    // Heal
    if (m_ai->IsHealer())
    {
        if (HealPlayer(GetHealTarget()) & (RETURN_NO_ACTION_OK | RETURN_CONTINUE))
            return RETURN_CONTINUE;
		if (m_bot->GetGroup())
		{
			Group::MemberSlotList const& groupSlot = m_bot->GetGroup()->GetMemberSlots();
			for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
			{
				Player *groupMember = sObjectMgr.GetPlayer(itr->guid);
				if (!groupMember || !groupMember->isAlive())
					continue;
				Pet * pet = groupMember->GetPet();
				if (!pet)
					continue;
				if (pet && pet->isAlive() && !pet->HasAuraType(SPELL_AURA_MOD_UNATTACKABLE) && (100 * pet->GetHealth() / pet->GetMaxHealth()) <= 60)
				{
					if (LESSER_HEALING_WAVE && m_ai->In_Reach(pet, LESSER_HEALING_WAVE) && m_ai->CastSpell(LESSER_HEALING_WAVE, *pet))
						return RETURN_CONTINUE;
				}
			}
		}
    }
    else
    {
        bool inRaidGroup = m_bot->GetGroup() && m_bot->GetGroup()->isRaidGroup();
        if ((spec == 0 || spec == SHAMAN_SPEC_ENHANCEMENT || spec == SHAMAN_SPEC_ELEMENTAL) && !inRaidGroup)
        {
            if (Healothers(GetHealTarget()) & RETURN_CONTINUE)
                return RETURN_CONTINUE;
        }
    }

    // Damage Spells

    CheckShields();
    //UseCooldowns();
    switch (spec)
    {
        case SHAMAN_SPEC_ENHANCEMENT:
            if (STORMSTRIKE > 0 && (m_bot->IsSpellReady(STORMSTRIKE)) && m_ai->CastSpell(STORMSTRIKE, *pTarget))
                return RETURN_CONTINUE;
            if (FLAME_SHOCK > 0 && (!pTarget->HasAura(FLAME_SHOCK)) && m_ai->CastSpell(FLAME_SHOCK, *pTarget))
                return RETURN_CONTINUE;
            /*if (EARTH_SHOCK > 0 && (m_bot->IsSpellReady(EARTH_SHOCK)) && m_ai->CastSpell(EARTH_SHOCK, *pTarget))
                return RETURN_CONTINUE;

            if (FOCUSED > 0 && m_ai->CastSpell(FOCUSED, *pTarget))
                return RETURN_CONTINUE;*/
            break;

        //case SHAMAN_SPEC_RESTORATION:
            // fall through to elemental

        case SHAMAN_SPEC_ELEMENTAL:
            if (ELEMENTAL_MASTERY > 0 && m_bot->IsSpellReady(ELEMENTAL_MASTERY) && m_ai->CastSpell(ELEMENTAL_MASTERY, *m_bot))
                return RETURN_CONTINUE;
            if (m_ai->GetFightFlg() && m_ai->GetAttackerCount() >= 3)
            {
                if (CHAIN_LIGHTNING > 0 && m_ai->In_Reach(pTarget, CHAIN_LIGHTNING) && m_bot->IsSpellReady(CHAIN_LIGHTNING) && m_ai->CastSpell(CHAIN_LIGHTNING, *pTarget))              
                    return RETURN_CONTINUE;
            }
            if (FLAME_SHOCK > 0 && (!pTarget->HasAura(FLAME_SHOCK)) && m_ai->CastSpell(FLAME_SHOCK, *pTarget))
                return RETURN_CONTINUE;
            if (LIGHTNING_BOLT > 0 && m_ai->CastSpell(LIGHTNING_BOLT, *pTarget))
                return RETURN_CONTINUE;
            /*if (PURGE > 0 && m_ai->CastSpell(PURGE, *pTarget))
                return RETURN_CONTINUE;*/
            /*if (FROST_SHOCK > 0 && !pTarget->HasAura(FROST_SHOCK, EFFECT_INDEX_0) && m_ai->CastSpell(FROST_SHOCK, *pTarget))
                return RETURN_CONTINUE;*/
            /*if (CHAIN_LIGHTNING > 0 && m_ai->CastSpell(CHAIN_LIGHTNING, *pTarget))
                return RETURN_CONTINUE;*/
    }

    return RETURN_NO_ACTION_OK;
} // end DoNextCombatManeuver

CombatManeuverReturns PlayerbotShamanAI::DoNextCombatManeuverPVP(Unit* pTarget)
{
    DropTotems();
    CheckShields();
    // UseCooldowns();

    Player* healTarget = (m_ai->GetScenarioType() == PlayerbotAI::SCENARIO_PVP_DUEL) ? GetHealTarget() : m_bot;
    if (HealPlayer(healTarget) & (RETURN_NO_ACTION_OK | RETURN_CONTINUE))
        return RETURN_CONTINUE;
    if (m_ai->CastSpell(LIGHTNING_BOLT))
        return RETURN_CONTINUE;

    return DoNextCombatManeuverPVE(pTarget); // TODO: bad idea perhaps, but better than the alternative
}

CombatManeuverReturns PlayerbotShamanAI::HealPlayer(Player* target)
{
    CombatManeuverReturns r = PlayerbotClassAI::HealPlayer(target);
    if (r != RETURN_NO_ACTION_OK)
        return r;

    if (!target->isAlive())
    {
        if (ANCESTRAL_SPIRIT && m_ai->CastSpell(ANCESTRAL_SPIRIT, *target))
        {
            std::string msg = "元素之灵会复活你， ";
            msg += target->GetName();
            m_bot->Say(msg, LANG_UNIVERSAL);
            return RETURN_CONTINUE;
        }
        return RETURN_NO_ACTION_ERROR; // not error per se - possibly just OOM
    }

    // Remove poison on group members if orders allow bot to do so
    if (Player* pPoisonedTarget = GetDispelTarget(DISPEL_POISON))
    {
        if (CURE_POISON_SHAMAN > 0 && (m_ai->GetCombatOrder() & PlayerbotAI::ORDERS_NODISPEL) == 0 && m_ai->CastSpell(CURE_POISON_SHAMAN, *pPoisonedTarget))
            return RETURN_CONTINUE;
    }
	
	// Remove disease on group members if orders allow bot to do so
    if (Player* pDiseasedTarget = GetDispelTarget(DISPEL_DISEASE))
    {
        if (CURE_DISEASE_SHAMAN > 0 && (m_ai->GetCombatOrder() & PlayerbotAI::ORDERS_NODISPEL) == 0 && m_ai->CastSpell(CURE_DISEASE_SHAMAN, *pDiseasedTarget))
            return RETURN_CONTINUE;
    }

	uint8 hp = target->GetHealthPercent();
	uint8 hpSelf = m_ai->GetHealthPercent();
	uint8 hpmaster = m_master->GetHealthPercent();
	uint8 ghp = 0;
	//get aoe heal count must in same subgroup because CHAIN_HEAL can only heal in same subgroup
	if (m_bot->GetGroup())
	{
		Group::MemberSlotList const& groupSlot = m_bot->GetGroup()->GetMemberSlots();
		uint8 subgroup = m_bot->GetSubGroup();
		for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
		{
			Player *groupMember = sObjectMgr.GetPlayer(itr->guid);

			if (!groupMember || !groupMember->isAlive() || groupMember->IsInDuel() || itr->group != subgroup)
				continue;
			if ((groupMember->GetMaxHealth() - groupMember->GetHealth()) > 900)
				ghp++;
		}
	}
	
	// Everyone is healthy enough, return OK. MUST correlate to highest value below (should be last HP check)
	if (target->GetHealthPercent() >= 90)
		return RETURN_NO_ACTION_OK;

	// Technically the best rotation is CHAIN + LHW + LHW, or RIPTIDE + LHW + LHW (proc Tidal Waves then two short LHW), subbing in HW for trouble (bad mana efficiency)
	if (target->GetHealthPercent() < 20)
	{
		// TODO: Use in conjunction with Nature's Swiftness
		if (NATURES_SWIFTNESS_SHAMAN > 0 && m_bot->IsSpellReady(NATURES_SWIFTNESS_SHAMAN) && m_ai->CastSpell(NATURES_SWIFTNESS_SHAMAN, *m_bot))
			return RETURN_CONTINUE;
		if (HEALING_WAVE > 0 && m_ai->In_Reach(target, HEALING_WAVE) /*&& (NOURISH == 0 ||   && CastSpell(NATURES_SWIFTNESS)*/ && m_ai->CastSpell(HEALING_WAVE, *target))
			return RETURN_CONTINUE;

		//if (NOURISH > 0 && m_ai->In_Reach(target,NOURISH) && CastSpell(NOURISH, target))
		//return RETURN_CONTINUE;
	}
	if (ghp >= 3 && CHAIN_HEAL > 0 && m_ai->CastSpell(CHAIN_HEAL, *target))
		return RETURN_CONTINUE;
	if (target->GetHealthPercent() < 50 && HEALING_WAVE > 0 && m_ai->CastSpell(HEALING_WAVE, *target))
		return RETURN_CONTINUE;
	if (target->GetHealthPercent() < 60 && LESSER_HEALING_WAVE > 0 && m_ai->CastSpell(10467, *target))
		return RETURN_CONTINUE;
    if (target->GetHealthPercent() < 70 && LESSER_HEALING_WAVE > 0 && m_ai->CastSpell(8010, *target))
		return RETURN_CONTINUE;
	if (target->GetHealthPercent() < 80 && LESSER_HEALING_WAVE > 0 && m_ai->CastSpell(8004, *target))
		return RETURN_CONTINUE;
	// if (target->GetHealthPercent() < 60 && RIPTIDE > 0 && !target->HasAura(RIPTIDE, EFFECT_INDEX_0) && m_ai->CastSpell(RIPTIDE, *target))
	// return RETURN_CONTINUE;
	

	return RETURN_NO_ACTION_OK;
} // end HealTarget

CombatManeuverReturns PlayerbotShamanAI::Healothers(Player* target)
{
    CombatManeuverReturns r = PlayerbotClassAI::HealPlayer(target);
    if (r != RETURN_NO_ACTION_OK)
        return r;

    if (!target->isAlive())
    {
        if (ANCESTRAL_SPIRIT && m_ai->CastSpell(ANCESTRAL_SPIRIT, *target))
        {
            std::string msg = "元素之灵会复活你， ";
            msg += target->GetName();
            m_bot->Say(msg, LANG_UNIVERSAL);
            return RETURN_CONTINUE;
        }
        return RETURN_NO_ACTION_ERROR; // not error per se - possibly just OOM
    }

    // Remove poison on group members if orders allow bot to do so
    if (Player* pPoisonedTarget = GetDispelTarget(DISPEL_POISON))
    {
        if (CURE_POISON_SHAMAN > 0 && (m_ai->GetCombatOrder() & PlayerbotAI::ORDERS_NODISPEL) == 0 && m_ai->CastSpell(CURE_POISON_SHAMAN, *pPoisonedTarget))
            return RETURN_CONTINUE;
    }

    // Remove disease on group members if orders allow bot to do so
    if (Player* pDiseasedTarget = GetDispelTarget(DISPEL_DISEASE))
    {
        if (CURE_DISEASE_SHAMAN > 0 && (m_ai->GetCombatOrder() & PlayerbotAI::ORDERS_NODISPEL) == 0 && m_ai->CastSpell(CURE_DISEASE_SHAMAN, *pDiseasedTarget))
            return RETURN_CONTINUE;
    }

    uint8 hp = target->GetHealthPercent();
    uint8 hpSelf = m_ai->GetHealthPercent();

    // Everyone is healthy enough, return OK. MUST correlate to highest value below (should be last HP check)
    if (target->GetHealthPercent() >= 60)
        return RETURN_NO_ACTION_OK;
    if (target->GetHealthPercent() < 40 && HEALING_WAVE > 0 && m_ai->CastSpell(HEALING_WAVE, *target))
        return RETURN_CONTINUE;
    if (target->GetHealthPercent() < 60 && LESSER_HEALING_WAVE > 0 && m_ai->CastSpell(LESSER_HEALING_WAVE, *target))
        return RETURN_CONTINUE;
   
    return RETURN_NO_ACTION_OK;
} // end HealTarget

void PlayerbotShamanAI::DropTotems()
{
    if (!m_ai)  return;
    if (!m_bot) return;

    uint32 spec = m_bot->GetSpec();

    Totem* earth = m_bot->GetTotem(TOTEM_SLOT_EARTH);
    Totem* fire = m_bot->GetTotem(TOTEM_SLOT_FIRE);
    Totem* water = m_bot->GetTotem(TOTEM_SLOT_WATER);
    Totem* air = m_bot->GetTotem(TOTEM_SLOT_AIR);

    // Earth Totems
    if ((earth == nullptr) || (m_bot->GetDistance(earth) > 30))
    {
        if (STRENGTH_OF_EARTH_TOTEM > 0 && m_ai->CastSpell(STRENGTH_OF_EARTH_TOTEM))
            return;
    }

    // Fire Totems
    if ((fire == nullptr) || (m_bot->GetDistance(fire) > 30))
    {
        if (m_ai->GetCombatOrder() & PlayerbotAI::ORDERS_RESIST_FROST && FROST_RESISTANCE_TOTEM > 0 && m_ai->CastSpell(FROST_RESISTANCE_TOTEM))
            return;
        // If the spec didn't take totem of wrath, use flametongue
        else if ((spec != SHAMAN_SPEC_ELEMENTAL) && FLAMETONGUE_TOTEM > 0 && m_ai->CastSpell(FLAMETONGUE_TOTEM))
            return;
    }

    // Air totems
    if ((air == nullptr) || (m_bot->GetDistance(air) > 30))
    {
        if (m_ai->GetCombatOrder() & PlayerbotAI::ORDERS_RESIST_NATURE && NATURE_RESISTANCE_TOTEM > 0 && m_ai->CastSpell(NATURE_RESISTANCE_TOTEM))
            return;
        else /*if (spec == SHAMAN_SPEC_ENHANCEMENT)*/
        {
            if (Grace_of_Air_Totem > 0 && m_ai->CastSpell(Grace_of_Air_Totem)/*WIND_FURY_TOTEM > 0 && !m_bot->HasAura(IMPROVED_ICY_TALONS) && m_ai->CastSpell(WIND_FURY_TOTEM)*/)
            return;
        }
        /*else
        {
            if (WRATH_OF_AIR_TOTEM > 0 && m_ai->CastSpell(WRATH_OF_AIR_TOTEM))
            return;
        }*/
    }

    // Water Totems
    if (MANA_TIDE_TOTEM > 0 && m_bot->IsSpellReady(MANA_TIDE_TOTEM) && m_ai->GetManaPercent() < 50 && m_ai->CastSpell(MANA_TIDE_TOTEM))
        return;
    if ((water == nullptr) || (m_bot->GetDistance(water) > 30))
    {
        if (m_ai->GetCombatOrder() & PlayerbotAI::ORDERS_RESIST_FIRE && FIRE_RESISTANCE_TOTEM > 0 && m_ai->CastSpell(FIRE_RESISTANCE_TOTEM))
            return;
        else if (MANA_SPRING_TOTEM > 0 && m_ai->CastSpell(MANA_SPRING_TOTEM))
            return;
    }

    /*if (EARTH_ELEMENTAL_TOTEM > 0 && m_ai->CastSpell(EARTH_ELEMENTAL_TOTEM))
        return RETURN_CONTINUE;*/
    /*if (EARTHBIND_TOTEM > 0 && !pTarget->HasAura(EARTHBIND_TOTEM, EFFECT_INDEX_0) && !m_bot->HasAura(STRENGTH_OF_EARTH_TOTEM, EFFECT_INDEX_0) && m_ai->CastSpell(EARTHBIND_TOTEM))
        return RETURN_CONTINUE;*/
    /*if (FIRE_ELEMENTAL_TOTEM > 0 && m_ai->CastSpell(FIRE_ELEMENTAL_TOTEM))
        return RETURN_CONTINUE;*/
    /*if (FIRE_NOVA_TOTEM > 0 && m_ai->CastSpell(FIRE_NOVA_TOTEM))
        return RETURN_CONTINUE;*/
    /*if (GROUNDING_TOTEM > 0 && !m_bot->HasAura(GROUNDING_TOTEM, EFFECT_INDEX_0) && !m_bot->HasAura(WRATH_OF_AIR_TOTEM, EFFECT_INDEX_0) && !m_bot->HasAura(WIND_FURY_TOTEM, EFFECT_INDEX_0) && m_ai->CastSpell(GROUNDING_TOTEM))
        return RETURN_CONTINUE;*/
    /*if (HEALING_STREAM_TOTEM > 0 && m_ai->GetHealthPercent() < 50 && !m_bot->HasAura(HEALING_STREAM_TOTEM, EFFECT_INDEX_0) && !m_bot->HasAura(MANA_SPRING_TOTEM, EFFECT_INDEX_0) && m_ai->CastSpell(HEALING_STREAM_TOTEM))
        return RETURN_CONTINUE;*/
    /*if (MAGMA_TOTEM > 0 && (!m_bot->HasAura(TOTEM_OF_WRATH, EFFECT_INDEX_0)) && m_ai->CastSpell(MAGMA_TOTEM))
        return RETURN_CONTINUE;*/
    /*if (SEARING_TOTEM > 0 && !pTarget->HasAura(SEARING_TOTEM, EFFECT_INDEX_0) && !m_bot->HasAura(TOTEM_OF_WRATH, EFFECT_INDEX_0) && m_ai->CastSpell(SEARING_TOTEM))
        return RETURN_CONTINUE;*/
    /*if (STONECLAW_TOTEM > 0 && m_ai->GetHealthPercent() < 51 && !pTarget->HasAura(STONECLAW_TOTEM, EFFECT_INDEX_0) && !pTarget->HasAura(EARTHBIND_TOTEM, EFFECT_INDEX_0) && !m_bot->HasAura(STRENGTH_OF_EARTH_TOTEM, EFFECT_INDEX_0) && m_ai->CastSpell(STONECLAW_TOTEM))
        return RETURN_CONTINUE;*/
    /*if (STONESKIN_TOTEM > 0 && !m_bot->HasAura(STONESKIN_TOTEM, EFFECT_INDEX_0) && !m_bot->HasAura(STRENGTH_OF_EARTH_TOTEM, EFFECT_INDEX_0) && m_ai->CastSpell(STONESKIN_TOTEM))
        return RETURN_CONTINUE;*/
    /*if (TREMOR_TOTEM > 0 && !m_bot->HasAura(STRENGTH_OF_EARTH_TOTEM, EFFECT_INDEX_0) && m_ai->CastSpell(TREMOR_TOTEM))
        return RETURN_CONTINUE;*/
}

void PlayerbotShamanAI::CheckShields()
{
    if (!m_ai)  return;
    if (!m_bot) return;

    uint32 spec = m_bot->GetSpec();

    if (spec == SHAMAN_SPEC_ENHANCEMENT && LIGHTNING_SHIELD > 0 && !m_bot->HasAura(LIGHTNING_SHIELD, EFFECT_INDEX_0))
        m_ai->CastSpell(LIGHTNING_SHIELD, *m_bot);
    /*if (EARTH_SHIELD > 0 && !GetMaster()->HasAura(EARTH_SHIELD, EFFECT_INDEX_0))
        m_ai->CastSpell(EARTH_SHIELD, *(GetMaster()));*/
}

/*void PlayerbotShamanAI::UseCooldowns()
{
    if (!m_ai)  return;
    if (!m_bot) return;

    uint32 spec = m_bot->GetSpec();

    if (BLOODLUST > 0 && (!GetMaster()->HasAura(BLOODLUST, EFFECT_INDEX_0)) && m_ai->CastSpell(BLOODLUST))
        return;

    switch(spec)
    {
        case SHAMAN_SPEC_ENHANCEMENT:
            break;

        case SHAMAN_SPEC_ELEMENTAL:
            if (ELEMENTAL_MASTERY > 0 && m_ai->CastSpell(ELEMENTAL_MASTERY, *m_bot))
                return;
            break;

        case SHAMAN_SPEC_RESTORATION:
            if (MANA_TIDE_TOTEM > 0 && m_ai->GetManaPercent() < 50 && m_ai->CastSpell(MANA_TIDE_TOTEM))
                return;
            else if (NATURES_SWIFTNESS_SHAMAN > 0 && m_ai->CastSpell(NATURES_SWIFTNESS_SHAMAN))
                return;

        default:
            break;
    }
}*/

void PlayerbotShamanAI::DoNonCombatActions()
{
    if (!m_ai)   return;
    if (!m_bot)  return;

    if (!m_bot->isAlive() || m_bot->IsInDuel()) return;

    uint32 spec = m_bot->GetSpec();

    CheckShields();
/*
       // buff myself weapon
       if (ROCKBITER_WEAPON > 0)
            (!m_bot->HasAura(ROCKBITER_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(WINDFURY_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(FLAMETONGUE_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(FROSTBRAND_WEAPON, EFFECT_INDEX_0) && m_ai->CastSpell(ROCKBITER_WEAPON,*m_bot) );
       else if (EARTHLIVING_WEAPON > 0)
            (!m_bot->HasAura(EARTHLIVING_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(FLAMETONGUE_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(FROSTBRAND_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(ROCKBITER_WEAPON, EFFECT_INDEX_0) && m_ai->CastSpell(WINDFURY_WEAPON,*m_bot) );
       else if (WINDFURY_WEAPON > 0)
            (!m_bot->HasAura(WINDFURY_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(FLAMETONGUE_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(FROSTBRAND_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(ROCKBITER_WEAPON, EFFECT_INDEX_0) && m_ai->CastSpell(WINDFURY_WEAPON,*m_bot) );
       else if (FLAMETONGUE_WEAPON > 0)
            (!m_bot->HasAura(FLAMETONGUE_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(WINDFURY_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(FROSTBRAND_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(ROCKBITER_WEAPON, EFFECT_INDEX_0) && m_ai->CastSpell(FLAMETONGUE_WEAPON,*m_bot) );
       else if (FROSTBRAND_WEAPON > 0)
            (!m_bot->HasAura(FROSTBRAND_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(WINDFURY_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(FLAMETONGUE_WEAPON, EFFECT_INDEX_0) && !m_bot->HasAura(ROCKBITER_WEAPON, EFFECT_INDEX_0) && m_ai->CastSpell(FROSTBRAND_WEAPON,*m_bot) );
 */
    // Mainhand
    Item* weapon;
    weapon = m_bot->GetItemByPos(EQUIPMENT_SLOT_MAINHAND);
    if (weapon && (weapon->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT) == 0) && spec == SHAMAN_SPEC_ELEMENTAL)
        m_ai->CastSpell(FLAMETONGUE_WEAPON, *m_bot);
    else if (weapon && (weapon->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT) == 0) && spec == SHAMAN_SPEC_ENHANCEMENT)
        m_ai->CastSpell(WINDFURY_WEAPON, *m_bot);

    //Offhand
    weapon = m_bot->GetItemByPos(EQUIPMENT_SLOT_OFFHAND);
    if (weapon && (weapon->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT) == 0) && spec == SHAMAN_SPEC_ENHANCEMENT)
        m_ai->CastSpell(FLAMETONGUE_WEAPON, *m_bot);

    // Revive
    if (HealPlayer(GetResurrectionTarget()) & RETURN_CONTINUE)
        return;

    // Heal
    if (m_ai->IsHealer())
    {
        if (HealPlayer(GetHealTarget()) & RETURN_CONTINUE)
            return;// RETURN_CONTINUE;
		if (m_bot->GetGroup())
		{
			Group::MemberSlotList const& groupSlot = m_bot->GetGroup()->GetMemberSlots();
			for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
			{
				Player *groupMember = sObjectMgr.GetPlayer(itr->guid);
				if (!groupMember || !groupMember->isAlive())
					continue;
				Pet * pet = groupMember->GetPet();
				if (!pet)
					continue;
				if (pet && pet->isAlive() && !pet->HasAuraType(SPELL_AURA_MOD_UNATTACKABLE) && (100 * pet->GetHealth() / pet->GetMaxHealth()) <= 60)
				{
					if (LESSER_HEALING_WAVE && m_ai->In_Reach(pet, LESSER_HEALING_WAVE) && m_ai->CastSpell(LESSER_HEALING_WAVE, *pet))
						return;
				}
			}
		}
    }
    else
    {
        // Is this desirable? Debatable.
        // TODO: In a group/raid with a healer you'd want this bot to focus on DPS (it's not specced/geared for healing either)
        bool inRaidGroup = m_bot->GetGroup() && m_bot->GetGroup()->isRaidGroup();
        if ((spec == 0 || spec == SHAMAN_SPEC_ENHANCEMENT || spec == SHAMAN_SPEC_ELEMENTAL) && !inRaidGroup)
        {
            if (Healothers(GetHealTarget()) & RETURN_CONTINUE)
                return ;
        }
    }

    // hp/mana check
    if (EatDrinkBandage())
        return;

    m_ai->AutoRepair();

	Player* master = GetMaster();
	if (master && master->HasAuraType(SPELL_AURA_MOUNTED))
	{
		Item* partialMatch = m_ai->FindMount(150);
		if (partialMatch)
		m_ai->UseItem(partialMatch);
	}
} // end DoNonCombatActions

bool PlayerbotShamanAI::CastHoTOnTank()
{
    if (!m_ai) return false;

    if ((PlayerbotAI::ORDERS_HEAL & m_ai->GetCombatOrder()) == 0) return false;

    // Shaman: Healing Stream Totem
    // None of these are cast before Pulling

    return false;
}
