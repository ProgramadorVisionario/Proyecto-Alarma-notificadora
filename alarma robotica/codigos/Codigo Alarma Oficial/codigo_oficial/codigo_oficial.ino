

#include <SoftwareSerial.h>

#include <RTClib.h>
#include <Arduino.h>
#include <TM1637Display.h>
#include <DFRobotDFPlayerMini.h> //librería mp3
#include <Wire.h>

//para evitar ruido de un hercio
DFRobotDFPlayerMini myDFPlayer = DFRobotDFPlayerMini();
SoftwareSerial mySoftwareSerial = SoftwareSerial(10, 11);



void Presentarse();
void Gestion_horario();
void reiniciar();

/*
Código de alarma electrónica automatizada

Programación iniciada el 6/6/2018 a las 20:08 Guayaquil-Ecuador

Se usarán 4 clases
-Reloj listo
-Display listo
-
-Alarma
*/
class Reloj
{ //las clases que no heredan ni usan otras clases debes escribirse primero (scope)
    private:
    RTC_DS1307 rtc;
    DateTime now = rtc.now(); 
    public:   
      enum Dias_semana {lunes = 1,martes,miercoles,jueves,viernes,sabado,domingo};

      Dias_semana dia;
      //CONSTRUCTOR DE LA CLASE Reloj
      Reloj()
      {
            Serial.begin(9600);
            Wire.begin();
            rtc.begin();
      }
      //PROTOTIPO DE MÉTODOS
      int Obtener_mes();
      int Obtener_dia_semana();
      int Obtener_dia();
      int Obtener_hora();
      int Obtener_minuto();
      int Obtener_segundo();
      void Imprimir_hora_serial();
      void Corregir_hora_segun_pc();
};
void Reloj::Corregir_hora_segun_pc()
{
    RTC_DS1307 rtc;
    DateTime now = rtc.now();

  char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  rtc.begin();
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    rtc.adjust(DateTime(2018, 7, 12, 21, 10, 0));
  }

}
int Reloj::Obtener_mes()
{
  return now.month();
}

int Reloj::Obtener_dia_semana() //1 = lunes , 
{
   return now.dayOfTheWeek();
}

int Reloj::Obtener_dia()
{
  return now.day();
}
int Reloj::Obtener_hora()
{
  return now.hour();
}
int Reloj::Obtener_minuto()
{
  /*

  0 1 2 3 4 5 6 7 8 9 10 .... 56 57 58 59 0
  RETRASAR 6 MINUTOS
  */
  /**if(now.minute() >= 6)
    {return ((now.minute())-6);}
  else
  {
     return ((59+now.minute())-6);
  }**/

  return now.minute();
}
int Reloj::Obtener_segundo()
{
  return now.second();
}
void Reloj::Imprimir_hora_serial()
{     
        int ano = now.year();
        int mes = now.month();
        int dia = now.day();
        int hora = now.hour();
        int minuto = now.minute();
        int segundo = now.second();
        //obtengo el primer mapeo por que será erróneo pero no los siguientes
        
        Serial.print(now.dayOfTheWeek());
        Serial.println(); 
        Serial.print(ano, DEC); // Año
        Serial.print('/');
        Serial.print(mes, DEC); // Mes
        Serial.print('/');
        Serial.print(dia, DEC); //Dia 
        Serial.print(' ');
        Serial.print(hora, DEC); // Horas
        Serial.print(':');
        Serial.print(minuto, DEC); // Minutos
        Serial.print(':');
        Serial.print(segundo, DEC); // Segundos
        Serial.println(); delay(1000); // La información se actualiza cada 1 seg.
}
//------------------------------------------------------------------------

