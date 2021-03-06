#include "funcionesesp.h"

void f1EnvioCaracteres(interface_t *iface, unsigned char *mac_dst,char type[])
{
    char character = 'A';
    
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

void f2EnvioFichero(interface_t *iface, unsigned char *mac_dst,char type[]){
    char cadena[255];
    bool fin = false;
    ifstream fichero_lec("envio.txt");
    if(fichero_lec.is_open()){
        while(!fin){
            fichero_lec.read(cadena, 254);
            cadena[fichero_lec.gcount()] = '\0';
            if(fichero_lec.gcount() == 0){
                fin = true;
            } else{
                unsigned char *datos = reinterpret_cast<unsigned char*>(cadena);
                EnviarCadena(iface,datos,mac_dst,type,fichero_lec.gcount());
            }
        }
        fichero_lec.close();
    }
}

void f3ParoEspera(int rol, interface_t *iface, unsigned char *mac_dst, char type[])
{
    bool salirMaestro = false;
    bool salirEsclavo = false;
    char aux = 'A';
   
    if(rol == 1)
    {
        printf("\nProtocolo paro y espera. Para salir pulse ESC.");
        printf("\nSeleccione el tipo de operación:");
        printf("\n[1] Operación selección.");
        printf("\n[2] Operación sondeo.");
        printf("\n[3] Salir.");

        while (!salirMaestro)
        {
            if (kbhit() == 1)
            {   
                aux = getch();
                if(aux == 27)
                {
                    salirMaestro = true;
                }else
                {         
                    switch (aux)
                    {
                        case '1': 
                        {
                            printf("\nSelección...\n");
                            /***
                             * FASE DE ESTABLECIMIENTO 
                             * Montar trama de control
                             * Enviar trama de control (Petición)
                             * Recibir trama de control (Rspuesta)
                             * Psar a fase de transferencia
                             */
                            enviarTramaControl(iface, mac_dst, type,'R', 5,'0');
                            while(true){
                                if(!recibirTramaControl(iface,'R', 6,'0')){
                                    continue;
                                }
                                else {
                                    printf("Pasamos a la fase de Transferencia\n");
                                    break;
                                }
                            }
                            char cadena[255];
                            bool fin = false;
                            int longitud, bce;
                            ifstream fichero_lec("EProtoc.txt");
                            if(fichero_lec.is_open()){
                                while(!fin){
                                    fichero_lec.read(cadena, 254);
                                    longitud = fichero_lec.gcount();
                                    cadena[longitud] = '\0';
                                    if(longitud == 0){
                                        fin = true;
                                    } else{
                                        bce = calcularBCE(cadena,longitud);
                                        char control[4] = {'R',2,'0',(char)longitud};
                                        char datos[4+longitud+1];
                                        char cbce[1] = {(char)bce};

                                        for(int i = 0; i<4;i++){
                                            datos[i]=control[i];
                                        }
                                        for (int i = 0; i < longitud; i++)
                                        {
                                            datos[i+4] = cadena[i];
                                        }
                                        datos[4+longitud-1] = cbce[0];
                                        unsigned char *datosT = reinterpret_cast<unsigned char*>(datos);
                                        enviarTramaDatos(iface, mac_dst, type, datosT,strlen(datos),'R',2,'0',bce);
                                    }
                                }
                                fichero_lec.close();
                            }
                            /***
                             * FASE DE TRANSFERENCIA 
                             * Calcular BCE a enviar
                             * Montar trama de datos
                             * Enviar trama de datos
                             * Recibir trama de control (Rspuesta)
                             *      -> Reenviar trama de datos
                             * ...
                             * Pasar a fase de liberación
                             */

                            /***
                             * FASE DE LIBERACIÓN
                             * Enviar trama de control (Petición)
                             * Recibir trama de control (Rspuesta)
                             * Cerrar
                             */
                        }
                            break;
                        case '2':
                            printf("\nSondeo...");
                            break;
                        case '3':
                            printf("\nSaliendo...");
                            salirMaestro = true;
                            break;
                        default:
                            break;
                    }
                }
            }    
        }
    
                            
    }else
    {
        if(rol == 2)
        {
            printf("\nProtocolo paro y espera. Para salir pulse ESC.");
            printf("\nEstás en modo esclavo\n");
            while (!salirEsclavo)
            {
                if(kbhit() == 1)
                {
                    aux = getch();
                    if(aux == 27)
                    {
                        salirEsclavo = true;
                    }
                }else
                    {
                        if(recibirTramaControl(iface,'R', 5,'0')){
                            enviarTramaControl(iface, mac_dst, type,'R', 6,'0');
                        }
                    }   
            } 
        }
    }

    
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

void ejecutarFunciones(int rol, interface_t *iface, unsigned char *mac_dst,char type[], char modo){ 
        switch (modo)
        {
            case 'P':
                printf("F1\n");
                f1EnvioCaracteres(iface, mac_dst, type);
                break;
            case 'Q':
                printf("F2\n");
                f2EnvioFichero(iface,mac_dst,type);
                break;
            case 'R':
                printf("F3\n");
                f3ParoEspera(rol,iface,mac_dst,type);
                break;
            default:
                break;
        }
    //salir = true;           
    
}
