// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "rune.h"
#include "cstdio"

Sprite* getSprite(Context& ctx, RuneAttribute::Target target, const Component::Options& options);
Sprite* getSprite(Context& ctx, RuneAttribute::AttackType attackType, const Component::Options& options);
Sprite* getSprite(Context& ctx, RuneAttribute::Element element, const Component::Options& options);

Rune::Rune(Context& ctx) {
	Name = "RuneNameGoesHere";
	Level = GetRandomValue(0, 50);
	AdditionalLevel = GetRandomValue(0, 5);
	Target = (RuneAttribute::Target)GetRandomValue(0, 4);
	Rarity = (RuneAttribute::Rarity)GetRandomValue(0, 4);
	AttackType = (RuneAttribute::AttackType)GetRandomValue(0, 1);
	Element = (RuneAttribute::Element)GetRandomValue(0, 6);
	FlatDamage = GetRandomValue(0, 500);
	//Buffs
	//Debuffs
	//Effect
	CritChance = (double)GetRandomValue(10, 200) / 100.0;
	CritMultiplier = (double)GetRandomValue(110, 400) / 100.0;
}

Color Rune::GetRarityColor(Context& ctx) {
	switch (Rarity) {
		case RuneAttribute::Common:
			return ctx.Colors.RarityCommon;
		case RuneAttribute::Uncommon:
			return ctx.Colors.RarityUncommon;
		case RuneAttribute::Rare:
			return ctx.Colors.RarityRare;
		case RuneAttribute::Epic:
			return ctx.Colors.RarityEpic;
		case RuneAttribute::Legendary:
			return ctx.Colors.RarityLegendary;
	}
	return WHITE;
}

std::string Rune::FormatName(Context& ctx, int additionalLevels) {
	if (AdditionalLevel <= 0) {
		return Name;
	} else {
		return std::string(TextFormat("%s +%i", Name.c_str(), additionalLevels));
	}
}

std::string Rune::FormattedName(Context& ctx) {
	return FormatName(ctx, (int)AdditionalLevel);
}

Component* Rune::GenerateComponent(Context& ctx, const Component::Options& options) {
	std::string testText = "This is a long description of this rune's effect. Some descriptions may be significantly longer, but if they are...well I hope they're saying something worthwhile. Can't say this one is saying anything worthwhile, but hey it is a lot of text, and that's useful to test out what a long description could look like.";
	auto panel = new VerticalPanel(ctx, options);
	auto topRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .18});
	auto damageRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .18});
	auto buffDebuffRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .18});
	auto effectRow = new WrappedLabel(ctx, testText, {.WidthScale = .98, .HeightScale = .4, .DefaultColor = WHITE});
	*panel += topRow;
	*panel += damageRow;
	*panel += buffDebuffRow;
	*panel += effectRow;

	// Top Row
	auto runeElement = getSprite(ctx, Element, {.WidthScale = .15, .HeightScale = 1});
	auto runeName = new Label(ctx, FormattedName(ctx), {.WidthScale = .55, .HeightScale = 1, .DefaultColor = GetRarityColor(ctx)});
	auto runeAttackType = getSprite(ctx, AttackType, {.WidthScale = .15, .HeightScale = .95});
	auto runeTarget = getSprite(ctx, Target, {.WidthScale = .15, .HeightScale = 1});
	*topRow += runeElement;
	*topRow += runeName;
	*topRow += runeAttackType;
	*topRow += runeTarget;

	// Damage Row
	auto runeFlatDamage = new Label(ctx, TextFormat("Power: %i", (int)FlatDamage), {.WidthScale = .35, .HeightScale = 1, .DefaultColor = WHITE});
	auto runeCrit = new Label(ctx, TextFormat("Crit: %01.01fx @ %i%%", (float)CritMultiplier, (int)(CritChance * 100.0)), {.WidthScale = .45, .HeightScale = 1, .DefaultColor = WHITE});
	*damageRow += runeFlatDamage;
	*damageRow += new VerticalPanel(ctx, {.WidthScale = .1, .HeightScale = 1});
	*damageRow += runeCrit;

	// Buff/Debuff Row
	auto buffLabel = new Label(ctx, "Buffs:", {.WidthScale = .22, .HeightScale = 1, .DefaultColor = WHITE});
	auto buffsPanel = new HorizontalPanel(ctx, {.WidthScale = .22, .HeightScale = 1});
	auto debuffLabel = new Label(ctx, "Debuffs:", {.WidthScale = .22, .HeightScale = 1, .DefaultColor = WHITE});
	auto debuffsPanel = new HorizontalPanel(ctx, {.WidthScale = .22, .HeightScale = 1});
	*buffDebuffRow += buffLabel;
	*buffDebuffRow += buffsPanel;
	*buffDebuffRow += debuffLabel;
	*buffDebuffRow += debuffsPanel;

	return panel;
}

Sprite* getSprite(Context& ctx, RuneAttribute::Target target, const Component::Options& options) {
	switch (target) {
		case RuneAttribute::SingleEnemy:
			return new Sprite(ctx, SpriteName::SingleEnemy, options);
		case RuneAttribute::AllEnemies:
			return new Sprite(ctx, SpriteName::AllEnemies, options);
		case RuneAttribute::Self:
			return new Sprite(ctx, SpriteName::Self, options);
		case RuneAttribute::SelfAndSingleEnemy:
			return new Sprite(ctx, SpriteName::SelfAndSingleEnemy, options);
		case RuneAttribute::SelfAndAllEnemies:
			return new Sprite(ctx, SpriteName::SelfAndAllEnemies, options);
	}
	return nullptr;
}

Sprite* getSprite(Context& ctx, RuneAttribute::AttackType attackType, const Component::Options& options) {
	switch (attackType) {
		case RuneAttribute::Physical:
			return new Sprite(ctx, SpriteName::Physical, options);
		case RuneAttribute::Special:
			return new Sprite(ctx, SpriteName::Special, options);
	}
	return nullptr;
}

Sprite* getSprite(Context& ctx, RuneAttribute::Element element, const Component::Options& options) {
	switch (element) {
		case RuneAttribute::None:
			return new Sprite(ctx, SpriteName::NoneRune, options);
		case RuneAttribute::Fire:
			return new Sprite(ctx, SpriteName::FireRune, options);
		case RuneAttribute::Water:
			return new Sprite(ctx, SpriteName::WaterRune, options);
		case RuneAttribute::Electric:
			return new Sprite(ctx, SpriteName::ElectricRune, options);
		case RuneAttribute::Wind:
			return new Sprite(ctx, SpriteName::WindRune, options);
		case RuneAttribute::Omni:
			return new Sprite(ctx, SpriteName::OmniRune, options);
		case RuneAttribute::Pure:
			return new Sprite(ctx, SpriteName::PureRune, options);
	}
	return nullptr;
}

Sprite* Rune::GetSprite(Context& ctx, const Component::Options& options) {
	return getSprite(ctx, Element, options);
}
