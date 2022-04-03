// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HORIZONTALPANEL_H
#define HORIZONTALPANEL_H
#include "context.h"
#include "component.h"
#include "vector"

class HorizontalPanel : public Component {
public:
	HorizontalPanel(Context& ctx, const Component::Options& options);
	~HorizontalPanel() override;
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;
	void Update(Context& ctx) override;
	void AddChild(Component* child);
	void operator +=(Component* component);
	Component& operator [](int i) { return *(children->at(i)); }

protected:
	void Draw(Context& ctx) override;

private:
	std::vector<Component*>* children;
};

#endif //HORIZONTALPANEL_H
