#include <16f877a.h>
#include <string.h>
#use delay (clock = 20000000 )
#define LCD_ENABLE_PIN  PIN_B0                        
#define LCD_RS_PIN PIN_B1  
#define LCD_RW_PIN PIN_B2 
#define LCD_DATA4 PIN_B4 
#define LCD_DATA5 PIN_B5 
#define LCD_DATA6 PIN_B6 
#define LCD_DATA7 PIN_B7 
#include <lcd.c>

#FUSES NOWDT, HS, PUT, NOPROTECT

#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)
void _khoi_dong(void);

void main()
{
   lcd_init();
   lcd_putc("ESP READY  ?");
   _khoi_dong();
   //gui ID va mat khau de ket noi
   printf("AT+CWJAP=\"");
    printf("EDN_Corp");
    printf("\",\"");
    printf("Edn2016333");
    printf("\"\r\n");
    //doi ket noi xong.........
    char _nhan_lan_2[];
    int _connercted = 0;
    do
    {
       gets(_nhan_lan_2);
       for (int j = 0; j < 60; ++j)
       {
          unsigned int _so_lan = 1;
          if (_nhan_lan_2[j] == 'O' && _nhan_lan_2[j+1] == 'K')
          {
             _connercted = 1;
             lcd_putc("CONNECTED WIFI");
             break;
          }
          _so_lan = _so_lan++;
          if (_so_lan == 59)
          {
             lcd_putc("FAIL...RECONNECT");
          }
       }
    }
    while(_connercted == 0);
   // Neu da ket noi thanh cong gui lenh lay IP local
   printf("AT+CIFSR\n");
   char _nhan_lan_3[];
   char _ip_nhan_duoc[];
   gets(_nhan_lan_3);
   for (int i = 9; i < 30; ++i)
   {
      _ip_nhan_duoc[i] = _nhan_lan_3[i];
      if (_nhan_lan_3[i] == " ")
      {
         //nhan LCD and thoat ra
         lcd_putc(_ip_nhan_duoc);
         break;
      }
   }


   while(true)
   {
   //_gui_noi_dung();
   //_nhan_noi_dung();
   //_dieu_khien();
   }
}
void _khoi_dong(void)
{
   char string[];
   unsigned int done = 0;
   printf("AT\n");
   for (int i = 0; i < 10; ++i)
   {
      gets(string);
      for (int j = 0; j < 20; ++j)
      {
         if(string[i] == 'O' && string[i+1] == 'K')
         {
            lcd_putc("OK/n");
            done = 1;
            break;
         }
      }
      if (done ==1)
      {
         break;
      }
   }
}
