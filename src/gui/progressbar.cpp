// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/progressbar.h"

ProgressBar::ProgressBar(Context& ctx, const Component::Options& options, float* trackedValue) {
	this->options = options;
	this->trackedValue = trackedValue;
}

int ProgressBar::Height(Context& ctx) {
	return (int)((float)parent->Height(ctx) * options.HeightScale);
}

int ProgressBar::Width(Context& ctx) {
	return (int)((float)parent->Width(ctx) * options.WidthScale);
}

void ProgressBar::Draw(Context& ctx) {
	auto color = options.DefaultColor;
	if (options.HoverColor.a > 0 && IsMouseOver(ctx)) {
		color = options.HoverColor;
	}
	DrawRectangle(X(), Y(), Width(ctx) * (*trackedValue), Height(ctx), color);
}