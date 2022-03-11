#include "envio.h"


void EnviarCaracter (interface_t *interfaz, unsigned char datos, unsigned char *mac_destino, char *tipo){
    //ReservarMemoriaDatos;
    unsigned char *caracter = new unsigned char;
    unsigned char *protocolo = new unsigned char;
    unsigned char *trama = new unsigned char;
    //AlmacenarDatos;
    *caracter = datos;
    *protocolo = *tipo;
   // mostrarInterfaz(interfaz);
    //ConstruirTrama;
    trama = BuildFrame(interfaz->MACaddr, mac_destino, protocolo, caracter); //devuelve un char, guardar
    //EnviarTrama;
    SendFrame(interfaz, trama, sizeof(char)); // envia la trama creada antes
    //LiberarMemoriaDatos;
    delete caracter;
    delete protocolo;
    delete trama;
  }
