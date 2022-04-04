// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BORDER_H
#define BORDER_H
#include "context.h"
#include "component.h"

class Border : public Component {
public:
	Border(Context& ctx, const Component::Options& options, float thicknessScale);
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;

protected:
	void Draw(Context& ctx) override;

private:
	float thicknessScale;
};

#endif //BORDER_H
