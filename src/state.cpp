// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "state.h"
#include "statuseffect.h"
#include "gui/menus.h"

State::State(Context& ctx) : ctx(ctx) {}

State::~State() {
	GameOver();
}

void State::NewGame() {
	this->CurrentRun.PlayerCharacter.Experience = 0;
	this->CurrentRun.PlayerCharacter.Health = 20;
	this->CurrentRun.PlayerCharacter.CurrentHealth = 20;
	this->CurrentRun.PlayerCharacter.PhysicalAttack = 10;
	this->CurrentRun.PlayerCharacter.SpecialAttack = 10;
	this->CurrentRun.PlayerCharacter.PhysicalArmor = 10;
	this->CurrentRun.PlayerCharacter.SpecialArmor = 10;
	this->CurrentRun.PlayerCharacter.Speed = 10;
	this->CurrentRun.PlayerCharacter.Evasion = 10;
	CurrentRun.ElapsedTime = 0;
	CurrentRun.ProgressTime = 0;
	ChanceProgress.NewRune = 0;
	ChanceProgress.FindBoss = 0;
	ChanceProgress.NextRuneCommon = 0;
	ChanceProgress.NextRuneUncommon = 0;
	ChanceProgress.NextRuneRare = 0;
	ChanceProgress.NextRuneEpic = 0;
	ChanceProgress.NextRuneLegendary = 0;

	this->CurrentRun.PlayerCharacter.Runes[0] = Rune();
	this->CurrentRun.PlayerCharacter.Runes[1] = Rune();
	this->CurrentRun.PlayerCharacter.Runes[2] = Rune();
	this->CurrentRun.PlayerCharacter.Runes[3] = Rune();
	this->CurrentRun.PlayerCharacter.Runes[4] = Rune();
	this->CurrentRun.PlayerCharacter.Runes[5] = Rune();

	this->CurrentRun.PlayerCharacter.Runes[0].Name = "Physical Attack";
	this->CurrentRun.PlayerCharacter.Runes[0].FlatDamage = 10;
	this->CurrentRun.PlayerCharacter.Runes[0].AttackType = RuneAttribute::Physical;
	this->CurrentRun.PlayerCharacter.Runes[0].Target = RuneAttribute::SingleEnemy;

	this->CurrentRun.PlayerCharacter.Runes[1].Name = "Special Attack";
	this->CurrentRun.PlayerCharacter.Runes[1].FlatDamage = 10;
	this->CurrentRun.PlayerCharacter.Runes[1].AttackType = RuneAttribute::Special;
	this->CurrentRun.PlayerCharacter.Runes[1].Target = RuneAttribute::SingleEnemy;

	if (GetRandomValue(0, 1) == 0) {
		this->CurrentRun.PlayerCharacter.Runes[2].Name = "Fire Slash";
		this->CurrentRun.PlayerCharacter.Runes[2].AttackType = RuneAttribute::Physical;
	} else {
		this->CurrentRun.PlayerCharacter.Runes[2].Name = "Fireball";
		this->CurrentRun.PlayerCharacter.Runes[2].AttackType = RuneAttribute::Special;
	}
	this->CurrentRun.PlayerCharacter.Runes[2].FlatDamage = 10;
	this->CurrentRun.PlayerCharacter.Runes[2].Element = RuneAttribute::Fire;
	this->CurrentRun.PlayerCharacter.Runes[2].Target = RuneAttribute::SingleEnemy;

	if (GetRandomValue(0, 1) == 0) {
		this->CurrentRun.PlayerCharacter.Runes[3].Name = "Thunder Slam";
		this->CurrentRun.PlayerCharacter.Runes[3].AttackType = RuneAttribute::Physical;
	} else {
		this->CurrentRun.PlayerCharacter.Runes[3].Name = "Lightning";
		this->CurrentRun.PlayerCharacter.Runes[3].AttackType = RuneAttribute::Special;
	}
	this->CurrentRun.PlayerCharacter.Runes[3].FlatDamage = 10;
	this->CurrentRun.PlayerCharacter.Runes[3].Element = RuneAttribute::Electric;
	this->CurrentRun.PlayerCharacter.Runes[3].Target = RuneAttribute::SingleEnemy;

	if (GetRandomValue(0, 1) == 0) {
		this->CurrentRun.PlayerCharacter.Runes[4].Name = "Water Blade";
		this->CurrentRun.PlayerCharacter.Runes[4].AttackType = RuneAttribute::Physical;
	} else {
		this->CurrentRun.PlayerCharacter.Runes[4].Name = "Drench";
		this->CurrentRun.PlayerCharacter.Runes[4].AttackType = RuneAttribute::Special;
	}
	this->CurrentRun.PlayerCharacter.Runes[4].FlatDamage = 10;
	this->CurrentRun.PlayerCharacter.Runes[4].Element = RuneAttribute::Water;
	this->CurrentRun.PlayerCharacter.Runes[4].Target = RuneAttribute::SingleEnemy;

	if (GetRandomValue(0, 1) == 0) {
		this->CurrentRun.PlayerCharacter.Runes[5].Name = "Wind Slash";
		this->CurrentRun.PlayerCharacter.Runes[5].AttackType = RuneAttribute::Physical;
	} else {
		this->CurrentRun.PlayerCharacter.Runes[5].Name = "Gust";
		this->CurrentRun.PlayerCharacter.Runes[5].AttackType = RuneAttribute::Special;
	}
	this->CurrentRun.PlayerCharacter.Runes[5].FlatDamage = 10;
	this->CurrentRun.PlayerCharacter.Runes[5].Element = RuneAttribute::Wind;
	this->CurrentRun.PlayerCharacter.Runes[5].Target = RuneAttribute::SingleEnemy;
}

