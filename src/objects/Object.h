//
// Created by frabe808 on 23/11/16.
//

#ifndef TDP005_OBJECT_H
#define TDP005_OBJECT_H


#include <bits/unique_ptr.h>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../interfaces/IComponent.h"

//class IComponent;

class Object : public sf::Sprite
{

public:
	Object();

	Object(const sf::Texture&, const sf::Vector2f&);

	~Object()
	{ };

	std::string Name{"Unknown"};

	void Init();

	void Update(double time) const;

	void Draw(sf::RenderWindow&) const;

	void HandleEvent(sf::Event) const;

	void SetActive(bool);

	void SetDisable(bool);

	bool IsActive() const;

	bool IsDisabled() const;

	template<typename T>
	bool Has() const;

	template<typename T>
	void Detach();

	template<typename T>
	T* Fetch() const;

	template<typename T, typename ... TArgs>

	T* Attach(TArgs&& ... Args);

private:

	bool _isActive{true};
	bool _isDisabled{false};

	std::vector<std::unique_ptr<IComponent>> Slots;


};

/**
 * Throws if T is not a base of IComponent.
 * @tparam T - Component used.
 */
template<typename T>
void ThrowIfNotComponent()
{
	if (!std::is_base_of<IComponent, T>::value)
		throw std::invalid_argument(
				"You can only check if Object has a component!");
}

/**
 * Checks if object has the component specified.
 * @tparam T - Component to check.
 * @return True, if object has the component.
 */
template<typename T>
bool Object::Has() const
{

	ThrowIfNotComponent<T>();

	for (const auto& comp : Slots)
	{
		if (dynamic_cast<T* >(comp.get()))
			return true;

	}

	return false;
}


/**
 * Attaches a component to object.
 * @tparam T - Component to attach.
 * @tparam TArgs - Component arguments to pass forward to Component
 * @param Args - Arguments to pass forward
 * @return Pointer to the attached component.
 */
template<typename T, typename ... TArgs>
T* Object::Attach(TArgs&& ... Args)
{

	ThrowIfNotComponent<T>();

	if (Fetch<T>() != nullptr)
		throw std::invalid_argument("Can't add more components of that type");

	T* nc = new T(std::forward<TArgs>(Args)...);

	std::unique_ptr<IComponent> ptr(nc);

	ptr->SetParent(this);

	Slots.emplace_back(std::move(ptr));

	return dynamic_cast<T* >(Slots.back().get());
}

/**
 * Fetches the component specified from object.
 * @tparam T - Component to fetch.
 * @return Pointer to component.
 */
template<typename T>
T* Object::Fetch() const
{

	ThrowIfNotComponent<T>();

	for (const auto& comp : Slots)
	{
		if (const auto& casted = dynamic_cast<T* >(comp.get()))
		{
			return casted;
		}
	}

	return nullptr;
}

/**
 * Detaches a component from object.
 * @tparam T - Component to detach.
 */
template<typename T>
void Object::Detach()
{
	ThrowIfNotComponent<T>();

	for (auto& del : Slots)
	{

		for (auto iter = Slots.begin(); iter != Slots.end(); iter++)
		{
			if (del.get() == iter->get())
			{
				Slots.erase(iter++);
				break;
			} else
			{
				iter++;
			}

		}

	};

}


#endif //TDP005_OBJECT_H
