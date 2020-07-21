/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BirincilIndeks.h
 * Author: serdarm99
 *
 * Created on 16 Nisan 2020 Perşembe, 01:27
 */
#include "IndeksEleman.h"
#include "SiraliDosya.h"
#ifndef BIRINCILINDEKS_H
#define BIRINCILINDEKS_H

using namespace std;

class BirincilIndeks{
public:
    SiraliDosya* sirali;
    list<IndeksEleman*> indeks;
    bool guncelleme;
    
    BirincilIndeks(char* sdAdi){
        guncelleme = false;
        sirali = new SiraliDosya(sdAdi);
        for(int i = 0;i < sirali->bulKayitSayisi();i++)
        {
            Araba *a = sirali->kayitOku(i);
            if(a->okuIsim()[0] != '*'){
                IndeksEleman *ie = new IndeksEleman(a->okuIsim(),i);
                indeks.push_back(ie);
            }
        }
        indeks.sort([](IndeksEleman* sol,IndeksEleman* sag){
            return strcmp(sol->okuIsim(),sag->okuIsim())< 0;
        });
        indeksYaz();
    }
    ~BirincilIndeks(){
        if(guncelleme) indeksYaz();
    }
    
    void indeksYaz(){
        fstream dosya("indeks.bin",ios::binary|ios::trunc|ios::out);
        list<IndeksEleman*>::const_iterator it;
        it = indeks.begin();
        while(it != indeks.end()){
            (*it)->binaryYazIndeks(dosya);
            it++;
        }
        dosya.close();
    }
    void indeksYazdir(){
        list<IndeksEleman*>::const_iterator it;
        it = indeks.begin();
        while(it != indeks.end()){
            cout << **it;
            it++;
        }
    }
    IndeksEleman* ikiliArama(char* arananIsim){
        list<IndeksEleman*>::const_iterator it;
        list<IndeksEleman*>::const_iterator itO;
        list<IndeksEleman*>::const_iterator itS;
        IndeksEleman* orta;
        it = indeks.begin();
        itS = indeks.end();
        while(it != itS){
            for(int i = 0;i<= indeks.size()/2;i++){
                if(i == indeks.size()/2){
                    itO = it;
                }
                ++it;
            }
            orta = (*it);
            if(strcmp(orta->okuIsim(),arananIsim)>0){
                it = itO;
            }
            else if(strcmp(orta->okuIsim(),arananIsim) == 0){
                cout << *orta;
                return orta;
            }
            else{
                itS = itO;
            }
            
        }
        cout <<"bulunamadi";
        return NULL;
        
        
    }
    int ara(char* arananIsim){
        IndeksEleman* ie = ikiliArama(arananIsim);
        if(ie != NULL){
            sirali->kayitOku(ie->okuRRN());
        }
        else cout<<"bulunamadi";
    }
};



#endif /* BIRINCILINDEKS_H */

