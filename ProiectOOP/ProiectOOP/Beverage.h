#ifndef BEVERAGE_H
#define BEVERAGE_H

#include <vector>
#include <string>
#include "Ingredient.h"
#include "ResourceHandler.h" 

class Beverage {
protected:
	std::string name;
	std::vector<Ingredient> ingredients;

public:
	Beverage(const std::string& name) : name(name) {}
	virtual ~Beverage() = default;

	void addIngredient(const Ingredient& ing) {
		ingredients.push_back(ing);
	}

	virtual void prepare(ResourceHandler& rh) const = 0;

	std::string getName() const { return name; }

	const std::vector<Ingredient>& getIngredients() const {
		return ingredients;
	}
};

#endif