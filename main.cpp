#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;





class baza{
public:
    virtual int getVal() const = 0;
    virtual void afisare() const = 0;
    virtual ~baza() = default;
};

class Locomotiva:public baza{
 int valoare;
 int id;
 public:
    Locomotiva(int x, int y):valoare{x},id{y} {}
    int getVal() const
    {
        return valoare;
    }
    void afisare() const
    {
        cout<<"Locomotiva cu valoarea: "<<valoare<<" si cu id-ul: "<<id<<endl<<endl;
    }
    ~Locomotiva() = default;
};

class Imbunatatire:public baza {
 string tip = nullptr; //AC, tapiterie x
 int pret = 0;
 public:
    Imbunatatire() = default;
    Imbunatatire(string s, int i):tip{s}, pret{i} {}
    int getVal() const
    {
        return pret;
    }
    void afisare() const
    {
        cout<<"Imbunatatire de tip "<<tip<<" si pret "<<pret<<endl;
    }
    ~Imbunatatire() = default;
};

class Vagon:public baza {
 vector<Imbunatatire> vi = vector<Imbunatatire>(); //vector cu imbunatatiri
 int nr_i = 0; //numar de imbunatatiri
 int pret_de_baza = 0;
//valoare= pret_de_baza + suma valorilor pentru fiecare imbunatatire
public:
    Vagon() = default;
    Vagon(vector<Imbunatatire> vec, int n, int p):vi{vec}, nr_i{}, pret_de_baza{p} {}
    int getVal() const
    {
        int valoare{pret_de_baza};
        vector<Imbunatatire>::const_iterator it=vi.begin();
        while (it!=vi.end())
        {
        valoare += (*it).getVal();
        it++;
        }
    }
    void afisare() const
    {
        cout<<"Vagon cu imbunatatirile: "<<endl;
        vector<Imbunatatire>::const_iterator it=vi.begin();
        while (it!=vi.end())
        {
        (*it).afisare();
        it++;
        }
        cout<<"cu nr de imbunatatiri "<<nr_i<<" si cu pretul de baza "<<pret_de_baza<<endl;
    }
    ~Vagon() = default;
};

class Garnitura:public baza {
protected:
 Locomotiva l;
 vector<Vagon> vv; // vector cu vagoanele
 int nr; // cate vagoane
// valoare = valoare locomotiva + suma valorilor vagoanelor
public:
    Garnitura(Locomotiva p, vector<Vagon> V, int i):l{p}, vv{V}, nr{i} {}
    int getVal() const
    {
        int valoare{l.getVal()};
        vector<Vagon>::const_iterator it=vv.begin();
        while (it!=vv.end())
        {
        valoare += (*it).getVal();
        it++;
        }
    }
    void afisare() const
    {
        l.afisare();
        vector<Vagon>::const_iterator it=vv.begin();
        while (it!=vv.end())
        {
        (*it).afisare();
        it++;
        }
        cout<<"cu nr de vagoane: "<<nr<<endl;
    }
    ~Garnitura() = default;
};


int main()
{
    vector<Imbunatatire> imb;
    imb.push_back(Imbunatatire("tapiterie",209));
    imb.push_back(Imbunatatire("altceva",90));

    vector<Vagon> va;
    va.push_back(Vagon(imb,21,3));
    va.push_back(Vagon(imb,23,1));

    vector<baza* > vec;
    vec.push_back(new Locomotiva(2000,1));
    vec.push_back(new Vagon(imb,2,1));
    vec.push_back(new Garnitura(Locomotiva(2000,1),va,45));

    vector<baza* >::const_iterator it=vec.begin();
    while(it!=vec.end())
    {
    (*it)->afisare();
    it++;
    }

    int numr{0};

    it=vec.begin();
    while(it!=vec.end())
    {
    if((*it)->getVal() < 10000) numr++;
    it++;
    }
    cout<<"Sunt "<<numr<<" bun(uri) cu valoarea < 10000"<<endl;


    it=vec.begin();
    it++;
    vector<baza* >::const_iterator it2 = it;
    it--;
    while(it != vec.end())
    {
        while(it2 != vec.end())
        if( (*it)->getVal() /* < (*it2)->getVal() */) swap(it,it2); ///sortare dupa valoarea bunurilor, desi una fara de sens
        it++;
    }

    ///am reapela afisarea vectorului daca am fi facut o functie pentru asta...



    ///cout << "Hello world!" << endl;

    return 0;
}
