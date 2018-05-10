#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

// Folosit ca sa memoram o productie
struct Productie {
    char litera;
    string cuvant;
};

// Folosit ca sa memoram o gramatica
struct Gramatica {
    Productie *productii;
    int nrProductii;
    vector<string> cuvinteGenerate;
};

/**
 *
 * @param cuvant = cuvantul pe care il genereaza la pasul curent (incepe initial cu starea 'S')
 * @param g = gramatica data
 * @param limitaLitere = lungimea maxima a cuvintelor generate
 */
void generareCuvinte(string cuvant, Gramatica &g, int limitaLitere) {
    int pozitieNeterminal = -1;
    char literaNeterminal = NULL;
    string copieCuvant;

    // Verificam daca avem neterminal si salvam pozitia daca da
    for(int i = 0; i <= cuvant.length(); i++) {
        if(cuvant[i] >= 'A' && cuvant[i] <= 'Z') {
            literaNeterminal = cuvant[i];
            pozitieNeterminal = i;
            break;
        }
    }

    // Daca nu exista neterminale in cuvant si daca ne incadram in limita de lungime atunci adaugam cuvantul
    // la vectorul de cuvinte generate
    if(pozitieNeterminal == -1 && cuvant.length() <= limitaLitere){
        if(cuvant.length() == 0) g.cuvinteGenerate.emplace_back("Cuvantul vid!");
        else g.cuvinteGenerate.emplace_back(cuvant);
        return;
    }
    // Daca mai exista neterminale in cuvant atunci le dezvoltam
    else if(pozitieNeterminal != -1){
        for(int i = 0; i < g.nrProductii; i++) {
            // Cautam in gramatica productia cu neterminalul curent, daca cuvantul se incadreaza in limita de litere atunci dezvoltam
            if(g.productii[i].litera == literaNeterminal && cuvant.length() <= limitaLitere) {
                // Facem o copie a cuvantul pt a o folosi in recursivitate(vrem ca atunci can termina recursia inca sa avem cuvantul dinainte)
                copieCuvant = cuvant;
                // Daca gasim ~ adica lambda atunci doar stergem litera neterminala din cuvantul curent
                if(g.productii[i].cuvant == "~") {
                    copieCuvant.erase(pozitieNeterminal, 1);
                }
                // Altfel, stergem litera si inlocuim cu stringul corespunzator productiei
                else {
                    copieCuvant.erase(pozitieNeterminal, 1);
                    copieCuvant.insert(pozitieNeterminal, g.productii[i].cuvant);
                }
                // Apelam recursiv cu ajutorul copiei cuvantului
                generareCuvinte(copieCuvant, g, limitaLitere);
            }
        }
    }

}

int main() {
    ifstream f("..//date-pdf.in");
    Gramatica gramatica;
    int limitaLitere;


    // Citim gramatica
    f >> gramatica.nrProductii;
    gramatica.productii = new Productie[gramatica.nrProductii];
    for (int i = 0; i < gramatica.nrProductii; i++) {
        f >> gramatica.productii[i].litera;
        f.get();
        f >> gramatica.productii[i].cuvant;
        f.get();
    }

    // Afisam gramatica
    cout<<"Gramatica este: \n";
    for (int i = 0; i < gramatica.nrProductii; i++) {
        cout<<gramatica.productii[i].litera<<":"<<gramatica.productii[i].cuvant<<endl;
    }
    cout<<endl;

    // Setam cuvantul de inceput sa fie 'S' adica sa inceapa din starea S generarea
    string stareInceput;
    stareInceput.push_back('S');
    cout<<"Introduceti limita de litere pana la care se vor genera cuvintele gramaticii:";
    cin>>limitaLitere;

    // Generam cuvintele pana in limita 'limitaLitere' si apoi le afisam
    generareCuvinte(stareInceput, gramatica, limitaLitere + 1);
    cout<<"Cuvintele generate sunt: \n";
    for(int i = gramatica.cuvinteGenerate.size() - 1; i >= 0; i--) {
        cout<<gramatica.cuvinteGenerate[i]<<endl;
    }


}