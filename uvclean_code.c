#define CLK 3
#define DT 4
#define SW 5
#define BUZZ 6
#define BULB 2
int counter = 0;
int state;
int Laststate;
int menuID = 1;
int menuChange = 0;
int buttonPress = 0;
int toneID;
int passwordTemp = 0;
int passwordID = 1;
int password1 = 0;
int password2 = 0;
int password3 = 0;
int password4 = 0;
int access = 0;
int leave = 0;
int minutes = 0;
int seconds10 = 0;
int seconds1 = 0;
unsigned long startMillis;

void tone1();
void tone2();
void tone3();
void tone4();
void tone5();



#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);




void setup() {
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW,INPUT);
  pinMode(BULB, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  Serial.begin(9600);
  
  Laststate = digitalRead(CLK);

  digitalWrite(BULB, LOW);
  Serial.print("BULB OFF");





    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();

    display.clearDisplay();

  for(int16_t i=0; i<max(display.width(),display.height())*1.3; i+=10) {
    display.drawTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, SSD1306_WHITE);
      display.setTextSize(3);
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      display.setCursor(2,16);
      display.print(F("UVClean"));
    display.display();
    delay(1);
    tone(BUZZ, 128*(i/10));
  }
  noTone(BUZZ);
  
  tone(BUZZ, 1024);
  delay(50);
  //noTone(BUZZ);
  //delay(10);
  tone(BUZZ, 2048);
  delay(50);
  tone(BUZZ, 4096);
  delay(50);
  noTone(BUZZ);
  delay(2500);
  
  
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("DISARMED"));
        display.setTextSize(1);
        display.println(F("Enter passcode:"));
        display.println(F(""));
        display.setTextSize(3);
        display.print(passwordTemp);
        display.println(F(" _ _ _"));
        display.display();

  while(access == 0) {
  state = digitalRead(CLK);
  if(state != Laststate)
  {
    if(digitalRead(DT) != state)
    {
      counter++;
      }
      else
      {
        counter--;
        }
  
         //Serial.println(counter);
  }
    
    Laststate= state;

    if(counter == 4) {
      counter = 0;
      menuChange = 1;
      passwordTemp++;
      toneID = 1;
    }

    if(counter == -4) {
      counter = 0;
      menuChange = 1;
      passwordTemp--;
      toneID = 1;
    }
    if(digitalRead(SW) != 1) {
      toneID = 2;
      menuChange = 1;
      switch(passwordID) {      //PASSCODE CHANGE AREA***************************
        case 1:
        if(passwordTemp == 3) { //Enter desired first digit
          password1 = 1;
        }
        break;
        case 2:
        if(passwordTemp == 3) { //enter desired second digit
          password2 = 1;
        }
        break;
        case 3:
        if(passwordTemp == 9) { //enter desired third digit
          password3 = 1;
        }
        break;
        case 4:
        if(passwordTemp == 9) { //enter desired fourth digit
          password4 = 1;
        }//                     *************************************************
        break;
      }
      passwordID++;
      passwordTemp = 0;
      delay(250);
    }

    if(passwordTemp == 10) {
      passwordTemp = 0;
    }

    if(passwordTemp == -1) {
      passwordTemp = 9;
    }

      if(menuChange == 1) {
      switch(passwordID) {
        case 1:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("DISARMED"));
        display.setTextSize(1);
        display.println(F("Enter passcode:"));
        display.println(F(""));
        display.setTextSize(3);
        display.print(passwordTemp);
        display.println(F(" _ _ _"));
        display.display();
        break;
        case 2:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("DISARMED"));
        display.setTextSize(1);
        display.println(F("Enter passcode:"));
        display.println(F(""));
        display.setTextSize(3);
        display.print(F("* "));
        display.print(passwordTemp);
        display.println(F(" _ _"));
        display.display();
        break;
        case 3:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("DISARMED"));
        display.setTextSize(1);
        display.println(F("Enter passcode:"));
        display.println(F(""));
        display.setTextSize(3);
        display.print(F("* * "));
        display.print(passwordTemp);
        display.println(F(" _"));
        display.display();

        break;
        case 4:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("DISARMED"));
        display.setTextSize(1);
        display.println(F("Enter passcode:"));
        display.println(F(""));
        display.setTextSize(3);
        display.print(F("* * * "));
        display.println(passwordTemp);
        display.display();

        break;
      }
        switch(toneID) {
        case 1:
        tone1();
        break;
        case 2:
        tone2();
        break;
        case 3:
        tone3();
        break;
      }
      menuChange = 0;
      }
      if(passwordID == 5) {
        if(password1 == 1 && password2 == 1 && password3 == 1 && password4 == 1) {
          access = 1;
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("ARMED"));
        display.setTextSize(1);
        display.println(F("Access granted"));
        display.println(F(""));
        display.setTextSize(3);
        display.println(F("* * * *"));
        display.display();
        tone4();
        delay(1000);
        }
        else {
          access = 0;
          passwordID = 1;
          passwordTemp = 0;
          password1 = 0;
          password2 = 0;
          password3 = 0;
          password4 = 0;
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("DISARMED"));
        display.setTextSize(1);
        display.println(F("Access denied"));
        display.println(F(""));
        display.setTextSize(3);
        display.println(F("* * * *"));
        display.display();
        tone5();
        delay(1000);
        
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(0,0);             // Start at top-left corner
        display.println(F("DISARMED"));
        display.setTextSize(1);
        display.println(F("Enter passcode:"));
        display.println(F(""));
        display.setTextSize(3);
        display.print(passwordTemp);
        display.println(F(" _ _ _"));
        display.display();
        }
      }
    }
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F(" MAIN MENU"));
  display.setTextSize(1);
  display.println(F(""));
  display.println(F(">Handheld Mode"));
  display.println(F(""));
  display.println(F(" Auto Mode"));
  display.println(F(""));
  display.println(F(" Safety Info"));
              
  display.display();  
  }

