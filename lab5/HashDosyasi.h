/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashDosyasi.h
 * Author: serdarm99
 *
 * Created on 05 Mayıs 2020 Salı, 20:14
 */

#ifndef HASHDOSYASI_H
#include "genel.h"

#include "Kova.h"
#include "SiraliDosya.h"
#define EV_ADRESI_SAYISI 23
#define HASHDOSYASI_H

class HashDosyasi{
public:
    HashDosyasi(char* dosyaAdi){
        kayitSayisi = 0;
        Kova* k = new Kova();
        hashDosyasi.open("hashArabalar.bin",ios::binary | ios::in | ios::out | ios::trunc);
        for(int i = 0 ;i< EV_ADRESI_SAYISI;i++){
            k->binaryYazKova(hashDosyasi,i);
        }
        SiraliDosya* sd = new SiraliDosya(dosyaAdi);
        Araba *a;
        char* aisim;
        for(int j = 0;(a=sd->kayitOku(j)) != NULL;j++){
            aisim = a->okuIsim();
            if(aisim[0] == '*')
                hashEkle(a);
        }
        sd->~SiraliDosya();
    }
    int hashEvAdresi(char* isim){
        int hashDeger = 0;
        for(int i = 0 ;i<strlen(isim);i++){
            hashDeger = hashDeger * 17 + isim[i];
        }
        int evAdresi = hashDeger % EV_ADRESI_SAYISI;
        if(evAdresi<0){
            return evAdresi + EV_ADRESI_SAYISI;
        }
        else{
            return evAdresi;
        }
    }
    int hashArtim(char* isim){
         int hashDeger = 0;
        for(int i = 0 ;i<strlen(isim);i++){
            hashDeger = 17 * hashDeger + isim[i];
        }
        int artim = (hashDeger/EV_ADRESI_SAYISI) % EV_ADRESI_SAYISI;
        if(artim<0){
            return artim + EV_ADRESI_SAYISI;
        }
        else{
            return artim;
        }
    }
    void basaSar(){
        hashDosyasi.clear();
        hashDosyasi.flush();
    }
    void hashYazdir(){
        basaSar();
        Kova* k = new Kova;
        for(int i = 0;i<EV_ADRESI_SAYISI;i++){
            k->binaryOkuKova(hashDosyasi,i);
            cout << *k;
        }
        basaSar();
    }
    void hashEkle(Araba* a){
        Kova gecici;
        if(kayitSayisi == (gecici.kovaSayisi()*EV_ADRESI_SAYISI)){
            cout << "Tablo dolu"<<endl;
        }
        if(a == NULL){
            cin >> (*a);
        }
        int evAdresi = hashEvAdresi(a->okuIsim());
        int artim = hashArtim(a->okuIsim());
        Araba* eleman;
        Kova* k = new Kova();
        int i;
        basaSar();
        while(true){
            k->binaryOkuKova(hashDosyasi,evAdresi);
            for(int i = 0;i<k->kovaSayisi();i++){
                eleman = k->okuEleman(i);
                if(strcmp(eleman->okuIsim(),a->okuIsim()) == 0){
                    cout << "eleman zaten mevcut"<< endl;
                    return;
                }
                if(strcmp(eleman->okuIsim(),"") == 0 || eleman->okuIsim()[0] == '*'){
                    k->yazEleman(i,a);
                    k->binaryYazKova(hashDosyasi,k->okuAdres());
                    kayitSayisi++;
                    cout << (*a) << "eklendi" <<endl<<"ev adresi"<<evAdresi<<endl<<"artim"<< artim<<endl<<"adres"<< evAdresi;
                    basaSar();
                    return;
                }
            }
            evAdresi = (evAdresi + artim) % EV_ADRESI_SAYISI;
        }
    }
    
    Kova* hashArama(char* isim){
        basaSar();
        int evAdresi = hashEvAdresi(isim);
        int artim = hashArtim(isim);
        int adim = 0;
        Kova* k = new Kova();
        k->binaryOkuKova(hashDosyasi,evAdresi);
        adim++;
        for(int i = 0; i<k->kovaSayisi();i++){
            if(strcmp(k->okuEleman(i)->okuIsim(),isim) == 0){
                cout << k->okuAdres() <<"te"<< i <<"nci sırada bulundu"<<adim<<"adimda bulundu"<<endl;
                basaSar();
                return k;
            }
        }
        int aranan2 = (evAdresi + artim) % EV_ADRESI_SAYISI;
        k->binaryOkuKova(hashDosyasi,aranan2);
        adim++;
        for(int i = 0; i<k->kovaSayisi();i++){
            if(strcmp(k->okuEleman(i)->okuIsim(),isim) == 0){
                cout << k->okuAdres() <<"te"<< i <<"nci sırada bulundu"<< adim <<"adimda bulundu"<<endl;
                basaSar();
                return k;
            }
        }
        for(int i = evAdresi + 1;i<EV_ADRESI_SAYISI;i++){
            k->binaryOkuKova(hashDosyasi,i);
            adim++;
            for(int j = 0; j<k->kovaSayisi();j++){
            if(strcmp(k->okuEleman(j)->okuIsim(),isim) == 0){
                cout << k->okuAdres() <<"te"<< j <<"nci sırada bulundu"<<adim<<"adimda bulundu"<<endl;
                basaSar();
                return k;
                }
            }
        }
        basaSar();
        cout <<"eleman bulunamadi"<<endl;
        return NULL;
        
    }
    
    void hashSil(char* isim){
        Kova* silinecek = hashArama(isim);
        Araba* a;
        if(silinecek != NULL){
            for(int i = 0;i<silinecek->kovaSayisi();i++){
                if(strcmp(silinecek->okuEleman(i)->okuIsim(),isim) == 0){
                    a = silinecek->okuEleman(i);
                    a->sil();
                    silinecek->yazEleman(i,a);
                }
            }
        }
        else
            cout <<"kayit zaten mevcut değil" <<endl;
        
    }
    
    
    void yogunlasmaFaktoruHesapla(){
        Kova* k = new Kova();
        int yF = (kayitSayisi / (k->kovaBoyutu()*EV_ADRESI_SAYISI))* 100;
        cout << yF;
    }
    
    fstream hashDosyasi;
    int kayitSayisi;
};

#endif /* HASHDOSYASI_H */

