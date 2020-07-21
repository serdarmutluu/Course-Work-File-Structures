/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: serdarm99
 *
 * Created on 03 Mart 2020 Salı, 20:40
 */

#include <iostream>
#include "Araba.h"
#include <string>
#include <fstream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Araba * arabalar[50];
    int i;
    string satir;
    ifstream dosya("arabalar.txt", ios::in);
    ofstream txtDosya("benimArabalar.txt", ios::out | ios::trunc);
    fstream binDosya("arabalar.bin", ios::out | ios::in | ios::trunc | ios::binary);
    // txt dosyadaki kayıt içermeyen ilk iki satir okunur
    getline(dosya, satir);
    getline(dosya, satir);
    for (i = 0; i < 50; i++) {
        arabalar[i] = new Araba();
        arabalar[i]->txtOku(dosya);
        txtDosya << *arabalar[i];
        arabalar[i]->binaryYaz(binDosya);
    }
    dosya.close();
    txtDosya.close();
    Araba a1, a2, a3;
    a1.kaydiOku(binDosya, 25);
    a2.kaydiOku(binDosya, 11);
    a3.kaydiOku(binDosya, 37);
    cout << a1 << endl << a2 << endl << a3 << endl;
    a1.binaryYaz(binDosya);
    binDosya.close();
}

