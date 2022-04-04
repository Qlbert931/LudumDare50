// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"
#include "context.h"
#include "component.h"

enum SpriteName {
	// Enemies
	SpearGoblin,
	BearBaby,
	Golem,

	// Runes
	NoneRune,
	FireRune,
	ElectricRune,
	WaterRune,
	WindRune,
	PureRune,
	OmniRune,

	// Icons
	Backpack,
	BackButton,
	HomeButton
};

class Sprite : public Component {
public:
	Sprite(Context& ctx, SpriteName spriteName, const Component::Options& options);
	~Sprite();
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;

protected:
	void Draw(Context& ctx) override;

private:
	void load(Context& ctx);
	void unload();

	SpriteName name;
	Texture2D* colorTex = nullptr;
	Texture2D* grayTex = nullptr;
};

#endif //SPRITE_H
