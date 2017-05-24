//
// Created by frabe808 on 23/11/16.
//

#include <iostream>
#include "IComponent.h"

/**
 * Sets parent object to the component.
 * @param parent - Object that should be the parent.
 */
void IComponent::SetParent(Object* parent)
{
	if (_parent != nullptr)
		std::cout << "ERROR: Can't set parent, it has already been set."
		          << std::endl;

	_parent = parent;
	Init();
}

/**
 * @return Parent object.
 */
Object* IComponent::Parent() const
{
	return _parent;
}
