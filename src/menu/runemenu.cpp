// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include <iostream>

// Temp variable to check for clicked
bool clicked = false;

void claimColor (Context& ctx, Component& component) {
	std::cout << "Clicked!" << std::endl;
	if (!clicked) {
		component.GetOptions().DefaultColor = Color{150, 150, 150, 255};
		clicked = true;
		return;
	}
	component.GetOptions().DefaultColor = Color{130, 130, 130, 255};
	clicked = false;
}

Component* Menu::CreateRuneMenu(Context& ctx) {

	auto runeMenuButtonOptions = Component::Options{
		.WidthScale = 1.0,
		.HeightScale = 1.0,
		.DefaultColor = Color{130, 130, 130, 255},
		.HoverColor = Color{150, 150, 150, 255}
	};

	auto runeMenu = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});

	auto backButtonArea = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .1});
	*runeMenu += backButtonArea;

	auto backButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(claimColor).WithWidthScale(.1));
	*backButtonArea += backButton->AddChild(new Sprite(ctx, SpriteName::Back, {.WidthScale = 1, .HeightScale = 1}));

	auto fillBackButtonArea = new VerticalPanel(ctx, {.WidthScale = .9, .HeightScale = 1});
	*backButtonArea += fillBackButtonArea;

	auto runeTitle = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = .2});
	*runeMenu += runeTitle;

	auto runeContainer = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = .7});
	*runeMenu += runeContainer;
	auto container1 = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .5});
	auto container2 = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .5});
	*runeContainer += container1;
	*runeContainer += container2;

	auto electricRuneBack = new HorizontalPanel(ctx, {.WidthScale = .15, .HeightScale = .8});
	auto fireRuneBack = new HorizontalPanel(ctx, {.WidthScale = .15, .HeightScale = .8});
	auto noneRuneBack = new HorizontalPanel(ctx, {.WidthScale = .15, .HeightScale = .8});


	auto pureRuneBack = new HorizontalPanel(ctx, {.WidthScale = .15, .HeightScale = .8});
	auto waterRuneBack = new HorizontalPanel(ctx, {.WidthScale = .15, .HeightScale = .8});
	auto windRuneBack = new HorizontalPanel(ctx, {.WidthScale = .15, .HeightScale = .8});

	*runeTitle += new Label(ctx, "Runes", {.WidthScale = 0.95, .HeightScale = 0.5, .DefaultColor = RAYWHITE});

	auto electricButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(claimColor));
	*electricButton += new Sprite(ctx, SpriteName::ElectricRune, {.WidthScale = .25, .HeightScale = .45});

	auto fireButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(claimColor));
	*fireButton += new Sprite(ctx, SpriteName::FireRune, {.WidthScale = .25, .HeightScale = .45});

	auto noneButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(claimColor));
	*noneButton += new Sprite(ctx, SpriteName::NoneRune, {.WidthScale = .25, .HeightScale = .45});

	auto pureButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(claimColor));
	*pureButton += new Sprite(ctx, SpriteName::PureRune, {.WidthScale = .25, .HeightScale = .45});

	auto waterButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(claimColor));
	*waterButton += new Sprite(ctx, SpriteName::WaterRune, {.WidthScale = .25, .HeightScale = .45});

	auto windButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(claimColor));
	*windButton += new Sprite(ctx, SpriteName::WindRune, {.WidthScale = .25, .HeightScale = .45});

	*electricRuneBack += electricButton;
	*fireRuneBack += fireButton;
	*noneRuneBack += noneButton;
	*pureRuneBack += pureButton;
	*waterRuneBack += waterButton;
	*windRuneBack += windButton;

	*container1 += electricRuneBack;
	*container1 += fireRuneBack;
	*container1 += noneRuneBack;
	*container2 += pureRuneBack;
	*container2 += waterRuneBack;
	*container2 += windRuneBack;

	return runeMenu;
};
