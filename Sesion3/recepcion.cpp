#include "recepcion.h"

char RecibirCaracter (interface_t *interfaz){
    const unsigned char* caracter;
    char recibido;
    //Trama=RecibirTrama;
    apacket_t trama = ReceiveFrame(interfaz);
    caracter = trama.packet;
    //Si (hay algo en el campo datos)
    
    if(!caracter)
    {
        //printf("Error, No recibe carácter");
        return 0;
    }else
    {
        recibido = caracter[14];
        
        return recibido;
    }
}

char *RecibirCadena (interface_t *interfaz){
    const unsigned char* datos;
    char recibido;
    char cadena[254];
    char *pCadena;
    //Trama=RecibirTrama;
    apacket_t trama = ReceiveFrame(interfaz);
    datos = trama.packet;
    
    //Si (hay algo en el campo datos)
    if(!datos)
    {
        //printf("Error, No recibe cadena");
        return 0;
    }else
    {
        for(int i= 0; i < (trama.header.len - 14); i++){
            cadena[i] = datos[14+i];
        }
    }
    pCadena = cadena;
    return pCadena;
}