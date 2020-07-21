#include "BirincilIndeks.h"

using namespace std;

void binaryDosyaYenidenYaz(){
    Araba *arabalar[50]; 
    int i;
    string satir;
    ifstream dosya("arabalar.txt", ios::in);
    fstream binDosya("arabalar.bin", ios::out|ios::in|ios::trunc|ios::binary);
    // txt dosyadaki kayıt içermeyen ilk iki satir okunur
    getline(dosya, satir);
    getline(dosya, satir);
    for(i=0; i<50; i++){
            arabalar[i] = new Araba();
            arabalar[i]->txtOku(dosya);
            arabalar[i]->binaryYaz(binDosya);
    }
    dosya.close();
    binDosya.close();
}
int main(int argc, char** argv) {
    binaryDosyaYenidenYaz();
    BirincilIndeks bi("arabalar.bin");
    bi.indeksYazdir();
//    bi.ara("Datsun 210");
//    bi.ara("Nissan Micra");
//    bi.kayitSil("Ford Fiesta");
//    bi.kayitEkle();
//    bi.kayitEkle();
//    bi.kayitSil("Renault 5 GTL");
//    bi.ara("Audi 5000s");
//    bi.ara("Toyota Mark");
//    bi.indeksYazdir();
    return 0; 
}
