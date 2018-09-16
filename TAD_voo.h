#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int hora, minuto;
}HoraVoo;

typedef struct{
    int VID,IDpista;
    HoraVoo Horadecolagem, Horapouso;
    char Aeroportodecolagem[30], Aeroportopouso[30];
}TipoVoo;

//Declaraçao de Operacoes
void Inicializa (TipoVoo* Voo, int VID, int IDpista, HoraVoo Horadecolagem, HoraVoo HoraPouso, char Aeroportodecolagem, char Aeroportopouso);
void get_TipoVoo (TipoVoo* Voo, int VID, int IDpista, HoraVoo Horadecolagem, HoraVoo HoraPouso, char Aeroportodecolagem, char Aeroportopouso);
void set_TipoVoo (TipoVoo* Voo, int IDpista, HoraVoo Horadecolagem, HoraVoo HoraPouso, char Aeroportodecolagem, char Aeroportopouso);
void setVID (TipoVoo* Voo, int *PVID);
