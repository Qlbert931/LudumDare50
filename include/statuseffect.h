// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef STATUSEFFECT_H
#define STATUSEFFECT_H
#include "character.h"

class StatusEffectInstance;

class StatusEffect {
public:
	virtual ~StatusEffect() {}
	virtual StatusEffectInstance* GetInstance(Context& ctx) = 0;
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
	int TurnsRemaining;
};

class BuffLifesteal : public StatusEffect {
public:
	StatusEffectInstance* GetInstance(Context& ctx) override;
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
	StatusEffectInstance* GetInstance(Context& ctx) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	double CritChance = 100;
};

class BuffAdrenaline : public StatusEffect {
	StatusEffectInstance* GetInstance(Context& ctx) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	double AttackBoost = 1.5;
};

class BuffElemental : public StatusEffect {
	StatusEffectInstance* GetInstance(Context& ctx) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	int chosenType;
	double resistanceBoost = 100;
};

class DebuffPoison : public StatusEffect {
	StatusEffectInstance* GetInstance(Context& ctx) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	int poisonDmg = 10;
};

class DebuffBleed : public StatusEffect {
	StatusEffectInstance* GetInstance(Context& ctx) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	int bleedDmg = 25;
};

class DebuffSleep : public StatusEffect {
	StatusEffectInstance* GetInstance(Context& ctx) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	bool asleep = false;
};

class DebuffSick : public StatusEffect {
	StatusEffectInstance* GetInstance(Context& ctx) override;
	void PreAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostAttack(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageDealt) override;
	void PreHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance) override;
	void PostHit(Context& ctx, CharacterInstance& character, StatusEffectInstance& instance, int damageReceived) override;
	Sprite* GetSprite(Context& ctx, const Component::Options& options) override;
	std::string Description(Context& ctx) override;
	bool IsBuff(Context& ctx) override;

	int TurnCounter;
	double sickDamage = .15;
};

#endif //STATUSEFFECT_H
