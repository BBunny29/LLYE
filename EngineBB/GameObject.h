#pragma once
#include <memory>

class Transform;

class GameObject
{
public:
	GameObject();
	~GameObject();

	std::shared_ptr<Transform> m_transform;

};

