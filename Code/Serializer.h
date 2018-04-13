#pragma once
#include "InputManager.h"
#include <memory>

class Serializer
{
public:
	Serializer() = default;
	~Serializer() = default;

	static void Serialize(std::string file, InputManager im);
	static void DeSerialize(std::string file, std::shared_ptr<InputManager> im);
};