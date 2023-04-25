#pragma once
#include "Component.h"

class Button : public Component
{
	using Super = Component;

public:
	Button();
	virtual ~Button();

	bool Picked(POINT screenPos);

	void Create(Vec2 screenPos, Vec2 Size, shared_ptr<class Material>);

	void AddOnClickedEvent(std::function<void(void)> func);
	void InvokeOnClicked();

private:
	std::function<void(void)> _onClicked;
	RECT _rect;

};