class Alarma
{
    private:
          //VARIABLES RELACIONADAS A LOS PINES
          const int pin_led_rojo = 9;
          const int intervalo = 0;
          //DFRobotDFPlayerMini myDFPlayer = DFRobotDFPlayerMini();
          //SoftwareSerial mySoftwareSerial = SoftwareSerial(10, 11);// nuevo RX nuevo TX pero el TX mp3 va en
                                                  // RX nuevo arduino y el RX mp3 va 
                                                  // en TX nuevo arduino
          /*
          
          Not all pins on the Mega and Mega 2560 support change interrupts,
          so only the following can be used for RX: 10, 11, 12, 13, 14, 15, 
          50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66),
          A13 (67), A14 (68), A15 (69). 
          
          */

          
    public:   
      //CONSTRUCTOR DE LA CLASE Reloj
      Alarma()
      {
          //INICIALIZACIÓN DE LOS PINES   
          pinMode(pin_led_rojo,OUTPUT);
          //mySoftwareSerial.begin(9600);
          //myDFPlayer.begin(mySoftwareSerial);
          //myDFPlayer.volume(30);  //Set volume value. From 0 to 30
          
      }
      //PROTOTIPO DE MÉTODOS
      void Prender_led();
      void Apagar_led();
      void Tocar_cambio();
      void Tocar_Inicio_del_dia();
      void Tocar_5_culminara_la_clase();
      void Tocar_5_para_receso();
      void Tocar_cesara_jornada();
      void Tocar_presentacion();
     
    
};

void Alarma::Prender_led()
{
  digitalWrite(pin_led_rojo,HIGH);
}
void Alarma::Apagar_led()
{
  digitalWrite(pin_led_rojo,LOW);
}
void Alarma::Tocar_cambio()
{
  myDFPlayer.play(1);  //Play the first mp3
  delay(1000);
}
void Alarma::Tocar_Inicio_del_dia()
{
  myDFPlayer.play(2);  
  delay(6000);
}
void Alarma::Tocar_5_culminara_la_clase()
{
  myDFPlayer.play(3);
  delay(7000);
}
void Alarma::Tocar_5_para_receso()
{
  myDFPlayer.play(4);
  delay(8000);
}
void Alarma::Tocar_cesara_jornada()
{
  myDFPlayer.play(5);
  delay(9000);
}
void Alarma::Tocar_presentacion()
{
  myDFPlayer.play(6);
  delay(45000);
}
//------------------------------------------------------------------------
class Display
{
    private:
          
          const int CLK = 2;
          const int DIO = 3;
          TM1637Display display = TM1637Display(CLK, DIO);
          Reloj display_reloj = Reloj();
    public:   
      
