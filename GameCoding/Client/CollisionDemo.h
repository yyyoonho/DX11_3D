#pragma once


class CollisionDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	shared_ptr<Shader> _shader;

};

#include "MonoBehaviour.h"
class MoveScript : public MonoBehaviour
{
public:
	virtual void Update() override;
};