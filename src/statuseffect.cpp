// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "statuseffect.h"

StatusEffectInstance* BuffLifesteal::GetInstance(Context& ctx, Character& target, Character& caster) {
	return new StatusEffectInstance(*this, target, caster);
}

void BuffLifesteal::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}

void BuffLifesteal::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) {
	if (instance.TurnsRemaining > 0) {
		instance.TurnsRemaining -= 1;
	}
}

void BuffLifesteal::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}

void BuffLifesteal::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) {
	if (&character.Parent != &instance.Target) {
		return;
	}
	int healAmount = (int)((double)damageReceived * Strength);
	instance.Caster.CurrentHealth += healAmount;
	if (instance.Caster.CurrentHealth > instance.Caster.Health) {
		instance.Caster.CurrentHealth = instance.Caster.Health;
	}
}

Sprite* BuffLifesteal::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Lifesteal, options);
}

std::string BuffLifesteal::Description(Context& ctx) {
	return TextFormat("Adds a buff giving %03.00f% life steal for %i turns.", (float)Strength, TurnCounter);
}

bool BuffLifesteal::IsBuff(Context& ctx) {
	return true;
}

StatusEffectInstance* BuffLucky::GetInstance (Context& ctx, Character& target, Character& caster) {
	return new StatusEffectInstance(*this, target, caster);
}

void BuffLucky::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	CritChance += CritChance * ctx.GameState->CurrentRun.ElapsedTime;
	character.CritChance = CritChance;
}
void BuffLucky::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageDealt) {
	if (instance.TurnsRemaining > 0) {
		instance.TurnsRemaining -= 1;
	}
}
void BuffLucky::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void BuffLucky::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,	int damageReceived) {}

Sprite* BuffLucky::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Lucky, options);
}

std::string BuffLucky::Description(Context& ctx) {
	return TextFormat("Adds a buff giving %03.00f% additional Critical Chance for %i turns.", (float) CritChance, TurnCounter);
}

bool BuffLucky::IsBuff(Context& ctx) {
	return true;
}

StatusEffectInstance* BuffAdrenaline::GetInstance (Context& ctx, Character& target, Character& caster) {
	return new StatusEffectInstance(*this, target, caster);
}

void BuffAdrenaline::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	AttackBoost += AttackBoost * ctx.GameState->CurrentRun.ElapsedTime;
	character.PhysicalAttack *= (int) AttackBoost;
	character.SpecialAttack *= (int) AttackBoost;
}
void BuffAdrenaline::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageDealt) {
	if (instance.TurnsRemaining > 0) {
		instance.TurnsRemaining -= 1;
	}
}
void BuffAdrenaline::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void BuffAdrenaline::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageReceived) {}
Sprite* BuffAdrenaline::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Adrenaline, options);
}
std::string BuffAdrenaline::Description(Context& ctx) {
	return TextFormat("Adds a buff boosting attack by %03.00f% for %i turns", (float) AttackBoost, TurnCounter);
}

bool BuffAdrenaline::IsBuff(Context& ctx) {
	return true;
}

StatusEffectInstance* BuffElemental::GetInstance (Context& ctx, Character& target, Character& caster) {
	return new StatusEffectInstance(*this, target, caster);
}

void BuffElemental::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	chosenType = GetRandomValue(0, 4);
	ResistanceBoost += ResistanceBoost * ctx.GameState->CurrentRun.ElapsedTime;
	switch(chosenType) {
		case 1:
			character.ElectricResistance += ResistanceBoost;
		case 2:
			character.WaterResistance += ResistanceBoost;
		case 3:
			character.WindResistance += ResistanceBoost;
		case 4:
			character.FireResistance += ResistanceBoost;
	}
}
void BuffElemental::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageDealt) {
	if (instance.TurnsRemaining > 0) {
		instance.TurnsRemaining -= 1;
	}
}

