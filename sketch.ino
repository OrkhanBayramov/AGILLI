/* By Orkhan Bayramov */
/* ARDUINO MEGA & NEXTION 7 INCH LCD WITH TOUCH SCREEN*/
/* sketch for 5 sector GreenHouse*/
/* in one sector 1 window(ac-motor) & 1 fan*/
/* between sectors have a FAN (5 fans turning on & off with own command)*/
/* 5in1 FAN group turning on & off with one command*/
/* Fans in sectors are controlling 2-2-1 mode*/
/* Last update: 25/10/2018*/

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
                                     // include library
 
#include "Nextion.h"
#include "NexTouch.h"
#include "NexHardware.h"
#include "NexNumber.h"
#include "NexText.h"
#include "NexButton.h"
#include "NexDualStateButton.h"
#include "NexSlider.h"
#include "DHT.h"//DHT sensor Library

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

#define DHTPIN 5                         // Define sensor pin(pin 5)
#define DHTTYPE DHT21                    // Using DHT21 sensor

DHT dht(DHTPIN, DHTTYPE);                // Create sensor object

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

int h=0, t=0;                             // "h" Hummidity, "t" Temperature
int targetTemp;                           // "targetTemp" user defined temperature
int targetHum;                            // "targetHum" user defined hummidity
//----------------------------

int variable1 = 0;                        // Create a variable to have a counter going up by one on each cycle
int counter = 0;                          // Create a variable to have a counter for the + and - buttons
int CurrentPage = 0;                      // Create a variable to store which page is currently loaded

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

long previousMillis = 0;
long interval = 2000;                     // Read DHT sensor each 2 seconds


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

   char buffer[10] = {0};

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

   boolean  autobutton=HIGH, manualbutton=HIGH, winactivated=HIGH, fanactivated=HIGH, 
           //----------------------------------------------------------------------------//
            window1=HIGH,  window2=HIGH,  window3=HIGH, window4=HIGH,   window5=HIGH,
           awindow1=HIGH, awindow2=HIGH, awindow3=HIGH, awindow4=HIGH, awindow5=HIGH,
           mwindow1=HIGH, mwindow2=HIGH, mwindow3=HIGH, mwindow4=HIGH, mwindow5=HIGH,
       //-------------------------------------------------------------------------------//
	       lfan1=HIGH,  lfan2=HIGH,  lfan3=HIGH,  lfan4=HIGH,
	   //-------------------------------------------------------------------------------//
           fan1=HIGH,  fan2=HIGH,  fan3=HIGH,  fan4=HIGH,
           afan1=HIGH, afan2=HIGH, afan3=HIGH, afan4=HIGH,
           mfan1=HIGH, mfan2=HIGH, mfan3=HIGH, mfan4=HIGH;

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
                                     // relay pins on ardunio

const int relay1 = 22;                              
const int relay2 = 23;                              
const int relay3 = 24;                            
const int relay4 = 25;                            
const int relay5 = 26;                             
const int relay6 = 27;                             
const int relay7 = 28;                           
const int relay8 = 29;                            
const int relay9 = 30;                            
const int relay10 = 31;                            
const int relay11 = 32;                                
const int relay12 = 33;                                
const int relay13 = 34;                                
const int relay14 = 35;                          
const int relay15 = 36;                                
const int relay16 = 37; 
const int linestatus = 51;
int lstatus = 0;

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
                                     // NEXTION PAGE LIST

NexPage logo = NexPage(0, 0, "logo");                // Page added as a touch event
NexPage start = NexPage(1, 0, "start");              // Page added as a touch event
NexPage home1 = NexPage(2, 0, "home1");              // Page added as a touch event 
NexPage autohome1 = NexPage(3, 0, "autohome1");      // Page added as a touch event 
NexPage manualhome1 = NexPage(4, 0, "manualhome1");  // Page added as a touch event 
NexPage terms1 = NexPage(5, 0, "terms1");            // Page added as a touch event                

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
                                     // HOME PAGE ON NEXTION LCD

NexDSButton automode = NexDSButton(2, 1, "automode");
NexDSButton manualmode = NexDSButton(2, 2, "manualmode");
NexNumber tempdata = NexNumber(2, 3, "tempdata");
NexNumber humdata = NexNumber(2, 4, "humdata");

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
                                     // AUTO-CONTROL PAGE ON NEXTION LCD
                  
NexNumber tempdataa = NexNumber(3, 15, "tempdataa");
NexNumber humdataa = NexNumber(3, 16, "humdataa");
NexNumber automodeon = NexNumber(3, 18, "automodeon");
NexNumber firstwo = NexNumber(3, 19, "firstwo");
NexNumber firstwc = NexNumber(3, 20, "firstwc");
NexNumber secondwo = NexNumber(3, 21, "secondwo");
NexNumber secondwc = NexNumber(3, 22, "secondwc");
NexNumber thirdwo = NexNumber(3, 23, "thirdwo");
NexNumber thirdwc = NexNumber(3, 24, "thirdwc");
NexNumber fourthwo = NexNumber(3, 25, "fourthwo");
NexNumber fourthwc = NexNumber(3, 26, "fourthwc");
NexNumber fifthwo = NexNumber(3, 27, "fifthwo");
NexNumber fifthwc = NexNumber(3, 28, "fifthwc");
NexNumber firstfo = NexNumber(3, 29, "firstfo");
NexNumber firstfc = NexNumber(3, 30, "firstfc");
NexNumber secondfo = NexNumber(3, 31, "secondfo");
NexNumber secondfc = NexNumber(3, 32, "secondfc");
NexNumber thirdfo = NexNumber(3, 33, "thirdfo");
NexNumber thirdfc = NexNumber(3, 34, "thirdfc");
NexNumber exao = NexNumber(3, 35, "exao");
NexNumber exac = NexNumber(3, 36, "exac"); 
//-----------------------------------------------------
NexDSButton winactive = NexDSButton(3, 7, "winactive");
NexDSButton windeactive = NexDSButton(3, 8, "windeactive");
NexDSButton fanactive = NexDSButton(3, 10, "fanactive");
NexDSButton fandeactive = NexDSButton(3, 9, "fandeactive");
//------------------------------------------------------
NexNumber targettempval = NexNumber(3, 11, "targettempval");
NexNumber targethumval = NexNumber(3, 12, "targethumval");
NexButton targettempup = NexButton(3, 1, "targettempup");
NexButton targettempdown = NexButton(3, 2, "targettempdown");
NexButton targethumup = NexButton(3, 4, "targethumup");
NexButton targethumdown = NexButton(3, 3, "targethumdown");

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
                                     // MANUAL-CONTROL PAGE ON NEXTION LCD

