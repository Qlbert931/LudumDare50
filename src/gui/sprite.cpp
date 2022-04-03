// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/sprite.h"
#include "raylib.h"

Sprite::Sprite(Context& ctx, SpriteName spriteName, const Component::Options& options) {
    this->name = spriteName;
    this->options = options;
}

Sprite::~Sprite() {
	unload();
}

int Sprite::Height(Context& ctx) {
    return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int Sprite::Width(Context& ctx) {
    return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void Sprite::Draw(Context &ctx) {
	load(ctx);
	if (ctx.Screen.HasResized()) {
		unload();
		load(ctx);
	}
	int halfWidth = Width(ctx) / 2;
	int halfHeight = Height(ctx) / 2;
	if (colorTex != nullptr) {
		DrawTexture(*colorTex, X() + halfWidth - (colorTex->width / 2), Y() + halfHeight - (colorTex->height / 2), WHITE);
	}
	if (grayTex != nullptr) {
		DrawTexture(*grayTex, X() + halfWidth - (grayTex->width / 2), Y() + halfHeight - (grayTex->height / 2), options.DefaultColor);
	}
	for (auto child : *children) {
		child->DrawComponent(ctx, X() + ((Width(ctx) / 2) - (child->Width(ctx) / 2)), Y() + ((Height(ctx) / 2) - (child->Height(ctx) / 2)));
	}
}

void Sprite::load(Context& ctx) {
	if (colorTex != nullptr) {
		return;
	}

	Image tempColorImg;
	Image tempGrayImg;
	bool hasGray = false;

	switch(name) {
		case SpriteName::SpearGoblin:
			hasGray = true;
			tempColorImg = LoadImage("../assets/enemies/speargoblin/color.png");
			tempGrayImg = LoadImage("../assets/enemies/speargoblin/gray.png");
			break;
		case SpriteName::BearBaby:
			hasGray = true;
			tempColorImg = LoadImage("../assets/enemies/babybearbaby/color.png");
			tempGrayImg = LoadImage("../assets/enemies/babybearbaby/gray.png");
			break;
		case SpriteName::Golem:
			hasGray = true;
			tempColorImg = LoadImage("../assets/enemies/golem/color.png");
			tempGrayImg = LoadImage("../assets/enemies/golem/gray.png");
			break;
		case NoneRune:
			tempColorImg = LoadImage("../assets/runes/none.png");
			break;
		case FireRune:
			tempColorImg = LoadImage("../assets/runes/fire.png");
			break;
		case ElectricRune:
			tempColorImg = LoadImage("../assets/runes/electric.png");
			break;
		case WaterRune:
			tempColorImg = LoadImage("../assets/runes/water.png");
			break;
		case WindRune:
			tempColorImg = LoadImage("../assets/runes/wind.png");
			break;
		case PureRune:
			tempColorImg = LoadImage("../assets/runes/pure.png");
			break;
		case OmniRune:
			tempColorImg = LoadImage("../assets/runes/omni.png");
			break;
		case Backpack:
			tempColorImg = LoadImage("../assets/icons/backpack.png");
			break;
	}

	// Scale the image based on the width/height. Use the smallest scaling factor, so that no dimension is larger than our bounds.
	float widthRatio = (float)Width(ctx) / (float)tempColorImg.width;
	float heightRatio = (float)Height(ctx) / (float)tempColorImg.height;
	float ratio = widthRatio;
	if (heightRatio < widthRatio) {
		ratio = heightRatio;
	}
	if (ratio != 1) {
		ImageResizeNN(&tempColorImg, (int)((float)tempColorImg.width * ratio), (int)((float)tempColorImg.height * ratio));
	}
	Texture2D tempColorTex = LoadTextureFromImage(tempColorImg);
	colorTex = new Texture2D{tempColorTex.id, tempColorTex.width, tempColorTex.height, tempColorTex.mipmaps, tempColorTex.format};
	UnloadImage(tempColorImg);

	if (hasGray) {
		if (ratio != 1) {
			// Assume the color and gray images are the same size
			ImageResizeNN(&tempGrayImg, (int)((float)tempGrayImg.width * ratio), (int)((float)tempGrayImg.height * ratio));
		}
		Texture2D tempGrayTex = LoadTextureFromImage(tempGrayImg);
		grayTex = new Texture2D{tempGrayTex.id, tempGrayTex.width, tempGrayTex.height, tempGrayTex.mipmaps, tempGrayTex.format};
		UnloadImage(tempGrayImg);
	}
}

void Sprite::unload() {
	if (colorTex != nullptr) {
		UnloadTexture(*colorTex);
		delete(colorTex);
		colorTex = nullptr;
	}
	if (grayTex != nullptr) {
		UnloadTexture(*grayTex);
		delete(grayTex);
		grayTex = nullptr;
	}
}
