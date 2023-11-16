#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;

class Entity;


using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T>

ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	//return typeID();
	return typeID;
}


constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;


class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}

};


class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void update()
	{
		for (auto& c : components) c->update();
		
	}

	void draw()
	{
		for (auto& c : components) c->draw();
	}

	bool isActive() { return active; }

	void destroy() { active = false; }

	template <typename T> 
	
	bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T,typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component>uPtr{ c };
		components.emplace_back(std::move(uPtr));
		
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> 
	T& getComponent() const
	{
		auto ptr = componentArray[getComponentTypeID<T>()];
		return *static_cast<T*>(ptr);
	}
};


class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entitiesList;

public:
	void update()
	{
		for (auto& e : entitiesList) e->update();
	}

	void draw()
	{
		for (auto& e : entitiesList) e->draw();
	}

	void refresh()
	{
		entitiesList.erase(std::remove_if(std::begin(entitiesList), std::end(entitiesList),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),

			std::end(entitiesList));
	}

	Entity &addEntity()
	{
		Entity *e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entitiesList.emplace_back(std::move(uPtr));
		return *e;
	}
};