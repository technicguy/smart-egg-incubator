#include <Wire.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "DHT.h"

#define DHTPIN 11
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

String menuItems[] = {"Temperature", "Humidity", "Cooling Fan", "Egg Turner", "Hatching Days", "Setting Status", "Live Status", "About Us", "ABOUT"};

int readKey;
int saveTemp = 0;
int saveHum = 0;
int saveFan = 0;
int saveTurn = 0;
int saveHatch = 0;

// Menu control variables
int menuPage = 0;
int maxMenuPages = round(((sizeof(menuItems) / sizeof(String)) / 2) + .5);
int cursorPosition = 0;

// Creates 3 custom characters for the menu display
byte right_Arrow[8]={B01000,B00100,B00010,B00001,B00010,B00100,B01000,B00000};
byte down_Arrow[8] ={B00100,B00100,B00100,B00100,B00100,B10101,B01110,B00100};
byte up_Arrow[8] =  {B00100,B01110,B10101,B00100,B00100,B00100,B00100,B00100};

byte egg_hatch[8] ={B00000,B01110,B11111,B10101,B01010,B11111,B11111,B01110};
byte egg_icon[8] = {B00000,B11001,B01011,B00100,B11010,B10011,B00000,B00000};
byte egg_turn[8] = {B00000,B01110,B10001,B10001,B10101,B10110,B10111,B00000};
byte chicken_icon[8]={B01100,B11100,B01001,B11111,B11111,B11110,B01010,B10010};
byte temp_c[8] =   {B11000,B11000,B00110,B01001,B01000,B01000,B01001,B00110};
byte water_drop[8]={B00100,B01110,B11111,B11111,B11111,B01110,B00000,B00000};
byte out_fan[8] =  {B00000,B11001,B01011,B00100,B11010,B10011,B00000,B00000};


int EEPROMtemp = 0;

LiquidCrystal lcd = LiquidCrystal(8, 9, 4, 5, 6, 7);
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int i = 0;
int j = 0;
int k = 0;

void setup() {

  Serial.begin(9600);
  dht.begin();  
  lcd.clear();
  // Initializes and clears the LCD screen
  lcd.begin(16, 2);
  // Creates the byte for the 3 custom characters 

  lcd.createChar(1,right_Arrow);
  lcd.createChar(2,up_Arrow);
  lcd.createChar(3,down_Arrow);
  
  lcd.createChar(4,egg_hatch);
  lcd.createChar(5,out_fan); 
  lcd.createChar(6,egg_turn);
  lcd.createChar(7,chicken_icon);
  lcd.createChar(8,temp_c);
  lcd.createChar(9,water_drop);
  lcd.createChar(10,egg_icon);

  lcd.clear();
  
}

void loop() {
  delay(500);
   
  int x;
  x = analogRead (0);
 lcd.setCursor(10,1);  
 
  mainMenuDraw();
  drawCursor();
  operateMainMenu();

}
void liveHome(){   
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.println("Humidity: ");
  Serial.print(h);
  Serial.println("%");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C "); 
  
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.write(byte(8));
  
  delay(500);
}
void mainHome() {
 int  saveTemp = EEPROM.read(0);
 int  saveHum = EEPROM.read(1);
 int  saveFan = EEPROM.read(2);
 int  saveTurn = EEPROM.read(3);
 int  saveHatch = EEPROM.read(4);
  
  lcd.setCursor(0,0);
  lcd.print(saveTemp);
  lcd.write(byte(8));
  //lcd.print("*");

  lcd.setCursor(6, 0);
  //lcd.print("H:");
  lcd.print(saveHum);
  lcd.write(byte(9));
   lcd.setCursor(12, 0);
  if(saveFan==0){
    lcd.print(saveTemp+1);
  }else{
    lcd.print(saveFan);
  }
  
  lcd.write(byte(5));

  lcd.setCursor(0, 1);
  lcd.print(saveTurn);
  lcd.write(byte(6));

  lcd.setCursor(6, 1);
  lcd.print(saveHatch);
  lcd.write(byte(7));
  
  lcd.setCursor(12, 1);
  lcd.print(saveHatch);
  lcd.write(byte(4));  
}



// This function will generate the 2 menu items that can fit on the screen. They will change as you scroll through your menu. Up and down arrows will indicate your current menu position.
void mainMenuDraw() {
 lcd.createChar(2,up_Arrow);
  Serial.print(menuPage);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems[menuPage]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems[menuPage + 1]);
  if (menuPage == 0) {
    lcd.setCursor(15, 1);
    lcd.write(byte(3));
  } else if (menuPage > 0 and menuPage < maxMenuPages) {
    lcd.setCursor(15, 1);
    lcd.write(byte(3));
    lcd.setCursor(15, 0);
    lcd.write(byte(2));
  } else if (menuPage == maxMenuPages) {
    lcd.setCursor(15, 0);
    lcd.write(byte(2));
  }
}

