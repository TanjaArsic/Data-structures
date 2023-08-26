#include<iostream>
#include<list>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

class Student //jun2 2022.
{
public:
	const char* ime;
	const char* prezime;
	double prosek;
	long long jmbg;
	int status; // 0-slobodan, 1-obrisan, 2-zauzet
	long next;
public:
	Student(const char* i, const char* p, double pr, long long j, int s, long n) : ime(i), prezime(p), prosek(pr), jmbg(j), status(s), next(n) {}
	Student() : ime(nullptr), prezime(nullptr), prosek(0.0), jmbg(0), status(0), next(-1) {}
};

class HashTable
{
protected:
	int count;
	static const int TABLE_SIZE = 64;
	Student table[TABLE_SIZE];
public:
	HashTable()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			table[i] = Student(nullptr, nullptr, 0.0, 0,0, -1);
		}
	}

	unsigned int fPrimary(long long key)
	{
		int day = key / 100000000000; // extract DD
		int month = (key / 1000000000) % 100; // extract MM
		long long ddd = (month - 1) * 30 + day; // sad je DDD

		long long updatedValue = ((ddd * 100000000) + (key % 1000000000)); // replace DDMM with DDD
		
		unsigned int trimmedValue = updatedValue / 10;

		return trimmedValue;

	}
	unsigned int gFibonacci(unsigned int k) //sekundarna transformacija
	{
		unsigned const int a = 2654435769;
		const int bit_size = 32;
		unsigned int b = log2(TABLE_SIZE);
		
		unsigned const ak = a * k;
		return ak >> (bit_size - b);
	}
	unsigned int hash(unsigned int key)
	{
		return gFibonacci(fPrimary(key));
	}

	void insertStudent(Student* student)
	{
		if (isInTable(student))
		{
			cout << "VEC POSTOJI" << endl;
			return;
		}

		unsigned int index = hash(student->jmbg);
		if (!(table[index].status == 0)) //ako postoji !table[index].free
		{
			while (table[index].next != -1)
				index = table[index].next;

			unsigned int tail = index;
			index = gFibonacci(index);

			while (!(table[index].status == 0) && index != tail)
				index = gFibonacci(index);

			if (index == tail)
				cout << "nevalja fibonachi" << endl;
			table[tail].next = index;
			table[index] = *student;

		}
		else //ako ne postoji insertuj
		{
			table[index] = *student;
			//table[index].status = 2;
			//table[index].next = -1;
		}
		
	}

	bool isInTable(Student* student)
	{
		unsigned int probe = hash(student->jmbg);
		unsigned int start = probe;
		do {
			if (table[probe].jmbg == student->jmbg)
				return true;
			probe = (probe + 1) % TABLE_SIZE;
		} while (probe != start);
		return false;
	}

	void printTable()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			Student* student = &table[i];
			std::cout << "Index " << i << ": " << std::endl;
			if (student->jmbg != 0) {
				std::cout << "Name: " << student->ime << " " << student->prezime << std::endl;
				std::cout << "Average: " << student->prosek << std::endl;
				std::cout << "JMBG: " << student->jmbg << std::endl;
			}
			else {
				std::cout << "Empty" << std::endl;
			}
			std::cout << "-------------------------" << std::endl;
		}
	}
};

//	
//	unsigned int f(const char* key) 
//	{
//		unsigned int hash = 0;
//		int i = 0;
//
//		while (key[i] != '\0') {
//			hash += key[i];
//			i++;
//		}

class Student2 // jun2 2023.
{
public:
	int indeks;
	long long jmbg;
	string ime;
	string prezime;
	int godinaUpisa;
	double ocena;
	int status; // -1 : deleted,	0 : prazno,		1: puno
	 
	Student2(int i, long long j, string ime, string prezime, int god, double oc, int st) :
		indeks(i), jmbg(j), ime(ime), prezime(prezime), godinaUpisa(god), ocena(oc), status(st) {	}
	
	Student2() : indeks(0), jmbg(0), ime(""), prezime(""), godinaUpisa(0), ocena(0.0), status(0) {	}
};

class HashTable2
{
protected:
	int count;
	static const int TABLE_SIZE = 64;
	Student2 table[TABLE_SIZE];

public:

