// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "enemy.h"
#include "state.h"
#include "statuseffect.h"

Enemy::Enemy(Context& ctx, double currentTime, bool isBoss) {
	//TODO: generate enemy stats
	double bossMult = 1;

	Name = "Test Name";
	spriteName = SpriteName::Dragon;
	IsBoss = isBoss;
	if (isBoss) { bossMult = 2.0; }

	Health = 100 * ctx.GameState->CurrentRun.ElapsedTime * bossMult;
	CurrentHealth = 5;

	double attackBalancer = GetRandomValue(0, 1) * bossMult;

	PhysicalAttack = 75 * ctx.GameState->CurrentRun.ElapsedTime * bossMult * attackBalancer;
	SpecialAttack = (attackBalancer*100 - PhysicalAttack) * bossMult * ctx.GameState->CurrentRun.ElapsedTime;

	double armorBalancer = GetRandomValue(0, 1) * bossMult;

	PhysicalArmor = 75 * ctx.GameState->CurrentRun.ElapsedTime * bossMult * armorBalancer;
	SpecialArmor = 75 * ctx.GameState->CurrentRun.ElapsedTime * bossMult * armorBalancer;;
	Speed = 75 * ctx.GameState->CurrentRun.ElapsedTime * bossMult;
	EncounterTime = currentTime;
	fireResistance = GetRandomValue(30, 50) * ctx.GameState->CurrentRun.ElapsedTime * bossMult;
	waterResistance = GetRandomValue(30, 50) * ctx.GameState->CurrentRun.ElapsedTime * bossMult;
	electricResistance = GetRandomValue(30, 50) * ctx.GameState->CurrentRun.ElapsedTime * bossMult;
	windResistance = GetRandomValue(30, 50) * ctx.GameState->CurrentRun.ElapsedTime * bossMult;
}

Enemy::~Enemy() {
	//TODO: is this needed?
}

int Enemy::Level(Context& ctx) {
	return (int)(EncounterTime / 10);
}

double Enemy::FireResistance(Context& ctx) {
	return fireResistance;
}

double Enemy::WaterResistance(Context& ctx) {
	return waterResistance;
}

double Enemy::ElectricResistance(Context& ctx) {
	return electricResistance;
}

double Enemy::WindResistance(Context& ctx) {
	return windResistance;
}

CharacterInstance& Enemy::Instance(Context& ctx) {
	instance.MaxHealth = Health;
	instance.CurrentHealth = CurrentHealth;
	instance.PhysicalAttack = PhysicalAttack;
	instance.SpecialAttack = SpecialAttack;
	instance.PhysicalArmor = PhysicalArmor;
	instance.SpecialArmor = SpecialArmor;
	instance.Speed = Speed;
	instance.Evasion = 0;
	instance.CritChance = 0;
	instance.CritMultiplier = 1;
	instance.DebuffResistance = (IsBoss) ? .5 : 0;
	instance.FireResistance = fireResistance;
	instance.WaterResistance = waterResistance;
	instance.ElectricResistance = electricResistance;
	instance.WindResistance = windResistance;
	return instance;
}

Sprite* Enemy::GetSprite(Context& ctx, const Component::Options& options) {
	Color color = WHITE;
	if (!(fireResistance == waterResistance && waterResistance == electricResistance && electricResistance == windResistance)) {
		RuneAttribute::Element leadingElement = RuneAttribute::Element::Fire;
		double leadingElementVal = fireResistance;
		if (waterResistance > leadingElementVal) {
			leadingElement = RuneAttribute::Element::Water;
			leadingElementVal = waterResistance;
		}
		if (electricResistance > leadingElementVal) {
			leadingElement = RuneAttribute::Element::Electric;
			leadingElementVal = electricResistance;
		}
		if (windResistance > leadingElementVal) {
			leadingElement = RuneAttribute::Element::Wind;
			leadingElementVal = windResistance;
		}
		switch (leadingElement) {
			case RuneAttribute::Fire:
				color = ctx.Colors.ElementFire;
				break;
			case RuneAttribute::Water:
				color = ctx.Colors.ElementWater;
				break;
			case RuneAttribute::Electric:
				color = ctx.Colors.ElementElectric;
				break;
			case RuneAttribute::Wind:
				color = ctx.Colors.ElementWind;
				break;
		}
	}
	Component::Options newOptions = options;
	return new Sprite(ctx, spriteName, newOptions.WithDefaultColor(color));
}

