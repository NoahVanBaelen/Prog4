#pragma once
#include <memory>
#include "GameObject.h"
#include <iostream>

class BaseComponent
{
	dae::GameObject* m_pOwner{ nullptr };
public:
	BaseComponent() = default;
	virtual void Update(float);
	virtual void FixedUpdate(float);
	virtual void LateUpdate(float);
	virtual void Render() const;

	virtual ~BaseComponent() = default;
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;
protected:
	explicit BaseComponent(dae::GameObject* pOwner) {
		m_pOwner = pOwner;
	}
	dae::GameObject* GetOwner() const { return m_pOwner; }
};

