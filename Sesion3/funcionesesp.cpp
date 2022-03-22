#include "funcionesesp.h"
bool f1EnvioCaracteres(char character, interface_t *iface, unsigned char *mac_dst,char type[])
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
    return true;
   
}
unsigned char * establecerConexionME(interface_t *interfaz, char tipo[], int rol)
{
    apacket_t frame;
    const unsigned char* trama;
    unsigned char *trama2;
    unsigned char destino[6];
    unsigned char *pDestino;
    //VARIABLE DE FIN DE BUCLE
    bool descubrimiento = false;
    if(rol == 1)
    {
        EnviarBroadCast(interfaz,tipo);
        while(!descubrimiento)
        {
            //RECEPCION DE LA TRAMA
            frame = ReceiveFrame(interfaz);
            //RECEPCIÓN DEL CAMPO DATOS DE LA TRAMA 
            trama = frame.packet;

            if(trama != NULL)
            {
                for (int i =0; i < 6; i++)
                {
                    destino[i] = trama[6 + i];
                }
            
                //destino = ObtenerDirOrigen(trama);
                if(trama[12] == tipo[0] && trama[13] == 0x02)
                {
                    
                    printf("Estación encontrada. La MAC es: ");
                    //MOSTRAMOS LA DIRECCIÓN MAC
                    for (int i = 0; i < 6; i++)
                        {
                            if(i == 5)
                            {
                                cout << hex << (int)destino[i];    
                            }else
                            {
                                cout << hex << (int)destino[i]<<" : ";
                            }
                            
                        }
                    descubrimiento = true;
                }
            }
        }  
    }else
    {
       if(rol == 2)
       {
            while(!descubrimiento)
            {
                //RECEPCION DE LA TRAMA
                frame = ReceiveFrame(interfaz);
                //RECEPCIÓN DEL CAMPO DATOS DE LA TRAMA 
                trama = frame.packet;

                if(trama != NULL)
                {
                    for (int i =0; i < 6; i++)
                    {
                        destino[i] = trama[6 + i];
                    }
                    if(trama[12] == tipo[0] && trama[13] == 0x01)
                    {
                        tipo[1] = 0x02;
                        unsigned char *protocolo = reinterpret_cast<unsigned char*>(tipo);
                        trama2 = BuildHeader(interfaz->MACaddr,destino,protocolo);
                        SendFrame(interfaz,trama2,0);
                        printf("Estación encontrada. La MAC es: ");
                        //MOSTRAMOS LA DIRECCIÓN MAC
                        for (int i = 0; i < 6; i++)
                        {
                            if(i == 5)
                            {
                                cout << hex << (int)destino[i];    
                            }else
                            {
                                cout << hex << (int)destino[i]<<" : ";
                            }
                            
                        }
                        descubrimiento = true;
                        
                    }
                }
            }
       } 
        
    }
    pDestino = destino;
    return pDestino;
}

