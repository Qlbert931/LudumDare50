// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include "iostream"

VerticalPanel* Menu::CreateRuneMenu(Context& ctx) {
	auto runeMenu = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});

	auto runeTitle = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = .3});
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



	auto runeMenuButtonLabelOptions = Component::Options{
		.WidthScale = .7,
		.HeightScale = .7,
		.DefaultColor = Color{200, 200, 200, 255}
	};
	*runeTitle += new Label(ctx, "Runes", {.WidthScale = 0.95, .HeightScale = 0.5, .DefaultColor = RAYWHITE});

	auto runeMenuButtonOptions = Component::Options{
		.WidthScale = 1.0,
		.HeightScale = 1.0,
		.DefaultColor = Color{130, 130, 130, 255},
		.HoverColor = Color{150, 150, 150, 255}};
	auto electricClickFunc = [](Context& ctx) { std::cout << "[ELECTRIC RUNE] Clicked!" << std::endl; };
	auto fireClickFunc = [](Context& ctx) { std::cout << "[FIRE RUNE] Clicked!" << std::endl; };
	auto noneClickFunc = [](Context& ctx) { std::cout << "[NONE RUNE] Clicked!" << std::endl; };
	auto pureClickFunc = [](Context& ctx) { std::cout << "[PURE RUNE] Clicked!" << std::endl; };
	auto waterClickFunc = [](Context& ctx) { std::cout << "[WATER RUNE] Clicked!" << std::endl; };
	auto windClickFunc = [](Context& ctx) { std::cout << "[WIND RUNE] Clicked!" << std::endl; };

	auto electricButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(electricClickFunc), new Sprite(ctx, SpriteName::ElectricRune, {.WidthScale = .25, .HeightScale = .45}));
	auto fireButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(fireClickFunc), new Sprite(ctx, SpriteName::FireRune, {.WidthScale = .25, .HeightScale = .45}));
	auto noneButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(noneClickFunc), new Sprite(ctx, SpriteName::NoneRune, {.WidthScale = .25, .HeightScale = .45}));
	auto pureButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(pureClickFunc), new Sprite(ctx, SpriteName::PureRune, {.WidthScale = .25, .HeightScale = .45}));
	auto waterButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(waterClickFunc), new Sprite(ctx, SpriteName::WaterRune, {.WidthScale = .25, .HeightScale = .45}));
	auto windButton = new Button(ctx, runeMenuButtonOptions.WithOnClick(windClickFunc), new Sprite(ctx, SpriteName::WindRune, {.WidthScale = .25, .HeightScale = .45}));

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
