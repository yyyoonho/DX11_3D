#pragma once
#include "IExecute.h"
#include "Geometry.h"

class MaterialDemo: public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	shared_ptr<Shader> _shader;

	// Object
	shared_ptr<GameObject> _obj;
	shared_ptr<GameObject> _obj2;

	// Camera
	shared_ptr<GameObject> _camera;
};