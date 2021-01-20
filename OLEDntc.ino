//Include library 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 

#define OLED_RESET -1 

Adafruit_SSD1306 display(OLED_RESET); 

//NTC set up
int ThermistorPin = 0;
int Vo;

void setup() { 
    
    //Initialize display by providing the display type and its I2C address. 
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
    
    //Set the text color. 
    display.setTextColor(SSD1306_WHITE); 
} 

void loop() { 

    //Temp calculations
    Vo = analogRead(ThermistorPin);

    //Opening screen
    display.setTextSize(1);
    display.display();
    delay(5000);

    //Display Celsisus Temp
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Current Temp - C");
    display.setTextSize(2);
    display.setCursor(12,10);
    display.print(getCelsius(readThermistor((float)Vo), -3.0));
    display.display();

    delay(5000);

    //Display Fahrenheit Temp
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Current Temp - F");
    display.setTextSize(2);
    display.setCursor(12,10);
    display.print(getFahrenheit(readThermistor((float)Vo), -6.0));
    display.display();
    
    delay(5000);
    Vo = 0;
} 


//Function to Return a Raw Thermistor/temperature value
float readThermistor(float VoltIn){

    float R1 = 10000;
    float R2;
    float logR2;
    float T;
    float c1 = 1.009249522e-03;
    float c2 = 2.378405444e-04;
    float c3 = 2.019202697e-07;

    R2 = R1 * (1023.0 / VoltIn - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    return T;
}

//Function to convert Raw temp value to Celsius, with calibration value
float getCelsius(float RawT, float cal){

    float celsius;
    celsius = RawT - 273.15 + cal;
    return celsius;
}

//Function to convert Raw temp value to Fahrenheit, with calibration value
float getFahrenheit(float RawT, float cal){

    float celsius = getCelsius(RawT, 0.0);
    float fahrenheit = celsius * ( 9.0/ 5.0 ) + 32.0 + cal;
    return fahrenheit;

}