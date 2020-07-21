/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SiraliDosya.h
 * Author: serdarm99
 *
 * Created on 21 Mart 2020 Cumartesi, 14:39
 */

#ifndef SIRALIDOSYA_H
#define SIRALIDOSYA_H

#include "Araba.h"
#include <deque>

#endif /* SIRALIDOSYA_H */

class SiraliDosya {
private:
    fstream dosya;
    deque<int> boslarListesi;
public:

    SiraliDosya(char* dosyaAdi) {
        dosya.open(dosyaAdi, ios::out | ios::in | ios::bin);
    }

    ~SiraliDosya() {
        dosya.close();
    }

    void basaSar() {
        dosya.clear();
        dosya.flush();
    }

    int ismeGoreArama(char* arananIsim) {
        char isim[50];
        int rrn = 0;
        while (!dosya.eof()) {
            dosya.read(isim, sizeof (isim));
            if (strcmp(isim, arananIsim) == 0) {
                rrn = dosya.tellg();
                rrn -= sizeof (isim);
                rrn /= sizeof (Araba);
                rrn += 1;
                cout << rrn;
                Araba *a = new Araba();
                a->kaydiOku(dosya, rrn);
                cout << a;
                return 0;
            } else if (isim[0] == '*') {
                cout << "aranan isim dosyada bulunamamistir";
                return -1;
            }
            dosya.seekg(94,ios::cur);
        }
        cout << "aranan isim dosyada bulunamamistir";
        return -1;
    }
};

