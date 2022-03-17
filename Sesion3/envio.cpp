#include "envio.h"


void EnviarCaracter (interface_t *interfaz, unsigned char datos, unsigned char *mac_destino, char tipo[]){
    //ReservarMemoriaDatos;
    unsigned char *caracter = new unsigned char;
    unsigned char *trama = new unsigned char;
    //AlmacenarDatos;
    *caracter = datos;
    unsigned char *protocolo = reinterpret_cast<unsigned char*>(tipo);
   // mostrarInterfaz(interfaz);
    //ConstruirTrama;
    trama = BuildFrame(interfaz->MACaddr, mac_destino, protocolo, caracter); //devuelve un char, guardar
    //EnviarTrama;
    SendFrame(interfaz, trama, sizeof(char)); // envia la trama creada antes
    //LiberarMemoriaDatos;
    delete caracter;
    delete trama;
  }

void EnviarBroadCast(interface_t *interfaz,char tipo[]){
  unsigned char mac_dst[6]={0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF}; //Dirección para broadcast
  //ReservarMemoria
  unsigned char *trama = new unsigned char;

  //Asignamos el tipo de trama(0x01) al protocolo
  tipo[1] = 0x01;
  unsigned char *protocolo = reinterpret_cast<unsigned char*>(tipo);
  //ConstruirTrama
  trama = BuildHeader(interfaz->MACaddr, mac_dst, protocolo); //devuelve un char, guardar
  SendFrame(interfaz, trama, sizeof(char)); // envia la trama creada antes
  
  delete trama;
}