EGC - Tema 2
	Crazy Driver
	Tirnacop Flavius-Costin 331CA

Cuprins

1.Cerinta
2.Utilizare
3.Implementare
4.Testare
5.Probleme Aparute
6.Continutul Arhivei
7.Functionalitati

1.Cerinta

Se cere sa se implementeze un joc intitulat Crazy Driver ce are la baza controlul
unei masini/nave 3D pe o sosea cu scopul de a evita anumite obstacole .Se va 
folosi framework-ul de la laboratorul 3.

2.Utilizare
	Programul se ruleaza direct fara niciun parametru de intrare.

	2.1 Fisiere
		Nu sunt folosite fisiere de intrare sau iesire

	2.2 Consola
		In consola nu se afiseaza nimic si nu se primesc parametrii.

	2.3 Input Tastatura
		Taste:
			[Sageata-Stanga]
				- cat timp butonul este tinut apasat playerul se va translata
				pe axa ox catre stanga
				- cat timp butonul este tinut apasat playerul se va roti pe axa
				oz cu un anumit unghi.
			[Sageata-Dreapta]
				- cat timp butonul este tinut apasat playerul se va translata
				pe axa ox catre dreapta
				- cat timp butonul este tinut apasat playerul se va roti pe axa
				oz cu un anumit unghi.
			[Escape]
				- butonul escape va inchide fereastra grafica si va oprii programul
	2.4 Interfata Grafica
		Interfaca grafica nu contine butoane apasabile.

3.Implementare
	IDE: Visual Studio 2013 RC
	Sistem Operare: Windows 8.1 Pro
	S-a folosit frameworkul din laboratorul 3

3.1 Schema generala

	Ideea de baza este ca nava/playerul sa supravietuiasca cat mai mult.Astfel inamici se vor spawna la fiecare 6 secunde initial, apoi acest timp fiind decrementat.Viteza inamicilor va creste deasemenea.

	
	3.2 Diagrama Clase

	Voi afisa doar calsele importante

+--main+----+Inamic.h+-----+Inamic1.h
       |             |
       |             +-----+Inamic2.h
       |             |
       |             +-----+Inamic3.h
       |
       |
       +----+Player.h
       |
       +----+Board.h
       |
       +----+DrawingWindow.cpp
       |
       +----+Transform3D.cpp
 
   
3.3 Mesaje
	
	Scorul se va modifica pe parcurs ce nava inainteaza crescand in fiecare 
	secunda cu o valoare prestabilita (care va creste pe parcurs).

	Vietile se vor decrementa pana la 0 cand jucatorul este lovit de catre inamici         

3.4 Evenimente
	
	Coliziune Naveta - Inamic : inamicul este scos din ecran si vietile decrementate
	Coliziune Naveta - Pereti : naveta nu are voie sa iasa din cadru

4.Testare
	IDE: Visual Studio 2013 RC
	Sistem Operare: Windows 8.1 Pro

	Se incearca supravietuirea cat mai mult posibil incercand sa se detecteze 
	eventuale buguri.

5. Probleme Aparute
	
	Multe probleme de setare a perspectivei.Unii inamici par a avea o traictorie
	anume dar cand se apropie aceasta pare diferita.

	Uneori drumul se suprapunea peste celelate obiecte.
	Solutie: drum transparent cu background schimbat.

	Colizunea dintre inamici se face folosind distanta euclidiana si o raza
	de volum aproximativa setata manual

6. Continutul Arhivei
	Pe langa fisierele specifice framework-ului din laboratorul am sa mentionez fisiere adaugate sau fisierele modificate.

	Pentru a respecta structura din framework si pentr a mentine codul cat mai lizibil si mai simplu, clasele au fost declarate

		- main.cpp
			sursa principala a aplicatiei
		- Inamic.h
			implementare calsa principala pentru inamic.va fi mosteninta de celelalte clase tip inamic
		- Inamic1.h
			mosteneste inamic.h si descrie inamicul de tip 1 
			inamic de tip CUB
		- Inamic2.h
			mosteneste inamic.h si descrie inamicul de tip 2
			inamic de tip PIRAMIDA
		- Inamic3.h
			mosteneste inamic.h si descrie inamicul de tip 3
			inamic de tip HEXAGON
		- Player.h
			implementarea clasei principale pentru nava spatiala
		- Board.h
			implementarea clasei pentru chenarul pe care se misca elementele
		- DrawingWindow.cpp
			s-a modificat fisierul adaugand functiile glutSpecialUpFunc(buttonUP);
			glutKeyboardUpFunc(keyboardbuttonUP);
			glClearColor(0,0,0,1);
			pentru recunoasterea ridicarii degetului de pe butoane si pentru a modifica backgroundul ferestrei.

7. functionalitati
	Functionalitati Standard (ca in enunt)
		-Miscare nava spatiala
		-Afisare scor / numar vieti
		-3 tipuri diferite de inamici formati din structuri complexe
		-Elementele nu ies din cadru
		-Detectare coliziune nava-inamic
	Functionalitati Bonus
		- Mai multe nivele de dificultate: la fiecare 6 secunde viteza de spawn si viteza inamicilor creste
		- Deplasare nava cu rotire 
		- Rotire sosea + inamici