NexDSButton win1openbutton = NexDSButton(4, 1, "win1openbutton");
NexDSButton win1closbutton = NexDSButton(4, 10, "win1closbutton");
NexDSButton win2openbutton = NexDSButton(4, 2, "win2openbutton");
NexDSButton win2closbutton = NexDSButton(4, 11, "win2closbutton");
NexDSButton win3openbutton = NexDSButton(4, 3, "win3openbutton");
NexDSButton win3closbutton = NexDSButton(4, 12, "win3closbutton");
NexDSButton win4openbutton = NexDSButton(4, 4, "win4openbutton");
NexDSButton win4closbutton = NexDSButton(4, 13, "win4closbutton");
NexDSButton win5openbutton = NexDSButton(4, 5, "win5openbutton");
NexDSButton win5closbutton = NexDSButton(4, 14, "win5closbutton");
//----------------------------------------------------------------
NexDSButton fan1openbutton = NexDSButton(4, 6, "fan1openbutton");
NexDSButton fan1closbutton = NexDSButton(4, 15, "fan1closbutton");
NexDSButton fan2openbutton = NexDSButton(4, 7, "fan2openbutton");
NexDSButton fan2closbutton = NexDSButton(4, 16, "fan2closbutton");
NexDSButton fan3openbutton = NexDSButton(4, 8, "fan3openbutton");
NexDSButton fan3closbutton = NexDSButton(4, 17, "fan3closbutton");
NexDSButton fan4openbutton = NexDSButton(4, 9, "fan4openbutton");
NexDSButton fan4closbutton = NexDSButton(4, 18, "fan4closbutton");
//-----------------------------------------------------------------
NexNumber tempdatam = NexNumber(4, 20, "tempdatam");
NexNumber humdatam = NexNumber(4, 21, "humdatam");
NexNumber manualmodeon = NexNumber(4, 23, "manualmodeon");

NexNumber fmo = NexNumber(4, 23, "fmo");
NexNumber fmc = NexNumber(4, 23, "fmc");
NexNumber wmo = NexNumber(4, 23, "wmo");
NexNumber wmc = NexNumber(4, 23, "wmc");
NexNumber exmo = NexNumber(4, 23, "exmo");
NexNumber exmc = NexNumber(4, 23, "exmc");
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
                                     // REGISTER NEXTION BUTTONS

NexTouch *nex_listen_list[] =
{ 
  &automode,
  &manualmode,
  &winactive,
  &windeactive,
  &fanactive,
  &fandeactive,
  &win1openbutton,
  &win1closbutton,
  &win2openbutton,
  &win2closbutton,
  &win3openbutton,
  &win3closbutton,
  &win4openbutton,
  &win4closbutton,
  &win5openbutton,
  &win5closbutton,
  &fan1openbutton,
  &fan1closbutton,
  &fan2openbutton,
  &fan2closbutton,
  &fan3openbutton,
  &fan3closbutton,
  &fan4openbutton,
  &fan4closbutton,
  &tempdata,
  &tempdataa,
  &tempdatam,
  &humdata,
  &humdataa,
  &humdatam,
  &targettempval,
  &targettempup,
  &targettempdown,
  &targethumval,
  &targethumup,
  &targethumdown,
  &automodeon,
  &manualmodeon,
  &firstwo,
  &firstwc,
  &secondwo,
  &secondwc,
  &thirdwo,
  &thirdwc,
  &fourthwo,
  &fourthwc,
  &fifthwo,
  &fifthwc,
  &firstfo,
  &firstfc,
  &secondfo,
  &secondfc,
  &thirdfo,
  &thirdfc,
  &exao,
  &exac,
  &fmo,
  &fmc,
  &wmo,
  &wmc,
  &exmo,
  &exmc,
  NULL
};

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
                                     // SETUP
  
void setup()
{
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);
  pinMode(relay9, OUTPUT);
  pinMode(relay10, OUTPUT);
  pinMode(relay11, OUTPUT);
  pinMode(relay12, OUTPUT);
  pinMode(relay13, OUTPUT);
  pinMode(relay14, OUTPUT);
//--------------------------------------
  digitalWrite(relay1,HIGH);                     
  digitalWrite(relay2,HIGH);                   
  digitalWrite(relay3,HIGH);                        
  digitalWrite(relay4,HIGH);                       
  digitalWrite(relay5,HIGH);                         
  digitalWrite(relay6,HIGH);                        
  digitalWrite(relay7,HIGH);                          
  digitalWrite(relay8,HIGH);                         
  digitalWrite(relay9,HIGH);                         
  digitalWrite(relay10,HIGH);                       
  digitalWrite(relay11,HIGH);                            
  digitalWrite(relay12,HIGH);                          
  digitalWrite(relay13,HIGH);                          
  digitalWrite(relay14,HIGH); 