void loop() {
  state = digitalRead(CLK);
  if(state != Laststate)
  {
    if(digitalRead(DT) != state)
    {
      counter++;
      }
      else
      {
        counter--;
        }
  
         //Serial.println(counter);
  }
  
  if(digitalRead(SW) != 1)
  {
    counter=0;
    //Serial.println(counter);
    
    }
    
    Laststate= state;

    if(counter == 4) {
      counter = 0;
      menuID++;
      menuChange = 1;
      toneID = 1;
    }

    if(counter == -4) {
      counter = 0;
      menuID--;
      menuChange = 1;
      toneID = 1;
    }

    if(digitalRead(SW) != 1) {
      menuChange = 1;
      toneID = 2;
      switch(menuID) {
        case 1:
        menuID = 11;
        break;
        case 2:
        menuID = 21;
        break;
        case 3:
        menuID = 31;
        break;
        case 11:
        toneID = 3;
        menuID = 101;
        break;
        case 12:
        menuID = 1;
        break;
        case 21:
        menuID = 201;
        break;
        case 22:
        menuID = 2;
        break;
        case 31:
        menuID = 3;
        break;
      }
      delay(250);
    }

    if(menuID == 0 || menuID == 4 || menuID == 10 || menuID == 13 || menuID == 20 || menuID == 23 || menuID == 30 || menuID == 32) {
      switch(menuID) {
        case 0:
        menuID = 3;
        break;
        case 4:
        menuID = 1;
        break;
        case 10:
        menuID = 12;
        break;
        case 13:
        menuID = 11;
        break;
        case 20:
        menuID = 22;
        break;
        case 23:
        menuID = 21;
        break;
        case 30:
        menuID = 31;
        break;
        case 32:
        menuID = 31;
        break;
      }
      menuChange = 1;
    }
    
    if(menuChange == 1) {
      switch(menuID) {
        case 1:
        menu1();
        menuChange = 0;
        break;
        case 2:
        menu2();
        menuChange = 0;
        break;
        case 3:
        menu3();
        menuChange = 0;
        break;
        case 11:
        menu11();
        menuChange = 0;
        break;
        case 101:
        digitalWrite(BULB, HIGH);
        Serial.println("BULB ON");
        tone3();
        while(leave == 0) {
          menu101();
          startMillis = millis();
          while(millis() <= startMillis + 500 && leave == 0) {
            if(digitalRead(SW) != 1) {
              leave = 1;
            }
          }
          menu102();
          startMillis = millis();
          while(millis() <= startMillis + 500 && leave == 0) {
            if(digitalRead(SW) != 1) {
              leave = 1;
            }
          }
          menu103();
          startMillis = millis();
          while(millis() <= startMillis + 500 && leave == 0) {
            if(digitalRead(SW) != 1) {
              leave = 1;
            }
          }
          menu104();
          startMillis = millis();
          while(millis() <= startMillis + 500 && leave == 0) {
            if(digitalRead(SW) != 1) {
              leave = 1;
            }
          }
        }
        digitalWrite(BULB, LOW);
        Serial.println("BULB OFF");
        leave = 0;
        menuID = 11;
        menuChange = 1;
        toneID = 5;
        break;
        case 12:
        menu12();
        menuChange = 0;
        break;
        case 21:
        menu21();
        menuChange = 0;
        break;
        case 201:
        minutes = 2;
        seconds10 = 0;
        seconds1 = 0;
        tone3();
        digitalWrite(BULB, HIGH);
        Serial.println("BULB ON");
        while(leave == 0) {
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(0,0);
          display.println(F("CAUTION:"));
          display.setTextSize(1);
          display.println(F("UVC irradiation in   progress"));
          display.setCursor(0,34);
          display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
          display.println(F("    TIME REMAINING:  "));
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(14,43);
          display.setTextSize(3);
          display.print(F(" "));
          display.print(minutes);
          display.print(F(":"));
          display.print(seconds10);
          display.print(seconds1);

          display.display();

          if(minutes == 0 && seconds10 == 0 && seconds1 == 0) {
            toneID = 4;
            leave = 1;
          }
          
          if(seconds1 == 0) {
            seconds1 = 9;
            seconds10--;
          }
          else {
            seconds1--;
          }
          
          if(seconds10 == -1) {
            seconds10 = 5;
            minutes--;
          }
          
          
          startMillis = millis();
          while(millis() <= startMillis + 1000 && leave == 0) {
            if(digitalRead(SW) != 1) {
              leave = 1;
              toneID = 5;
            }
          }  
        }
        digitalWrite(BULB, LOW);
        Serial.println("BULB OFF");
        leave = 0;
        menuID = 21;
        menuChange = 1;
        break;
        case 22:
        menu22();
        menuChange = 0;
        break;
        case 31:
        menu31();
        menuChange = 0;
        break;
      }

      switch(toneID) {
        case 1:
        tone1();
        break;
        case 2:
        tone2();
        break;
        case 3:
        tone3();
        break;
        case 4:
        tone4();
        toneID = 15;
        break;
        case 5:
        tone5();
        delay(250);
        toneID = 15;
        break;
        case 15:
        noTone(BUZZ);
        break;
      }
    }

    
}

