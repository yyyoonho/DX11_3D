#pragma once
#include "IExecute.h"

class AssimpTool : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