// When called, this function will erase the current cursor and redraw it based on the cursorPosition and menuPage variables.
void drawCursor() {

  
  for (int x = 0; x < 2; x++) {     // Erases current cursor
    lcd.setCursor(0, x);
    lcd.print(" ");
    
  }

  // The menu is set up to be progressive (menuPage 0 = Item 1 & Item 2, menuPage 1 = Item 2 & Item 3, menuPage 2 = Item 3 & Item 4), so
  // in order to determine where the cursor should be you need to see if you are at an odd or even menu page and an odd or even cursor position.
  if (menuPage % 2 == 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is even and the cursor position is even that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      //lcd.write(byte(1));
      lcd.print(">");
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is even and the cursor position is odd that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      //lcd.write(byte(1));
      lcd.print(">");
    }
  }
  if (menuPage % 2 != 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is odd and the cursor position is even that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      //lcd.write(byte(1));
      lcd.print(">");
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is odd and the cursor position is odd that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      //lcd.write(byte(1));
      lcd.print(">");
    }
  }
}


void operateMainMenu() {
 
  int activeButton = 0;
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 0: // When button returns as 0 there is no action taken
        break;
      case 1:  // This case will execute if the "forward" button is pressed
        button = 0;
        switch (cursorPosition) { 
          case 0:
            menuItem1();            
            break;
          case 1:
            menuItem2();
            break;
          case 2:
            menuItem3();
            break;
          case 3:
            menuItem4();
            break;
          case 4:
            menuItem5();
            break;
          case 5:
            menuItem6();
            break;
          case 6:
            menuItem7();
            break;
          case 7:
            menuItem8();
            break;
          case 8:
            menuItem9();
            break;   
          case 9:
            menuItem10();
            break;                      
        }
        activeButton = 1;
        mainMenuDraw();
        drawCursor();
        break;
      case 2:
        button = 0;
        if (menuPage == 0) {
          cursorPosition = cursorPosition - 1;
          cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        }
        if (menuPage % 2 == 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        if (menuPage % 2 != 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        cursorPosition = cursorPosition - 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));

        mainMenuDraw();
        drawCursor();
        activeButton = 1;
        break;
      case 3:
        button = 0;
        if (menuPage % 2 == 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        if (menuPage % 2 != 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        cursorPosition = cursorPosition + 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        mainMenuDraw();
        drawCursor();
        activeButton = 1;
        break;
    }
  }

}

// This function is called whenever a button press is evaluated. The LCD shield works by observing a voltage drop across the buttons all hooked up to A0.
int evaluateButton(int x) {
  int result = 0;
  if (x < 50) {
    result = 1; // right
  } else if (x < 195) {
    result = 2; // up
  } else if (x < 380) {
    result = 3; // down
  } else if (x < 790) {
    result = 4; // left
  }else if (x < 850) {
    result = 5; // Select
  }
  return result;
}

// If there are common usage instructions on more than 1 of your menu items you can call this function from the sub
// menus to make things a little more simplified. If you don't have common instructions or verbage on multiple menus
// I would just delete this void. You must also delete the drawInstructions()function calls from your sub menu functions.
void drawInstructions() {
  lcd.createChar(2,up_Arrow);  
  lcd.setCursor(0, 1); // Set cursor to the bottom line
  lcd.print("Use ");
  lcd.write(byte(2)); // Up arrow
  lcd.print("/");
  lcd.write(byte(3)); // Down arrow
  lcd.print(" buttons");
}


