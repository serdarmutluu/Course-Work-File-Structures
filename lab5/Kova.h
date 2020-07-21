/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Kova.h
 * Author: serdarm99
 *
 * Created on 03 Mayıs 2020 Pazar, 19:47
 */

#ifndef KOVA_H
#define KOVA_H
#define KOVA_SAYISI 3

#include "Araba.h"

class Kova {
public:
    Araba* kovaElemanlari[KOVA_SAYISI];
    int adres;

    Kova() {
        adres = -1;
        for (int i = 0; i < KOVA_SAYISI; i++) {
            kovaElemanlari[i] = new Araba();
        }
    }

    friend ostream& operator<<(ostream& o, Kova& k) {
        for (int i = 0; i < KOVA_SAYISI; i++) {
            o << *k.kovaElemanlari[i];
        }
        o.flush();
        return o;
    }
    int okuAdres(){
        return adres;
    }

    Araba* okuEleman(int n) {
        if (n < KOVA_SAYISI)
            return kovaElemanlari[n];
        else
            return NULL;
    }

    void yazEleman(int n, Araba* a) {
        if (n < KOVA_SAYISI)
            kovaElemanlari[n] = a;
        else
            return;
    }
    void binaryYazKova(fstream& dosya){
        for(int i = 0;i<KOVA_SAYISI;i++){
            kovaElemanlari[i]->binaryYaz(dosya);
        }
    }

    void binaryYazKova(fstream& dosya, int adr) {
        adres = adr;
        dosya.seekp(adres*kovaBoyutu(),ios::beg);
        binaryYazKova(dosya);
    }
    void binaryOkuKova(fstream& dosya){
        for(int i = 0;i<KOVA_SAYISI;i++){
            kovaElemanlari[i]->binaryOku(dosya);
        }
    }

    void binaryOkuKova(fstream& dosya, int adr) {
        adres = adr;
        dosya.seekg(adres*kovaBoyutu(),ios::beg);
        binaryOkuKova(dosya);
    }

    static int kovaSayisi() {
        int sayi = KOVA_SAYISI;
        return sayi;
    }

    int kovaBoyutu() {
        int size;
        size = (kovaSayisi() * sizeof (Araba*) + sizeof (int));
        return size;
    }
    
};


#endif /* KOVA_H */

