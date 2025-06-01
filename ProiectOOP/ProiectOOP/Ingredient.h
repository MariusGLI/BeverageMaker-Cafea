#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include <iostream>

class Ingredient {
private:
	std::string name;
	int quantity; // in mililitri sau grame

public:
	Ingredient(const std::string& name, int quantity)
		: name(name), quantity(quantity) {}

	std::string getName() const { return name; }
	int getQuantity() const { return quantity; }

	void display() const {
		std::cout << "- " << name << ": " << quantity << std::endl;
	}
};

#endif