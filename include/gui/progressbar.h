// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#include "context.h"
#include "component.h"

class ProgressBar : public Component {
public:
	ProgressBar(Context& ctx, const Component::Options& options, float* trackedValue);
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;

protected:
	void Draw(Context& ctx) override;

private:
	float* trackedValue;
};

#endif //PROGRESSBAR_H
