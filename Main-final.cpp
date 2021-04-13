//Szyfr Polibiusza
//£ukasz Ka³a, Mateusz Dec
#include <iostream>
#include <cstdlib>

class Polibiusz
{
	char* word_; //tekst jawny
	int world_len_; //d - d³ugoœæ bloku danych
	char key_tab_[5][5]; //K - Klucz szyfrowania
	int* encrypted_word_; //C - szyfrogram
	char small_to_large(char);// zamiana ma³ych na du¿e litery
	int find_coord(bool, char);// Wyszukiwanie koordynatów litery
public:
	Polibiusz(std::string&);
	void encrypt(); // funkcja szyfruj¹ca
	int* get_encrypted_word();// zwrócenie szyfrogramu C
	void print_encrypted_word();// wypisanie szyfrogramu C
};

class Polibiusz_decyrpt
{
	int* encrypted_word_;//C - szyfrogram
	int encrypted_word_len_;//d - d³ugoœæ bloku danych
	char key_tab_[5][5];//K - klucz szyfrowania
	char* word_;//tekst jawny
public:
	Polibiusz_decyrpt(std::string &);
	void decrypt();//funkcja deszyfruj¹ca
	char* get_decrypted_word();// zwrócenie tekstu jawnego po wypisaniu
	void print_decrypted_word();// wypisanie tekstu jawnego
};

int main()
{
	std::string word ;
	std::cout<<"Podaj slowo do zaszyfrowania: ";
	getline(std::cin,word);
	std::string enc_word;
	
	std::string enc_word2 = "2534441525"; // zaszyfrowane s³owo 

	Polibiusz p(word);// za³adowanie tekstu jawnego
	p.encrypt();// szyfrowanie
	p.print_encrypted_word();// wypisanie zaszyfrowanego s³owa
	std::cout<<"Podaj slowo do odszyfrowania: ";
	getline(std::cin,enc_word);
	Polibiusz_decyrpt e(enc_word);// za³adowanie szyfrogramu C
	e.decrypt();// Odszyfrowanie szyfrogramu C
	e.print_decrypted_word();// Wypisanie tekstu jawnego po odszyfrowaniu
	
	system("pause");
	return 0;
}

char Polibiusz::small_to_large(char c)
{
	if (c >= 'a')
		c -= 'a'-'A';
	if(c == 'J')
		return'I';
	return c;
}

int Polibiusz::find_coord(bool b ,char c) //{b} 0 -> x & 1 -> y; {c} litera;
{
	for(int x = 0; x<5; x++)
	{
		for(int y = 0; y<5; y++)
		{
			if (key_tab_[x][y] == c)
			{
				if (b == 0)
					return x;
				return y;
			}
		}
	}
	return -1;
}

Polibiusz::Polibiusz(std::string& s)
{
	char a = 'A';
	int counter = 0;
	world_len_ = s.length();
	word_ = new char[world_len_];
	for (int x = 0; x < world_len_; x++)
	{
		word_[x] = small_to_large(s[x]); //konwersja liter na du¿e
	}
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (counter == 9) counter++;// pominiêcie  litery J
			// wype³nienie tabeli 5x5 klejnymi literami (Klucza szfrowania K)
			key_tab_[x][y] = char(a + counter);
			
			counter++;
		}
	}
	encrypted_word_ = 0;
}

void Polibiusz::encrypt()
{
	encrypted_word_ = new int[world_len_*2];
	for (int i = 0, ii = 0; i < world_len_ * 2; i += 2, ii++) //szyfrowanie ( za ka¿d¹ liczbê podstawiane s¹ jej koordynaty w Kluczu K (tabeli liter 5x5)
	{
		encrypted_word_[i] = find_coord(0, word_[ii]);
		encrypted_word_[i + 1] = find_coord(1, word_[ii]);
	}
}

int* Polibiusz::get_encrypted_word()
{
	return encrypted_word_;
}

void Polibiusz::print_encrypted_word()
{
	std::cout << std::endl;
	for(int i = 0;i<world_len_*2;i++)
	{
		std::cout << encrypted_word_[i]+1;
	}
	std::cout << std::endl;
}

Polibiusz_decyrpt::Polibiusz_decyrpt(std::string & s)
{
	char a = 'A';
	int counter = 0;
	encrypted_word_len_ = s.length();
	encrypted_word_ = new int[encrypted_word_len_];
	for(int i = 0; i<s.length(); i++)
	{
		encrypted_word_[i] = int(s[i]) - 49;// przepisanie pobranego ci¹gu i zamiana na integer
	}
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (counter == 9) counter++;
			key_tab_[x][y] = char(a + counter);// utowrzenie Klucza szfrowania K (poprzez wype³nienie tabeli kolejnymi literami)

			counter++;
		}
	}
	word_ = new char [encrypted_word_len_/2];
}

void Polibiusz_decyrpt::decrypt()
{
	int x;
	int y;
	for (int i = 0,  ii =0; i < encrypted_word_len_; i+=2, ii++)
	{
		//odszyfrowanie poprzez pobieranie kolejnych znaków szyfrogramu C po 2 znaki
		//i u¿ywania ich jako po³o¿enia kolejnych liter i wstawiania liter o danym po³o¿enia do tablicy
		//sk³adaj¹cego siê z 2 kolejnych znaków
		x = encrypted_word_[i];
		y = encrypted_word_[i + 1];
		word_[ii] = key_tab_[x][y];
	}

}

char* Polibiusz_decyrpt::get_decrypted_word()
{
	return word_;
}

void Polibiusz_decyrpt::print_decrypted_word()
{
	for(int i = 0;i<encrypted_word_len_/2;i++)
	{
		std::cout << word_[i];
	}
	std::cout << std::endl;
}