      Display()
      {
        
         display.setBrightness(2);
      }
      //PROTOTIPO DE MÉTODOS
      void Imprimir_hora();
    
};
void Display::Imprimir_hora()
{

  //para poner los puntos ":"
   uint8_t segto;
   int value = 1244;
   segto = 0x80 | display.encodeDigit((value / 100)%10);
   display.setSegments(&segto, 1, 1);

   
   int minuto = display_reloj.Obtener_minuto();
   int hora = display_reloj.Obtener_hora();

   display.showNumberDec(minuto,false);
   display.showNumberDec(hora,false,2,0);

   
   
}
//------------------------------------------------------------------------
void Presentarse()
{
   //objetos de mis clases
   Reloj reloj_alarma = Reloj();
   Display display_alarma = Display(); 
   Alarma la_alarma = Alarma();

   //imprimir hora
   display_alarma.Imprimir_hora();

    //presentarse
   la_alarma.Prender_led();
   la_alarma.Tocar_cambio();
   la_alarma.Tocar_presentacion();
   la_alarma.Apagar_led();
   delay(3000);
   //imprimir hora
   display_alarma.Imprimir_hora();
   
   //inicio de clases
   la_alarma.Prender_led();
   la_alarma.Tocar_cambio();
   la_alarma.Tocar_Inicio_del_dia();
   la_alarma.Apagar_led();
   delay(20000);
   //imprimir hora
   display_alarma.Imprimir_hora();

   

   //clase a punto de terminar
   la_alarma.Prender_led();
   la_alarma.Tocar_cambio();
   la_alarma.Tocar_5_culminara_la_clase();
   la_alarma.Apagar_led();
   delay(20000);
   //imprimir hora
   display_alarma.Imprimir_hora();
   
   //recreo 1
   la_alarma.Prender_led();
   la_alarma.Tocar_cambio();
   la_alarma.Tocar_5_para_receso();
   la_alarma.Apagar_led();
   delay(20000);
   //imprimir hora
   display_alarma.Imprimir_hora();

   //clase a punto de terminar
   la_alarma.Prender_led();
   la_alarma.Tocar_cambio();
   la_alarma.Tocar_5_culminara_la_clase();
   la_alarma.Apagar_led();
   delay(20000);
   //imprimir hora
   display_alarma.Imprimir_hora();

   //clase a punto de terminar
   la_alarma.Prender_led();
   la_alarma.Tocar_cambio();
   la_alarma.Tocar_5_culminara_la_clase();
   la_alarma.Apagar_led();
   delay(20000);
   //imprimir hora
   display_alarma.Imprimir_hora();

   //recreo 1
   la_alarma.Prender_led();
   la_alarma.Tocar_cambio();
   la_alarma.Tocar_5_para_receso();
   la_alarma.Apagar_led();
   delay(20000);
   //imprimir hora
   display_alarma.Imprimir_hora();

   //clase a punto de terminar
   la_alarma.Prender_led();
   la_alarma.Tocar_cambio();
   la_alarma.Tocar_5_culminara_la_clase();
   la_alarma.Apagar_led();
   delay(20000);
   //imprimir hora
   display_alarma.Imprimir_hora();

   //salida
   la_alarma.Prender_led();
   la_alarma.Tocar_cambio();
   la_alarma.Tocar_cesara_jornada();
   la_alarma.Apagar_led();
   delay(20000);
   //imprimir hora
   display_alarma.Imprimir_hora();

   

}

 

         
void Gestion_horario()
{ 
      //objetos de mis clases instanciar
Reloj reloj_alarma =Reloj();
Display display_alarma = Display(); 
Alarma la_alarma = Alarma();  
      
         //imprimir hora
         display_alarma.Imprimir_hora();
      
         //decidir si es inicio de clase (a las 7:45 AM)
         bool hora_inicio_clases = ((int)reloj_alarma.Obtener_hora() == 7) && ((int)reloj_alarma.Obtener_minuto() == 45)&&  
         ((int)reloj_alarma.Obtener_segundo() < 2) &&((int)reloj_alarma.Obtener_dia_semana() <=5);

         //decidir si es salida (a las 14:30 PM) //5 minutos antes
         bool hora_salida = ((int)reloj_alarma.Obtener_hora() == 14) && 
         ((int)reloj_alarma.Obtener_minuto() == 25) && ((int)reloj_alarma.Obtener_segundo() < 2) 
         &&((int)reloj_alarma.Obtener_dia_semana() <=5);

         //decidir si es recreo (a las 10:00 PM) y (12:30) //5 minutos antes
         bool primer_recreo = ((int)reloj_alarma.Obtener_hora() == 9) && 
         ((int)reloj_alarma.Obtener_segundo() < 2) &&((int)reloj_alarma.Obtener_minuto() == 55);
         
         bool segundo_recreo = ((int)reloj_alarma.Obtener_hora() == 12) && 
         ((int)reloj_alarma.Obtener_segundo() < 2) &&((int)reloj_alarma.Obtener_minuto() == 25);

         //decidir si es clases  //5 minutos antes
         //termina a las 8:30
         bool hora1 = ((int)reloj_alarma.Obtener_hora() == 8) && ((int)reloj_alarma.Obtener_segundo() < 2) &&((int)reloj_alarma.Obtener_minuto() == 25);
         //termina a las 9:15
         bool hora2 = ((int)reloj_alarma.Obtener_hora() == 9) && ((int)reloj_alarma.Obtener_segundo() < 2) &&((int)reloj_alarma.Obtener_minuto() == 10);
         //termina a las 11:00
         bool hora3 = ((int)reloj_alarma.Obtener_hora() == 10) && ((int)reloj_alarma.Obtener_segundo() < 2) &&((int)reloj_alarma.Obtener_minuto() == 55);
         //termina a las 11:45
         bool hora4 = ((int)reloj_alarma.Obtener_hora() == 11) && ((int)reloj_alarma.Obtener_segundo() < 2) &&((int)reloj_alarma.Obtener_minuto() == 40);
         //termina a las 13:45
         bool hora5 = ((int)reloj_alarma.Obtener_hora() == 13) && ((int)reloj_alarma.Obtener_segundo() < 2) &&((int)reloj_alarma.Obtener_minuto() == 40);
       
         bool entre_semana = ((int)reloj_alarma.Obtener_dia_semana() <=5);
         myDFPlayer.volume(0); 
         if(hora_inicio_clases && entre_semana)
         { 
                 myDFPlayer.volume(30);
                 la_alarma.Prender_led();
                 la_alarma.Tocar_cambio();
                 la_alarma.Tocar_Inicio_del_dia();
                 la_alarma.Apagar_led();
         }
      
         
         if(hora_salida && entre_semana)
         {
                 myDFPlayer.volume(30);
                 la_alarma.Prender_led();
                 la_alarma.Tocar_cambio();
                 la_alarma.Tocar_cesara_jornada();
                 la_alarma.Apagar_led();
         }
      
        
       
         if((primer_recreo ||segundo_recreo ) && entre_semana)
         {
                 myDFPlayer.volume(30);
                 la_alarma.Prender_led();
                 la_alarma.Tocar_cambio();
                 la_alarma.Tocar_5_para_receso();
                 la_alarma.Apagar_led();
         }
      
         
       if((hora1||hora2||hora3||hora4||hora5)  && entre_semana)
       {
         myDFPlayer.volume(30);
         la_alarma.Prender_led();
         la_alarma.Tocar_cambio();
         la_alarma.Tocar_5_culminara_la_clase();
         la_alarma.Apagar_led();
       }
       myDFPlayer.volume(0);
}

