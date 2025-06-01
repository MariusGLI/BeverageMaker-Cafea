#include <iostream>
#include <limits>
#include <string>
#include "RecipeRepo.h"
#include "ResourceHandler.h"

int main() {
	RecipeRepo repo;
	ResourceHandler handler;

	if (!repo.loadFromFile("recipes.txt")) {
		std::cerr << "Eroare la incarcarea retetelor. Asigurati-va ca 'recipes.txt' exista si are formatul corect.\n";
	}

	handler.addResource("Apa", 500);
	handler.addResource("Cafea", 100);
	handler.addResource("Lapte", 200);
	handler.addResource("Ceai", 50);

	int opt = -1;
	while (opt != 0) {
		handler.showResources();
		repo.showMenu();

		std::cout << "Alege o bautura: ";
		std::cin >> opt;

		if (std::cin.fail()) {
			std::cout << "Intrare invalida! Te rog introdu un numar.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (opt == 0) {
			// Add an extra ignore here just to be absolutely sure the buffer is clean before exiting
			// In theory, std::cin >> opt should handle the newline, but it doesn't hurt to be safe.
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "La revedere!\n";
			break;
		}

		if (!repo.prepareRecipe(opt, handler)) {
			char refillChoice;
			std::cout << "Doriti sa reincarcati resursele? (d/n): ";
			std::cin >> refillChoice;

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (refillChoice == 'd' || refillChoice == 'D') {
				std::string resourceToRefill;
				int refillQuantity;
				bool nameEnteredCorrectly = false;

				while (!nameEnteredCorrectly) {
					std::cout << "Ce resursa doriti sa reincarcati? (ex: Apa, Cafea, Lapte, Ceai): ";
					std::getline(std::cin, resourceToRefill);

					if (resourceToRefill == "anuleaza") {
						std::cout << "Reincarcarea a fost anulata.\n";
						break;
					}

					if (handler.resourceExists(resourceToRefill)) {
						nameEnteredCorrectly = true;
					}
					else {
						std::cout << "Resursa '" << resourceToRefill << "' nu exista. Incercati din nou.\n";
					}
				}

				if (!nameEnteredCorrectly) {
					continue;
				}

				std::cout << "Ce cantitate? ";
				std::cin >> refillQuantity;

				if (std::cin.fail() || refillQuantity <= 0) {
					std::cout << "Cantitate invalida. Reincarcare anulata.\n";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				handler.refillResource(resourceToRefill, refillQuantity);
			}
			else {
				std::cout << "Reincarcarea a fost anulata. Alegeti o alta bautura sau iesiti.\n";
			}
		}
	}

	return 0;
}