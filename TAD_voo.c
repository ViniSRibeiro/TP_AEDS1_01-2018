#include <stdio.h>
#include <stdlib.h>
#include "TAD_voo.h"

void setVID(TipoVoo* Voo, int VID){
    Voo->VID = VID;
}

int getVID(TipoVoo *voo){
    return voo->VID;
}

void Inicializa (TipoVoo* Voo, int VID, int IDpista, HoraVoo Horadecolagem, HoraVoo Horapouso, char Aeroportodecolagem, char Aeroportopouso){

    Voo-> VID = VID;
    Voo-> IDpista = IDpista;
    Voo-> Horadecolagem = Horadecolagem;
    Voo-> Horapouso = Horapouso;
    Voo-> Aeroportodecolagem = Aeroportodecolagem;
    Voo-> Aeroportopouso = Aeroportopouso;

}

void get_TipoVoo (TipoVoo* Voo, int VID, int IDpista, HoraVoo Horadecolagem, HoraVoo HoraPouso, char Aeroportodecolagem, char Aeroportopouso){

printf("%d\n", Voo->VID);
printf("%d\n", Voo->IDpista);
printf("%d\n", Voo->Horadecolagem);
printf("%d\n", Voo->Horapouso);
printf("%c\n", Voo->Aeroportodecolagem);
printf("%c\n", Voo->Aeroportopouso);
}

void set_TipoVoo (TipoVoo* Voo, int IDpista, HoraVoo Horadecolagem, HoraVoo HoraPouso, char Aeroportodecolagem, char Aeroportopouso, int *PVID){

    setVID(Voo-> *PVID);
    Voo-> IDpista = rand()%5;

}
