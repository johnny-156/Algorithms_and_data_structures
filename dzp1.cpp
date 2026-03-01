#include <stack>
#include <queue>
#include <vector>

#include <iostream>
using namespace std;

typedef struct odgovor {
	string tekst;
	int ocena;
	int kom; //flag koji oznacava da li je u pitanju komentar ili odgovor
	vector<odgovor> odgovori;
}odgovor;

typedef struct pitanje {
	string tekst;
	vector<odgovor> odgovori;
}pitanje;

vector<pitanje> svaPitanja; //kreiranje niza za unos pitanja

void preorderObilazak(vector<pitanje> svaPitanja, int i) {
	if ((svaPitanja.begin() + i) > svaPitanja.begin() + svaPitanja.size()) {
		cout << "***Neodgovarajuci indeks!***" << endl;
		return;
	}
	else {
		cout << svaPitanja[i].tekst << endl;
		odgovor next;
		if (svaPitanja[i].odgovori.size() > 0) {
			next = svaPitanja[i].odgovori[0];
			cout << next.tekst << endl;
		}
		else {
			cout << "***Nema odgovora na ovo pitanje!***" << endl;
			return;
		}
		stack<odgovor> stack;
		for (int j = 1; j < svaPitanja[i].odgovori.size(); j++) {
			stack.push(svaPitanja[i].odgovori[j]);
		}

		while (!stack.empty()) {

			while (stack.size() > 0) {
				next = stack.top();
				stack.pop();
				cout << next.tekst << endl;
				for (int j = 1; j < next.odgovori.size(); j++) {
					stack.push(next.odgovori[j]);
				}
				if (next.odgovori.size() != 0) {
					next = next.odgovori[0];
				}
			}
		}
	}
}

void levelorderObilazak(vector<pitanje> svaPitanja, int i) {
	if ((svaPitanja.begin() + i) > svaPitanja.begin() + svaPitanja.size()) {
		cout << "***Neodgovarajuci indeks!***" << endl;
		return;
	}
	else {
		cout << svaPitanja[i].tekst << endl;
		odgovor next;
		queue<odgovor> queue;
		for (int j = 0; j < svaPitanja[i].odgovori.size(); j++) {
			queue.push(svaPitanja[i].odgovori[j]);
		}
		while (!queue.empty()) {
			next = queue.front();
			queue.pop();
			cout << next.tekst << endl;
			for (int j = 1; j < next.odgovori.size(); j++) {
				queue.push(next.odgovori[j]);
			}
		}
	}
}

void levelorderOdg(vector<pitanje> svaPitanja, int indeks, string tekst) {
	queue<odgovor*> queue;
	for (int j = 0; j < svaPitanja[indeks].odgovori.size(); j++) {
		queue.push(&svaPitanja[indeks].odgovori[j]);
	}
	odgovor* next1=nullptr;
	while (!queue.empty()) {
		next1 = queue.front();
		queue.pop();
		if (next1->tekst == tekst) {
			if (next1->odgovori.size() == 10) {
				cout << "***Popunjeno je 10 odgovora!***" << endl;
			}
			else {
				cout << "Kako glasi Vas odgovor? " << endl;
				string tekst1; cin >> tekst1;

				odgovor odg1;
				odg1.ocena = 0;
				odg1.kom = 1; //ovo je odgovor na odgovor (komentar)
				odg1.tekst = tekst1;
				odg1.odgovori.clear();

				next1->odgovori.push_back(odg1);
			}
			break;
		}
		for (int j = 1; j < next1->odgovori.size(); j++) { //odgovori tejuceg cvora se stavljaju u red
			queue.push(&next1->odgovori[j]);
		}
	}
}

