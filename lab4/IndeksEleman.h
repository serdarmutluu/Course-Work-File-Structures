/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IndeksEleman.h
 * Author: serdarm99
 *
 * Created on 15 Nisan 2020 Çarşamba, 17:04
 */

#ifndef INDEKSELEMAN_H
#define INDEKSELEMAN_H
#include "genel.h"

using namespace std;

class IndeksEleman{
public:
    friend ostream& operator<<(ostream& o, IndeksEleman& ie){
        o << ie.RRN <<" "; 
        o << ie.isim << "\n";
        o.flush();
        return o;
    }
    IndeksEleman(){
        
    }
    IndeksEleman(char* isim,int r){
        strcpy(this->isim,isim);
        RRN = r;
    }
    
    
    void binaryOkuIndeks(fstream& dosya){
        dosya.read(isim,sizeof(isim));
        dosya.read(reinterpret_cast<char*>(&RRN), sizeof(int));
    }
    void binaryYazIndeks(fstream& dosya){
        dosya.write(isim,sizeof(isim));
        dosya.write(reinterpret_cast<const char*>(&RRN), sizeof(int));
    }
    char* okuIsim(){
        return isim;
    }
    int okuRRN(){
        return RRN;
    }
    
private:
    char isim[50];
    int RRN;
};


#endif /* INDEKSELEMAN_H */

