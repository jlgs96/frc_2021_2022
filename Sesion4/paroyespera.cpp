#include "paroyespera.h"

bool enviarTramaControl(interface_t *interfaz, unsigned char *mac_destino, char tipo[],char direccion, char control,char ntrama){
    unsigned char *protocolo = reinterpret_cast<unsigned char*>(tipo);
    unsigned char *trama = new unsigned char;
    unsigned char datos[3] = {direccion,control,ntrama};
    trama = BuildFrame(interfaz->MACaddr, mac_destino, protocolo, datos);
    SendFrame(interfaz,trama,3);
    delete trama;
    printf("E ");
    printf("%c ",direccion);
    switch (control)
    {
    case 4:
        printf("EOT ");
        break;
    case 5:
        printf("ENQ ");
        break;
    case 6:
        printf("ACK ");
        break;
    case 21:
        printf("NACK");
        break;
    }
    printf("%c\n",ntrama);

    return true;
}

bool recibirTramaControl(interface_t *interfaz,char direccion, char control, char ntrama){
    const unsigned char* datos;
    bool correcta = false;
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
        if((trama.header.len - 14)==3){
            if(datos[14]==direccion && datos[15]==control && datos[16]==ntrama){
                printf("R ");
                printf("%c ",direccion);
                switch (control)
                {
                case 4:
                    printf("EOT ");
                    break;
                case 5:
                    printf("ENQ ");
                    break;
                case 6:
                    printf("ACK ");
                    break;
                case 21:
                    printf("NACK");
                    break;
                }
                printf("%c\n",ntrama);
                correcta = true;
            }
        }
    }

    return correcta;
}

int calcularBCE(char datos[], int longitud){
    int bce = 0;
    for (int i = 0; i < longitud-1; i++)
    {
        bce = datos[i]^datos[i+1];
    }
    return bce;
}

bool enviarTramaDatos(interface_t *interfaz, unsigned char *mac_destino, char tipo[], unsigned char *datos,int longitud, char direccion, char control, char ntrama, int bce){
    unsigned char *protocolo = reinterpret_cast<unsigned char*>(tipo);
    unsigned char *trama = new unsigned char;
    trama = BuildFrame(interfaz->MACaddr, mac_destino, protocolo, datos);
    SendFrame(interfaz,trama,longitud);
    delete trama;
    printf("E ");
    printf("%c ",direccion);
    if(control == 2)
        printf("STX");
    printf("%c",ntrama);
    printf("%d\n",bce);

    return true;
}