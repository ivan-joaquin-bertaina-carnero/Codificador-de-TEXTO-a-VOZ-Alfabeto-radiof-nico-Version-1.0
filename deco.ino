/*
Iván Joaquín Bertaina - Mayo 2019


*/

//Incluímos las librerías necesarias para usar el módulo "DFPlayer Mini"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//Configuramos pines a usar para el puerto serial por software
#define Soft_Rx 10
#define Soft_Tx 11
SoftwareSerial SerialxSoft(Soft_Rx,Soft_Tx); 

//Creamos un objeto del tipo DFRobotDFPlayerMini con el nombre MiniRepMP3
DFRobotDFPlayerMini MiniRepMP3;
//void printDetail(uint8_t type, int value); ->> Usar para mostrar info del modulo.

//Definimos las constantes a usar.
#define STOP 5
#define LED_STANDBY 6
#define LED_READ 7
#define LED_CHECK 8
#define LED_PLAY  9

// Definimos las variables de tiempo a usar.
unsigned long int inicial=0;
unsigned long int actual=0;

int retardo1=1500; //Retardo de Caracteres VÁLIDOS
int retardo2=500; //Retardo de Caracteres NO VÁLIDOS

int estado=0;
int i=0;
int j=0;


char texto[100];

//Realizamos la configuración inicial.
void setup() 
{
  digitalWrite(LED_STANDBY,LOW);
  digitalWrite(LED_READ,LOW);
  digitalWrite(LED_CHECK,LOW);
  digitalWrite(LED_PLAY,LOW);
  pinMode(STOP,INPUT_PULLUP);
  Serial.begin(9600);
  inicial= millis();

  //Inicializamos el Puerto Serial por software e informamos por el Puerto Serie principal.
  SerialxSoft.begin(9600);
  Serial.println("########################################################################\n");
  Serial.println("Codificador de TEXTO a VOZ (Alfabeto radiofónico) Version 1.0\n");
  Serial.println("Desarrollado por Iván Joaquín Bertaina para LabDIEC - Junio 2019\n");
  Serial.println("Bahía Blanca - Buenos Aires - Argentina\n");
  Serial.println("########################################################################\n");
  Serial.println(F("Inicializando modulo MP3 ... (Puede llevar 3~5 segundos)"));
  if (!MiniRepMP3.begin(SerialxSoft))
    {
      Serial.println(F("No se puede iniciar:"));
      Serial.println(F("1. Revisar conexiones!"));
      Serial.println(F("2. Insertar tarjeta SD!"));
      while(true);
    }
  Serial.println(F("DFPlayer Mini conectado."));

  //Configuramos el Módulo DFPlayer Mini
  MiniRepMP3.setTimeOut(500); //Tiempo máximo de espera en la comunicación serial 500ms
  MiniRepMP3.volume(30); //Volumen inicial (0~30).
  MiniRepMP3.EQ(DFPLAYER_EQ_NORMAL); //Seleccionamos equalizador.
  MiniRepMP3.outputDevice(DFPLAYER_DEVICE_SD); //Seleccionamos tarjeta microSD.
  MiniRepMP3.enableDAC();
  MiniRepMP3.outputSetting(true, 15);
  Serial.println("\n------------------------------------------------------------------------\n");
  Serial.println("[ ESTADO 0 - STANDBY ] Esperando el ingreso de texto.");
  Serial.flush();
  
}