void menu1() {
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F(" MAIN MENU"));
  display.setTextSize(1);
  display.println(F(""));
  display.println(F(">Handheld Mode"));
  display.println(F(""));
  display.println(F(" Auto Mode"));
  display.println(F(""));
  display.println(F(" Safety Info"));
              
  display.display();  
}

void menu2() {
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F(" MAIN MENU"));
  display.setTextSize(1);
  display.println(F(""));
  display.println(F(" Handheld Mode"));
  display.println(F(""));
  display.println(F(">Auto Mode"));
  display.println(F(""));
  display.println(F(" Safety Info"));
              
  display.display();  
}

void menu3() {
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F(" MAIN MENU"));
  display.setTextSize(1);
  display.println(F(""));
  display.println(F(" Handheld Mode"));
  display.println(F(""));
  display.println(F(" Auto Mode"));
  display.println(F(""));
  display.println(F(">Safety Info"));
              
  display.display();  
}

void menu11() {
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("HANDHELD"));
  display.setTextSize(1);
  display.println(F("Press button to      turn the UVC lamp    ON/OFF"));
  display.println(F(""));
  display.setTextSize(2);
  //display.println(F(""));
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.print(F("START"));
  display.setTextColor(SSD1306_WHITE);
  display.println(F(" EXIT"));
  
  
  /*
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(F("OFF"));
  display.setTextColor(SSD1306_WHITE);
  display.println(F("ON"));  
   */           
  display.display();  
}

