#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera() : Super(ComponentType::Camera)
{
	_width = static_cast<float>(GAME->GetGameDesc().width);
	_height = static_cast<float>(GAME->GetGameDesc().height);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	UpdateMatrix();
}

void Camera::UpdateMatrix()
{
	Vec3 eyePosition = GetTransform()->GetPosition();
	Vec3 focusPosition = eyePosition + GetTransform()->GetLook();
	Vec3 upDirection = GetTransform()->GetUp();

	_matView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
	
	if (_type == ProjectionType::Perspective)
	{
		_matProjection = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	}
	else
	{
		_matProjection = ::XMMatrixOrthographicLH(_width, _height, _near, _far);
	}
	
}

void Camera::SortGameObject()
{
	shared_ptr<Scene> scene = CUR_SCENE;
	unordered_set<shared_ptr<GameObject>>& gameObjects = scene->GetObjects();

	_vecForward.clear();

	for (auto& gameObject : gameObjects)
	{
		if (IsCulled(gameObject->GetLayerIndex()))
			continue;

		if (gameObject->GetMeshRenderer() == nullptr
			&& gameObject->GetModelRenderer() == nullptr
			&& gameObject->GetModelAnimator() == nullptr)
			continue;

		_vecForward.push_back(gameObject);
	}
}

void Camera::Render_Forward()
{
	S_MatView = _matView;
	S_MatProjection = _matProjection;

	GET_SINGLE(InstancingManager)->Render(_vecForward);
}
