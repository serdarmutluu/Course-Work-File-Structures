#include "SiraliDosya.h"

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
    SiraliDosya sd("arabalar.bin");
    sd.ismeGoreArama("Honda Accord");
    sd.ismeGoreArama("Dodge Challenger");
    sd.modeleGoreArama(77);
    sd.kayitSil("Chevrolet Camaro");
    sd.kayitSil("Audi 5000");
    sd.ismeGoreArama("Chevrolet Camaro");
    //sd.kayitEkle();
    //sd.kayitEkle();
    //sd.kayitEkle();
    //sd.ismeGoreArama("Toyota Mark");
    return 0; 
}