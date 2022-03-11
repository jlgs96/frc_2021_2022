#include "recepcion.h"

char RecibirCaracter (interface_t *interfaz){
    const unsigned char* caracter;
    char recibido;
    //Trama=RecibirTrama;
    apacket_t trama = ReceiveFrame(interfaz);
    caracter = trama.packet;
    //Si (hay algo en el campo datos)
    
    if(caracter == NULL)
    {
        //printf("Error, No recibe carácter");
        return 0;
    }else
    {
        recibido = caracter[14];
        
        return recibido;
    }
}