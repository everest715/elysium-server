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

#include "PlayerbotMageAI.h"
#include "../Spells/SpellAuras.h"

class PlayerbotAI;

PlayerbotMageAI::PlayerbotMageAI(Player* const master, Player* const bot, PlayerbotAI* const ai) : PlayerbotClassAI(master, bot, ai)
{
    ARCANE_MISSILES         = m_ai->initSpell(ARCANE_MISSILES_1);
    ARCANE_EXPLOSION        = m_ai->initSpell(ARCANE_EXPLOSION_1);
    COUNTERSPELL            = m_ai->initSpell(COUNTERSPELL_1);
    SLOW                    = m_ai->initSpell(SLOW_1);
    ARCANE_BLAST            = m_ai->initSpell(ARCANE_BLAST_1);
    ARCANE_POWER            = m_ai->initSpell(ARCANE_POWER_1);
    DAMPEN_MAGIC            = m_ai->initSpell(DAMPEN_MAGIC_1);
    AMPLIFY_MAGIC           = m_ai->initSpell(AMPLIFY_MAGIC_1);
    MAGE_ARMOR              = m_ai->initSpell(MAGE_ARMOR_1);
    ARCANE_INTELLECT        = m_ai->initSpell(ARCANE_INTELLECT_1);
    ARCANE_BRILLIANCE       = m_ai->initSpell(ARCANE_BRILLIANCE_1);
    MANA_SHIELD             = m_ai->initSpell(MANA_SHIELD_1);
    CONJURE_WATER           = m_ai->initSpell(CONJURE_WATER_1);
    CONJURE_FOOD            = m_ai->initSpell(CONJURE_FOOD_1);
	CONJURE_MANA_GEM        = m_ai->initSpell(CONJURE_MANA_GEM_1);
    EVOCATION               = m_ai->initSpell(EVOCATION_1);
    FIREBALL                = m_ai->initSpell(FIREBALL_1);
    FIRE_BLAST              = m_ai->initSpell(FIRE_BLAST_1);
    FLAMESTRIKE             = m_ai->initSpell(FLAMESTRIKE_1);
    SCORCH                  = m_ai->initSpell(SCORCH_1);
    POLYMORPH               = m_ai->initSpell(POLYMORPH_1);
    PRESENCE_OF_MIND        = m_ai->initSpell(PRESENCE_OF_MIND_1);
    PYROBLAST               = m_ai->initSpell(PYROBLAST_1);
    BLAST_WAVE              = m_ai->initSpell(BLAST_WAVE_1);
    COMBUSTION              = m_ai->initSpell(COMBUSTION_1);
    DRAGONS_BREATH          = m_ai->initSpell(DRAGONS_BREATH_1);
    FIRE_WARD               = m_ai->initSpell(FIRE_WARD_1);
    MOLTEN_ARMOR            = m_ai->initSpell(MOLTEN_ARMOR_1);
    ICY_VEINS               = m_ai->initSpell(ICY_VEINS_1);
    FROSTBOLT               = m_ai->initSpell(FROSTBOLT_1);
    FROST_NOVA              = m_ai->initSpell(FROST_NOVA_1);
    BLIZZARD                = m_ai->initSpell(BLIZZARD_1);
    CONE_OF_COLD            = m_ai->initSpell(CONE_OF_COLD_1);
    ICE_BARRIER             = m_ai->initSpell(ICE_BARRIER_1);
	SUMMON_WATER_ELEMENTAL  = m_ai->initSpell(SUMMON_WATER_ELEMENTAL_1);
    FROST_WARD              = m_ai->initSpell(FROST_WARD_1);
	ICE_LANCE               = m_ai->initSpell(ICE_LANCE_1);
    FROST_ARMOR             = m_ai->initSpell(FROST_ARMOR_1);
    ICE_ARMOR               = m_ai->initSpell(ICE_ARMOR_1);
    ICE_BLOCK               = m_ai->initSpell(ICE_BLOCK_1);
    COLD_SNAP               = m_ai->initSpell(COLD_SNAP_1);
	MAGE_REMOVE_CURSE       = m_ai->initSpell(REMOVE_CURSE_MAGE_1);
    // RANGED COMBAT
    SHOOT                   = m_ai->initSpell(SHOOT_2);

    RECENTLY_BANDAGED       = 11196; // first aid check

    // racial
    ESCAPE_ARTIST           = m_ai->initSpell(ESCAPE_ARTIST_ALL); // gnome
    PERCEPTION              = m_ai->initSpell(PERCEPTION_ALL); // human
    BERSERKING              = m_ai->initSpell(BERSERKING_ALL); // troll
    WILL_OF_THE_FORSAKEN    = m_ai->initSpell(WILL_OF_THE_FORSAKEN_ALL); // undead
}

