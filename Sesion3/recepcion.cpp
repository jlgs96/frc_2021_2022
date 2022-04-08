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

char *RecibirCadena (interface_t *interfaz){
    const unsigned char* cadena;
    char *recibido;
    //Trama=RecibirTrama;
    apacket_t trama = ReceiveFrame(interfaz);
    cadena = trama.packet;
    //Si (hay algo en el campo datos)
    
    if(cadena == NULL)
    {
        //printf("Error, No recibe carácter");
        return 0;
    }else
    {
        for (int i = 0; i < (int)cadena[13]; i++)
        {
            *recibido = cadena[14+i];
        }
        cout << recibido << endl;
        
        
        return recibido;
    }
}