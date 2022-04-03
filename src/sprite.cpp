// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/sprite.h"
#include "raylib.h"

Sprite::Sprite(SpriteName spriteName, Color spriteColor) {
    this->name = spriteName;
    this->color = spriteColor;
}

Sprite::~Sprite() {

}

int Sprite::Height(Context& ctx) {
    return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int Sprite::Width(Context& ctx) {
    return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void Sprite::Draw(Context &ctx) {
    Image grayImage, backImage;

    switch(name) {
        case SpriteName::None:
        case SpriteName::SpearGoblin:
            grayImage = LoadImage("../Art/Enemies/SpearGoblin/GrayLayer.png");
            backImage = LoadImage("../Art/Enemies/SpearGoblin/ColorLayer.png");
        case SpriteName::BearBaby:
            grayImage = LoadImage("../Art/Enemies/BabyBearBaby/GrayLayer.png");
            backImage = LoadImage("../Art/Enemies/BabyBearBaby/ColorLayer.png");
        case SpriteName::Golem:
            grayImage = LoadImage("../Art/Enemies/Golem/GrayLayer.png");
            backImage = LoadImage("../Art/Enemies/Golem/ColorLayer.png");
    }
    // Resize the image to whatever size we feel necessary
//    int resizeVar = 250;
//    ImageResize(grayImage, resizeVar, resizeVar);
//    ImageResize(backImage, resizeVar, resizeVar);

    // Extract a texture from the corresponding image
    Texture2D grayTexture = LoadTextureFromImage(grayImage);
    Texture2D backTexture = LoadTextureFromImage(backImage);

    // Release the image data
    UnloadImage(grayImage);
    UnloadImage(backImage);

    // Draw the textures at the same position + tinting the gray one with the given color
    DrawTexture(grayTexture, X(), Y(), color);
    DrawTexture(backTexture, X(), Y(), WHITE);
}