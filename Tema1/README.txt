EGC - Tema 1
	Geometry Wars
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

Se cere sa se implementeze un joc de tipul Geometry Wars folosint framework-ul din laboratoarele 1-3.Jocul trebuie sa aiba la baza un teren de joc, un jucator controlat din taste si o serie de inamici care trebuiesc distrusi pentru a acumula scor.

2.Utilizare
	Programul se ruleaza direct fara niciun parametru de intrare.

	2.1 Fisiere
		Nu sunt folosite fisiere de intrare sau iesire

	2.2 Consola
		In consola nu se afiseaza nimic si nu se primesc parametrii.

	2.3 Input Tastatura
		Taste:
			[Sageata-Sus]
				- cat timp butonul este tinut apasa nava va inainta cu o acceleratie crescatoare
			[Sageata-Stanga]
				- cat timp butonul este tinut apasat nava se va roti catre stanga cu un unghi prestabilit
			[Sageata-Dreapta]
				- cat timp butonul este tinut apasat nava se va roti catre dreapta cu un unghi prestabilit
			[Space]
				- cand tasta space va fi apasata arma navei spatiale va fi activata/dezactivata.
			[Escape]
				- butonul escape va inchide fereastra grafica si va oprii programul
	2.4 Interfata Grafica
		Interfaca grafica nu contine butoane apasabile.

3.Implementare
	IDE: Visual Studio 2013 RC
	Sistem Operare: Windows 8.1 Pro

3.1 Schema generala

	Ideea de baza este ca nava spatiala sa supravietuiasca cat mai mult.Astfel inamici se vor spawna la fiecare 10 secunde initial, apoi acest timp fiind decrementat.Viteza inamicilor va creste de asemenea.

	Inamicii inteligenti vor ataca naveta spatiala, se vor deplasa direct catre centrul ei.

	Inamici tip stea vor ricosa din pereti.

	La colectarea unui PowerUp naveta va incepe sa traga cu lasere in 3 directii.



	3.2 Diagrama Clase

+--main+----+Inamic.h+-----+Inamic1.h
       |             |
       |             +-----+Inamic2.h
       |             |
       |             +-----+Inamic3.h
       |             |
       |             +-----+PowerUp.h
       |
       +----+Laser.h
       |
       +----+Naveta.h
       |
       +----+DrawingWindow.cpp
       |
       +----+Transform2d.cpp
       |
       +----+Visual2D.cpp
   
3.3 Mesaje
	Scorul se va modifica cand un inamic va fi omorat de catre burghiul sau laserul navei spatiale

	Vietile se vor decrementa pana la 0 cand jucatorul este lovit de catre inamici         

3.4 Evenimente
	
	Coliziune Burghiu - Inamic : inamicul este scos din ecran si scorul updatat
	Coliziune Naveta - Inamic : inamicul este scos din ecran si vietile decrementate
	Coliziune Naveta - Pereti : naveta nu are voie sa iasa din cadru
	Coliziune Inamici - Pereti : acestia vor ricosa la un unghi egal cu unghi_curent - PI/2
	Coliziune Burghiu - PowerUp : Naveta va incepe sa traga cu lasere
	Coliziune Lasere - Inamici : ambele vor disparea si scorul va fi updatat



4.Testare
	IDE: Visual Studio 2013 RC
	Sistem Operare: Windows 8.1 Pro

	Se activeaza burghiul si se incearca sa se supravietuiasca cat mai mult posibil, incercat sa se detecteze eventuale buguri.	

5. Probleme Aparute
	Daca s-ar firespectat cerinta precizata in enunt prin care orice obiect nu are voie sa paraseasca chenarul atunci nava ar fi ramas blocata cu burghiul intr-un colt.Conform unui post de pe forum burghiul navei spatiale are voie sa iasa din cadru.

	Dificil de implementat coliziunea cu obiectele

	Probleme cu rotatia inamicilor.Inamicii erau detectati la coliziuni cu un delay semnificativ.Astfel s-a renuntat la rotirea inamicilor.

	Probleme de optimizare la coliziuni, s-au mai redus din punctele verificate folosind hitbox pe inamici.

6. Continutul Arhivei
	Pe langa fisierele specifice framework-ului din laboratoarele 1-3 am sa mentionez fisiere adaugate sau fisierele modificate.

	Pentru a respecta structura din framework si pentr a mentine codul cat mai lizibil si mai simplu, clasele au fost declarate

		- main.cpp
			sursa principala a aplicatiei
		- Inamic.h
			implementare calsa principala pentru inamic.va fi mosteninta de celelalte clase tip inamic
		- Inamic1.h
			mosteneste inamic.h si descrie inamicul de tip 1 (cele doua patrate verzi).
		- Inamic2.h
			mosteneste inamic.h si descrie inamicul de tip 2 (stea de culoare mov).
		- Inamic3.h
			mosteneste inamic.h si descrie inamicul de tip 3(patrat + romb de culori diferite).
		- Laser.h
			inplementarea clasei proiectilelor trase de nava spatiala
		- Naveta.h
			implementarea clasei principale pentru nava spatiala
		- PowerUp
			mosteneste inamic.h si descrie inamicul de tip powerUp care activeaza laserele odata distrusa cu burghiul
		- DrawingWindow.cpp
			s-a modificat fisierul adaugand functiile glutSpecialUpFunc(buttonUP);
			glutKeyboardUpFunc(keyboardbuttonUP);
			glClearColor(0.2,0.2,0.2,1);
			pentru recunoasterea ridicarii degetului de pe butoane si pentru a modifica backgroundul ferestrei.

7. functionalitati
	Functionalitati Standard (ca in enunt)
		-Miscare nava spatiala
		-Afisare scor / numar vieti
		-3 tipuri diferite de inamici formati din structuri complexe
		-Elementele nu ies din cadru
		-Detectare coliziune nava-inamic
	Functionalitati Bonus
		- Mai multe nivele de dificultate: la fiecare 10 secunde viteza de spawn si viteza inamicilor creste
		- Inamici inteligenti: inamicii se indreapta catre jucator sau inamicii ricoseaza din pereti
		- Deplasare nava cu accelerare si franare
		- Burghiu + adaugare de proiectile de tip laser
		- Bonusuri: Cand apare un inamic de tip cerc portocaliu iar acesta este distrus cu burgiul (si doar cu burghiul) nava va incepe sa traga cu lasere in 3 directii timp de 10 secunde