	HashTable2()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			table[i] = Student2(0,0,"","",0,0.0,0);
		}
	}
	unsigned int gFibonacci(unsigned int key)
	{
		unsigned const int a = 2654435769;
		const int bit_size = 32;
		unsigned int b = log2(TABLE_SIZE);

		unsigned const ak = a * key;
		return ak >> (bit_size - b);

	}

	unsigned int fPrimary(long long key)
	{
		int day = key / 100000000000; 
		int month = (key / 1000000000) % 100; 
		long long ddd = (month - 1) * 30 + day; 

		long long updatedValue = ((ddd * 100000000) + (key % 1000000000)); // replace DDMM with DDD

		unsigned int trimmedValue = updatedValue / 10;

		return trimmedValue;

	}

	unsigned int hash(long long key)
	{
		return gFibonacci(fPrimary(key));
	}

	void insertStudent(Student2* student)
	{
		int attempt = 0;
		unsigned int index = hash(student->jmbg);
		unsigned int originalIndex = index;
		while (table[index].status != -1 && table[index].status != 0)
		{
			attempt++;
			index = (originalIndex + attempt * attempt) % TABLE_SIZE;
			if (attempt >= TABLE_SIZE)
				return; //tablica je puna
		}
		
		table[index] = *student;
		//table[index].status = 2;
		//table[index].next = -1;	
	}

	void returnData(string ime, string prezime, long long key, double& ocena, int& godinaUpisa, int& brojIndexa)
	{
		unsigned int index = hash(key);

		if (table[index].status == 1 && table[index].jmbg == key
			&& table[index].ime == ime && table[index].prezime == prezime)
		{
			ocena = table[index].ocena;
			godinaUpisa = table[index].godinaUpisa;
			brojIndexa = table[index].indeks;
		}
		else
			ocena = 0.0;
			godinaUpisa = 0;
			brojIndexa = 0;
	}

	void printTable()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			Student2* student = &table[i];
			cout << "Address " << i << ": " << endl;
			if (student->jmbg != 0) 
			{
				cout << "Ime i prezime: " << student->ime << " " << student->prezime << endl;
				cout << "Prosecna ocena: " << student->ocena << endl;
				cout << "JMBG: " << student->jmbg << endl;
				cout << "Indeks: " << student->ocena << endl;
				cout << "Godina upisa: " << student->godinaUpisa << endl;
			}
			else {
				cout << "Empty" << endl;
			}
			cout << "-------------------------" << endl;
		}
	}

};

class Slika //okt2 2022.
{
public:
	string vreme;
	unsigned int oznaka;
	int status;
	Slika(string v, unsigned int o, int s) : vreme(v), oznaka(o), status(s) {}
	Slika() : vreme("00.00.0000. 00.00.00"), oznaka(000), status(0){}

};
class Nadzor
{
protected:
	static const int TABLE_SIZE = 64;
	int count;
	Slika table[TABLE_SIZE];
public:
	Nadzor()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			table[i] = Slika();
		}
	}
	unsigned int gFibonacci(unsigned int k)
	{
		unsigned const int a = 2654435769;
		const int bit_size = 32;
		unsigned int b = log2(TABLE_SIZE);
		unsigned const ak = a * k;
		return ak >> (bit_size - b);
	}
	unsigned int fPrimary(string vreme, unsigned int oznaka)
	{
		//0123456789..23456789
		//дд.мм.гггг. чч.мм.сс
		// ccc
		unsigned int extractedDays = stoi(vreme.substr(0, 2));
		unsigned int hoursToSeconds = stoi(vreme.substr(12, 2)) * 3600 + stoi(vreme.substr(15, 2))*60 + stoi(vreme.substr(18));
		unsigned int time = extractedDays * 100000 + hoursToSeconds; //pretvara se u broj
		unsigned int hash = time * 1000 + oznaka; //neynam sta radim
		cout << hash << endl;
		return hash;

	}
	unsigned int hash(string vreme, unsigned int oznaka)
	{
		return gFibonacci(fPrimary(vreme,oznaka));
	}
	void insert(Slika* s)
	{
		unsigned int index = hash(s->vreme, s->oznaka);
		unsigned int originalIndex = index;
		int attempt = 0;
		while (table[index].status != -1 && table[index].status != 0)
		{
			attempt++;
			index = (originalIndex + attempt * attempt) % TABLE_SIZE;

			if (attempt >= TABLE_SIZE)
			{
				cout << "tablica je puna" << endl;
				return;
			}
		}
		table[index] = *s;
	}
	void printTable()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			Slika* s = &table[i];
			cout << "Index " << i << ": " << endl;
			if (s->status != 0 && s->status != -1)
			{
				cout << "Vreme: " << s->vreme << endl;
				cout << "Kamera: " << s->oznaka << endl;
			}
			else {
				cout << "Empty" << endl;
			}
			cout << "-------------------------" << endl;
		}
	}
};

