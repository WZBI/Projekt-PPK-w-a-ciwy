#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
#include <fstream>

using namespace std;
typedef pair<double, pair<string, string> > Droga;      //tworzy szablon do przechowywania 2 typów zmiennych
map<string, string> Miasta;                         //Tworzenie mapy o nazwie Miasta

double pobierajkoszt(Droga droga) {                 //Pobiera liczbe z linijki
    return droga.first;
}

string pobierajMiasto1(Droga droga) {               //pobiera miasto z pozycji 1
    return droga.second.first;
}

string pobierajMiasto2(Droga droga) {               //pobiera miasto z pozycji 2
    return droga.second.second;
}


string zwrockorzen(string miasto) {                             //zwraca miasto ³¹cz¹ce 2 miasta
    if (Miasta.count(miasto)) {
        return Miasta[miasto] = zwrockorzen(Miasta[miasto]);
    }
    else return miasto;
}

int main(int argn, char* args[]) {
    vector<Droga> Drogi;
    bool jestplikwejsciowy = false;
    bool jestplikwyjsciowy = false;
    char* Plikwejsciowy = NULL;
    char* Plikwyjsciowy = NULL;
    for (int i = 1; i < argn - 1; i++) {
        int len = strlen(args[i]);
        if (len >= 2 && args[i][0] == '-') {        //przypisuje pliki wejœciowy i wyjœciowy do wartoœci char
            if (args[i][1] == 'i') {                
                Plikwejsciowy = args[i + 1];
                jestplikwejsciowy = true;
            }
            if (args[i][1] == 'o') {
                Plikwyjsciowy = args[i + 1];
                jestplikwyjsciowy = true;
            }
        }
    }
    if (!jestplikwejsciowy) {
        cout << "Brak pliku wejsciowego" << endl;
        return 0;
    }
    ifstream fi(Plikwejsciowy);
    cout << "Dane wejsciowe:" << endl;
    while (true) {
        Droga road;
        double Koszt;                                       //czyta linijke polinijce i zapisuje nazwy miast jako startmiasto i endmiasto
        string startmiasto = "";
        string endmiasto = "";
        fi >> startmiasto >> endmiasto >> Koszt;
        if (startmiasto == "" || endmiasto == "") {
            break;
        }
        cout << startmiasto << " " << endmiasto << " " << Koszt << endl;
        Drogi.push_back(make_pair(Koszt, make_pair(startmiasto, endmiasto)));
    }
    ofstream fo;
    if (jestplikwyjsciowy) {
        fo.open(Plikwyjsciowy);
    }
    sort(Drogi.begin(), Drogi.end());
    cout << "Plik wyjsciowy: " << endl;
    for (int i = 0; i < Drogi.size(); i++) {
        string PierwszeMiasto = pobierajMiasto1(Drogi[i]);
        string DrugieMiasto = pobierajMiasto2(Drogi[i]);
        double Koszt = pobierajkoszt(Drogi[i]);
        string PierwszeMiastoRoot = zwrockorzen(PierwszeMiasto);
        string DrugieMiastoRoot = zwrockorzen(DrugieMiasto);
        if (PierwszeMiastoRoot != DrugieMiastoRoot) {
            cout << PierwszeMiasto << " " << DrugieMiasto << " " << Koszt << endl;
            if (jestplikwyjsciowy) {
                fo << PierwszeMiasto << " " << DrugieMiasto << " " << Koszt << endl;
            }
            Miasta[PierwszeMiastoRoot] = DrugieMiastoRoot;
        }
    }
    fo.close();
    fi.close();
    return 0;
}