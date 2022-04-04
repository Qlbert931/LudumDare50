// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "rune.h"
#include "statuseffect.h"

Sprite* getSprite(Context& ctx, RuneAttribute::Target target, const Component::Options& options);
Sprite* getSprite(Context& ctx, RuneAttribute::AttackType attackType, const Component::Options& options);
Sprite* getSprite(Context& ctx, RuneAttribute::Element element, const Component::Options& options);

Rune::Rune() {
	Name = "Skip Turn";
	Level = 1;
	AdditionalLevel = 0;
	Target = RuneAttribute::Target::Self;
	Rarity = RuneAttribute::Rarity::Common;
	AttackType = RuneAttribute::AttackType::Special;
	Element = RuneAttribute::Element::None;
	FlatDamage = 0;
	//Buffs
	//Debuffs
	CritChance = 0;
	CritMultiplier = 1;
}

Rune::Rune(Context& ctx, bool forPlayer) {
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
	CritChance = (double)GetRandomValue(10, 200) / 100.0;
	CritMultiplier = (double)GetRandomValue(110, 400) / 100.0;
}

Rune::~Rune() {
	for (auto buff : Buffs) {
		delete(buff);
	}
	for (auto debuff : Debuffs) {
		delete(debuff);
	}
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

std::string Rune::EffectText(Context& ctx) {
	if (Buffs.empty() && Debuffs.empty()) {
		std::string str;
		switch (AttackType) {
			case RuneAttribute::Physical:
				str += "A physical attack";
				break;
			case RuneAttribute::Special:
				str += "A special attack";
				break;
		}
		switch (Element) {
			case RuneAttribute::None:
				str += " affected by armor";
				break;
			case RuneAttribute::Fire:
				str += " affected by fire resistance and armor";
				break;
			case RuneAttribute::Water:
				str += " affected by water resistance and armor";
				break;
			case RuneAttribute::Electric:
				str += " affected by electric resistance and armor";
				break;
			case RuneAttribute::Wind:
				str += " affected by wind resistance and armor";
				break;
			case RuneAttribute::Omni:
				str += " affected by all resistances and unaffected by armor";
				break;
			case RuneAttribute::Pure:
				str += " unaffected by any resistances or armor";
				break;
		}
		switch (Target) {
			case RuneAttribute::SingleEnemy:
				str += " on a single enemy.";
				break;
			case RuneAttribute::AllEnemies:
				str += " on all enemies.";
				break;
			case RuneAttribute::Self:
				str += " on yourself.";
				break;
			case RuneAttribute::SelfAndSingleEnemy:
				str += " on a single enemy and yourself.";
				break;
			case RuneAttribute::SelfAndAllEnemies:
				str += " on everyone, including yourself.";
				break;
		}
		return str;
	}
	std::string str;
	for (auto buff : Buffs) {
		str += buff->Description(ctx);
	}
	for (auto debuff : Debuffs) {
		str += debuff->Description(ctx);
	}
	return str;
}

Component* Rune::GenerateComponent(Context& ctx, const Component::Options& options) {
	auto panel = new VerticalPanel(ctx, options);
	auto topRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .18});
	auto damageRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .18});
	auto buffDebuffRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .18});
	auto effectRow = new WrappedLabel(ctx, EffectText(ctx), {.WidthScale = .98, .HeightScale = .4, .DefaultColor = WHITE});
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

double Rune::FireResistance(Context& ctx) {
	switch (Element) {
		case RuneAttribute::None:
			switch (Rarity) {
				case RuneAttribute::Common:
					return 0;
				case RuneAttribute::Uncommon:
					return 0;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return .02;
				case RuneAttribute::Legendary:
					return .05;
			}
		case RuneAttribute::Fire:
			switch (Rarity) {
				case RuneAttribute::Common:
					return .08;
				case RuneAttribute::Uncommon:
					return .12;
				case RuneAttribute::Rare:
					return .18;
				case RuneAttribute::Epic:
					return .30;
				case RuneAttribute::Legendary:
					return .50;
			}
		case RuneAttribute::Water:
			switch (Rarity) {
				case RuneAttribute::Common:
					return -.05;
				case RuneAttribute::Uncommon:
					return -.03;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return 2;
				case RuneAttribute::Legendary:
					return 5;
			}
		case RuneAttribute::Electric:
			switch (Rarity) {
				case RuneAttribute::Common:
					return -.05;
				case RuneAttribute::Uncommon:
					return -.03;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return 2;
				case RuneAttribute::Legendary:
					return 5;
			}
		case RuneAttribute::Wind:
			switch (Rarity) {
				case RuneAttribute::Common:
					return -.05;
				case RuneAttribute::Uncommon:
					return -.03;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return .02;
				case RuneAttribute::Legendary:
					return .05;
			}
		case RuneAttribute::Omni:
			switch (Rarity) {
				case RuneAttribute::Common:
					return .01;
				case RuneAttribute::Uncommon:
					return .02;
				case RuneAttribute::Rare:
					return .04;
				case RuneAttribute::Epic:
					return .08;
				case RuneAttribute::Legendary:
					return .12;
			}
		case RuneAttribute::Pure:
			return 0;
			break;
	}
	return 0;
}

