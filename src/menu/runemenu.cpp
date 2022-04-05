// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include "rune.h"

void runeMenuBackPressed(Context& ctx, Component& component) {
	ctx.Menu.Set(Context::Menus::Index::MainMenu);
}

Component* Menu::CreateRuneMenu(Context& ctx) {
	auto runeMenu = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});

	auto topButtonRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .1});
	*runeMenu += topButtonRow;
	auto backButton = new Button(ctx, Component::Options{
		.WidthScale = .1,
		.HeightScale = .85,
		.DefaultColor = ctx.Colors.Button,
		.HoverColor = ctx.Colors.ButtonHover,
		.OnClick = runeMenuBackPressed,
	});
	*topButtonRow += backButton;
	*topButtonRow += new VerticalPanel(ctx, {.WidthScale = .78, .HeightScale = 1});
	auto innerBackButton = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	*backButton += innerBackButton;
	*innerBackButton += new Sprite(ctx, SpriteName::Back, {.WidthScale = .35, .HeightScale = .9});
	*innerBackButton += new Label(ctx, "Back", {.WidthScale = .55, .HeightScale = 1, .DefaultColor = WHITE});
	auto playButton = (new Button(ctx, Component::Options{
		.WidthScale = .1,
		.HeightScale = .85,
		.DefaultColor = ctx.Colors.Button,
		.HoverColor = ctx.Colors.ButtonHover,
	}))->AddChild(new Label(ctx, "Play", {.WidthScale = .55, .HeightScale = 1, .DefaultColor = WHITE}));
	*topButtonRow += playButton;

	auto runeTitle = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = .2});
	*runeTitle += new Label(ctx, "Runes", {.WidthScale = 1, .HeightScale = 1, .DefaultColor = WHITE});
	*runeMenu += runeTitle;

	auto runeContainer = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = .7});
	*runeMenu += runeContainer;
	auto container1 = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .5});
	auto container2 = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .5});
	*runeContainer += container1;
	*runeContainer += container2;

	auto runeOptions = Component::Options{
		.WidthScale = .3,
		.HeightScale = .8,
		.DefaultColor = ctx.Colors.Button,
		.HoverColor = ctx.Colors.ButtonHover};
	auto electricRuneBack = Rune(ctx, RuneAttribute::Common).GenerateComponent(ctx, runeOptions);
	auto fireRuneBack = Rune(ctx, RuneAttribute::Common).GenerateComponent(ctx, runeOptions);
	auto noneRuneBack = Rune(ctx, RuneAttribute::Common).GenerateComponent(ctx, runeOptions);

	auto pureRuneBack = Rune(ctx, RuneAttribute::Common).GenerateComponent(ctx, runeOptions);
	auto waterRuneBack = Rune(ctx, RuneAttribute::Common).GenerateComponent(ctx, runeOptions);
	auto windRuneBack = Rune(ctx, RuneAttribute::Common).GenerateComponent(ctx, runeOptions);

	*container1 += electricRuneBack;
	*container1 += fireRuneBack;
	*container1 += noneRuneBack;
	*container2 += pureRuneBack;
	*container2 += waterRuneBack;
	*container2 += windRuneBack;

	return runeMenu;
};
