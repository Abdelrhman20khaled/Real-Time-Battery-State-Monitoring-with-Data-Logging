#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <MAX6675.h>
#include <HardwareSerial.h>
#include <Preferences.h>

// I2C Pins SDA and SCL
#define I2C_SDA_Pin           21
#define I2C_SCL_Pin           22
#define EEPROM_I2C_Address    0x50
#define RTC_I2C_Address       0x68

// Charging Plug Pin
#define Plug_Pin              32

// UART2 Pins
#define UART1_RX_Pin          17
#define UART1_TX_Pin          18

// Voltage and Current Sensor ADC Pins
#define VoltageSensor_Pin     35
#define CurrentSensor_Pin     34

// Temperature Sensor SPI Pins (MAX6675)
#define TemperatureSensor_MISO_Pin  19
#define TemperatureSensor_SCK_Pin   5
#define TemperatureSensor_CS_Pin    16

RTC_DS3231 rtc;
MAX6675 tempSensor(TemperatureSensor_CS_Pin, TemperatureSensor_MISO_Pin, TemperatureSensor_SCK_Pin); 
Preferences preferences;

int Cycle_Count = 0;
bool lastState = LOW;

int lastDebounceTime = 0;
int debounceDelay = 50;
float battery_temperature = 0;
float battery_voltage = 0;
float adjustedVoltage = 0;
float current = 0;


void getPlugState() 
{
  bool currentState = digitalRead(Plug_Pin);

  if (currentState != lastState) 
  {
    delay(50);  // Simple debounce
    currentState = digitalRead(Plug_Pin); 

    if (currentState != lastState) 
    {
      if (currentState == HIGH) 
      {
        Cycle_Count++;
      } 
      else 
      {
        //DO NO THING
      }

      lastState = currentState;  // Update state
    }
  }
  Serial.print("Number of Charging Cycles: ");
  Serial.print(Cycle_Count);
  Serial.println(" Cycle/s");
  
}




void getBatteryVoltage() 
{
  float ADC_vRead = analogRead(VoltageSensor_Pin);
  battery_voltage = (ADC_vRead / 4095.0) * 3.3;
  Serial.print("Battery Voltage Now: ");
  Serial.print(battery_voltage);
  Serial.println(" V");
}

void getBatteryCurrent() 
{
  int adcRaw = analogRead(CurrentSensor_Pin);
  float voltage = 1.66; //(adcRaw / 4095.0) * 3.3;

  // Adjust offset and sensitivity (for 3.3V-powered ACS712-05A)
  float offsetVoltage = 1.65; // Sensor outputs 1.65V at 0 A
  adjustedVoltage = voltage - offsetVoltage;

  // Clamp to 0V minimum
  if (adjustedVoltage < 0)
  {
    adjustedVoltage = 0;
  }

  current = adjustedVoltage / 0.185;

  // Clamp max to 5 A
  if (current > 5.0)
  {
    current = 5.0;
  } 
  else
  {
    //DO NO THING
  }

  Serial.print("Battery Current Now: ");
  Serial.print(current);
  Serial.println(" A");
}

void getBatteryTemperature() 
{
  float battery_states = tempSensor.read();
  battery_temperature  = tempSensor.getCelsius();
  Serial.print("Battery Temperature Now: ");
  Serial.print(battery_temperature);
  Serial.println(" C");
}

void setup()
{
  //Serial.begin(9600);
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, UART1_RX_Pin, UART1_TX_Pin);
  Wire.begin(I2C_SDA_Pin, I2C_SCL_Pin);
  analogReadResolution(12);

  if (!rtc.begin()) {
    //Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    //Serial.println("RTC lost power, setting time to compile time");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  tempSensor.begin();

  pinMode(Plug_Pin, INPUT_PULLDOWN);
  digitalWrite(Plug_Pin, LOW);

  /* 
     Open preferences with a namespace Cycle_Count
     false = read/write mode
  */
  //preferences.begin("Cycle_Count", false); // 
  //it's safe to read from flash
  //Cycle_Count = preferences.getInt("Cycle_Count", 0);

  delay(500); // Give MAX6675 time to stabilize
}

void loop() 
{
  Serial.println("==================== System Budget ======================");
  getPlugState();
  getBatteryTemperature();
  getBatteryVoltage();
  getBatteryCurrent();
  Serial.println("---------------------------------------------------------");
  Serial1.println(String(Cycle_Count));
  Serial1.println(String(battery_voltage));
  Serial1.print(String(current));

  
  delay(5000); // 5 second interval

}
