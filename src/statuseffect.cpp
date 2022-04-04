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