double Rune::WaterResistance(Context& ctx) {
	switch (Element) {
		case RuneAttribute::None:
			switch (Rarity) {
				case RuneAttribute::Common:
					return 0;
				case RuneAttribute::Uncommon:
					return 0;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return .02;
				case RuneAttribute::Legendary:
					return .05;
			}
		case RuneAttribute::Fire:
			switch (Rarity) {
				case RuneAttribute::Common:
					return -.05;
				case RuneAttribute::Uncommon:
					return -.03;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return 2;
				case RuneAttribute::Legendary:
					return 5;
			}
		case RuneAttribute::Water:
			switch (Rarity) {
				case RuneAttribute::Common:
					return .08;
				case RuneAttribute::Uncommon:
					return .12;
				case RuneAttribute::Rare:
					return .18;
				case RuneAttribute::Epic:
					return .30;
				case RuneAttribute::Legendary:
					return .50;
			}
		case RuneAttribute::Electric:
			switch (Rarity) {
				case RuneAttribute::Common:
					return -.05;
				case RuneAttribute::Uncommon:
					return -.03;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return 2;
				case RuneAttribute::Legendary:
					return 5;
			}
		case RuneAttribute::Wind:
			switch (Rarity) {
				case RuneAttribute::Common:
					return -.05;
				case RuneAttribute::Uncommon:
					return -.03;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return .02;
				case RuneAttribute::Legendary:
					return .05;
			}
		case RuneAttribute::Omni:
			switch (Rarity) {
				case RuneAttribute::Common:
					return .01;
				case RuneAttribute::Uncommon:
					return .02;
				case RuneAttribute::Rare:
					return .04;
				case RuneAttribute::Epic:
					return .08;
				case RuneAttribute::Legendary:
					return .12;
			}
		case RuneAttribute::Pure:
			return 0;
			break;
	}
	return 0;
}

double Rune::ElectricResistance(Context& ctx) {
	switch (Element) {
		case RuneAttribute::None:
			switch (Rarity) {
				case RuneAttribute::Common:
					return 0;
				case RuneAttribute::Uncommon:
					return 0;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return .02;
				case RuneAttribute::Legendary:
					return .05;
			}
		case RuneAttribute::Fire:
			switch (Rarity) {
				case RuneAttribute::Common:
					return -.05;
				case RuneAttribute::Uncommon:
					return -.03;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return 2;
				case RuneAttribute::Legendary:
					return 5;
			}
		case RuneAttribute::Water:
			switch (Rarity) {
				case RuneAttribute::Common:
					return -.05;
				case RuneAttribute::Uncommon:
					return -.03;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return 2;
				case RuneAttribute::Legendary:
					return 5;
			}
		case RuneAttribute::Electric:
			switch (Rarity) {
				case RuneAttribute::Common:
					return .08;
				case RuneAttribute::Uncommon:
					return .12;
				case RuneAttribute::Rare:
					return .18;
				case RuneAttribute::Epic:
					return .30;
				case RuneAttribute::Legendary:
					return .50;
			}
		case RuneAttribute::Wind:
			switch (Rarity) {
				case RuneAttribute::Common:
					return -.05;
				case RuneAttribute::Uncommon:
					return -.03;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return .02;
				case RuneAttribute::Legendary:
					return .05;
			}
		case RuneAttribute::Omni:
			switch (Rarity) {
				case RuneAttribute::Common:
					return .01;
				case RuneAttribute::Uncommon:
					return .02;
				case RuneAttribute::Rare:
					return .04;
				case RuneAttribute::Epic:
					return .08;
				case RuneAttribute::Legendary:
					return .12;
			}
		case RuneAttribute::Pure:
			return 0;
			break;
	}
	return 0;
}

double Rune::WindResistance(Context& ctx) {
	switch (Element) {
		case RuneAttribute::None:
			switch (Rarity) {
				case RuneAttribute::Common:
					return 0;
				case RuneAttribute::Uncommon:
					return 0;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return .02;
				case RuneAttribute::Legendary:
					return .05;
			}
		case RuneAttribute::Fire:
			switch (Rarity) {
				case RuneAttribute::Common:
					return -.05;
				case RuneAttribute::Uncommon:
					return -.03;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return 2;
				case RuneAttribute::Legendary:
					return 5;
			}
		case RuneAttribute::Water:
			switch (Rarity) {
				case RuneAttribute::Common:
					return -.05;
				case RuneAttribute::Uncommon:
					return -.03;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return 2;
				case RuneAttribute::Legendary:
					return 5;
			}
		case RuneAttribute::Electric:
			switch (Rarity) {
				case RuneAttribute::Common:
					return -.05;
				case RuneAttribute::Uncommon:
					return -.03;
				case RuneAttribute::Rare:
					return 0;
				case RuneAttribute::Epic:
					return 2;
				case RuneAttribute::Legendary:
					return 5;
			}
		case RuneAttribute::Wind:
			switch (Rarity) {
				case RuneAttribute::Common:
					return .08;
				case RuneAttribute::Uncommon:
					return .12;
				case RuneAttribute::Rare:
					return .18;
				case RuneAttribute::Epic:
					return .30;
				case RuneAttribute::Legendary:
					return .50;
			}
		case RuneAttribute::Omni:
			switch (Rarity) {
				case RuneAttribute::Common:
					return .01;
				case RuneAttribute::Uncommon:
					return .02;
				case RuneAttribute::Rare:
					return .04;
				case RuneAttribute::Epic:
					return .08;
				case RuneAttribute::Legendary:
					return .12;
			}
		case RuneAttribute::Pure:
			return 0;
			break;
	}
	return 0;
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
