#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;

class Entity;
class Manager;


using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T>

inline ComponentID getComponentTypeID() noexcept
{
	static_assert(std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	//return typeID();
	return typeID;
}


constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;


using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;


class Component
{
public:
	Entity* entity_p;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}

};


class Entity
{

private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray = {nullptr};
	ComponentBitSet componentBitSet;				//BitSet of size maxComponent(32)
	GroupBitSet groupBitSet;						//BitSet of size maxGroups(32)

public:

	Entity(Manager& mManager) : manager(mManager) {}

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

	bool hasGroup(Group mGroup)
	{
		return groupBitSet[mGroup];
	}
	
	void addGroup(Group mGroup);

	void delGroup(Group mGroup)
	{
		groupBitSet[mGroup] = false;
	}

	template <typename T> 
	
	bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T,typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* PointerToNewComponent(new T(std::forward<TArgs>(mArgs)...));
		//adding pointer to entitys to the component
		PointerToNewComponent->entity_p = this;

		std::unique_ptr<Component>uPtr{ PointerToNewComponent };
		components.emplace_back(std::move(uPtr));
		
		componentArray[getComponentTypeID<T>()] = PointerToNewComponent;
		componentBitSet[getComponentTypeID<T>()] = true;

		PointerToNewComponent->init();
		return *PointerToNewComponent;
	}

	template<typename T> 
	T& getComponent() const
	{
		ComponentID id = getComponentTypeID<T>();

		try 
		{
			if (id < maxComponents) {
				auto ptr = componentArray[id];
				return *static_cast<T*>(ptr);
			}
			else {
				// Handle error: Component ID out of bounds
				// Return a default or throw an exception
				throw std::out_of_range("Component ID out of bounds");
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
};


class Manager
{
private:
	
	std::vector<std::unique_ptr<Entity>> entitiesList;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

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
		for (auto i(0u);i < maxGroups;i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}

		entitiesList.erase(std::remove_if(std::begin(entitiesList), std::end(entitiesList),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),

			std::end(entitiesList));
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity &addEntity()
	{
		Entity *e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entitiesList.emplace_back(std::move(uPtr));
		return *e;
	}
};
