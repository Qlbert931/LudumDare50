// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef STATUSEFFECT_H
#define STATUSEFFECT_H
#include "character.h"
#include "state.h"

class StatusEffectInstance;

class StatusEffect {
public:
	virtual ~StatusEffect() {}
	virtual StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) = 0;
	virtual void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) = 0;
	virtual void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) = 0;
	virtual void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) = 0;
	virtual void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) = 0;
	virtual bool IsBuff(Context& ctx) = 0;
	virtual Sprite* GetSprite(Context& ctx, const Component::Options& options) = 0;
	virtual std::string Description(Context& ctx) = 0;
};

class StatusEffectInstance {
public:
	StatusEffectInstance(StatusEffect& status, Character& target, Character& caster) : StatusEffect(status), Target(target), Caster(caster) {};
	void PreAttack(Context& ctx, CharacterInstance& character) { StatusEffect.PreAttack(ctx, character, *this); };
	void PostAttack(Context& ctx, CharacterInstance& character, int damageDealt) { StatusEffect.PostAttack(ctx, character, *this, damageDealt); };
	void PreHit(Context& ctx, CharacterInstance& character) { StatusEffect.PreHit(ctx, character, *this); };
	void PostHit(Context& ctx, CharacterInstance& character, int damageReceived) { StatusEffect.PostHit(ctx, character, *this, damageReceived); };
	bool IsCaster(Context& ctx, Character& character) { return &Caster == &character; }
	bool IsTarget(Context& ctx, Character& character) { return &Target == &character; }
	bool IsBuff(Context& ctx) { return StatusEffect.IsBuff(ctx); }
	bool ShouldRemoveInstance(Context& ctx) { return TurnsRemaining != -1 && TurnsRemaining <= 0; }

	StatusEffect& StatusEffect;
	Character& Target;
	Character& Caster;
	int TurnsRemaining{};
};

class BuffLifesteal : public StatusEffect {
public:
	BuffLifesteal(double strength) {
		TurnCounter = 0;
		Strength = strength/2;
	};

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	double Strength;
};

class BuffLucky : public StatusEffect {
public:
	BuffLucky(double critChance){
		TurnCounter = 0;
		CritChance = critChance; //100;
	};

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	double CritChance;
};

class BuffAdrenaline : public StatusEffect {
public:
	BuffAdrenaline (double attackBoost) {
		TurnCounter = 0;
		AttackBoost = attackBoost/2;
	};

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	double AttackBoost;
};

class BuffElemental : public StatusEffect {
public:
	BuffElemental( double resistanceBoost) {
		TurnCounter = 0;
		chosenType = 0;
		ResistanceBoost = resistanceBoost;
	};

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	int chosenType;
	double ResistanceBoost;
};

class DebuffPoison : public StatusEffect {
public:
	DebuffPoison(double poisonDmg) {
		TurnCounter = 0;
		PoisonDmg = 10;
	};

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	int PoisonDmg;
};

class DebuffBleed : public StatusEffect {
public:
	DebuffBleed(double bleedDmg) {
		TurnCounter = 0;
		BleedDmg = bleedDmg;
	};

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	int BleedDmg;
};

class DebuffSleep : public StatusEffect {
public:
	DebuffSleep() {
		TurnCounter = 0;
		asleep = false;
	};

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	bool asleep;
};

class DebuffSick : public StatusEffect {
public:
	DebuffSick(double sickMult) {
		TurnCounter = 0;
		SickMult = sickMult;
	};

	StatusEffectInstance* GetInstance(Context& ctx, Character& target, Character& caster) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	double SickMult = .15;
};

#endif //STATUSEFFECT_H
