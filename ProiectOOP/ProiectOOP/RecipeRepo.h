#ifndef RECIPE_REPO_H
#define RECIPE_REPO_H

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include "Recipe.h"
#include "ResourceHandler.h" 

class RecipeRepo {
private:
	std::vector<std::unique_ptr<Beverage>> recipes;

public:
	bool loadFromFile(const std::string& filename) {
		std::ifstream fin(filename);
		if (!fin) {
			std::cerr << "Nu pot deschide fisierul: " << filename << "\n";
			return false;
		}

		std::string line;
		while (std::getline(fin, line)) {
			if (line.empty()) continue;

			auto recipe = std::make_unique<Recipe>(line);

			while (std::getline(fin, line) && !line.empty()) {
				std::istringstream iss(line);
				std::string ingName;
				int qty;

				size_t lastSpace = line.find_last_of(' ');
				if (lastSpace == std::string::npos) {
					std::cerr << "Format invalid in fisierul de retete (lipsa cantitate): " << line << std::endl;
					continue;
				}
				ingName = line.substr(0, lastSpace);
				std::string qtyStr = line.substr(lastSpace + 1);

				try {
					qty = std::stoi(qtyStr);
					if (qty <= 0) {
						std::cerr << "Cantitate invalida (negativa sau zero) pentru ingredientul '" << ingName << "': " << qtyStr << " in reteta " << recipe->getName() << std::endl;
						continue;
					}
				}
				catch (const std::invalid_argument& e) {
					std::cerr << "Cantitate invalida (nu este numar) in fisierul de retete pentru ingredientul '" << ingName << "': " << qtyStr << " in reteta " << recipe->getName() << std::endl;
					continue;
				}
				catch (const std::out_of_range& e) {
					std::cerr << "Cantitate prea mare in fisierul de retete pentru ingredientul '" << ingName << "': " << qtyStr << " in reteta " << recipe->getName() << std::endl;
					continue;
				}

				recipe->addIngredient(Ingredient(ingName, qty));
			}

			recipes.push_back(std::move(recipe));
		}

		fin.close();
		return true;
	}

	void showMenu() const {
		std::cout << "\n=== Meniu Bauturi ===\n";
		for (size_t i = 0; i < recipes.size(); ++i) {
			std::cout << i + 1 << ". " << recipes[i]->getName() << "\n";
		}
		std::cout << "0. Iesire\n";
	}

	bool prepareRecipe(size_t index, ResourceHandler& rh) const {
		if (index < 1 || index > recipes.size()) {
			std::cerr << "Alegere invalida.\n";
			return false;
		}

		const auto& recipe = recipes[index - 1];

		bool canPrepare = true;
		for (const auto& ing : recipe->getIngredients()) {
			if (rh.getResourceQuantity(ing.getName()) < ing.getQuantity()) {
				std::cerr << "Eroare: Resursa insuficienta pentru " << recipe->getName() << ": " << ing.getName()
					<< " (necesar: " << ing.getQuantity()
					<< ", disponibil: " << rh.getResourceQuantity(ing.getName()) << ")\n";
				canPrepare = false;
				break;
			}
		}

		if (canPrepare) {
			for (const auto& ing : recipe->getIngredients()) {
				rh.consumeResource(ing.getName(), ing.getQuantity());
			}
			recipe->prepare(rh);
			return true;
		}
		else {
			return false;
		}
	}
};

#endif