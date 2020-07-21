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

        dosya.open(dosyaAdi, ios::in | ios::out | ios::binary);
    }

    ~SiraliDosya() {
        dosya.close();
    }

    void basaSar() {
        dosya.clear(); //dosyanın işaretçi durumları ile bayraklarını sıfırlar ve
        dosya.flush(); //tampondaki bilgileri dosyaya aktarir


    }

    int ismeGoreArama(char* arananIsim) {
        basaSar();
        Araba a;
        int rrn = 0;
        while (!dosya.eof()) {//dosya sonuna gelinene kadar okuma yapilir
            a.kaydiOku(dosya, rrn + 1);
            char* isim = a.okuIsim();
            if (strcmp(a.okuIsim(), arananIsim) == 0) {//bulundugunda konsola yazdirilir
                cout << a;
                cout << rrn + 1 << ". kayıtta bulundu" << "\n";
                return rrn;
            } else if (*isim == '*') {
                cout << "aranan isim dosyada bulunamamistir" << "\n";
                return -1;
            }
            rrn++;

        }

        cout << "aranan isim dosyada bulunamamistir" << "\n";
        return -1;
    }

    bool modeleGoreArama(int arananModel) {
        basaSar();
        Araba a;
        int rrn = 0;
        bool sonuc = false;
        while (!dosya.eof()) {//dosya sonuna gelinene kadar okuma yapılır
            a.kaydiOku(dosya, rrn + 1);
            if (a.okuModel() == arananModel) {//bulundugunda kayit konsola bastirilir
                cout << a;
                cout << rrn + 1 << " numaralı kayıtta " << a.okuIsim() << " bulundu" << "\n";
                sonuc = true;
            } else {
            }
            rrn += 1;
        }
        return sonuc;
    }

    void kayitSil(char* isim) {//kayit silme
        basaSar();
        Araba a;
        int RRN = ismeGoreArama(isim);
        a.kaydiOku(dosya, RRN + 1);
        if (RRN == -1) {//kaydin dosyada bulunup bulunmadigi kontrol edilir
            cout << "kayit zaten dosyada mevcut degil" << "\n";
        } else {//kayit dosyada mevcutsa
            boslarListesi.push_back(RRN); //silinecek kaydin RRN si boslar listesine eklenir
            a.sil(); //silme islemi yapilir
            a.kaydiYaz(dosya, RRN + 1); //silindikten sonra tekrar yazılır
            cout << isim << " kaydı silindi" << "\n";
        }
    }

    void kayitEkle() {//konsolda alinan ozelliklerdeki araba kaydi dosyaya eklenir
        basaSar();
        Araba a;
        cin >> a;
        if (ismeGoreArama(a.okuIsim()) == -1) {
            if (int(boslarListesi.size()) != 0) {
                int rrn = boslarListesi.front();
                cout << a.okuIsim() << " " << rrn + 1 << ". kayda yazılıyor\n";
                basaSar();
                a.kaydiYaz(dosya, rrn + 1);
                boslarListesi.pop_front();

            } else {
                basaSar();
                a.binaryYaz(dosya);
                cout << "boslar listesinde bos yer yok " << a.okuIsim() << " sona ekleniyor\n";

            }

        } else {
            cout << a.okuIsim() << " zaten dosyada mevcut\n";
        }
    }



};

