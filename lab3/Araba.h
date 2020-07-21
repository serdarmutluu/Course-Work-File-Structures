
#ifndef ARABA_H
#define ARABA_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

class Araba {
public:
    Araba(){}
    Araba(const Araba& orig){}
    virtual ~Araba(){}
    friend ostream& operator<<(ostream& o, Araba& a){
        o<<"#"<<a.isim<<"||"<<a.mpg<<"||"<<a.silindir<<"||"<<
                a.devinim<<"||"<<a.beygirGucu<<"||"<<
                a.agirlik<<"||"<<a.model<<"||"<<a.mensei<<endl;
        o.flush();
        return o;
    }
    friend istream& operator>>(istream& i, Araba& a){
        string data;
        cout << "Araba ismi:";
        getline(i,data);
        strcpy(a.isim,data.c_str());
        cout << "Araba mpg:";
        getline(i,data);
        a.mpg = atof(data.c_str());
        cout << "Araba silindir:";
        getline(i,data);
        a.silindir = atoi(data.c_str());
        cout<<"Araba devinim:";
        getline(i,data);
        a.devinim = (double)atof(data.c_str());
        cout << "Araba beygirGucu:";
        getline(i,data);
        a.beygirGucu = atof(data.c_str());
        cout <<"Araba agirlik:";
        getline(i,data);
        a.agirlik = (double)atof(data.c_str());
        cout <<"Araba model:";
        getline(i,data);
        a.model = atoi(data.c_str());
        cout <<"Araba mensei:";
        getline(i,data);
        strcpy(a.mensei,data.c_str());
        return i;
    }
    void txtOku(ifstream& dosya){
        string data;
        getline(dosya, data, '\t');
        strcpy(isim, data.c_str());
        getline(dosya, data, '\t');
        mpg = atof(data.c_str());
        getline(dosya, data, '\t');
        silindir = atoi(data.c_str());
        getline(dosya, data, '\t');
        devinim = (double)atof(data.c_str());
        getline(dosya, data, '\t');
        beygirGucu = atof(data.c_str());
        getline(dosya, data, '\t');
        agirlik = (double)atof(data.c_str());
        getline(dosya, data, '\t');
        model = atoi(data.c_str());
        getline(dosya, data, '\n');
        strcpy(mensei, data.c_str());
    }
    void binaryOku(fstream& dosya){
        dosya.read(isim, sizeof(isim));
        dosya.read(reinterpret_cast<char*>(&mpg), sizeof(float));
        dosya.read(reinterpret_cast<char*>(&silindir), sizeof(int));
        dosya.read(reinterpret_cast<char*>(&devinim), sizeof(double));
        dosya.read(reinterpret_cast<char*>(&beygirGucu), sizeof(float));
        dosya.read(reinterpret_cast<char*>(&agirlik), sizeof(double));
        dosya.read(reinterpret_cast<char*>(&model), sizeof(int));
        dosya.read(mensei, sizeof(mensei));
    }
    void binaryYaz(fstream& dosya){
        dosya.write(isim, sizeof(isim));
        dosya.write(reinterpret_cast<const char*>(&mpg), sizeof(float));
        dosya.write(reinterpret_cast<const char*>(&silindir), sizeof(int));
        dosya.write(reinterpret_cast<const char*>(&devinim), sizeof(double));
        dosya.write(reinterpret_cast<const char*>(&beygirGucu), sizeof(float));
        dosya.write(reinterpret_cast<const char*>(&agirlik), sizeof(double));
        dosya.write(reinterpret_cast<const char*>(&model), sizeof(int));
        dosya.write(mensei, sizeof(mensei));
    }
    void kaydiOku(fstream& dosya, int siraNo){
        dosya.seekg((siraNo-1)*boyut(),ios::beg);
        binaryOku(dosya);
    }
    void kaydiYaz(fstream& dosya, int siraNo){
        dosya.seekp((siraNo-1)*boyut(),ios::beg);
        binaryYaz(dosya);
    }
    void sil(){
        isim[0] = '*';
    }
    int boyut(){
        return sizeof(isim)+2*sizeof(float)+2*sizeof(int)+
                2*sizeof(double)+sizeof(mensei);
    }
    char* okuIsim(){    return isim;    }
    int okuModel(){    return model;    }
    
private:
    char isim[50];
    float mpg;
    int silindir;
    double devinim;
    float beygirGucu;
    double agirlik;
    int model;
    char mensei[20];
};

#endif /* ARABA_H */