Component* Enemy::GenerateComponent(Context& ctx, const Component::Options& options) {
	auto panel = new VerticalPanel(ctx, options);
	auto topRow = new Label(ctx, TextFormat("Lv. %i %s", Level(ctx), Name.c_str()), {.WidthScale = 1, .HeightScale = .15, .DefaultColor = WHITE});
	auto healthRow = new ProgressBar(ctx, {.WidthScale = .98, .HeightScale = .13, .DefaultColor = ctx.Colors.HealthBar}, &Health, &CurrentHealth);
	auto spriteRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .55});
	auto resistancesRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .10});
	auto statusEffectsRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .07});
	*panel += topRow;
	*panel += healthRow;
	*panel += spriteRow;
	*panel += resistancesRow;
	*panel += statusEffectsRow;

	// Sprite Row
	*spriteRow += GetSprite(ctx, {.WidthScale = .7, .HeightScale = 1});
	auto attackArmorColumn = new VerticalPanel(ctx, {.WidthScale = .3, .HeightScale = 1});
	*spriteRow += attackArmorColumn;
	if (PhysicalAttack > SpecialAttack) {
		*attackArmorColumn += new Sprite(ctx, SpriteName::PhysicalAttack, {.WidthScale = 1, .HeightScale = .25});
		*attackArmorColumn += new Label(ctx, TextFormat("%i", PhysicalAttack), {.WidthScale = 1, .HeightScale = .25, .DefaultColor = WHITE});
	} else {
		*attackArmorColumn += new Sprite(ctx, SpriteName::SpecialAttack, {.WidthScale = 1, .HeightScale = .25});
		*attackArmorColumn += new Label(ctx, TextFormat("%i", SpecialAttack), {.WidthScale = 1, .HeightScale = .25, .DefaultColor = WHITE});
	}
	if (PhysicalArmor > SpecialArmor) {
		*attackArmorColumn += new Sprite(ctx, SpriteName::PhysicalArmor, {.WidthScale = 1, .HeightScale = .25});
		*attackArmorColumn += new Label(ctx, TextFormat("%i", PhysicalArmor), {.WidthScale = 1, .HeightScale = .25, .DefaultColor = WHITE});
	} else {
		*attackArmorColumn += new Sprite(ctx, SpriteName::SpecialArmor, {.WidthScale = 1, .HeightScale = .25});
		*attackArmorColumn += new Label(ctx, TextFormat("%i", SpecialArmor), {.WidthScale = 1, .HeightScale = .25, .DefaultColor = WHITE});
	}

	// Resistances Row
	auto resistanceSpriteOption = Component::Options{.WidthScale = .1, .HeightScale = 1};
	auto resistanceLabelOption = Component::Options{.WidthScale = .15, .HeightScale = 1, .DefaultColor = WHITE};
	*resistancesRow += new Sprite(ctx, SpriteName::FireResistance, resistanceSpriteOption);
	*resistancesRow += new Label(ctx, TextFormat("%i%%", (int)(100.0 * fireResistance)), resistanceLabelOption);
	*resistancesRow += new Sprite(ctx, SpriteName::WaterResistance, resistanceSpriteOption);
	*resistancesRow += new Label(ctx, TextFormat("%i%%", (int)(100.0 * waterResistance)), resistanceLabelOption);
	*resistancesRow += new Sprite(ctx, SpriteName::ElectricResistance, resistanceSpriteOption);
	*resistancesRow += new Label(ctx, TextFormat("%i%%", (int)(100.0 * electricResistance)), resistanceLabelOption);
	*resistancesRow += new Sprite(ctx, SpriteName::WindResistance, resistanceSpriteOption);
	*resistancesRow += new Label(ctx, TextFormat("%i%%", (int)(100.0 * windResistance)), resistanceLabelOption);

	// Buff/Debuff Row
	auto statusEffectOption = Component::Options{.WidthScale = .1, .HeightScale = 1};
	for (StatusEffectInstance* statusEffect : ctx.GameState->CurrentBattle.StatusEffects) {
		if (statusEffect->IsCaster(ctx, *this) && statusEffect->IsBuff(ctx)) {
			*statusEffectsRow += statusEffect->StatusEffect.GetSprite(ctx, statusEffectOption);
		} else if (statusEffect->IsTarget(ctx, *this) && !statusEffect->IsBuff(ctx)) {
			*statusEffectsRow += statusEffect->StatusEffect.GetSprite(ctx, statusEffectOption);
		}
	}

	return panel;
}