struct R
{
	string name;
	string prezime;
};
class Radnik // Kolokvijum I 2021.
{
public:
	unsigned int key;
	R* record;
	int status;
	int next;
public:
	Radnik():key(0), record(nullptr), status(0), next(-1){}
	Radnik(unsigned int k, R* r, int s, int n) : key(k), record(r), status(s), next(n) {}
};
class Preduzece
{
protected :
	int count;
	static const int TABLE_SIZE = 16;
	Radnik table[TABLE_SIZE];
public:
	Preduzece()
	{
		count = 0;
		for (int i = 0; i < TABLE_SIZE; i ++)
		{
			table[i] = Radnik();
		}
	}
	unsigned int hash(unsigned int key) //samo fibonacci
	{
		unsigned const int a = 2654435769;
		const int bit_size = 32;
		unsigned int b = log2(TABLE_SIZE);
		unsigned const ak = a * key;
		return ak >> (bit_size - b);
	}
	void printTable()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			Radnik* r = &table[i];
			cout << "Index " << i << ": " << endl;
			if (r->status != 0 && r->status != -1 )
			{
				cout << "Ime: " << r->record->name << endl;
				cout << "Prezime: " << r->record->prezime << endl;
			}
			
			cout << "-------------------------" << endl;
		}
	}
	void insert(Radnik* r)
	{
		unsigned int index = hash(r->key);
		unsigned int originalIndex = index;
		int attempt = 0;
		while (table[index].status != -1 && table[index].status != 0)
		{
			attempt++;
			index = (originalIndex + attempt * attempt) % TABLE_SIZE;

			if (attempt >= TABLE_SIZE)
			{
				cout << "tablica je puna" << endl;
				return;
			}
		}
		if (index != originalIndex)
			table[originalIndex].next = index;
		table[index] = *r;
	}

	R* returnDeleteLast(unsigned int key)
	{
		unsigned int index = hash(key);
		if( table[index].status !=1 || table[index].next == -1)
		{
			cout << "Nije dobar kljuc ili nema sinonima" << endl;
			return nullptr;
		}
		int prev = -1;
		while (table[index].status == 1 && table[index].next != -1)
		{
			prev = index;
			index = table[index].next;
		}
		if (prev != -1)
		{
			table[prev].next = -1;
		}
		table[index].status = -1;
		return table[index].record;
	}




};

int main(int argc, char* argv[])
{
	//HashTable* studentTable = new HashTable();
	////Student* s1 = new Student("Mark", "Markovic", 4.75, 2023101512345,2, - 1);
	//HashTable2* tablica = new HashTable2();
	//Student2* s1 = new Student2(17645,1726333626374,"Mark", "Markovic", 2019, 6.2, 1);
	//cout << "Hash value for s1: " << tablica->hash(s1->jmbg) << endl;
	//tablica->insertStudent(s1);
	//tablica->printTable(); 
	//delete s1;
	//delete studentTable; 
	//delete tablica;
	// 
	//Nadzor* pozar = new Nadzor();
	//Slika* slika1 = new Slika("19.12.2000. 11.30.47", 987, 1);
	//Slika* slika2 = new Slika("19.12.2000. 11.30.47", 987, 1);
	//pozar->insert(slika1);
	//pozar->insert(slika2);
	//cout << "Hash value for slika1: " << pozar->hash(slika1->vreme, slika1->oznaka) << endl;
	//cout << "Hash value for slika2: " << pozar->hash(slika2->vreme, slika2->oznaka) << endl;
	//pozar->printTable();
	//delete pozar; delete slika1; delete slika2;
	//return 0;

	R r1 = { "Tanja", "Arsic" };
	R r2 = { "tanja", "arsic" };
	R r3 = { "tanja", "ignjatovic" };
	Preduzece* preduzece = new Preduzece();
	Radnik* rad1 = new Radnik(123456789, &r1, 1, -1);
	Radnik* rad2 = new Radnik(123456789, &r2, 1, -1);
	Radnik* rad3 = new Radnik(123450789, &r3, 1, -1);

	cout << "Hash vrednost za radnika je: " << preduzece->hash(rad1->key) << endl;
	
	preduzece->insert(rad1);
	preduzece->insert(rad2);
	preduzece->insert(rad3);

	preduzece->printTable();
	R* s2 = preduzece->returnDeleteLast(rad1->key);
	cout << "Ime posl sin: " << s2->name << " " << s2->prezime << endl;
}
