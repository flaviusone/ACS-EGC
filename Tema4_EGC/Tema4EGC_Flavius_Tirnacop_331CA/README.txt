EGC - Tema 4
	Sleeping Beauty
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

Se cere sa se implementeze animatia unui obiect 3d prin interpolari succesive plus
un sistem de particule ce se bazeaza pe conceptul de billboarding.


2.Utilizare
	Programul se ruleaza direct fara niciun parametru de intrare.

	2.1 Fisiere
		Nu sunt folosite fisiere de intrare sau iesire

	2.2 Consola
		In consola nu se afiseaza nimic si nu se primesc parametrii.

	2.3 Input Tastatura
		Space - Reincarca shader
		W - Toggle Wireframe
	2.4 Interfata Grafica
		Interfaca grafica nu contine butoane apasabile.

3.Implementare
	IDE: Visual Studio 2013
	Sistem Operare: Windows 8.1 Pro
	S-au folosit frameworkurile din laboratoarele 4 si 5 de shadere

3.1 Schema generala

	S-a folosit un automat de stari pentru a trece intre cele 3 tipuri de stari:
	Somn -> surpriza -> enervare -> somn -> somn -> surpriza -> enervare -> somn -> somn -> surpriza -> enervare -> …

	Sistemul de particule apare doar in starea zero adica din somn - > surpriza. "Zgomotul" trezeste personajul care trece in starea de surpriza.

	
3.2 Diagrama Clase

Pe langa fisierele din framework au mai fost adaugate:

- Object.hpp	
	clasa responsabila cu pastrarea datelor specifice capetelor
- Particle.hpp 
	clasa responsabila cu pastrarea datelor specifice notelor muzicale
- shader_particle_fragment.glsl	
	fragment shaderul pentru sistemul de particule
- shader_particle_vertex.glsl
	vertex shaderul pentru sistemul de particule
	

4.Testare
	IDE: Visual Studio 2013
	Sistem Operare: Windows 8.1 Pro

	Se incearca supravietuirea cat mai mult posibil incercand sa se detecteze 
	eventuale buguri.

5. PASI DE REZOVLARE:

	La initializare:
		- incarcare shadere
		- incarcare obiecte capete
		- incarcate textura cap, particula
		- setare pozitie camera, lumina, capete (model-view matrix)
		- legare de atribute capete
		- creare particule
		- legare de atribute particule
	In notifyBeginFrame()
		- update timp si stare actuala automat
	In notifyDisplayFrame()
		- golire ecran
		- trimitere date generale catre shader_phong (model_matrix, view_matrix etc.)
		- implementare automat cu stari.In functie de stare se va intampla:
			daca stare 0 sau 1
				- desenare cap 
				- legare textura cap
				- trimtiere date generale catre shader_particle
				- desenare fiecare particula + textura (se trimit catre shader)
			altfel
				- desenare cap 
				- legare textura cap

	In shader_phong_fragment
		- asemanator cu cel din laborator se seteaza doar lumina+textura
				out_color = vec4(tex1*1.4*light, 1);
	In shader_phong_vertex
		- se modifica pozitie, normale si texturi dupa formula:
			pozitie_finala = pozitie intiala  + timp * change_per_frame;
	In shader_particle_fragment
		- se seteaza culoarea particulei
		- se face discard la ce este alb (sau nuante de gri) pentru textura alpha
	In shader_particle_vertex
		- se modifica pozitia particulelor dupa formula
		 	pozitie_noua = pozitie_veche + timp * viteza;
		- se foloseste formula pentru billboarding

6. Probleme Aparute
	
	La partea de alpha discard s-a observat ca daca se face discard la elementele albe
	notele vor aparea pixellated asa ca se va face discard si la unele nuante de gri.

	Probleme cu bindarea catre shader a datelor specifice capetelor.Discreptante intre
	starile din automat

7. Continutul Arhivei
	Pe langa fisierele specifice framework-ului din laboratorul am sa mentionez fisiere adaugate sau fisierele modificate.

		- main.cpp
		- Object.hpp	
			clasa responsabila cu pastrarea datelor specifice capetelor
		- Particle.hpp 
			clasa responsabila cu pastrarea datelor specifice notelor muzicale
		- shader_particle_fragment.glsl	
			fragment shaderul pentru sistemul de particule
		- shader_particle_vertex.glsl
			vertex shaderul pentru sistemul de particule

8. functionalitati
	Functionalitati Standard (ca in enunt)