void reiniciar()
{
    pinMode(7,OUTPUT);
    digitalWrite(7,HIGH);
    delay(100);  
}


   
void setup() {   
 mySoftwareSerial.begin(9600);
 myDFPlayer.begin(mySoftwareSerial);
 myDFPlayer.volume(30); 

 //objetos de mis clases instanciar
 Reloj reloj_alarma =Reloj();  //los objetos deben instanciarce dentro de una función o un método nunca fuera de estos
 Display display_alarma = Display(); 
 Alarma la_alarma = Alarma();


 //delay(1000);
 
 
 
 la_alarma.Tocar_cambio();

     //la_alarma.Tocar_cambio();
     //la_alarma.Tocar_Inicio_del_dia();
     //la_alarma.Tocar_5_culminara_la_clase();
     //la_alarma.Tocar_5_para_receso();
     //la_alarma.Tocar_cesara_jornada();
     //la_alarma.Tocar_presentacion();
 // no funciona bien //reloj_alarma.Corregir_hora_segun_pc();
  /*RTC_DS1307 rtc;
  DateTime now = rtc.now();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  //rtc.adjust(DateTime(2018, 7, 12, 21, 10, 0));*/
 
}


void loop() {

  Reloj reloj_alarma =Reloj();  //los objetos deben instanciarce dentro de una función o un método nunca fuera de estos
  Display display_alarma = Display(); 
  Alarma la_alarma = Alarma();

   reloj_alarma.Imprimir_hora_serial();
  Presentarse();
  Gestion_horario();
  delay(1000);
  

}
