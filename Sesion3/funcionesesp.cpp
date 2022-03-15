#include "funcionesesp.h"
void f1EnvioCaracteres(char character, interface_t *iface, unsigned char *mac_dst,char *type)
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