//Rutina principal del tipo Maquina de Estados.
void loop()
{


/*
Función de prueba para leer todas los MP3

for(i=1;i<=MiniRepMP3.readFileCounts();i++)
{
 //MiniRepMP3.playMp3Folder(i);
 delay(4000);
}

*/
 

  switch(estado)
  {
      // ESTADO 0: STAND-BY (EN ESPERA).
      case 0:
              if(Serial.available())
                    {
                        estado=1;
                        i=0;
                        j=0;
                          digitalWrite(LED_STANDBY,LOW);
                          digitalWrite(LED_READ,HIGH);
                          digitalWrite(LED_CHECK,LOW);
                          digitalWrite(LED_PLAY,LOW);
                    }
                      else
                          {
                            digitalWrite(LED_STANDBY,HIGH);
                            digitalWrite(LED_READ,LOW);
                            digitalWrite(LED_CHECK,LOW);
                            digitalWrite(LED_PLAY,LOW);
                          }
      break;

      // ESTADO 1: RECEPCIÓN DE DATOS.
      case 1:
          Serial.println("\n------------------------------------------------------------------------\n");
          Serial.println("[ ESTADO 1 - READ ] Se guardan y muestran los caracteres ingresados.\n");
          if (Serial.available())
            {
              size_t count = Serial.readBytesUntil('\n', texto, 100);
              i=count;
              estado=2;
              Serial.print("Texto ingresado: ");
              for(j=0;j<i;j++)
                {
                  Serial.print(texto[j]);
                }
              Serial.println();
              Serial.print("Cantidad de caracteres: "); Serial.println(i);
              Serial.println("\n------------------------------------------------------------------------\n");
              Serial.println("[ ESTADO 2 - CHECK ] Se verifican y reemplazan caracteres NO VÁLIDOS.\n");
            }
      break;

      // ESTADO 2: CHEQUEO DE VALIDEZ DE DATOS.
      case 2:
              for(j=0;j<i;j++)
                {
                  delay(retardo2);
                  Serial.print(" |"); Serial.print(texto[j]); Serial.print("| ");
                  if(isAlphaNumeric(texto[j]))
                    {
                      if(isAlpha(texto[j]))
                      {
                        Serial.print("< OK! >"); delay(retardo2); Serial.print(" CARACTER ALFABETICO"); delay(retardo2);
                        switch(texto[j])
                          {
                            //Chequeamos letra A y convertimos a MAYÚSCULAS.
                            case 'a':
                              texto[j]='A';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                            
                            //Chequeamos letra B y convertimos a MAYÚSCULAS.
                            case 'b':
                              texto[j]='B';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                            
                            //Chequeamos letra C y convertimos a MAYÚSCULAS.
                            case 'c':
                              texto[j]='C';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra D y convertimos a MAYÚSCULAS.
                            case 'd':
                              texto[j]='D';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra E y convertimos a MAYÚSCULAS.
                            case 'e':
                              texto[j]='E';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra F y convertimos a MAYÚSCULAS.
                            case 'f':
                              texto[j]='F';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra G y convertimos a MAYÚSCULAS.
                            case 'g':
                              texto[j]='G';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra H y convertimos a MAYÚSCULAS.
                            case 'h':
                              texto[j]='H';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra I y convertimos a MAYÚSCULAS.
                            case 'i':
                              texto[j]='I';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra J y convertimos a MAYÚSCULAS.
                            case 'j':
                              texto[j]='J';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;              
                      
                            //Chequeamos letra K y convertimos a MAYÚSCULAS.
                            case 'k':
                              texto[j]='K';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra L y convertimos a MAYÚSCULAS.
                            case 'l':
                              texto[j]='L';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra M y convertimos a MAYÚSCULAS.
                            case 'm':
                              texto[j]='M';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra N y convertimos a MAYÚSCULAS.
                            case 'n':
                              texto[j]='N';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra O y convertimos a MAYÚSCULAS.
                            case 'o':
                              texto[j]='O';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra P y convertimos a MAYÚSCULAS.
                            case 'p':
                              texto[j]='P';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra Q y convertimos a MAYÚSCULAS.
                            case 'q':
                              texto[j]='Q';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra R y convertimos a MAYÚSCULAS.
                            case 'r':
                              texto[j]='R';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra S y convertimos a MAYÚSCULAS.
                            case 's':
                              texto[j]='S';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra T y convertimos a MAYÚSCULAS.
                            case 't':
                              texto[j]='T';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra U y convertimos a MAYÚSCULAS.
                            case 'u':
                              texto[j]='U';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra V y convertimos a MAYÚSCULAS.
                            case 'v':
                              texto[j]='V';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;                    
                      
                            //Chequeamos letra W y convertimos a MAYÚSCULAS.
                            case 'w':
                              texto[j]='W';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra X y convertimos a MAYÚSCULAS.
                            case 'x':
                              texto[j]='X';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra Y y convertimos a MAYÚSCULAS.
                            case 'y':
                              texto[j]='Y';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                      
                            //Chequeamos letra Z y convertimos a MAYÚSCULAS.
                            case 'z':
                              texto[j]='Z';
                              Serial.println(" > LETRA convertida a MAYÚSCULAS.");
                            break;
                            
                            //Chequeamos casos no determinados y reemplazamos por ESPACIO.
                            default:
                              if(texto[j]=='A'||texto[j]=='B'||texto[j]=='C'||texto[j]=='D'||texto[j]=='E'||texto[j]=='F'||texto[j]=='G'||texto[j]=='H'||texto[j]=='I'||texto[j]=='J'||texto[j]=='K'||texto[j]=='L'||texto[j]=='M'||texto[j]=='N'||texto[j]=='O'||texto[j]=='P'||texto[j]=='Q'||texto[j]=='R'||texto[j]=='S'||texto[j]=='T'||texto[j]=='U'||texto[j]=='V'||texto[j]=='W'||texto[j]=='X'||texto[j]=='Y'||texto[j]=='Z')
                                {
                                   Serial.println(" > LETRA ingresada en MAYÚSCULAS.");  
                                }
                                  else
                                    {
                                    }
                            break;
                          }
                            if(digitalRead(LED_CHECK))
                              {
                                digitalWrite(LED_CHECK,LOW);
                              }
                               else
                                    {
                                      digitalWrite(LED_CHECK,HIGH);
                                    }
                      }
                      else
                        {
                          if(texto[j]=='0'||texto[j]=='1'||texto[j]=='2'||texto[j]=='3'||texto[j]=='4'||texto[j]=='5'||texto[j]=='6'||texto[j]=='7'||texto[j]=='8'||texto[j]=='9')
                            {
                              Serial.print("< OK! >"); delay(retardo2); Serial.println("  CARACTER NUMÉRICO."); delay(retardo2);  
                            }
                              else
                                  {
                                  }
                        }
                    }
                    else
                        {
                          texto[j]='#';
                          Serial.print("< NO VALIDO! > NO ES LETRA NI NÚMERO, se reemplaza por #."); delay(retardo2); Serial.println();
                                      
                        }
                    
                }
        estado=3;
        j=0;
        digitalWrite(LED_STANDBY,LOW);
        digitalWrite(LED_READ,LOW);
        digitalWrite(LED_CHECK,LOW);
        digitalWrite(LED_PLAY,HIGH);
        Serial.println("\n------------------------------------------------------------------------\n");
        Serial.println("[ ESTADO 3 - PLAY ] Reproduciendo los caracteres ya verificados.");
      break;

      // ESTADO 3: REPRODUCCIÓN
      case 3:
         Serial.println();
         Serial.print("Reproduciendo: ");
         for(j=0;j<i;j++)
           {
             Serial.print(texto[j]);
           }
         Serial.println("\n");
        
        for(j=0;j<i;j++)
          {             
            Serial.print("| i = "); Serial.print(i);
            Serial.print("| j = "); Serial.print(j);
            Serial.print("| "); Serial.print(texto[j]); Serial.print(" > ");
            if(digitalRead(LED_PLAY))
              {
                digitalWrite(LED_PLAY,LOW);
              }
                else
                  {
                    digitalWrite(LED_PLAY,HIGH);
                  }
            //Reproducción
            switch(texto[j])
              {
                                 
                case 'A':
                  MiniRepMP3.playMp3Folder(1); Serial.print("ALFA"); delay(retardo1); Serial.println();              
                break;
                                 
                case 'B':
                  MiniRepMP3.playMp3Folder(2); Serial.print("BRAVO"); delay(retardo1); Serial.println();                    
                break;
                 
                case 'C':
                  MiniRepMP3.playMp3Folder(3); Serial.print("CHARLIE"); delay(retardo1); Serial.println();                   
                break;          
                 
                case 'D':
                  MiniRepMP3.playMp3Folder(4); Serial.print("DELTA"); delay(retardo1); Serial.println();                    
                break; 
                 
                case 'E':
                  MiniRepMP3.playMp3Folder(5); Serial.print("ECHO"); delay(retardo1); Serial.println();                   
                break;
                 
                case 'F':
                  MiniRepMP3.playMp3Folder(6); Serial.print("FOXTROT"); delay(retardo1); Serial.println();                  
                break;
                 
                case 'G':
                  MiniRepMP3.playMp3Folder(7); Serial.print("GOLF"); delay(retardo1); Serial.println();              
                break;
                
                 
                case 'H':
                  MiniRepMP3.playMp3Folder(8); Serial.print("HOTEL"); delay(retardo1); Serial.println();          
                break;
                 
                case 'I':
                  MiniRepMP3.playMp3Folder(9); Serial.print("INDIA"); delay(retardo1); Serial.println();              
                break;
                
                 
                case 'J':
                  MiniRepMP3.playMp3Folder(10); Serial.print("JULIETT"); delay(retardo1); Serial.println();               
                break;
                 
                case 'K':
                  MiniRepMP3.playMp3Folder(11); Serial.print("KILO"); delay(retardo1); Serial.println();                
                break;
                 
                case 'L':
                  MiniRepMP3.playMp3Folder(12); Serial.print("LIMA"); delay(retardo1); Serial.println();              
                break;
                
                 
                case 'M':
                  MiniRepMP3.playMp3Folder(13); Serial.print("MIKE"); delay(retardo1); Serial.println();                
                break;
                 
                case 'N':
                  MiniRepMP3.playMp3Folder(14); Serial.print("NOVEMBER"); delay(retardo1); Serial.println();            
                break;             
                 
                case 'O':
                  MiniRepMP3.playMp3Folder(15); Serial.print("OSCAR"); delay(retardo1); Serial.println();             
                break;               
                 
                case 'P':
                  MiniRepMP3.playMp3Folder(16); Serial.print("PAPA"); delay(retardo1); Serial.println();               
                break;              
                 
                case 'Q':
                  MiniRepMP3.playMp3Folder(17); Serial.print("QUEBEC"); delay(retardo1); Serial.println();           
                break;              
                 
                case 'R':
                  MiniRepMP3.playMp3Folder(18); Serial.print("ROMEO"); delay(retardo1); Serial.println();                 
                break;             
                 
                case 'S':
                  MiniRepMP3.playMp3Folder(19); Serial.print("SIERRA"); delay(retardo1); Serial.println();               
                break;     
                 
                case 'T':
                  MiniRepMP3.playMp3Folder(20); Serial.print("TANGO"); delay(retardo1); Serial.println();             
                break;
                 
                case 'U':
                  MiniRepMP3.playMp3Folder(21); Serial.print("UNIFORM"); delay(retardo1); Serial.println();                
                break;
                 
                case 'V':
                  MiniRepMP3.playMp3Folder(22); Serial.print("VICTOR"); delay(retardo1); Serial.println();           
                break;
                
                 
                case 'W':
                  MiniRepMP3.playMp3Folder(23); Serial.print("WHISKEY"); delay(retardo1); Serial.println();              
                break;
                 
                case 'X':
                  MiniRepMP3.playMp3Folder(24); Serial.print("X-RAY"); delay(retardo1); Serial.println();            
                break;
                 
                case 'Y':
                  MiniRepMP3.playMp3Folder(25); Serial.print("YANKEE"); delay(retardo1); Serial.println();         
                break;
                 
                case 'Z':
                  MiniRepMP3.playMp3Folder(26); Serial.print("ZULU"); delay(retardo1); Serial.println();    
                break;
                 
                case '0':
                  MiniRepMP3.playMp3Folder(27); Serial.print("ZERO"); delay(retardo1); Serial.println();                 
                break;
                 
                case '1':
                  MiniRepMP3.playMp3Folder(28); Serial.print("ONE"); delay(retardo1); Serial.println();        
                break;
                 
                case '2':
                  MiniRepMP3.playMp3Folder(29); Serial.print("TWO"); delay(retardo1); Serial.println();         
                break;
                 
                case '3':
                  MiniRepMP3.playMp3Folder(30); Serial.print("THREE"); delay(retardo1); Serial.println();       
                break;         
                 
                case '4':
                  MiniRepMP3.playMp3Folder(31); Serial.print("FOUR"); delay(retardo1); Serial.println();              
                break;      
                 
                case '5':
                  MiniRepMP3.playMp3Folder(32); Serial.print("FIVE"); delay(retardo1); Serial.println();              
                break;   
                 
                case '6':
                  MiniRepMP3.playMp3Folder(33); Serial.print("SIX"); delay(retardo1); Serial.println();              
                break;
                 
                case '7':
                  MiniRepMP3.playMp3Folder(34); Serial.print("SEVEN"); delay(retardo1); Serial.println();             
                break;  
                 
                case '8':
                  MiniRepMP3.playMp3Folder(35); Serial.print("EIGHT"); delay(retardo1); Serial.println();            
                break;
                 
                case '9':
                  MiniRepMP3.playMp3Folder(36); Serial.print("NINE"); delay(retardo1); Serial.println();
                break;    
                 
                default:
                  delay(retardo2); Serial.print("[SILENCIO]"); delay(retardo2); Serial.println();
                break;                        
             }
          }

          estado=0;
          Serial.println("\n------------------------------------------------------------------------\n");
          Serial.println("[ ESTADO 0 - STANDBY ] Esperando el ingreso de texto.");
          Serial.flush();
          break;
  }
}
