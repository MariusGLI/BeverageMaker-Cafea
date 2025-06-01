#ifndef RESOURCE_HANDLER_H
#define RESOURCE_HANDLER_H

#include <unordered_map>
#include <string>
#include <iostream>

class ResourceHandler {
private:
	std::unordered_map<std::string, int> resources;

public:
	void addResource(const std::string& name, int quantity) {
		resources[name] += quantity;
	}

	void refillResource(const std::string& name, int quantity) {
		if (resources.count(name)) {
			resources[name] += quantity;
			std::cout << "Resursa '" << name << "' reincarcata cu " << quantity << " unitati. Noua cantitate: " << resources[name] << std::endl;
		}
		else {
			// Aceasta ramane aici pentru cazul in care cineva ar folosi direct refillResource
			// pentru o resursa inexistenta, fara a trece prin logica de validare din main.
			std::cout << "Resursa '" << name << "' nu exista, a fost adaugata cu " << quantity << " unitati.\n";
		}
	}

	bool consumeResource(const std::string& name, int quantity) {
		if (resources.count(name) && resources[name] >= quantity) {
			resources[name] -= quantity;
			return true;
		}
		return false;
	}

	int getResourceQuantity(const std::string& name) const {
		auto it = resources.find(name);
		if (it != resources.end()) {
			return it->second;
		}
		return 0;
	}

	// METODĂ NOUĂ: Verifica dacă o resursă există în map
	bool resourceExists(const std::string& name) const {
		return resources.count(name) > 0;
	}

	void showResources() const {
		std::cout << "\n--- Resurse Disponibile ---\n";
		for (const auto& pair : resources) {
			std::cout << pair.first << ": " << pair.second << std::endl;
		}
	}
};

#endif