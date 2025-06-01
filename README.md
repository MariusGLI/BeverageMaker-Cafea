Această aplicație C++ simulează funcționalitatea de bază a unei mașini de cafea sau a unui automat de băuturi. Scopul principal este de a demonstra principii de programare orientată pe obiecte (OOP), cum ar fi încapsularea, moștenirea și polimorfismul, într-un context practic și ușor de înțeles.

Structura Aplicației:

Aplicația este organizată în mai multe clase, fiecare având o responsabilitate specifică:

Ingredient:

Scop: Reprezintă un ingredient individual necesar pentru o băutură (ex: "Apa", "Cafea", "Lapte", "Ceai").
Atribute: Numele ingredientului (string) și cantitatea (int, ex: ml sau grame).
Funcționalitate: Stochează și oferă acces la numele și cantitatea ingredientului.
ResourceHandler:

Scop: Gestionează stocul de resurse disponibile în mașina de cafea (ex: câtă apă, cafea, lapte, ceai există).
Atribute: Un unordered_map (tabel de hash) care mapează numele resurselor (string) la cantitatea lor (int).
Funcționalitate:
addResource(name, quantity): Adaugă sau crește cantitatea unei resurse.
refillResource(name, quantity): Reîncarcă o resursă existentă sau o adaugă dacă nu există, afișând mesaje relevante.
consumeResource(name, quantity): Scade cantitatea unei resurse dacă este disponibilă.
getResourceQuantity(name): Returnează cantitatea disponibilă a unei resurse.
resourceExists(name): Verifică dacă o resursă cu un anumit nume există în stoc.
showResources(): Afișează toate resursele disponibile și cantitățile lor.
Beverage (Clasa de Bază Abstractă):

Scop: Definește interfața comună pentru toate băuturile care pot fi preparate. Este o clasă abstractă, ceea ce înseamnă că nu pot fi create obiecte de tip Beverage direct, ci doar de tipuri derivate.
Atribute: Numele băuturii (string) și o listă de ingrediente necesare (std::vector<Ingredient>).
Funcționalitate:
addIngredient(ing): Adaugă un ingredient în lista de ingrediente a băuturii.
prepare(ResourceHandler& rh): O metodă pur virtuală, ceea ce obligă clasele derivate să implementeze propria logică de preparare.
getName(): Returnează numele băuturii.
getIngredients(): Returnează lista de ingrediente necesare.
Recipe (Clasa Derivată din Beverage):

Scop: Implementează logica specifică de preparare pentru o anumită rețetă de băutură.
Funcționalitate:
Suprascrie metoda prepare(ResourceHandler& rh) din clasa de bază Beverage.
Logica de preparare include:
Personalizare pentru "Apa": Afișează mesajul "Se adauga apa in pahar" cu o animație cu puncte-puncte, apoi un mesaj de finalizare.
Pentru alte băuturi: Afișează un mesaj de început ("--- Preparare X ---"), iterează prin ingrediente afișând mesajele de adăugare și animații.
Personalizare pentru "Ceai Negru": Include mesaje și delay-uri specifice pentru faza de infuzare.
Logica generală: Pentru celelalte băuturi (cafea, cappuccino etc.), afișează un mesaj general de "Fierbere apa si amestecare ingrediente".
Toate băuturile afișează la final mesajul "X este gata! Pofta buna!".
RecipeRepo:

Scop: Gestionează colecția de rețete disponibile și interacțiunea cu fișierul de rețete.
Atribute: Un vector de obiecte std::unique_ptr<Beverage>, care stochează rețetele încărcate. Utilizarea unique_ptr asigură gestionarea automată a memoriei și permite stocarea polimorfică (obiecte Recipe ca Beverage).
Funcționalitate:
loadFromFile(filename): Încarcă rețetele dintr-un fișier text (recipes.txt). Fiecare rețetă începe cu numele băuturii, urmată de ingrediente și cantități, separate de linii goale. Include validări pentru formatul fișierului.
showMenu(): Afișează un meniu numerotat al băuturilor disponibile.
prepareRecipe(index, rh): Încearcă să prepare o rețetă selectată de utilizator. Înainte de preparare, verifică dacă există suficiente resurse. Dacă da, consumă resursele prin ResourceHandler și apoi apelează metoda prepare() a rețetei specifice.
main.cpp:

Scop: Punctul de intrare al aplicației, conține bucla principală de interacțiune cu utilizatorul.
Funcționalitate:
Inițializează un RecipeRepo și un ResourceHandler.
Încarcă rețetele din recipes.txt.
Adaugă resurse inițiale în ResourceHandler.
Rulează o buclă while care:
Afișează resursele curente.
Afișează meniul de băuturi.
Citește alegerea utilizatorului.
Gestionează intrările invalide (non-numerice).
Dacă utilizatorul alege 0, afișează "La revedere!" și închide aplicația.
Încearcă să prepare băutura aleasă.
Dacă prepararea eșuează (ex: resurse insuficiente), oferă utilizatorului opțiunea de a reîncărca resurse.
Logica de reîncărcare permite introducerea repetată a numelui resursei până la o intrare validă sau anulare.
