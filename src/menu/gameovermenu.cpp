// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include <iostream>

Component* Menu::CreateGameOverMenu(Context& ctx) {
	auto gameOverMenu = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	*gameOverMenu += new Label(ctx, "Game Over", {.WidthScale = .5, .HeightScale = .2, .DefaultColor = RAYWHITE});
	*gameOverMenu += new Label(ctx, "1h 59m 28.49s", {.WidthScale = .95, .HeightScale = .3, .DefaultColor = RAYWHITE});

	auto titleLevel = new HorizontalPanel (ctx, {.WidthScale = 1, .HeightScale =.15});
	*gameOverMenu += titleLevel;
	*titleLevel += new Label(ctx, "Monsters Slain:", {.WidthScale = .3, .HeightScale = 1, .DefaultColor = RAYWHITE});
	*titleLevel += new Label(ctx, "Bosses Slain:", {.WidthScale = .3, .HeightScale = 1, .DefaultColor = RAYWHITE});

	auto numberLevel = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .15});
	*gameOverMenu += numberLevel;
	*numberLevel += new Label(ctx, "5", {.WidthScale = .3, .HeightScale = 1,.DefaultColor = RAYWHITE});
	*numberLevel += new Label(ctx, "6", {.WidthScale = .3, .HeightScale = 1,.DefaultColor = RAYWHITE});

	auto homeButtonRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .15});
	*gameOverMenu += homeButtonRow;
	auto homeButton = new Button(ctx,Component::Options{ .WidthScale = 0.2, .HeightScale = 1.0, .DefaultColor = ctx.Colors.Button, .HoverColor = ctx.Colors.ButtonHover});
	auto homeButtonFill = new HorizontalPanel(ctx, {.WidthScale = .75, .HeightScale = 1});
	*homeButtonRow += homeButton;
	*homeButtonRow += homeButtonFill;
	auto homeButtonContents = new HorizontalPanel(ctx, {.WidthScale = .9, .HeightScale = 1});
	*homeButton += homeButtonContents;
	auto homeButtonContentsSprite = new Sprite(ctx, SpriteName::Home, {.WidthScale = 0.4, .HeightScale = 1});
	auto homeButtonContentsLabel = new Label(ctx, "HOME", {.WidthScale = 0.4, .HeightScale = 1, .DefaultColor = BLACK});
	*homeButtonContents += homeButtonContentsSprite;
	*homeButtonContents += homeButtonContentsLabel;

	return new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
}