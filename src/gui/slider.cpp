// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/slider.h"

Slider::Slider(Context& ctx, const Component::Options& options, Color trackColor, float* trackedValue) {
	this->options = options;
	this->trackColor = trackColor;
	this->trackedValue = trackedValue;
	this->tab = new SliderTab(ctx, options);
	this->tab->parent = this;
}

Slider::~Slider() {
	delete(tab);
}

int Slider::Height(Context& ctx) {
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int Slider::Width(Context& ctx) {
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void Slider::Update(Context& ctx) {
	Component::Update(ctx);
	//TODO: handle dragging and sliding
}

void Slider::Draw(Context& ctx) {
	int height = Height(ctx);
	int width = Width(ctx);
	int trackThickness = (int)((float)height * 0.1);
	if ((int)((float)width * 0.1) < trackThickness) {
		trackThickness = (int)((float)width * 0.1);
	}
	DrawRectangle(X(), Y() + (height / 2) - (trackThickness / 2), width, trackThickness, trackColor);

	int tabSize = height;
	if (width < height) {
		tabSize = width;
	}
	int moveableLength = width - tabSize;
	int tabX = X() + (tabSize / 2) + (int)((float)moveableLength * (*trackedValue));
	int tabY = Y() + (height / 2) - (tabSize / 2);
	DrawRectangle(tabX, tabY, tabSize, tabSize, trackColor);
	tab->DrawComponent(ctx, tabX + trackThickness, tabY + trackThickness);
}

SliderTab::SliderTab(Context& ctx, const Component::Options& options) {
	this->options = options;
}

SliderTab::~SliderTab() {

}

int SliderTab::Height(Context& ctx) {
	int parentHeight = parent->Height(ctx);
	int parentWidth = parent->Width(ctx);
	int trackThickness = (int)((float)parentHeight * 0.1);
	if ((int)((float)parentWidth * 0.1) < trackThickness) {
		trackThickness = (int)((float)parentWidth * 0.1);
	}

	int tabSize = parentHeight;
	if (parentWidth < parentHeight) {
		tabSize = parentWidth;
	}
	return tabSize - (2 * trackThickness);
}

int SliderTab::Width(Context& ctx) {
	return Height(ctx);
}

void SliderTab::Draw(Context& ctx) {
	auto color = options.DefaultColor;
	if (options.HoverColor.a > 0 && IsMouseOver(ctx)) {
		color = options.HoverColor;
	}
	int innerTabSize = Height(ctx);
	DrawRectangle(X(), Y(), innerTabSize, innerTabSize, color);
}