//---------------------------------------
//---------------------------------------
  dht.begin();
  Serial.begin(9600);
  nexInit();
//---------------------------------------
//--------------------------------------- 
  
  
}


void loop()
{
//------------------------------------------------------------------------------------------------- 
//------------------------------------------------------------------------------------------------- 
                                 // Line in Check
	lstatus = digitalRead(linestatus);
	if(lstatus==HIGH)
	{
	Serial.println("Line status is HIGH");
	}
//------------------------------------------------------------------------------------------------- 
//------------------------------------------------------------------------------------------------- 
                                 //  Temperature & Hummidity  monitoring

   unsigned long currentMillis = millis();             //time elapsed
  if(currentMillis - previousMillis > interval)       // Comparison between the elapsed time and the time in which the action is to be executed
  {
    previousMillis = currentMillis;                   // "Last time is now"

     h = dht.readHumidity();                          // humidity value
     t = dht.readTemperature();                       // temperature value
  
    memset(buffer, 0, sizeof(buffer)); // clear buffer
      itoa(t, buffer, 10);
          tempdata.setValue(t);
              tempdataa.setValue(t);
                 tempdatam.setValue(t);
  

      memset(buffer, 0, sizeof(buffer)); // clear buffer
      itoa(h, buffer, 10);
          humdata.setValue(h);
              humdataa.setValue(h);
                 humdatam.setValue(h);
				 
				 
				 Serial.println(t);
				 Serial.println(h);
        
 }
 //------------------------------------------------------------------------
                                 //  Target temperature & hummidity setting
  
  uint32_t targettemp = 0;
        targettempval.getValue(&targettemp);
           if(targettemp >0)
           {
             targetTemp = targettemp;
           }
        Serial.println(targetTemp);

//-------------------------------------------------------------------------
    uint32_t targethum = 0;
        targethumval.getValue(&targethum);
           if(targethum >0)
           {
             targetHum = targethum;
           }
        Serial.println(targetHum);
  
  //-------------------------------------------------------------------------
       /* extremHum=targetHum+15;
		if(h>extremHum)
		{
		 extrem=LOW;
		}
		if(h<extremHum)
		{
		 extrem=HIGH;
		}
		    */
  
//------------------------------------------------------------------------------------------------- 
//-------------------------------------------------------------------------------------------------   
                                 // Mode Selection
   //------------------------------------------------------------------
   //------------------------------------------------------------------
   //------------------------------------------------------------------
                    // Auto-Control Mode
          
    uint32_t automodeonon = 0;  
        automodeon.getValue(&automodeonon);  
          if(automodeonon > 0 && autobutton==HIGH)
            {
             autobutton=LOW;
			 Serial.println("Auto-Mode selected");
            }
    uint32_t automodeonoff = 0; 
        automodeon.getValue(&automodeonoff);  
          if(automodeonoff < 1 && autobutton==LOW)
            {
             autobutton=HIGH;
			 Serial.println("End Automode");
            }
         
    //--------------------------------------------------------
                 // Automatic Window Control Activation
    //--------------------------------------------------------     
          uint32_t windowson = 0 ;
                    winactive.getValue(&windowson); 
                       if(windowson > 0 && winactivated==HIGH)
                        { 
                         winactivated=LOW;
             Serial.println("Automatic Window Control Activated");
                        }
          uint32_t windowsoff =0;  
                    windeactive.getValue(&windowsoff); 
  
                       if(windowsoff > 0 && winactivated==LOW)
                        {  
                         winactivated=HIGH;
             Serial.println("Automatic Window Control De-Activated");
                        }
        //--------------------------------------------------------
                 // Automatic FAN Control Activation
    //--------------------------------------------------------
            uint32_t fanson = 0;  
                    fanactive.getValue(&fanson); 
                       if(fanson > 0 && fanactivated==HIGH)
                        { 						
                         fanactivated=LOW;
						 Serial.println("Automatic FAN control activated");
                        }
            uint32_t fansoff = 1;  
                    fandeactive.getValue(&fansoff);
                       if(fansoff > 0 && fanactivated==LOW)
                        { 
						 fanactivated=HIGH;
						 Serial.println("Automatic FAN control de-activated");
                        }
    
      
   //------------------------------------------------------------------     
   //------------------------------------------------------------------
                    // Manual-Control Mode
          
    uint32_t manualmodeonon = 0;  
        manualmodeon.getValue(&manualmodeonon);  
          if(manualmodeonon > 0 && manualbutton==HIGH)
            {
             manualbutton=LOW;
			 Serial.println("MANUAL-MODE selected");
            }
           if(manualmodeonon < 1 && manualbutton==LOW)
		    {
			 manualbutton=HIGH;
			 Serial.println("END MANUAL-MODE");
			}

        //--------------------------------------------------------
                 // Window Control Pharagraph (MANUAL-MODE)
    //--------------------------------------------------------
                            // first window
          uint32_t win1openbuttonon = 0; 
                    win1openbutton.getValue(&win1openbuttonon);  
                       if(win1openbuttonon > 0 && mwindow1==HIGH) 
                        {
                          mwindow1=LOW;
                        }
                uint32_t win1closbuttonon = 0;  
                    win1closbutton.getValue(&win1closbuttonon); 
                       if(win1closbuttonon > 0 && mwindow1==LOW) 
                        {
                         mwindow1=HIGH;
						 
                        }

    //--------------------------------------------------------
                            // Second window
          uint32_t win2openbuttonon = 0; 
                    win2openbutton.getValue(&win2openbuttonon);  
                       if(win2openbuttonon > 0 && mwindow2==HIGH) 
                        {
                          mwindow2=LOW;
                        }
                uint32_t win2closbuttonon = 0;  
                    win2closbutton.getValue(&win2closbuttonon); 
                       if(win2closbuttonon > 0 && mwindow2==LOW) 
                        {
                         mwindow2=HIGH;
                        } 
      
    //--------------------------------------------------------
                            // Third window
          uint32_t win3openbuttonon = 0; 
                    win3openbutton.getValue(&win3openbuttonon);  
                       if(win3openbuttonon > 0 && mwindow3==HIGH) 
                        {
                          mwindow3=LOW;
                        }
                uint32_t win3closbuttonon = 0;  
                    win3closbutton.getValue(&win3closbuttonon); 
                       if(win3closbuttonon > 0 && mwindow3==LOW) 
                        {
                         mwindow3=HIGH;
                        } 
    
    //--------------------------------------------------------
                            // Fourth window
          uint32_t win4openbuttonon = 0; 
                    win4openbutton.getValue(&win4openbuttonon);  
                       if(win4openbuttonon > 0 && mwindow4==HIGH) 
                        {
                          mwindow4=LOW;
                        }
                uint32_t win4closbuttonon = 0;  
                    win4closbutton.getValue(&win4closbuttonon); 
                       if(win4closbuttonon > 0 && mwindow4==LOW) 
                        {
                         mwindow4=HIGH;
                        } 
    
    //--------------------------------------------------------
                            // Fifth window
          uint32_t win5openbuttonon = 0; 
                    win5openbutton.getValue(&win5openbuttonon);  
                       if(win5openbuttonon > 0 && mwindow5==HIGH) 
                        {
                          mwindow5=LOW;
                        }
                uint32_t win5closbuttonon = 0;  
                    win5closbutton.getValue(&win5closbuttonon); 
                       if(win5closbuttonon > 0 && mwindow5==LOW) 
                        {
                         mwindow5=HIGH;
                        }       
            
    //--------------------------------------------------------
                  // FAN Control Pharagraph (MANUAL-MODE)
    //--------------------------------------------------------
                // First FAN
        uint32_t fan1openbuttonon = 0; 
                    fan1openbutton.getValue(&fan1openbuttonon); 
                       if(fan1openbuttonon > 0 && mfan1==HIGH) 
                        {
                         mfan1=LOW;
                        }
                uint32_t fan1closbuttonon = 0;  
                    fan1closbutton.getValue(&fan1closbuttonon);
                       if(fan1closbuttonon > 0 && mfan1==LOW) 
                        {
                         mfan1=HIGH;
                        }   
            
    //--------------------------------------------------------
                // Second FAN
        uint32_t fan2openbuttonon = 0; 
                    fan2openbutton.getValue(&fan2openbuttonon); 
                       if(fan2openbuttonon > 0 && mfan2==HIGH) 
                        {
                         mfan2=LOW;
                        }
                uint32_t fan2closbuttonon = 0;  
                    fan2closbutton.getValue(&fan2closbuttonon);
                       if(fan2closbuttonon > 0 && mfan2==LOW) 
                        {
                         mfan2=HIGH;
                        }
        
    //--------------------------------------------------------
                // Third FAN
        uint32_t fan3openbuttonon = 0; 
                    fan3openbutton.getValue(&fan3openbuttonon); 
                       if(fan3openbuttonon > 0 && mfan3==HIGH) 
                        {
                         mfan3=LOW;
                        }
                uint32_t fan3closbuttonon = 0;  
                    fan3closbutton.getValue(&fan3closbuttonon);
                       if(fan3closbuttonon > 0 && mfan3==LOW) 
                        {
                         mfan3=HIGH;
                        }

        //--------------------------------------------------------
                // Fourth FAN
        uint32_t fan4openbuttonon = 0; 
                    fan4openbutton.getValue(&fan4openbuttonon); 
                       if(fan4openbuttonon > 0 && mfan4==HIGH) 
                        {
                         mfan4=LOW;
                        }
                uint32_t fan4closbuttonon = 0;  
                    fan4closbutton.getValue(&fan4closbuttonon);
                       if(fan4closbuttonon > 0 && mfan4==LOW) 
                        {
                         mfan4=HIGH;
                        }

//------------------------------------------------------------------------------------------------- 
//-------------------------------------------------------------------------------------------------
                           //----*** ENGINE ***----//
	//---------------------------------------------------------					   
    //---------------------------------------------------------
                               // First Window
                if(manualbutton==LOW && mwindow1==LOW && window1==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay1,LOW);
                     delay(5000);
                     digitalWrite(relay1,HIGH);
                     window1=LOW;
					 firstwo.setValue(1);
					 firstwc.setValue(0);
           Serial.println("First Window Opened Manually");
                    }
                if(manualbutton==LOW && mwindow1==HIGH && window1==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay2,LOW);
                     delay(5000);
                     digitalWrite(relay2,HIGH);
                     window1=HIGH;
					 firstwo.setValue(0);
                     firstwc.setValue(1);
           Serial.println("First Window Closed Manually");
                    }

        //---------------------------------------------------------
                               // Second Window
                if(manualbutton==LOW && mwindow2==LOW && window2==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay3,LOW);
                     delay(5000);
                     digitalWrite(relay3,HIGH);
                     window2=LOW;
					 secondwo.setValue(1);
                     secondwc.setValue(0);
           Serial.println("Second Window Opened Manually");
                    }
                if(manualbutton==LOW && mwindow2==HIGH && window2==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay4,LOW);
                     delay(5000);
                     digitalWrite(relay4,HIGH);
                     window2=HIGH;
					 secondwo.setValue(0);
                     secondwc.setValue(1);
           Serial.println("Second Window Closed Manually");
                    }
    
        //---------------------------------------------------------
                               // Third Window
                if(manualbutton==LOW && mwindow3==LOW && window3==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay5,LOW);
                     delay(5000);
                     digitalWrite(relay5,HIGH);
                     window3=LOW;
					 thirdwo.setValue(1);
                     thirdwc.setValue(0);
           Serial.println("Third Window Opened Manually");
                    }
                if(manualbutton==LOW && mwindow3==HIGH && window3==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay6,LOW);
                     delay(5000);
                     digitalWrite(relay6,HIGH);
                     window3=HIGH;
					 thirdwo.setValue(0);
                     thirdwc.setValue(1);
           Serial.println("Third Window Closed Manually");
                    }

        //---------------------------------------------------------
                               // Fourth Window
                if(manualbutton==LOW && mwindow4==LOW && window4==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay7,LOW);
                     delay(5000);
                     digitalWrite(relay7,HIGH);
                     window4=LOW;
					 fourthwo.setValue(1);
                     fourthwc.setValue(0);
           Serial.println("Fourth Window Opened Manually");
                    }
                if(manualbutton==LOW && mwindow4==HIGH && window4==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay8,LOW);
                     delay(5000);
                     digitalWrite(relay8,HIGH);
                     window4=HIGH;
					 fourthwo.setValue(0);
                     fourthwc.setValue(1);
           Serial.println("Fourth Window Closed Manually");
                    }

        //---------------------------------------------------------
                               // Fifth Window
                if(manualbutton==LOW && mwindow5==LOW && window5==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay9,LOW);
                     delay(5000);
                     digitalWrite(relay9,HIGH);
                     window5=LOW;
					 fifthwo.setValue(1);
                     fifthwc.setValue(0);
           Serial.println("Fifth Window Opened Manually");
                    }
                if(manualbutton==LOW && mwindow5==HIGH && window5==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay10,LOW);
                     delay(5000);
                     digitalWrite(relay10,HIGH);
                     window5=HIGH;
					 fifthwo.setValue(0);
                     fifthwc.setValue(1);
           Serial.println("Fifth Window Closed Manually");
                    }

        //---------------------------------------------------------
                               // First FAN
                if(manualbutton==LOW && mfan1==LOW && fan1==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay11,LOW);
                     fan1=LOW;
					 firstfo.setValue(1);
					 firstfc.setValue(0);
                       Serial.println("First FAN Activated Manually");
					 delay(4000);
                    }
                if(manualbutton==LOW && mfan1==HIGH && fan1==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay11,HIGH);
                     fan1=HIGH;
					 firstfo.setValue(0);
					 firstfc.setValue(1);
                       Serial.println("First FAN De-Activated Manually");
					 delay(4000);
                    }
			    if(lstatus==LOW && lfan1==HIGH)
				    {
					 digitalWrite(relay11,HIGH);
                     fan1=HIGH;
					 lfan1=LOW;
					 firstfo.setValue(0);
					 firstfc.setValue(1);
                       Serial.println("First FAN De-Activated by line checker");
					}
                if(lstatus==HIGH && lfan1==LOW)
				    {
					 lfan1=HIGH;
					}
        //---------------------------------------------------------
                               // Second FAN
                if(manualbutton==LOW && mfan2==LOW && fan2==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay12,LOW);
                     fan2=LOW;
					 secondfo.setValue(1);
					 secondfc.setValue(0);
                       Serial.println("Second FAN Activated Manually");
					   delay(4000);
                    }
                if(manualbutton==LOW && mfan2==HIGH && fan2==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay12,HIGH);
                     fan2=HIGH;
					 secondfo.setValue(0);
					 secondfc.setValue(1);
                       Serial.println("Second FAN De-Activated Manually");
					 delay(4000);
                    }
		        if(lstatus==LOW && lfan2==HIGH)
				    {
					 digitalWrite(relay12,HIGH);
                     fan2=HIGH;
					 lfan2=LOW;
					 secondfo.setValue(0);
					 secondfc.setValue(1);
                       Serial.println("Second FAN De-Activated by line checker");
					}
                if(lstatus==HIGH && lfan2==LOW)
				    {
					 lfan2=HIGH;
					}
        //---------------------------------------------------------
                               // Third FAN
                if(manualbutton==LOW && mfan3==LOW && fan3==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay13,LOW);
                     fan3=LOW;
					 thirdfo.setValue(1);
					 thirdfc.setValue(0);
                       Serial.println("Third FAN Activated Manually");
					   delay(4000);
                    }
                if(manualbutton==LOW && mfan3==HIGH && fan3==LOW)
                    {
                     digitalWrite(relay13,HIGH);
                     fan3=HIGH;
					 thirdfo.setValue(0);
					 thirdfc.setValue(1);
                       Serial.println("Third FAN De-Activated Manually");
					 delay(4000);
                    }
			     if(lstatus==LOW && lfan3==HIGH)
				    {
					 digitalWrite(relay13,HIGH);
                     fan3=HIGH;
					 lfan3=LOW;
					 thirdfo.setValue(0);
					 thirdfc.setValue(1);
                       Serial.println("Third FAN De-Activated by line checker");
					}
                if(lstatus==HIGH && lfan3==LOW)
				    {
					 lfan3=HIGH;
					}
        //---------------------------------------------------------
                               // Fourth FAN
                if(manualbutton==LOW && mfan4==LOW && fan4==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay14,LOW);
                     fan4=LOW;
					 exao.setValue(1);
					 exac.setValue(0);
                       Serial.println("Fourth FAN Activated Manually");
					   delay(4000);
                    }
                if(manualbutton==LOW && mfan4==HIGH && fan4==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay14,HIGH);
                     fan4=HIGH;
					 exao.setValue(0);
					 exac.setValue(1);
                       Serial.println("Fourth FAN De-Activated Manually");
					 delay(4000);
                    }
                if(lstatus==LOW && lfan4==HIGH)
				    {
					 digitalWrite(relay14,HIGH);
                     fan4=HIGH;
					 lfan4=LOW;
					 exao.setValue(0);
					 exac.setValue(1);
                      Serial.println("Fourth FAN De-Activated by line checker");
					}
				if(lstatus==HIGH && lfan4==LOW)
				    {
					 lfan4=HIGH;
					}
		//-----------------------------------------------------------
                if(window1==LOW && window2==LOW && window3==LOW && window4==LOW && window5==LOW)
				    {
					 wmo.setValue(1);
					 wmc.setValue(0);
				    }

				if(window1==HIGH && window2==HIGH && window3==HIGH && window4==HIGH && window5==HIGH)
				    {
					 wmc.setValue(1);
					 wmo.setValue(0);
				    }

				if(fan1==LOW && fan2==LOW && fan3==LOW)
				    {
					 fmo.setValue(1);
					 fmc.setValue(0);
				    }

			    if(fan1==HIGH && fan2==HIGH && fan3==HIGH)
				    {
					 fmc.setValue(1);
					 fmo.setValue(0);
                    }
				if(fan4==HIGH)
				    {
					 exmo.setValue(0);
					 exmc.setValue(1);
					}
				if(fan4==LOW)
				    {
					 exmo.setValue(1);
					 exmc.setValue(0);
					}
				

		
