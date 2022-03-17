#include "funcionesesp.h"
void f1EnvioCaracteres(char character, interface_t *iface, unsigned char *mac_dst,char type[])
{
    while (character != 27)
    {
         //SI SE HA PULSADO TECLA: ENVIAMOS EL CARACTER
        if(kbhit()==1)
        {
            character = getch();
            EnviarCaracter(iface,character,mac_dst,type); 
        }else
        //SI NO, RECIBIMOS EL CARÁCTER
        {
            character = RecibirCaracter(iface);
           if(character != 0)
                printf("\n Recibido: %c",character);
        }     
    }
   
}

unsigned char *ObtenerDirOrigen(const unsigned char *trama){
    unsigned char Arrdest[6];
    for (int i = 0; i < 6; i++)
    {
        Arrdest[i] = trama[6+i];
    }

    unsigned char *dest = Arrdest;
    return dest;
}

unsigned char * establecerConexionME(interface_t *interfaz, char tipo[], int rol){
    apacket_t frame;
    const unsigned char* trama;
    unsigned char *trama2 = new unsigned char;
    unsigned char *destino;
    if(rol == 1){
        EnviarBroadCast(interfaz,tipo);
        while(1){
            frame = ReceiveFrame(interfaz);
            trama = frame.packet;
            if(trama != 0){
                if(trama[12] == tipo[0] && trama[13] == 0x02){
                    destino = ObtenerDirOrigen(trama);
                    break;
                }
            }
        }  
    }else{
        while(1){
            frame = ReceiveFrame(interfaz);
            trama = frame.packet;
            if(trama != 0){
                if(trama[12] == tipo[0] && trama[13] == 0x01){
                    destino = ObtenerDirOrigen(trama);
                    tipo[1] = 0x02;
                    unsigned char *protocolo = reinterpret_cast<unsigned char*>(tipo);
                    trama2 = BuildHeader(interfaz->MACaddr,destino,protocolo);
                    SendFrame(interfaz,trama2,sizeof(char));
                    break;
                }
            }
        }
    }
    delete trama2;
    return destino;
}

