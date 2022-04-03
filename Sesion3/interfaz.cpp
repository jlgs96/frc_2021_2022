#include "interfaz.h"
#include "funcionesesp.h"
void mostrarInterfacesDisponibles(pcap_if_t *interfaces_disponibles)
{
    int index = 0;
    while (interfaces_disponibles != NULL)
    {
    cout<< "["<< index << "] ";
    printf(interfaces_disponibles->name);
    printf("\n" );
    index++;
    interfaces_disponibles = interfaces_disponibles->next;
    }

}
int pedirInterfaz()
{
    int interfaz;
    printf("Seleccione interfaz : ");
    cin >> interfaz;
    return interfaz;
}



void seleccionInterfaz(pcap_if_t *interfaces_disponibles, interface_t *interfaz)
{
    int index = 0;
    int ielegida = pedirInterfaz();
    while (interfaces_disponibles != NULL)
    {
        if (ielegida == index)
        {
            printf("Interfaz elegida: ");
            printf(interfaces_disponibles->name);
            printf("\n");
            setDeviceName(interfaz, interfaces_disponibles->name);
            GetMACAdapter(interfaz);
            mostrarInterfaz(interfaz);

            break;
        }else
            interfaces_disponibles = interfaces_disponibles->next;
            index++;
        
    }
}

void mostrarInterfaz(interface_t *interfaz){
   // printf("\nLa dirección MAC es: \n");
    PrintMACAdapter(interfaz);
}

char elegirGrupo(){
    int codGrupo = 48;
    char grupo;
    int nGrupo = 0;
    while( 0 >= nGrupo || nGrupo > 10){
        printf("Introduzca el número de grupo: \n");
        cin >> nGrupo;
    }
    grupo = codGrupo + nGrupo;
    return grupo;
}

int seleccionarRol(){
    int rol = 0;
    while (rol != 1 && rol != 2)
    {
        printf("\nSelecciona el modo de la estación: ");
        printf("\n[1] Modo Maestra");
        printf("\n[2] Modo Esclava\n");
        cin >> rol;            
    }
    if(rol == 1)
    {
        printf("Esperando a que se una la estacion esclava\n");
    }else{
        if(rol == 2)
        {
        printf("Esperando a que se una la estacion maestra\n");
        }
    }
    return rol;
}

void seleccionModo(int rol, char caracter, interface_t *iface, unsigned char *destino, char type[2])
{
    bool salir = false;
    char modo = 'ª';
    char aux;
    aux = getch();
    while(!salir)
    {
        printf("\n Selección de modo:");
        //PARTE MAESTRO:
        if(rol == 1)
        {
            printf("\n[F1]- Envío de caracteres interactivo");
            printf("\n[F2] - Envío de un fichero");
            printf("\n[ESC] - Salir\n");
            modo = getch();
            if(modo == 27)
            {
                if(kbhit()==1){
                    modo = getch();
                    if(modo == 'O')
                    {
                    //   printf("-----PASA COMPROBACIÓN DE TECLA ESCAPE-----");
                        modo = getch();
                        ejecutarFunciones(rol,iface,destino,type,modo);
                        //modo = getch();
                    }
                }else{
                    //printf("----------SALIMOS EQUIPO--------------");
                    salir = true;
                } 
            }
        
            
        }else
        {
            //PARTE ESCLAVO:
            if(rol == 2)
            {
                printf("\n[F1] - Envío de caracteres interactivo");
                printf("\n[ESC] - Salir\n");
                
                modo = getch();
                if(modo == 27)
                {
                // printf("-----PASA COMPROBACIÓN DE TECLA ESPECIAL-----");
                    if(kbhit()==1){
                        modo = getch();
                        if(modo == 'O')
                        {
                        //   printf("-----PASA COMPROBACIÓN DE TECLA ESCAPE-----");
                            modo = getch();
                            
                            ejecutarFunciones(rol,iface,destino,type,modo);
                            //modo = getch();
                        }
                    }else{
                        //printf("----------SALIMOS EQUIPO--------------");
                        salir = true;
                    }  
                }
                
            }
        }
    }
    
}
