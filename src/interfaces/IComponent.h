//
// Created by frabe808 on 23/11/16.
//

#ifndef TDP005_ICOMPONENT_H
#define TDP005_ICOMPONENT_H


#include <string>
#include <SFML/Window/Event.hpp>

class Object;

class IComponent
{

public:
	IComponent() = default;

	virtual ~IComponent()
	{ };

	std::string Name{"BaseComponent"};

	void SetParent(Object*);

	Object* Parent() const;

	virtual void Init() = 0;

	virtual void Update(double time) = 0;

	virtual void HandleEvent(sf::Event) = 0;

protected:
	Object* _parent{nullptr};

};

#endif //TDP005_ICOMPONENT_H