void menuItem1() { 
  int activeButton = 0;  
  lcd.clear();
   int  saveTemp = EEPROM.read(0);
  lcd.setCursor(0, 0);
  drawInstructions();
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.print(saveTemp);
  lcd.write(byte(8));
  
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 2:
        button = 0;
        saveTemp = saveTemp + 1;
        saveTemp = constrain(saveTemp,0,50);        
        lcd.setCursor(0,0);
        lcd.print("               ");
        lcd.setCursor(0, 0);
        lcd.print("Temp Up: ");        
        lcd.print(saveTemp);
        lcd.write(byte(8));
        EEPROM.write(0,saveTemp);
        break;
      case 3:
        button = 0;
        saveTemp = saveTemp - 1;
        saveTemp = constrain(saveTemp,0,50);
        lcd.setCursor(0,0);
        lcd.print("               ");
        lcd.setCursor(0, 0);
        lcd.print("Temp Down: ");  
        lcd.print(saveTemp);
        lcd.write(byte(8));
        EEPROM.write(0,saveTemp);
        break;
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;        
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("-- VALUES --");
        lcd.setCursor(2,1);
        lcd.print("-- STORED --");
        delay(1500);
        activeButton = 1;
        break;
    }
    
  }

  
}
void menuItem2() { 
  int activeButton = 0;
  lcd.clear();
   int  saveHum = EEPROM.read(1);
  lcd.setCursor(0, 0);
  drawInstructions();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(saveHum);
  lcd.print("%");
  
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 2:
        button = 0;
        saveHum = saveHum + 1;
        saveHum = constrain(saveHum,0,100);
        lcd.setCursor(0,0);
        lcd.print("               ");
        lcd.setCursor(0, 0);
        lcd.print("Hum Up: ");
        lcd.print(saveHum);
        lcd.print("%");
        EEPROM.write(1,saveHum);
        break;
      case 3:
        button = 0;
        saveHum = saveHum - 1;
        saveHum = constrain(saveHum,0,100);
        lcd.setCursor(0,0);
        lcd.print("               ");
        lcd.setCursor(0, 0);
        lcd.print("Hum Down: ");
        lcd.print(saveHum);
        lcd.print("%");
        EEPROM.write(1,saveHum);
        break;
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("-- VALUES --");
        lcd.setCursor(2,1);
        lcd.print("-- STORED --");
        delay(1500);
        activeButton = 1;
        break;
    }
  }
}
void menuItem3() { 
    
  int activeButton = 0;
  lcd.clear();
   int  saveFan = EEPROM.read(2);
  lcd.setCursor(0, 0);
  drawInstructions();
  lcd.setCursor(0, 0);
  lcd.print("Cooling On: ");
  lcd.print(saveFan);
  lcd.write(byte(5));

  
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 2:
        button = 0;
        saveFan = saveFan + 1;
        saveFan = constrain(saveFan,0,50);
        lcd.setCursor(0,0);
        lcd.print("               ");
        lcd.setCursor(0,0);
        lcd.print("Increase: ");
        lcd.print(saveFan);
        lcd.write(byte(5));
        EEPROM.write(2,saveFan);
        break;
      case 3:
        button = 0;
        saveFan = saveFan - 1;
        saveFan = constrain(saveFan,0,50);
        lcd.setCursor(0,0);
        lcd.print("               ");        
        lcd.setCursor(0,0);
        lcd.print("Decrease: ");
        lcd.print(saveFan);
        lcd.write(byte(5));
        EEPROM.write(2,saveFan);
        break;
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("-- VALUES --");
        lcd.setCursor(2,1);
        lcd.print("-- STORED --");
        delay(1500);
        activeButton = 1;
        break;
    }
  }
}

void menuItem4() { 
  int activeButton = 0;
  lcd.clear();
   int  saveTurn = EEPROM.read(3);
  lcd.setCursor(0, 0);
  drawInstructions();
  lcd.setCursor(0, 0);
  lcd.print("Turn a day:");
  lcd.print(saveTurn);
  lcd.write(byte(6));  
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 2:
        button = 0;
        saveTurn = saveTurn + 1;
        saveTurn = constrain(saveTurn,0,96);
        lcd.setCursor(0,0);
        lcd.print("               ");
        lcd.setCursor(0,0);
        lcd.print("Increase: ");
        lcd.print(saveTurn);
        lcd.write(byte(6));
        break;
      case 3:
        button = 0;
        saveTurn = saveTurn - 1;
        saveTurn = constrain(saveTurn,0,96);
        lcd.setCursor(0,0);
        lcd.print("               ");
        lcd.setCursor(0,0);
        lcd.print("Decrease: ");
        lcd.print(saveTurn);
        lcd.write(byte(6));
        break;
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("-- VALUES --");
        lcd.setCursor(2,1);
        lcd.print("-- STORED --");
        delay(1500);
        activeButton = 1;
        break;
    }
  }
}


void menuItem5() { 
  int activeButton = 0;
  lcd.clear();
   int  saveHatch = EEPROM.read(4);
  lcd.setCursor(0, 0);
  drawInstructions();
  lcd.setCursor(0, 0);
  lcd.print("Hatch:");    
  lcd.print(saveHatch);
  lcd.write(byte(7));
  lcd.print(" days");
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 2:
        button = 0;
        saveHatch = saveHatch + 1;
        saveHatch = constrain(saveHatch,0,96);
        lcd.setCursor(0,0);
        lcd.print("               ");
        lcd.setCursor(0,0);
        lcd.print("Increase: ");
        lcd.print(saveHatch);
        lcd.write(byte(7));
        break;
      case 3:
        button = 0;
        saveHatch = saveHatch - 1;
        saveHatch = constrain(saveHatch,0,96);
        lcd.setCursor(0,0);
        lcd.print("               ");
        lcd.setCursor(0,0);
        lcd.print("Decrease: ");
        lcd.print(saveHatch);
        lcd.write(byte(7));
        break;
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("-- VALUES --");
        lcd.setCursor(2,1);
        lcd.print("-- STORED --");
        delay(1500);
        activeButton = 1;
        break;
    }
  }
}

void menuItem6() { // Function executes when you select the 6th item from main menu
  int activeButton = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  mainHome();

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void menuItem7() { 
  int activeButton = 0;
  delay(100);
  liveHome();
  
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4: 
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void menuItem8() { // Function executes when you select the 8th item from main menu
  int activeButton = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IOT Incubator");
  lcd.setCursor(0, 1);
  lcd.print("eSanshar IT Experts");
  
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void menuItem9() { // Function executes when you select the 9th item from main menu
  int activeButton = 0;

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sub Menu 9");

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void menuItem10() { // Function executes when you select the 10th item from main menu
  int activeButton = 0;

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sub Menu 10");

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        break;
    }
  }
}
