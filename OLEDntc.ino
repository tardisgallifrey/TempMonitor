//Include library 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 

#define OLED_RESET -1 

Adafruit_SSD1306 display(OLED_RESET); 

//NTC set up
int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


void setup() { 
    
    //Initialize display by providing the display type and its I2C address. 
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
    
    //Set the text size and color. 
    display.setTextSize(1); 
    display.setTextColor(SSD1306_WHITE); 
} 

void loop() { 


    //Temp calculations
    Vo = analogRead(ThermistorPin);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    Tc = T - 273.15 - 8.00;                //Celsius
    Tf = (Tc * 9.0)/ 5.0 + 32.0;           //Fahrenheit


    //Clear previous image. 
    display.clearDisplay(); 
    display.setCursor(0, 0); 
    display.print("Current Temperature");
    display.setTextSize(2);
    display.setCursor(10, 10);
    display.print(Tf);
    display.setTextSize(1);     //set back to size 1 for header line.
    
    //Display changes if any were made. 
    display.display(); 
    
    delay(5000);
} 