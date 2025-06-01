#ifndef RECIPE_H
#define RECIPE_H

#include "Beverage.h"
#include <thread>
#include <chrono>
#include <iostream>

void animateDelay(int seconds) {
	for (int i = 0; i < seconds; ++i) {
		std::cout << ". " << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	std::cout << "\n";
}

class Recipe : public Beverage {
public:
	Recipe(const std::string& name) : Beverage(name) {}

	void prepare(ResourceHandler& rh) const override {
		if (name == "ApaPlata") {
			std::cout << "Se adauga apa in pahar";
			animateDelay(3);
			// Nu mai folosim 'return;' aici, pentru a afișa mesajul final comun
		}
		else {
			std::cout << "\n--- Preparare " << name << " ---\n";

			for (const auto& ing : ingredients) {
				std::cout << "Adaugam " << ing.getQuantity() << " unitati de " << ing.getName();
				animateDelay(1);
			}

			if (name == "CeaiNegru") {
				std::cout << "Infuzare ceai";
				animateDelay(3);
				std::cout << "Se infuzeaza ceaiul";
				animateDelay(1);
			}
			else {
				std::cout << "Fierbere apa si amestecare ingrediente";
				animateDelay(2);
			}
		}

		// Acest mesaj va fi afișat pentru TOATE băuturile, inclusiv "Apa"
		std::cout << name << " este gata! Pofta buna!\n";
	}
};

#endif