void BuffElemental::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void BuffElemental::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageReceived) {}
Sprite* BuffElemental::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::ElementalShield, options);
}
std::string BuffElemental::Description(Context& ctx) {
	switch(chosenType) {
		case 1:
			return TextFormat("Adds a buff boosting Electric resistance by %03.00f% for %i turns.", (float) ResistanceBoost, TurnCounter);
		case 2:
			return TextFormat("Adds a buff boosting Water resistance by %03.00f% for %i turns.", (float) ResistanceBoost, TurnCounter);
		case 3:
			return TextFormat("Adds a buff boosting Wind resistance by %03.00f% for %i turns.", (float) ResistanceBoost, TurnCounter);
		case 4:
			return TextFormat("Adds a buff boosting Fire resistance by %03.00f% for %i turns.", (float) ResistanceBoost, TurnCounter);
	}
	return TextFormat("");
}
bool BuffElemental::IsBuff(Context& ctx) { return true; }

StatusEffectInstance* DebuffPoison::GetInstance (Context& ctx, Character& target, Character& caster) {
	return new StatusEffectInstance(*this, target, caster);
}

void DebuffPoison::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	PoisonDmg += (int) ctx.GameState->CurrentRun.ElapsedTime * PoisonDmg;
	character.Parent.CurrentHealth -= PoisonDmg;
}
void DebuffPoison::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageDealt) {}
void DebuffPoison::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffPoison::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageReceived) {}
Sprite* DebuffPoison::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Poison, options);
}
std::string DebuffPoison::Description(Context& ctx) {
	return TextFormat("Adds a debuff applying %03.00f% poison damage for %i turns.",(float) PoisonDmg, TurnCounter);
}
bool DebuffPoison::IsBuff(Context& ctx) { return false; }

StatusEffectInstance* DebuffBleed::GetInstance (Context& ctx, Character& target, Character& caster) {
	return new StatusEffectInstance(*this, target, caster);
}

void DebuffBleed::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	BleedDmg += (int) ctx.GameState->CurrentRun.ElapsedTime * BleedDmg;
	character.Parent.CurrentHealth -= BleedDmg;
}
void DebuffBleed::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageDealt) {}
void DebuffBleed::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffBleed::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageReceived) {}
Sprite* DebuffBleed::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Bleed, options);
}
std::string DebuffBleed::Description(Context& ctx) {
	return TextFormat("Adds a debuff bleeding for %03.00f% damage for %i turns.", (float) BleedDmg, TurnCounter);
}
bool DebuffBleed::IsBuff(Context& ctx) { return false; }

StatusEffectInstance* DebuffSleep::GetInstance (Context& ctx, Character& target, Character& caster) {
	return new StatusEffectInstance(*this, target, caster);
}

void DebuffSleep::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	if (instance.TurnsRemaining > 0) {
		asleep = true;
	}
	else {
		asleep = false;
	}

	if (asleep) {
		// skip turn
	}
}
void DebuffSleep::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageDealt) {
	if (instance.TurnsRemaining > 0) {
		instance.TurnsRemaining -= 1;
	}
}
void DebuffSleep::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffSleep::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageReceived) {}
Sprite* DebuffSleep::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Sleep, options);
}
std::string DebuffSleep::Description(Context& ctx) {
	return TextFormat("Adds a debuff sleeping the affected for i% turns", TurnCounter);
}
bool DebuffSleep::IsBuff(Context& ctx) { return false; }

StatusEffectInstance* DebuffSick::GetInstance (Context& ctx, Character& target, Character& caster) {
	return new StatusEffectInstance(*this, target, caster);
}
void DebuffSick::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffSick::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageDealt) {
	SickMult = character.PhysicalAttack * SickMult + ctx.GameState->CurrentRun.ElapsedTime * SickMult;
	character.Parent.CurrentHealth -= (int) SickMult;
	if (instance.TurnsRemaining > 0) {
		instance.TurnsRemaining -= 1;
	}
}
void DebuffSick::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffSick::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageReceived) {}
Sprite* DebuffSick::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Sick, options);
}
std::string DebuffSick::Description(Context& ctx) {
	return TextFormat("Adds a debuff inflicting %03.00f% damage per their physical damage for i% turns", (float) SickMult, TurnCounter);
}
bool DebuffSick::IsBuff(Context& ctx) { return false; }