void menu12() {
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("HANDHELD"));
  display.setTextSize(1);
  display.println(F("Press button to      turn the UVC lamp    ON/OFF"));
  display.println(F(""));
  display.setTextSize(2);
  //display.println(F(""));
  display.print(F("START "));
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.println(F("EXIT")); 
              
  display.display();
}

void menu21() {
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("AUTO"));
  display.setTextSize(1);
  display.println(F("Press button to beginautomatic sterilizat-ion process"));
  display.println(F(""));
  display.setTextSize(2);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.print(F("START"));
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.print(F(" EXIT"));
             
  display.display();  
}

void menu22() {
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("AUTO"));
  display.setTextSize(1);
  display.println(F("Press button to beginautomatic sterilizat-ion process"));
  display.println(F(""));
  display.setTextSize(2);
  display.print(F("START "));
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.print(F("EXIT"));
             
  display.display();  
}

void menu31() {
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("SAFETY"));
  display.setTextSize(1);
  display.println(F("This device emits UVCradiation (wavelength100-280nm) UV skin   and eye protection   must always be worn  during operation."));
              
  display.display();  
}

void menu101() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("CAUTION:"));
  display.setTextSize(1);
  display.println(F("UVC irradiation in   progress"));
  display.setTextSize(2);
  display.println(F(""));
  display.print(F("   "));
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(F("STOP"));

  display.display();
}

void menu102() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("CAUTION:"));
  display.setTextSize(1);
  display.println(F("UVC irradiation in   progress."));
  display.setTextSize(2);
  display.println(F(""));
  display.print(F("   "));
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(F("STOP"));

  display.display();
}

void menu103() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("CAUTION:"));
  display.setTextSize(1);
  display.println(F("UVC irradiation in   progress.."));
  display.setTextSize(2);
  display.println(F(""));
  display.print(F("   "));
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(F("STOP"));

  display.display();
}

void menu104() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("CAUTION:"));
  display.setTextSize(1);
  display.println(F("UVC irradiation in   progress..."));
  display.setTextSize(2);
  display.println(F(""));
  display.print(F("   "));
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(F("STOP"));

  display.display();
}

void tone1() {
  tone(BUZZ, 512);
  delay(25);
  noTone(BUZZ);
}

void tone2() {
  tone(BUZZ, 880);
  delay(25);
  noTone(BUZZ);
}

void tone3() {
  for(int i = 0; i <= 10; i++) {
    //tone(BUZZ, 1760);
    tone(BUZZ, 2048);
    delay(10);
    tone(BUZZ, 1024);
    delay(10);
  }
  noTone(BUZZ);  
}

void tone4() {
  for(int i = 0; i <= 3; i++) {
    tone(BUZZ, 2048);
    delay(25);
    noTone(BUZZ);
    delay(25);
  }  
}

void tone5() {
  tone(BUZZ, 247);
  delay(50);
  noTone(BUZZ);
  delay(25);
  tone(BUZZ, 247);
  delay(100);
  noTone(BUZZ);
}
  
