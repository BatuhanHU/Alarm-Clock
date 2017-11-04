#include <DS1302.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,10,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'D', 'C', 'B', 'A'}, 
{'#', '9', '6', '3'}, 
{'0', '8', '5', '2'},
{'*', '7', '4', '1'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {13,12,11,10}; //Rows 0 to 3
byte colPins[numCols]= {9,8,7,6}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);


// Init the DS1302
DS1302 rtc(2, 3, 4);

// Init a Time-data structure
Time t;

int alarm_saat = 21;
int alarm_dakika = 15;

void setup()
{
    lcd.init();                      // initialize the lcd 
    pinMode(5, OUTPUT);
 // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.clear();
}

void loop()
{
  char keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY){
    if(keypressed == '1'){
      alarm_saat++;
      if(alarm_saat > 23) alarm_saat = 0;
    }
    if(keypressed == '2'){
      alarm_saat--;
      if(alarm_saat < 0) alarm_saat = 23;
    }
    if(keypressed == '4'){
      alarm_dakika++;
      if(alarm_dakika > 59) alarm_dakika = 0;
    }
    if(keypressed == '5'){
      alarm_dakika--;
      if(alarm_dakika < 0) alarm_dakika = 23;
    }
    Serial.print(keypressed);
  }
  // Get data from the DS1302
  t = rtc.getTime();
  //digitalWrite(7, HIGH);
  
  if(t.hour == alarm_saat && t.min == alarm_dakika && t.sec < 15){
    if(t.sec != 1 && t.sec != 3 && t.sec != 5 && t.sec != 7 && t.sec != 9 && t.sec != 11 && t.sec != 13 && t.sec != 15)digitalWrite(5, HIGH);
    else digitalWrite(5, LOW);
  }
  else digitalWrite(5, LOW);
  
  lcd.clear();
  lcd.print("Saat ");
  if(t.hour < 10) lcd.print("0");
  lcd.print(t.hour, DEC);
  lcd.print(":");
  if(t.min < 10) lcd.print("0");
  lcd.print(t.min, DEC);
  lcd.print(":");
  if(t.sec < 10) lcd.print("0");
  lcd.print(t.sec, DEC);
  
  lcd.setCursor(0,1);
  lcd.print("Alarm ");
  if(alarm_saat < 10) lcd.print("0");
  lcd.print(alarm_saat, DEC);
  lcd.print(":");
  if(alarm_dakika < 10) lcd.print("0");
  lcd.print(alarm_dakika, DEC);
  lcd.print(":00");
  
  // Wait one second before repeating :)
  delay (100);
}