int main() {

	int izbor;
	while (true) {

		cout << "\n1. Kreiranje niza pitanja i unos proizvoljnog broja pitanja\n"
			"2. Dodavanje novog pitanja\n"
			"3. Dodavanje novog odgovora na neko pitanje\n"
			"4. Dodavanje novog komentara na neki odgovor\n"
			"5. Pretraga, vraca pokazivac na koren stabla\n"
			"6. Pretraga odgovora\n"
			"7. Povecavanje ocene nekog odgovora\n"
			"8. Uredjivanje odgovora opadajuce\n"
			"9. Ispis svih pitanja\n"
			"10. Ispis pojedinacnog pitanja i svih odgovora\n"
			"11. Brisanje odgovora/komentara i svih njegovih odgovora\n"
			"12. Brisanje pojedinacnog pitanja i svih odgovora\n"
			"13. Pronalazak odgovora/komentara na zadato pitanje sa najvisom ocenom\n"
			"0. Zavrsetak rada\n\n"
			"Vas izbor? ";

		cin >> izbor;

		switch (izbor) {
		case 1: { //unos proizvoljnog broja pitanja
			svaPitanja.clear();
			cout << endl << "Unesite broj pitanja: ";
			int brojPitanja; cin >> brojPitanja;

			for (int i = 0; i < brojPitanja; i++) {
				cout << "Unesite " << i + 1 << ". pitanje: ";
				string tekst; cin >> tekst;

				pitanje p;
				p.tekst = tekst;

				vector<odgovor> odg;
				odg.clear();
				p.odgovori = odg;

				svaPitanja.push_back(p);
			}
			break;
		}
		case 2: { //dodavanje novog pitanja
			cout << endl << "Unesite tekst novog pitanja: ";
			string tekst; cin >> tekst;

			pitanje p;
			p.tekst = tekst;

			vector<odgovor> odg;
			odg.clear();
			p.odgovori = odg;

			svaPitanja.push_back(p);

			break;
		}
		case 3: { //dodavanje novog odgovora na neko pitanje, pocetna ocena 0
			cout << endl << "Unesite pitanje: ";
			string tekst; cin >> tekst;

			int indeks = -1;
			for (int i = 0; i < svaPitanja.size(); i++) {
				if (svaPitanja[i].tekst == tekst) {
					indeks = i;
					break;
				}
			}
			if (indeks == -1) {
				cout << "***Ne postoji dato pitanje!***";
				break;
			}
			else {
				if (svaPitanja[indeks].odgovori.size() == 10) {
					cout << "***Popunjeno je 10 odgovora!" << endl;
					break;
				}
				cout << "Kako glasi Vas odgovor? " << endl;
				string tekst1; cin >> tekst1;

				odgovor odg;
				odg.ocena = 0;
				odg.kom = 0; //ovo je direktni odgovor na pitanje
				odg.tekst = tekst1;
				odg.odgovori.clear();

				svaPitanja[indeks].odgovori.push_back(odg);
			}
			break;
		}
		case 4: { //dodavanje novog komentara na neki odgovor, pocetna ocena 0
			cout << endl << "Unesite pitanje: ";
			string pit; cin >> pit;

			int indeks = -1;
			for (int i = 0; i < svaPitanja.size(); i++) {
				if (svaPitanja[i].tekst == pit) {
					indeks = i;
					break;
				}
			}

			if (indeks == -1) {
				cout << "***Ne postoji dato pitanje!***";
				break;
			}
			cout << endl << "Unesite odgovor na koji odgovarate: ";
			string tekst; cin >> tekst;

			odgovor* odg = nullptr;
			levelorderOdg(svaPitanja, indeks, tekst);

			break;
		}
		case 5: { //pretraga pitanja, koja vraca pokazivac na koren stabla
			cout << endl << "Unesite tekst pitanja koje trazimo: ";
			string tekst;  cin >> tekst;

			int indeks = -1;
			for (int i = 0; i < svaPitanja.size(); i++) {
				if (svaPitanja[i].tekst == tekst) {
					indeks = i;
					break;
				}
			}
			if (indeks == -1) {
				cout << "***Ne postoji pitanje koje trazite!***" << endl;
			}
			else {
				cout << "Trazeno pitanje je: " << svaPitanja[indeks].tekst << endl;
			}

			break;
		}
		case 6: { //pretraga odgovora, preorder
			cout << endl << "Unesite tekst pitanja, ciji odgovor/komentar trazimo: ";
			string tekst;  cin >> tekst;

			int indeks = -1;
			for (int i = 0; i < svaPitanja.size(); i++) {
				if (svaPitanja[i].tekst == tekst) {
					indeks = i;
					break;
				}
			}
			if (indeks == -1) {
				cout << "***Ne postoji pitanje koje trazite!***" << endl;
			}
			else {
				preorderObilazak(svaPitanja, indeks);
			}

			break;
		}
		case 7: { //povecanje ocene nekog odgovora
			cout << endl << "Unesite tekst pitanja za ciji odgovor/komentar povecavamo ocenu: ";
			string tekst;  cin >> tekst;

			int indeks = -1;
			for (int i = 0; i < svaPitanja.size(); i++) {
				if (svaPitanja[i].tekst == tekst) {
					indeks = i;
					break;
				}
			}
			if (indeks == -1) {
				cout << "***Ne postoji pitanje koje trazite!***" << endl;
				break;
			}
			int f = 0;
			cout << "Unesite odgovor za koji povecavamo ocenu: ";
			cin >> tekst;

			for (int i = 0; i < svaPitanja[indeks].odgovori.size(); i++) {
				if (svaPitanja[indeks].odgovori[i].tekst == tekst) {
					f = 1;
					cout << "Za koliko zelite da povecavate ocenu? " << endl;
					int br; cin >> br;

					svaPitanja[indeks].odgovori[i].ocena += br;
					cout << "Uspesno povecanje odgovora za " << br << endl;
					break;
				}
			}
			if (f == 0) {
				cout << "***Ne postoji dati odgovor!***" << endl;
			}

			break;
		}
		case 8: { //uredivanje odgovora opadajuce


			break;
		}
		case 9: { //ispis svih pitanja
			cout << endl << "Sva pitanja koja su postavljena: " << endl;

			for (int i = 0; i < svaPitanja.size(); i++) {
				cout << "Pitanje " << i + 1 << ". " << svaPitanja[i].tekst << endl << endl;
			}
			break;
		}
		case 10: { //ispis pojedinacnog pitanja i svih njegovih odgovora i komentara
			cout << endl << "Unesite tekst pitanja: ";
			string tekst;  cin >> tekst;

			int indeks = -1;
			for (int i = 0; i < svaPitanja.size(); i++) {
				if (svaPitanja[i].tekst == tekst) {
					indeks = i;
					break;
				}
			}
			if (indeks == -1) {
				cout << "***Ne postoji dato pitanje!***" << endl;
				break;
			}
			else {
				levelorderObilazak(svaPitanja, indeks);
			}

			break;
		}
		case 11: { //brisanje odgovora/komentara i svih njegovih komentara
			cout << endl << "Unesite tekst pitanja koje trazimo: ";
			string tekst;  cin >> tekst;

			int indeks = -1;
			for (int i = 0; i < svaPitanja.size(); i++) {
				if (svaPitanja[i].tekst == tekst) {
					indeks = i;
					break;
				}
			}
			if (indeks == -1) {
				cout << "***Ne postoji pitanje koje trazite!***" << endl;
				break;
			}
			cout << "Unesite tekst odgovora koji se brise" << endl;
			string str; cin >> str;
			int flag = 0;
			for (int i = 0; i < svaPitanja[indeks].odgovori.size(); i++) {
				if (str == svaPitanja[indeks].odgovori[i].tekst) {
					flag = 1;
					svaPitanja[indeks].odgovori.erase(svaPitanja[indeks].odgovori.begin() + i);
				}
			}
			if (flag == 0) {
				cout << "***Ne postoji dati odgovor, pa ga ne mozemo obrisati!***" << endl;
			}

			break;
		}
		case 12: { //brisanje pojedinacnog pitanja i svih odgovora
			cout << endl << "Unesite pitanje koje u potpunosti zelite obrisati: ";
			string tekst; cin >> tekst;

			int flag = 0; //flag koji oznacava da li je pitanje pronadjeno
			for (int i = 0; i < svaPitanja.size(); i++) {
				if (tekst == svaPitanja[i].tekst) {
					flag = 1;
					svaPitanja.erase(svaPitanja.begin() + i);
				}
			}
			if (flag == 0) {
				cout << "***Ne postoji dato pitanje, pa ga ne mozemo obrisati!***" << endl;
			}

			break;
		}
		case 13: { //pronalazak odgovora/komentara na zadato pitanje sa najvisom ocenom
			cout << endl << "Unesite tekst pitanja koje trazimo: ";
			string tekst;  cin >> tekst;

			int indeks = -1;
			for (int i = 0; i < svaPitanja.size(); i++) {
				if (svaPitanja[i].tekst == tekst) {
					indeks = i;
					break;
				}
			}
			if (indeks == -1) {
				cout << "***Ne postoji pitanje koje trazite!***" << endl;
				break;
			}
			int max = -1;
			int ind = -1;
			for (int i = 0; i < svaPitanja[indeks].odgovori.size(); i++) {
				if (svaPitanja[indeks].odgovori[i].ocena > max) {
					ind = i;
					max = svaPitanja[indeks].odgovori[i].ocena;
				}
			}
			if (ind == -1) {
				cout << "***Ne postoji nijedan odgovor!***";
				break;
			}
			else {
				cout << "Komentar sa najvisom ocenom je: " << svaPitanja[indeks].odgovori[ind].tekst << endl;
			}

			break;
		}

		case 0:
			return 0;
		default:
			cout << "Greska, uneli ste nepostojecu opciju! " << endl;
			break;
		}
	}
}