//------------------------------------------------------------------------------------------------- 
//------------------------------------------------------------------------------------------------- 
                                     // AUTO-CONTROL MODE
    //------------------------------------------------------------
                              // First Window 
            if(t>targetTemp && autobutton==LOW && winactivated==LOW && window1==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay1,LOW);                       
                     delay(5000);
                     digitalWrite(relay1, HIGH);               
					 window1=LOW;
					 firstwo.setValue(1);
					 firstwc.setValue(0);
					 Serial.println("First window opened automaticly");
                    }
            if(t<targetTemp && autobutton==LOW && winactivated==LOW && window1==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay2,LOW);                       
                     delay(5000);
                     digitalWrite(relay2,HIGH);                     
					 window1=HIGH;
					 firstwo.setValue(0);
					 firstwc.setValue(1);
					 Serial.println("First window closed automaticly");
                    }    
            if(autobutton==LOW && winactivated==HIGH && window1==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay2,LOW);                       
                     delay(5000);
                     digitalWrite(relay2,HIGH);                     
					 window1=HIGH;
					 firstwo.setValue(0);
					 firstwc.setValue(1);
					 Serial.println("First window closed automaticly");
                    }
			if(window1==LOW)
                    {
					 firstwo.setValue(1);
					 firstwc.setValue(0);
                    }
            if(window1==HIGH)
			        {
					 firstwo.setValue(0);
					 firstwc.setValue(1);
					}
			
			
			
        //------------------------------------------------------------
                              // Second Window 
            if(t>targetTemp && autobutton==LOW && winactivated==LOW && window2==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay3,LOW);                       
                     delay(5000);
                     digitalWrite(relay3, HIGH);               
                     window2=LOW;
					 secondwo.setValue(1);
					 secondwc.setValue(0);
					 Serial.println("Second window opened automaticly");
                    }
            if(t<targetTemp && autobutton==LOW && winactivated==LOW && window2==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay4,LOW);                       
                     delay(5000);
                     digitalWrite(relay4,HIGH);                     
					 window2=HIGH;
					 secondwo.setValue(0);
					 secondwc.setValue(1);
					 Serial.println("Second window closed automaticly");
                    }    
            if(autobutton==LOW && winactivated==HIGH && window2==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay4,LOW);                       
                     delay(5000);
                     digitalWrite(relay4,HIGH);                     
					 window2=HIGH;
					 secondwo.setValue(0);
					 secondwc.setValue(1);
					 Serial.println("Second window closed automaticly");
                    }
			if(window2==LOW)
			        {
					 secondwo.setValue(1);
					 secondwc.setValue(0);
					}
			if(window2==HIGH)
			        {
					 secondwo.setValue(0);
					 secondwc.setValue(1);
					}

        //------------------------------------------------------------
                              // Third Window 
            if(t>targetTemp && autobutton==LOW && winactivated==LOW && window3==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay5,LOW);                       
                     delay(5000);
                     digitalWrite(relay5, HIGH);               
					 window3=LOW;
					 thirdwo.setValue(1);
					 thirdwc.setValue(0);
					 Serial.println("Third window opened automaticly");
                    }
            if(t<targetTemp && autobutton==LOW && winactivated==LOW && window3==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay6,LOW);                       
                     delay(5000);
                     digitalWrite(relay6,HIGH);                     
					 window3=HIGH;
					 thirdwo.setValue(0);
					 thirdwc.setValue(1);
					 Serial.println("Third window closed automaticly");
                    }    
            if(autobutton==LOW && winactivated==HIGH && window3==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay6,LOW);                       
                     delay(5000);
                     digitalWrite(relay6,HIGH);                     
					 window3=HIGH;
					 thirdwo.setValue(0);
					 thirdwc.setValue(1);
					 Serial.println("Third window closed automaticly");
                    }
			if(window3==LOW)
			        {
					 thirdwo.setValue(1);
					 thirdwc.setValue(0);
					}
			if(window3==HIGH)
			        {
					 thirdwo.setValue(0);
					 thirdwc.setValue(1);
					}

		//------------------------------------------------------------
                              // Fourth Window 
            if(t>targetTemp && autobutton==LOW && winactivated==LOW && window4==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay7,LOW);                       
                     delay(5000);
                     digitalWrite(relay7, HIGH);               
					 window4=LOW;
                     fourthwo.setValue(1);
					 fourthwc.setValue(0);
					 Serial.println("Fourth window opened automaticly");
                    }
            if(t<targetTemp && autobutton==LOW && winactivated==LOW && window4==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay8,LOW);                       
                     delay(5000);
                     digitalWrite(relay8,HIGH);                     
					 window4=HIGH;
					 fourthwo.setValue(0);
					 fourthwc.setValue(1);
					 Serial.println("Fourth window closed automaticly");
                    }    
            if(autobutton==LOW && winactivated==HIGH && window4==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay8,LOW);                       
                     delay(5000);
                     digitalWrite(relay8,HIGH);                     
					 window4=HIGH;
					 fourthwo.setValue(0);
					 fourthwc.setValue(1);
					 Serial.println("Fourth window closed automaticly");
                    }
			if(window4==LOW)
			        {
					 fourthwo.setValue(1);
					 fourthwc.setValue(0);
					}
			if(window4==HIGH)
			        {
					 fourthwo.setValue(0);
					 fourthwc.setValue(1);
					}

		//------------------------------------------------------------
                              // Fifth Window 
            if(t>targetTemp && autobutton==LOW && winactivated==LOW && window5==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay9,LOW);                       
                     delay(5000);
                     digitalWrite(relay9, HIGH);               
					 window5=LOW;
                     fifthwo.setValue(1);
                     fifthwc.setValue(0);
					 Serial.println("Fifth window opened automaticly");
					 }
            if(t<targetTemp && autobutton==LOW && winactivated==LOW && window5==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay10,LOW);                       
                     delay(5000);
                     digitalWrite(relay10,HIGH);                     
					 window5=HIGH;
					 fifthwo.setValue(0);
                     fifthwc.setValue(1);
					 Serial.println("Fifth window closed automaticly");
                    }    
            if(autobutton==LOW && winactivated==HIGH && window5==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay10,LOW);                       
                     delay(5000);
                     digitalWrite(relay10,HIGH);                     
					 window5=HIGH;
					 fifthwo.setValue(0);
                     fifthwc.setValue(1);
					 Serial.println("Fifth window closed automaticly");
                    }
			if(window5==LOW)
			        {
					 fifthwo.setValue(1);
                     fifthwc.setValue(0);
					}
		    if(window5==HIGH)
			        {
					 fifthwo.setValue(0);
                     fifthwc.setValue(1);
					}

		//------------------------------------------------------------
        //------------------------------------------------------------
                             // FAN control	
		//------------------------------------------------------------
		                     // first FAN
		    if(h>targetHum && autobutton==LOW && fanactivated==LOW && afan1==HIGH && fan1==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay11,LOW);  
                     afan1=LOW;
					 fan1=LOW;
					 firstfo.setValue(1);
					 firstfc.setValue(0);
					 Serial.println("First FAN opened automaticly");
                     delay(4000);
                    }
            if(h<targetHum && autobutton==LOW && fanactivated==LOW && afan1==LOW && fan1==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay11,HIGH);       
                     afan1=HIGH;
					 fan1=HIGH;
					 firstfo.setValue(0);
					 firstfc.setValue(1);
					 Serial.println("First FAN closed automaticly");
                     delay(4000);
                    }
            if(autobutton==LOW && fanactivated==HIGH && afan1==LOW && fan1==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay11,HIGH);           
                     afan1=HIGH;
					 fan1=HIGH;
					 firstfo.setValue(0);
					 firstfc.setValue(1);
					 Serial.println("First FAN closed automaticly");
                     delay(4000);
                    }
			if(lstatus==LOW && lfan1==HIGH)
			        {
					 digitalWrite(relay11,HIGH);           
                     afan1=HIGH;
					 fan1=HIGH;
					 lfan1=LOW
					 firstfo.setValue(0);
					 firstfc.setValue(1);
					 Serial.println("First FAN closed, line is LOW");
					}
			if(lstatus==HIGH && lfan1==LOW)
			        { 
					 lfan1=HIGH;
					}
			if(fan1==LOW)
			        {
					 firstfo.setValue(1);
					 firstfc.setValue(0);
					}
		    if(fan1==HIGH)
			        {
					 firstfo.setValue(0);
					 firstfc.setValue(1);
					}
		//------------------------------------------------------------
		                     // second FAN
		    if(h>targetHum && autobutton==LOW && fanactivated==LOW && afan2==HIGH  && fan2==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay12,LOW);  
                     afan2=LOW;
					 fan2=LOW;
					 secondfo.setValue(1);
					 secondfc.setValue(0);
					 Serial.println("Second FAN opened automaticly");
                     delay(4000);
                    }
            if(h<targetHum && autobutton==LOW && fanactivated==LOW && afan2==LOW && fan2==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay12,HIGH);       
                     afan2=HIGH;
					 fan2=HIGH;
					 secondfo.setValue(0);
					 secondfc.setValue(1);
					 Serial.println("Second FAN closed automaticly");
                     delay(4000);
                    }
            if(autobutton==LOW && fanactivated==HIGH && afan2==LOW && fan2==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay12,HIGH);           
                     afan2=HIGH;
					 fan2=HIGH;
					 secondfo.setValue(0);
					 secondfc.setValue(1);
					 Serial.println("Second FAN closed automaticly");
                     delay(4000);
                    }
		    if(lstatus==LOW && lfan2==HIGH)
			        {
					 digitalWrite(relay12,HIGH);           
                     afan2=HIGH;
					 fan2=HIGH;
					 lfan2=LOW;
					 secondfo.setValue(0);
					 secondfc.setValue(1);
					 Serial.println("Second FAN closed, line is LOW");
					}
			if(lstatus==HIGH && lfan2==LOW)
			        { 
					 lfan2=HIGH;
					}
            if(fan2==LOW)
			        {
					 secondfo.setValue(1);
					 secondfc.setValue(0);
					}
			if(fan2==HIGH)
			        {
					 secondfo.setValue(0);
					 secondfc.setValue(1);
					}			
		//------------------------------------------------------------
		                     // third FAN
		    if(h>targetHum && autobutton==LOW && fanactivated==LOW && afan3==HIGH && fan3==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay13,LOW);  
                     afan3=LOW;
					 fan3=LOW;
					 thirdfo.setValue(1);
					 thirdfc.setValue(0);
					 Serial.println("Third FAN opened automaticly");
                     delay(4000);
                    }
            if(h<targetHum && autobutton==LOW && fanactivated==LOW && afan3==LOW && fan3==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay13,HIGH);       
                     afan3=HIGH;
					 fan3=HIGH;
					 thirdfo.setValue(0);
					 thirdfc.setValue(1);
					 Serial.println("Third FAN closed automaticly");
                     delay(4000);
                    }
            if(autobutton==LOW && fanactivated==HIGH && afan3==LOW && fan3==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay13,HIGH);           
                     afan3=HIGH;
					 fan3=HIGH;
					 thirdfo.setValue(0);
					 thirdfc.setValue(1);
					 Serial.println("Third FAN closed automaticly");
                     delay(4000);
                    }
			if(lstatus==LOW && lfan3==HIGH)
			        {
					 digitalWrite(relay13,HIGH);           
                     afan3=HIGH;
					 fan3=HIGH;
					 lfan3=LOW
					 thirdfo.setValue(0);
					 thirdfc.setValue(1);
					 Serial.println("Third FAN closed, line is LOW");
					}
			if(lstatus==HIGH && lfan3==LOW)
			        { 
					 lfan3=HIGH;
					}
            if(fan3==LOW)
			        {
					 thirdfo.setValue(1);
					 thirdfc.setValue(0);
					}
			if(fan3==HIGH)
			        {
					 thirdfo.setValue(0);
					 thirdfc.setValue(1);
					}