void State::NextRoom() {
	if (ctx.GameState->CurrentRun.PlayerCharacter.Experience == 10) {
		ctx.GameState->CurrentRun.PlayerCharacter.Experience = 0;
		ctx.GameState->CurrentRun.PlayerCharacter.LevelUp(ctx);
		ctx.Menu.Set(Context::Menus::LevelUpMenu);
		ctx.Menu.ReloadLevelUpMenu(ctx);
		((Menu::LevelUpMenuComponent*)ctx.Menu[ctx.Menu.Current()])->RoomLoad(ctx);
	}
	switch (ctx.Menu.Current()) {
		case Context::Menus::MainMenu:
			NewGame();
			ctx.Menu.ReloadCombatMenu(ctx);
			ctx.Menu.Set(Context::Menus::CombatMenu);
			return;
		case Context::Menus::RuneMenu:
			return;
		case Context::Menus::GameOverMenu:
			ctx.Menu.Set(Context::Menus::MainMenu);
			return;
		case Context::Menus::NewRuneMenu:
			ctx.Menu.ReloadCombatMenu(ctx);
			ctx.Menu.Set(Context::Menus::CombatMenu);
			return;
		case Context::Menus::PauseMenu:
			return;
		case Context::Menus::LevelUpMenu:
		case Context::Menus::CombatMenu:
			double probability = ((double)GetRandomValue(0, 1000000000) / 1000000000.0);
			ChanceProgress.NewRune += Chances::Rune;
			if (probability <= ChanceProgress.NewRune) {
				ChanceProgress.NewRune = 0;
				this->CurrentRun.ReplacingIndex = -1;
				probability = ((double)GetRandomValue(0, 1000000000) / 1000000000.0);
				ChanceProgress.NextRuneLegendary += Chances::RarityLegendary;
				//TODO: will these panic if I delete the old rune?
				if (probability <= ChanceProgress.NextRuneLegendary) {
					ChanceProgress.NextRuneLegendary = 0;
					ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, RuneAttribute::Legendary);
					ctx.Menu.ReloadNewRuneMenu(ctx);
					ctx.Menu.Set(Context::Menus::NewRuneMenu);
					return;
				}
				ChanceProgress.NextRuneEpic += Chances::RarityEpic;
				if (probability <= ChanceProgress.NextRuneEpic) {
					ChanceProgress.NextRuneEpic = 0;
					ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, RuneAttribute::Epic);
					ctx.Menu.ReloadNewRuneMenu(ctx);
					ctx.Menu.Set(Context::Menus::NewRuneMenu);
					return;
				}
				ChanceProgress.NextRuneRare += Chances::RarityRare;
				if (probability <= ChanceProgress.NextRuneRare) {
					ChanceProgress.NextRuneRare = 0;
					ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, RuneAttribute::Rare);
					ctx.Menu.ReloadNewRuneMenu(ctx);
					ctx.Menu.Set(Context::Menus::NewRuneMenu);
					return;
				}
				ChanceProgress.NextRuneUncommon += Chances::RarityUncommon;
				if (probability <= ChanceProgress.NextRuneUncommon) {
					ChanceProgress.NextRuneUncommon = 0;
					ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, RuneAttribute::Uncommon);
					ctx.Menu.ReloadNewRuneMenu(ctx);
					ctx.Menu.Set(Context::Menus::NewRuneMenu);
					return;
				}
				ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, RuneAttribute::Common);
				ctx.Menu.ReloadNewRuneMenu(ctx);
				ctx.Menu.Set(Context::Menus::NewRuneMenu);
				return;
			}
			break;
	}
}

void State::Attack(int runeIndex) {

}

void State::GameOver() {
	for (auto enemy : CurrentBattle.Enemies) {
		delete(enemy);
	}
	CurrentBattle.Enemies.clear();
	for (auto statusEffect : CurrentBattle.StatusEffects) {
		delete(statusEffect);
	}
	CurrentBattle.StatusEffects.clear();
}
