#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <exception>
#include <new>

using namespace std;
template <typename NekiTip>
int **AlocirajFragmentirano(const vector<NekiTip> &vek, int koliko_puta);
template <typename NekiTip>
int **AlocirajKontinualno(const vector<NekiTip> &vek, int koliko_puta);
template <typename NekiTip>
int **KreirajPoUvrnutomPravilu(vector<NekiTip> &vek, int koliko_puta,bool fragmentirano =true);
template <typename NekiTip>
int Period(vector<NekiTip> v);
int main()
{
    try{
    cout<<"Unesite broj elemenata vektora: ";
    int broj_elemenata;
    cin>>broj_elemenata;
    int broj;
    vector<int> vek;
    cout<<"Unesite elemente vektora: ";
    for(int i=0;i<broj_elemenata;i++){
        cin>>broj;
        vek.push_back(broj);
    }
    cout<<"Unesite broj ponavljanja: ";
    int koliko_puta=3;
    cin>>koliko_puta;
    cout<<"Odaberite alokaciju: 1 – fragmentirana, 0 – kontinualna: ";
    bool fragmentirano=true;
    cin>>fragmentirano;

    int **pok{nullptr};
    pok=KreirajPoUvrnutomPravilu(vek,koliko_puta,fragmentirano);
    cout<<"Dinamicki alocirana matrica:"<<endl;
    for(int i=0;i<koliko_puta*vek.size();i++){
        for(int j=0;j<vek[i%vek.size()];j++){
            cout<<pok[i][j]<<" ";
        }
           cout<<endl;
        if(i%vek.size()==vek.size()-1) cout<<endl;
    }
    if(fragmentirano){
        for(int i=0;i<koliko_puta*vek.size();i++) delete [] pok[i];
        delete[] pok;
    }else {
        delete[] pok[0];
        delete[] pok;
    }
    return 0;
    }
    catch(domain_error e){
        cout<<"Izuzetak: ";
    cout<<e.what();
    }
    catch(const char poruka[]){
                cout<<"Izuzetak: ";
        cout<<poruka;
    }
    catch(bad_alloc e){
                cout<<"Izuzetak: ";
        cout<<e.what();
    }
}
template <typename NekiTip>
int **KreirajPoUvrnutomPravilu(vector<NekiTip> &vek, int koliko_puta,bool fragmentirano){
    if(vek.empty() or vek.size()<=0)throw  "Prazan vektor!";
    if(koliko_puta<=0) throw domain_error ("Neispravan broj ponavljanja!");
    if(*min_element(vek.begin(),vek.end())<=0)throw domain_error ("Neispravan vektor!");
    try{
    if(Period(vek)!=0){
            vek.resize(Period(vek));
    }else{
        int najveci_element = *max_element(vek.begin(),vek.end());
        for(int i=0; i<vek.size();i++) vek[i]=najveci_element+1-vek[i];
    }
    if(fragmentirano){
        return AlocirajFragmentirano(vek,koliko_puta);
    }else   return AlocirajKontinualno(vek,koliko_puta);
    return 0;
    }
    catch(...)
    {
    throw;
    }
}
template <typename NekiTip>
int **AlocirajKontinualno(const vector<NekiTip> &vek, int koliko_puta){
    if(vek.empty() or vek.size()<=0)throw "Prazan vektor!";
    if(koliko_puta<=0) throw domain_error ("Neispravan broj ponavljanja!");
    if(*min_element(vek.begin(),vek.end())<=0)throw domain_error ("Neispravan vektor!");
    try{
    int suma_elem=0;
    int najveci_element = *max_element(vek.begin(),vek.end());
    for(int i=0;i<vek.size();i++)suma_elem+=vek[i];
    int **pok{nullptr};
    pok = new int*[vek.size()*koliko_puta];

    try{
    pok[0]= new int[suma_elem*koliko_puta];
    for(int i=1;i<=koliko_puta*vek.size();i++){
            pok[i] = pok[i-1]+vek[(i-1)%vek.size()];
    }
    }
    catch(...){
        delete [] pok;
    throw;
    }
    for(int i=0;i<koliko_puta*vek.size();i++){
        for(int j=0;j<vek[i%(vek.size())];j++){
            pok[i][j]= vek[i%(vek.size())]-j;
        }
    }

    return pok;
    }
    catch(...){
    throw;
    }

}
template <typename NekiTip>
int **AlocirajFragmentirano(const vector<NekiTip> &vek, int koliko_puta){

    if(vek.empty() or vek.size()<=0)throw "Prazan vektor!";
    if(koliko_puta<=0) throw domain_error ("Neispravan broj ponavljanja!");
    if(*min_element(vek.begin(),vek.end())<=0)throw domain_error ("Neispravan vektor!");
    try{
    int **pok{nullptr};
    pok=new int*[vek.size()*koliko_puta];
    int najveci_element = *max_element(vek.begin(),vek.end());
    for(int i=0;i<koliko_puta*vek.size();i++)pok[i]=nullptr;
    try{
    for(int i=0;i<koliko_puta*vek.size();i++){
            pok[i] = new int[vek[i%(vek.size())]];
        }
    }
    catch(...){
        for(int i=0;i<koliko_puta*vek.size();i++)delete [] pok[i];
            delete [] pok;
        throw;
    }
    for(int i=0;i<koliko_puta*vek.size();i++){
        for(int j=0;j<vek[i%(vek.size())];j++){
            pok[i][j]= najveci_element-vek[i%(vek.size())]+j +1;
        }
    }
    return pok;
    }
    catch(...){
        throw;
    }
}
template <typename NekiTip>
int Period(vector<NekiTip> v){
        vector<int> periodi;
        if(v.empty()) return 0;
        for(int i = 1; i< v.size(); i++) if(v[0] == v[i])periodi.push_back(i);
        for(int i = 0; i< periodi.size(); i++){
                for(int j = 0; j < v.size()-periodi[i]; j++){
                        if(v[j] != v[j+periodi[i]]) remove(periodi.begin(),periodi.end(),periodi[i]);
                }
        }
        if(periodi.size()==0)return 0;
        return *max_element(periodi.begin(),periodi.end());
}

