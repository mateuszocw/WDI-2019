#include <iostream>
using namespace std;

const int N = 6; //do zad 6 i 7
const int 2do30 = 1000000000; //(wartosc nieco mniejsza od 2^30) do zad 7
const int S = 4; //do zad 8

//zad 6:
/*	Zasada:
Szukam od prawej strony aż do znalezienia liczby pierwszej.
Jeśli funkcja nie znajdzie liczby pierwszej zwraca false.
Jeśli znajdzie liczbę pierwszą, wywołuje kolejną funkcję (chyba, że doszła do końca tablicy - wtedy zwraca true)
*Jeśli stoi 0 na początku ciągu funkcja zwraca false (np. 000011 daje false)
*/
bool prime(int n) {
	if (n < 2) return false;
	if (n == 2) return true;
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) return false;
	}
	return true;
}
bool cut(int t[N], int i, int liczba) { //cut(t, N-1, 0)
	if (i < 0) return true;
	for (int mask = 1; i >= 0 && mask < 2do30; i--, mask *= 2) { //	mask < 2do30 - ograniczenie do 30 elementów
		if (t[i] == 1) { //Jeśli stoi '0' to nie muszę go dodawać i sprawdzać tak otrzymanej liczby
			liczba += mask;
			if (prime(liczba)) {
				if (cut(t, i - 1, 0)) return true;
			}
		}
	}
	return false;
}

//zad 7:

//Szukam {1, potem 2, 3 ... N} elementowych zbiorów, których suma jest równa sumie ich indeksów.
//Gdy znajdę, zwracam jego sumę.
int zbiory(int t[N], int p, int si, int sw, int n) { 
	if (n == 1) {
		for (int i = p; i < N; i++) {
			if (sw + t[i] == si + i) {
				cout << i <<  ": " << sw+t[i] << "=" << si+i << endl; return i;
			}
		}
	}
	else if (n > 1) {
		for (int i = p, x; i <= N - n; i++) {
			x = zbiory(t, i + 1, si + i, sw + t[i], n - 1);
			if (x > 0) return  i + x;
		}
	}
	return 0;
}

//zad 8:
/*	
	pozycja króla: w=0, k=?
	król porusza się tylko w dół (albo po skosie w dół)
	f zwraca minimalny koszt przejścia
	Uwzględnić koszt startowy i końcowy do sumy
*/

int koszt(int t[S][S], int w, int k) { //(t, 0, 0)
	if (w == S - 1) return t[w][k]; //gdy dojde na koniec, zwracam koszt ostatniego pola (do poprzedniej funkcji)
	else {
		int L, R, D; L = R = D = INT_MAX;
		if (k - 1 >= 0) { //jeśli możliwy ruch w lewo (nie wyskakujemy poza tablice)
			L= t[w][k] + koszt(t, w + 1, k - 1);
		}
		if (k + 1 < S) { //jeśli możliwy ruch w prawo
			R = t[w][k] + koszt(t, w + 1, k + 1);
		}
		D= t[w][k] + koszt(t, w + 1, k); //ruch w dół zawsze mogę wykonać!
		return L < R ? (L < D ? L : D) : (R < D) ? R : D; //zwracam najmniejszy koszt z 3 ruchów
	}
}



int main()
{
		//zad 6: 

	int t1[N] = { 1, 1, 1, 0, 1, 1 }; //spr 1 (powinno dac true)
	cout << "Sprawdzam dla 111011: ";
	if (cut(t1, N - 1, 0)) cout << "True";
	else cout << "False";
	int t2[N] = { 1, 1, 0, 1, 0, 0 }; //spr 2 (powinno dac false)
	cout << endl << "Sprawdzam dla 110100: ";
	if (cut(t2, N - 1, 0)) cout << "True";
	else cout << "False";


		//zad 7:
		
	int t7[N] = { 1, 7, 3, 5, 11, 2 }; //0:1, 3:5, 5:2 poprawny wynik to 8...
	int x;
	for (int n = 1; n <= N; n++) {
		if ((x = zbiory(t7, 0, 0, 0, n)) > 0) {
			cout << n << ": " << x;
			break;
		}
	}

		//zad 8:
	int koszta[S][S] = { //przykladowe wartosci
	{3, 2, 1, 4}, 
	{7, 11, 12, 2},
	{3, 6, 3, 6},
	{1, 2, 11, 12}
	};
  
	for (int i = 0; i < S; i++) {
		cout << "Jeśli krol startuje z pola (w,k) : (0," << i << ") to minimalny koszt wynosi: " << koszt(koszta, 0, i) << endl;
	}
	return 0;
  }