//------------------------------------------------------------------------------------------------- 
//-------------------------------------------------------------------------------------------------
                    // extrem FAN
		    if(h>targetHum+7 && autobutton==LOW && fanactivated==LOW && afan4==HIGH && fan4==HIGH && lstatus==HIGH)
                    {
                     digitalWrite(relay14,LOW);  
                     afan4=LOW;
					 fan4=LOW;
					 exao.setValue(1);
					 exac.setValue(0);
					 Serial.println("Fourth FAN turned-on due to increased humidity!!!");
                     delay(4000);
                    }
            if(h<targetHum+7 && autobutton==LOW && fanactivated==LOW && afan4==LOW && fan4==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay14,HIGH);       
                     afan4=HIGH;
					 fan4=HIGH;
					 exao.setValue(0);
					 exac.setValue(1);
					 Serial.println("First fan turned-off successfully!!!");
                     delay(4000);
                    }
			if(h<targetHum+7 && autobutton==LOW && fanactivated==LOW && mfan4==LOW && fan4==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay14,HIGH);       
                     mfan4=HIGH;
					 fan4=HIGH;
					 exao.setValue(0);
					 exac.setValue(1);
					 Serial.println("First fan turned-off successfully!!!");
                     delay(4000);
                    }		
            if(autobutton==LOW && fanactivated==HIGH && afan4==LOW && fan4==LOW && lstatus==HIGH)
                    {
                     digitalWrite(relay14,HIGH);           
                     afan4=HIGH;
					 fan4=HIGH;
					 exao.setValue(0);
					 exac.setValue(1);
					 Serial.println("First fan turned-off successfully");
                     delay(4000);
                    }
			if(lstatus==LOW && lfan4==HIGH)
			        {
					 digitalWrite(relay14,HIGH);           
                     afan4=HIGH;
					 fan4=HIGH;
					 lfan4=LOW
					 exao.setValue(0);
					 exac.setValue(1);
					 Serial.println("First fan turned-off, line is LOW");
					}
			if(lstatus==HIGH && lfan4==LOW)
			        { 
					 lfan4=HIGH;
					}
            if(fan4==LOW)
			        {
					 exao.setValue(1);
					 exac.setValue(0);
					}
			if(fan4==HIGH)
			        {
					 exao.setValue(0);
					 exac.setValue(1);
					}
//------------------------------------------------------------------------------------------------- 
//------------------------------------------------------------------------------------------------- 
  nexLoop(nex_listen_list);
}