PlayerbotMageAI::~PlayerbotMageAI() {}

CombatManeuverReturns PlayerbotMageAI::DoFirstCombatManeuver(Unit* pTarget)
{
    // There are NPCs in BGs and Open World PvP, so don't filter this on PvP scenarios (of course if PvP targets anyone but tank, all bets are off anyway)
    // Wait until the tank says so, until any non-tank gains aggro or X seconds - whichever is shortest
    if (m_ai->GetCombatOrder() & PlayerbotAI::ORDERS_TEMP_WAIT_TANKAGGRO)
    {
        if (m_WaitUntil > m_ai->CurrentTime() && m_ai->GroupTankHoldsAggro())
        {
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

CombatManeuverReturns PlayerbotMageAI::DoFirstCombatManeuverPVE(Unit* /*pTarget*/)
{
    return RETURN_NO_ACTION_OK;
}

CombatManeuverReturns PlayerbotMageAI::DoFirstCombatManeuverPVP(Unit* /*pTarget*/)
{
    return RETURN_NO_ACTION_OK;
}

CombatManeuverReturns PlayerbotMageAI::DoNextCombatManeuver(Unit *pTarget)
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

CombatManeuverReturns PlayerbotMageAI::DoNextCombatManeuverPVE(Unit *pTarget)
{
    if (!m_ai)  return RETURN_NO_ACTION_ERROR;
    if (!m_bot) return RETURN_NO_ACTION_ERROR;

    Unit* pVictim = pTarget->getVictim();
    bool meleeReach = m_bot->CanReachWithMeleeAttack(pTarget);

    uint32 spec = m_bot->GetSpec();

    if (m_ai->GetCombatStyle() != PlayerbotAI::COMBAT_RANGED/* && !meleeReach*/)
        m_ai->SetCombatStyle(PlayerbotAI::COMBAT_RANGED);
    // switch to melee if in melee range AND can't shoot OR have no ranged (wand) equipped
    /* else if(m_ai->GetCombatStyle() != PlayerbotAI::COMBAT_MELEE */
          /* && meleeReach */
          /* && (SHOOT == 0 || !m_bot->GetWeaponForAttack(RANGED_ATTACK, true, true))) */
      /* m_ai->SetCombatStyle(PlayerbotAI::COMBAT_MELEE); */	
	usetrinkets();
    //Used to determine if this bot is highest on threat
    Unit *newTarget = m_ai->FindAttacker((PlayerbotAI::ATTACKERINFOTYPE) (PlayerbotAI::AIT_VICTIMSELF | PlayerbotAI::AIT_HIGHESTTHREAT), m_bot);
    
	// Remove curse on group members
    if (Player* pCursedTarget = GetDispelTarget(DISPEL_CURSE))
    {
        if (MAGE_REMOVE_CURSE > 0 && CastSpell(MAGE_REMOVE_CURSE, pCursedTarget))
            return RETURN_CONTINUE;
    }

	if (newTarget && !m_ai->IsNeutralized(newTarget)) // Bot has aggro and the mob is not already crowd controled
	{
		// If elite
		if (m_ai->IsElite(newTarget) && newTarget->GetHealthPercent() > 50 && m_ai->GetFightFlg())
		{		
			if (pTarget != newTarget)
			{
				// If the attacker is a beast or humanoid, let's the bot give it a form more suited to the low intellect of something fool enough to attack a mage
				Creature * pCreature = dynamic_cast<Creature*>(newTarget);
				if (pCreature && (pCreature->GetCreatureInfo()->type == CREATURE_TYPE_HUMANOID || pCreature->GetCreatureInfo()->type == CREATURE_TYPE_BEAST))
				{
					if (POLYMORPH > 0 && CastSpell(POLYMORPH, newTarget))
						return RETURN_NO_ACTION_OK;
				}			
			}
			else
			{
				/*if (ICE_BARRIER > 0 && m_bot->IsSpellReady(ICE_BARRIER) && !m_bot->HasAura(ICE_BARRIER, EFFECT_INDEX_0) && CastSpell(ICE_BARRIER, m_bot))
					return RETURN_CONTINUE;*/
				// Cast mana shield if no shield is already up
				if (MANA_SHIELD > 0 && m_ai->GetHealthPercent() < 50 && !m_bot->HasAura(MANA_SHIELD) && !m_bot->HasAura(ICE_BARRIER) && m_ai->SelfBuff(MANA_SHIELD))
					return RETURN_CONTINUE;
			}
		}
		if (newTarget->GetHealthPercent() > 10 && m_ai->IsWorldBoss(newTarget))
			// Have threat, can't quickly lower it. 3 options remain: Stop attacking, lowlevel damage (wand), keep on keeping on.
			return CastSpell(SHOOT, pTarget);
	}

	// Mana check and replenishment
    if (EVOCATION && m_ai->GetManaPercent() <= 10 && m_bot->IsSpellReady(EVOCATION) && !newTarget && m_ai->SelfBuff(EVOCATION))
    {
		m_ai->SetIgnoreUpdateTime(8);
		return RETURN_CONTINUE;
	}
	if (m_ai->GetManaPercent() <= 20)
	{
		Item* gem = FindManaGem();
		if (gem)
			m_ai->UseItem(gem);
	}
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
	
    if (m_ai->GetManaPercent() <= 5)
    {
        CastSpell(SHOOT, pTarget);
        return RETURN_CONTINUE;
    }
	
	if (pTarget->HasAura(25178))
	{
		if (FROSTBOLT > 0 && m_ai->In_Reach(pTarget, FROSTBOLT) && m_ai->CastSpell(FROSTBOLT, *pTarget));
		return RETURN_CONTINUE;
	}
	if (pTarget->HasAura(25177))
	{
		if (FIREBALL > 0 && m_ai->In_Reach(pTarget, FIREBALL) && m_ai->CastSpell(FIREBALL, *pTarget));
		return RETURN_CONTINUE;
	}
	if (pTarget->HasAura(25181))
	{
		if (ARCANE_MISSILES > 0 && m_ai->In_Reach(pTarget, ARCANE_MISSILES) && m_ai->CastSpell(ARCANE_MISSILES, *pTarget));
		return RETURN_CONTINUE;
	}
    switch (spec)
    {
        case MAGE_SPEC_FROST:
            if (m_ai->GetHealthPercent() < 20) 
            {
                if (COLD_SNAP > 0 && !m_bot->IsSpellReady(ICE_BLOCK) && m_bot->IsSpellReady(COLD_SNAP) && CastSpell(COLD_SNAP, m_bot))
                    return RETURN_CONTINUE;
                if (ICE_BLOCK > 0 && !m_bot->HasAura(ICE_BLOCK, EFFECT_INDEX_0) && m_bot->IsSpellReady(ICE_BLOCK) && CastSpell(ICE_BLOCK, m_bot))
                {
                    m_ai->SetIgnoreUpdateTime(10);
                    return RETURN_CONTINUE;
                }
            }
            if (m_ai->GetHealthPercent() < 90)
            {
                if (ICE_BARRIER > 0 && m_bot->IsSpellReady(ICE_BARRIER) && !m_bot->HasAura(ICE_BARRIER, EFFECT_INDEX_0) && CastSpell(ICE_BARRIER, m_bot))
                    return RETURN_CONTINUE;         
            }
			if (m_ai->GetFightFlg() && m_ai->GetAttackerCount() >= 4)
			{				
                if (FROST_NOVA > 0 && meleeReach && m_bot->IsSpellReady(FROST_NOVA) && !pTarget->HasAura(FROST_NOVA, EFFECT_INDEX_0) && CastSpell(FROST_NOVA, pTarget))
                {
                    m_bot->GetMotionMaster()->MoveFleeing(pTarget, 0.5);
                    return RETURN_CONTINUE;
                }
				if (CONE_OF_COLD > 0 && meleeReach && !pTarget->HasAura(CONE_OF_COLD, EFFECT_INDEX_0) && CastSpell(CONE_OF_COLD, pTarget))
					return RETURN_CONTINUE;
                if (BLIZZARD > 0 && !meleeReach && m_ai->In_Reach(pTarget, BLIZZARD) && CastSpell(BLIZZARD, pTarget))
                {
                    m_ai->SetIgnoreUpdateTime(8);
                    return RETURN_CONTINUE;
                }				
			}
            if (FROSTBOLT > 0 && m_ai->In_Reach(pTarget,FROSTBOLT))
                return CastSpell(FROSTBOLT, pTarget);
            break;

        case MAGE_SPEC_FIRE:
            if (m_ai->GetFightFlg() && m_ai->GetAttackerCount() >= 4)
            {
                if (FROST_NOVA > 0 && meleeReach && m_bot->IsSpellReady(FROST_NOVA) && !pTarget->HasAura(FROST_NOVA, EFFECT_INDEX_0) && CastSpell(FROST_NOVA, pTarget))
                {
                    m_bot->GetMotionMaster()->MoveFleeing(pTarget, 0.5);
                    return RETURN_CONTINUE;
                }
                if (FLAMESTRIKE > 0 && m_ai->In_Reach(pTarget, FLAMESTRIKE) && !pTarget->HasAura(FLAMESTRIKE) && CastSpell(FLAMESTRIKE, pTarget))
                {
                    return RETURN_CONTINUE;
                }
                if (BLAST_WAVE > 0 && m_bot->GetCombatDistance(pTarget) < 8.0f && m_bot->IsSpellReady(BLAST_WAVE) && CastSpell(BLAST_WAVE, pTarget))
                {          
                    return RETURN_CONTINUE;
                }           
                if (ARCANE_EXPLOSION>0 && m_bot->GetCombatDistance(pTarget) < 8.0f && CastSpell(ARCANE_EXPLOSION, pTarget))
                {
                    return RETURN_CONTINUE;
                }
            }
            if (SCORCH > 0 && m_ai->In_Reach(pTarget, SCORCH) && SpellSequence < 6 && CastSpell(SCORCH, pTarget))
		    {
			    SpellSequence = SpellSequence + 1;
			    return RETURN_CONTINUE;
		    }
		    if (SCORCH > 0 && m_ai->In_Reach(pTarget, SCORCH) && !pTarget->HasAura(22959) && CastSpell(SCORCH, pTarget))
		    {
			    SpellSequence = 0;
			    return RETURN_CONTINUE;
		    }
		    if (COMBUSTION > 0 && m_ai->In_Reach(m_bot, COMBUSTION) && !m_bot->HasAura(COMBUSTION, EFFECT_INDEX_0) && m_bot->IsSpellReady(COMBUSTION) && CastSpell(COMBUSTION, m_bot))
			    return RETURN_CONTINUE;
		    if (PYROBLAST > 0 && m_ai->In_Reach(pTarget, PYROBLAST) && m_bot->HasAura(12536) && CastSpell(PYROBLAST, pTarget))
			    return RETURN_CONTINUE;
		    if (FIRE_BLAST > 0 && m_ai->In_Reach(pTarget, FIRE_BLAST) && m_bot->IsSpellReady(FIRE_BLAST) && CastSpell(FIRE_BLAST, pTarget))
			    return RETURN_CONTINUE;
		    if (FIREBALL > 0 && m_ai->In_Reach(pTarget, FIREBALL))
			    return CastSpell(FIREBALL, pTarget);
            break;

        case MAGE_SPEC_ARCANE:
			if (ICE_BLOCK > 0 && m_ai->In_Reach(m_bot, ICE_BLOCK) && !m_bot->HasAura(ICE_BLOCK, EFFECT_INDEX_0) && m_ai->GetHealthPercent() < 20 && m_bot->IsSpellReady(ICE_BLOCK) && CastSpell(ICE_BLOCK, m_bot))
			{
				m_ai->SetIgnoreUpdateTime(10);
				return RETURN_CONTINUE;
			}
            if (ARCANE_POWER > 0 && m_bot->IsSpellReady(ARCANE_POWER) && CastSpell(ARCANE_POWER))
                return RETURN_CONTINUE;
            /*if (ARCANE_MISSILES > 0 && m_ai->In_Reach(pTarget,ARCANE_MISSILES) && CastSpell(ARCANE_MISSILES, pTarget))
            {
                m_ai->SetIgnoreUpdateTime(3);
                return RETURN_CONTINUE;
            }
            if (ARCANE_EXPLOSION > 0 && m_ai->GetAttackerCount() >= 3 && meleeReach && CastSpell(ARCANE_EXPLOSION, pTarget))
                return RETURN_CONTINUE;
            if (COUNTERSPELL > 0 && pTarget->IsNonMeleeSpellCasted(true) && CastSpell(COUNTERSPELL, pTarget))
                return RETURN_CONTINUE;
            if (SLOW > 0 && m_ai->In_Reach(pTarget,SLOW) && !pTarget->HasAura(SLOW, EFFECT_INDEX_0) && CastSpell(SLOW, pTarget))
                return RETURN_CONTINUE;
            if (MANA_SHIELD > 0 && m_ai->GetHealthPercent() < 50 && pVictim == m_bot && !m_bot->HasAura(MANA_SHIELD, EFFECT_INDEX_0) && CastSpell(MANA_SHIELD, m_bot))
                return RETURN_CONTINUE;*/
			if (PRESENCE_OF_MIND > 0 && m_bot->IsSpellReady(PRESENCE_OF_MIND) && CastSpell(PRESENCE_OF_MIND))
				return RETURN_CONTINUE;
			if (m_ai->GetFightFlg() && m_ai->GetAttackerCount() >= 4)
			{
                if (FROST_NOVA > 0 && meleeReach && m_bot->IsSpellReady(FROST_NOVA) && !pTarget->HasAura(FROST_NOVA, EFFECT_INDEX_0) && CastSpell(FROST_NOVA, pTarget))
                {
                    m_bot->GetMotionMaster()->MoveFleeing(pTarget, 0.5);
                    return RETURN_CONTINUE;
                }
                if (CONE_OF_COLD > 0 && meleeReach && !pTarget->HasAura(CONE_OF_COLD, EFFECT_INDEX_0) && CastSpell(CONE_OF_COLD, pTarget))
                    return RETURN_CONTINUE;
                if (BLIZZARD > 0 && !meleeReach && m_ai->In_Reach(pTarget, BLIZZARD) && CastSpell(BLIZZARD, pTarget))
                {
                    m_ai->SetIgnoreUpdateTime(8);
                    return RETURN_CONTINUE;
                }
			}
			if (FROSTBOLT > 0 && m_ai->In_Reach(pTarget, FROSTBOLT))
				return CastSpell(FROSTBOLT, pTarget);
            break;

        default:
            // No spec due to low level OR no spell found yet
            if (FROSTBOLT > 0 && m_ai->In_Reach(pTarget, FROSTBOLT) && !pTarget->HasAura(FROSTBOLT, EFFECT_INDEX_0))
                return CastSpell(FROSTBOLT, pTarget);
            if (FIREBALL > 0 && m_ai->In_Reach(pTarget, FIREBALL)) // Very low levels
                return CastSpell(FIREBALL, pTarget);
            break;
    }
  

    // Default: shoot with wand
    return CastSpell(SHOOT, pTarget);

    return RETURN_NO_ACTION_ERROR; // What? Not even Fireball is available?
} // end DoNextCombatManeuver

CombatManeuverReturns PlayerbotMageAI::DoNextCombatManeuverPVP(Unit* pTarget)
{
    if (FIREBALL && m_ai->In_Reach(pTarget,FIREBALL) && m_ai->CastSpell(FIREBALL))
        return RETURN_CONTINUE;

    return DoNextCombatManeuverPVE(pTarget); // TODO: bad idea perhaps, but better than the alternative
}

static const uint32 uPriorizedManaGemIds[4] =
{
    MANA_RUBY_DISPLAYID, MANA_CITRINE_DISPLAYID, MANA_AGATE_DISPLAYID, MANA_JADE_DISPLAYID
};

// Return a mana gem Item based on the priorized list
Item* PlayerbotMageAI::FindManaGem() const
{
    Item* gem;
    for (uint8 i = 0; i < countof(uPriorizedManaGemIds); ++i)
    {
        gem = m_ai->FindConsumable(uPriorizedManaGemIds[i]);
        if (gem)
            return gem;
    }
    return nullptr;
}

void PlayerbotMageAI::DoNonCombatActions()
{
    Player* master = GetMaster();

    if (!m_bot || !master)
        return;

	// Remove curse on group members
    if (Player* pCursedTarget = GetDispelTarget(DISPEL_CURSE))
    {
        if (MAGE_REMOVE_CURSE > 0 && CastSpell(MAGE_REMOVE_CURSE, pCursedTarget))
            return;
    }
	
    // Buff armor
    if (MAGE_ARMOR)
    {
        if (m_ai->SelfBuff(MAGE_ARMOR))
            return;
    }
    else if (ICE_ARMOR)
    {
        if (m_ai->SelfBuff(ICE_ARMOR))
            return;
    }
    else if (FROST_ARMOR)
        if (m_ai->SelfBuff(FROST_ARMOR))
            return;

    // buff group
    if (m_ai->GetFightFlg())
    {
        // the check for group targets is performed by NeedGroupBuff (if group is found for bots by the function)
        if (NeedGroupBuff(ARCANE_BRILLIANCE, ARCANE_INTELLECT) && m_ai->HasSpellReagents(ARCANE_BRILLIANCE))
        {
            if (Buff(&PlayerbotMageAI::BuffHelper, ARCANE_BRILLIANCE) & RETURN_CONTINUE)
                return;
        }
        else if (Buff(&PlayerbotMageAI::BuffHelper, ARCANE_INTELLECT) & RETURN_CONTINUE)
            return;
    }

	Item* gem = FindManaGem();
    if (!gem && CONJURE_MANA_GEM && m_ai->CastSpell(CONJURE_MANA_GEM, *m_bot))
    {
        m_ai->SetIgnoreUpdateTime(3);
        return;
    }
	
    // TODO: The beauty of a mage is not only its ability to supply itself with water, but to share its water
    // So, conjure at *least* 1.25 stacks, ready to trade a stack and still have some left for self
    if (m_ai->FindDrink() == nullptr && CONJURE_WATER && m_ai->CastSpell(CONJURE_WATER, *m_bot))
    {
        m_ai->TellMaster("我渴了，自己烧点水喝.");
        m_ai->SetIgnoreUpdateTime(3);
        return;
    }
    if (m_ai->FindFood() == nullptr && CONJURE_FOOD && m_ai->CastSpell(CONJURE_FOOD, *m_bot))
    {
        m_ai->TellMaster("我饿了，自己做点吃的.");
        m_ai->SetIgnoreUpdateTime(3);
        return;
    }

    if (EatDrinkBandage())
        return;
	
    m_ai->AutoRepair();

	if (master && master ->HasAuraType(SPELL_AURA_MOUNTED))
	{
		Item* partialMatch = m_ai -> FindMount(150) ;
		if (partialMatch)
		m_ai->UseItem(partialMatch);		
	}
	
} // end DoNonCombatActions

// TODO: this and priest's BuffHelper are identical and thus could probably go in PlayerbotClassAI.cpp somewhere
bool PlayerbotMageAI::BuffHelper(PlayerbotAI* ai, uint32 spellId, Unit *target)
{
    if (!ai)          return false;
    if (spellId == 0) return false;
    if (!target)      return false;

    Pet* pet = target->GetPet();
    if (pet && pet->isAlive() && !pet->HasAuraType(SPELL_AURA_MOD_UNATTACKABLE) && ai->Buff(spellId, pet))
        return true;

    if (ai->Buff(spellId, target))
        return true;

    return false;
}

// Return to UpdateAI the spellId usable to neutralize a target with creaturetype
uint32 PlayerbotMageAI::Neutralize(uint8 creatureType)
{
    if (!m_bot)         return 0;
    if (!m_ai)          return 0;
    if (!creatureType)  return 0;

    if (creatureType != CREATURE_TYPE_HUMANOID && creatureType != CREATURE_TYPE_BEAST)
    {
        m_ai->TellMaster("I can't polymorph that target.");
        return 0;
    }

    if (POLYMORPH)
        return POLYMORPH;
    else
        return 0;

    return 0;
}