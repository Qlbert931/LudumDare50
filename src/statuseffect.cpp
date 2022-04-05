// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "statuseffect.h"

StatusEffectInstance* BuffLifesteal::GetInstance(Context& ctx) {
	return nullptr;
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
	return TextFormat("Adds a buff giving %03.00f% lifesteal for %i turns.", (float)Strength, TurnCounter);
}

bool BuffLifesteal::IsBuff(Context& ctx) {
	return true;
}

StatusEffectInstance* BuffLucky::GetInstance(Context& ctx) { return nullptr; }

void BuffLucky::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
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
	return TextFormat("Adds a buff giving 100% Critical Chance for %i turns.", TurnCounter);
}

bool BuffLucky::IsBuff(Context& ctx) {
	return true;
}

StatusEffectInstance* BuffAdrenaline::GetInstance(Context& ctx) { return nullptr; }

void BuffAdrenaline::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	character.PhysicalAttack *= AttackBoost;
	character.SpecialAttack *= AttackBoost;
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
	return TextFormat("Adds a buff boosting attack by 150% for %i turns", TurnCounter);
}

bool BuffAdrenaline::IsBuff(Context& ctx) {
	return true;
}

StatusEffectInstance* BuffElemental::GetInstance(Context& ctx) { return nullptr; }

void BuffElemental::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	chosenType = GetRandomValue(0, 4);
	switch(chosenType) {
		case 1:
			character.ElectricResistance += resistanceBoost;
		case 2:
			character.WaterResistance += resistanceBoost;
		case 3:
			character.WindResistance += resistanceBoost;
		case 4:
			character.FireResistance += resistanceBoost;
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
	return TextFormat("Adds a buff boosting resistance against the elements", TurnCounter);
}
bool BuffElemental::IsBuff(Context& ctx) { return true; }

StatusEffectInstance* DebuffPoison::GetInstance(Context& ctx) { return nullptr; }
void DebuffPoison::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	character.Parent.CurrentHealth -= poisonDmg;
}
void DebuffPoison::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageDealt) {}
void DebuffPoison::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffPoison::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageReceived) {}
Sprite* DebuffPoison::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Poison, options);
}
std::string DebuffPoison::Description(Context& ctx) {
	return TextFormat("Adds a debuff reducing their health through poison", TurnCounter);
}
bool DebuffPoison::IsBuff(Context& ctx) { return false; }

StatusEffectInstance* DebuffBleed::GetInstance(Context& ctx) { return nullptr; }
void DebuffBleed::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	character.Parent.CurrentHealth -= bleedDmg;
}
void DebuffBleed::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageDealt) {}
void DebuffBleed::PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffBleed::PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageReceived) {}
Sprite* DebuffBleed::GetSprite(Context& ctx, const Component::Options& options) {
	return new Sprite(ctx, SpriteName::Bleed, options);
}
std::string DebuffBleed::Description(Context& ctx) {
	return TextFormat("Adds a debuff forcing them to bleed away their health for i% turns", TurnCounter);
}
bool DebuffBleed::IsBuff(Context& ctx) { return false; }

StatusEffectInstance* DebuffSleep::GetInstance(Context& ctx) { return nullptr; }
void DebuffSleep::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {
	if (instance.TurnsRemaining > 0) {
		asleep = true;
	}
	else {
		asleep = false;
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

StatusEffectInstance* DebuffSick::GetInstance(Context& ctx) { return nullptr; }
void DebuffSick::PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) {}
void DebuffSick::PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance,int damageDealt) {
	character.Parent.CurrentHealth -= character.PhysicalAttack*sickDamage;
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
	return TextFormat("Adds a debuff inflicting damage depending on higher attack damage for i% turns", TurnCounter);
}
bool DebuffSick::IsBuff(Context& ctx) { return false; }