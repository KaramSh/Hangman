#include<LiquidCrystal.h>
#define SERVO_PIN 11
LiquidCrystal lcd (7,6,5,4,3,2); //RS, E, D4, D5, D6, D7

//char Letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

 char Letters2[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int Letter_Changer = 0;
int Letter_Changer2 = 0;
int Joystick_Btn = 13;
int Joystick_Btn2 = 12;
//int JoyStick_X1 = A1;
//int JoyStick_Y1 = A2;
int JoyStick_X2 = A3;
int JoyStick_Y2 = A4;

char guesses [250] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };

int arrayCounter = 0;
int guessNum = 0;
int lives = 6;
int correct = 0;
String phrase = "BARBB";
String phrase2 = "BBBA";
String phrase3 = "Work Please";
int k = 0;
int L = 9;
int H = 1;
int ServoCnt = 0;
int ServoCnt2 = 1;

int lenMicroSecondsOfPeriod = 20 * 1000; // 25 milliseconds (ms)
int lenMicroSecondsOfPulse = 1 * 1000; // 1 ms is 0 degrees
int first = 0.7 * 1000; //0.5ms is 0 degrees in HS-422 servo
int end = 3.7 * 1000;
int increment = 0.01 * 1000;
int current = 0;

unsigned long seed = 0;
char Display [250] = {'_',  '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'};
int currLvl = 1;

const String Lvl_One_WordBank [21] = {" ", "BAR", "MOW", "MOR", "FIE", "YAG", "DAP", "ORF", "SAL", "REV", "HOD", "ALT", "TAW", "ERE",
                                "NEF", "OBI", "NEB", "KEB", "ALB", "LUX", "BIS"};


const char* Lvl_Two_WordBank [21] = {" ", "DEME", "DAZE", "SEAH", "JILL", "ZION", "SCOT", "YERN", "BAWD", "CAKE", "AIRY", "SPET", 
                               "BIAS", "JOUK", "HALE", "DRAG", "BANC", "STOR", "ROCK", "RHOB", "YOLL"};

const char* Lvl_Three_WordBank [21] = {" ", "RETCH", "SPONG", "APAIR", "PALPI", "QUAIL", "SLICH", "WHELP", "BOSOM", "ALGOW", "GOUTY",
                                  "TITHE", "BUSBY", "URITH", "SHORE", "DIKER", "BASSO", "OILER", "CATER", "HINNY", "EDEMA"};

byte Heart[8] = {  0b00000,
                   0b01010,
                   0b11111,
                   0b11111,
                   0b01110,
                   0b00100,
                   0b00000,
                   0b00000 };

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);

} task;


int delay_gcd;
const unsigned short tasksNum = 3; // Remember to change this as your testing each SM
task tasks[tasksNum];


// ********************************************* Button Reader *********************************************
/*int Button_Reader(int x) {
  if (x == 0 && digitalRead(x) == HIGH) {
    	return 1;
  }
      else if (x == 13 && digitalRead(x) == LOW) {
        return 1;
      }
      else {
        return 0;
      }
}

*/

int Button_Reader2(int x) {
  if (x == 0 && digitalRead(x) == HIGH) {
    	return 1;
  }
      else if (x == 12 && digitalRead(x) == LOW) {
        return 1;
      }
      else {
        return 0;
      }
}

// ********************************************* correctness *********************************************
int correctness (char guess)
{
  //Check if phrase contains char

  if (currLvl == 1) {  
      for (int i = 0; i < 250; i ++) {
        if (guess == guesses[i])//If previously entered
        {
          return 0;
        }
      }
          
      for (int i = 0; i < phrase.length(); i ++) { 
        if (phrase.charAt(i) == guess)//If correct
        {
          if (lives < 6) {
            ++lives;
          }

          guessNum ++;
          guesses [guessNum-1] = guess;
          return 1;
        }
      }

      //If not correct
      lives --;
      guessNum ++;
      guesses [guessNum-1] = guess;
      Serial.println("WE ARE GOOD");
      
      return -1;
  }

  else if (currLvl == 2) { 
        for (int i = 0; i < 250; i ++) {
          if (guess == guesses[i])//If previously entered
          {
            return 0;
          }
        }
            
        for (int i = 0; i < phrase2.length(); i ++) { 
          if (phrase2.charAt(i) == guess)//If correct
          {
            if (lives < 6) {
              ++lives;
            }

            guessNum ++;
            guesses [guessNum-1] = guess;
            return 1;
          }
        }

        //If not correct
        lives --;
        guessNum ++;
        guesses [guessNum-1] = guess;
        Serial.println("WE ARE GOOD");
        
        return -1;
    }

    else if (currLvl == 3) { 
        for (int i = 0; i < 250; i ++) {
          if (guess == guesses[i])//If previously entered
          {
            return 0;
          }
        }
            
        for (int i = 0; i < phrase3.length(); i ++) { 
          if (phrase3.charAt(i) == guess)//If correct
          {
            if (lives < 6) {
              ++lives;
            }

            guessNum ++;
            guesses [guessNum-1] = guess;
            return 1;
          }
        }

        //If not correct
        lives --;
        guessNum ++;
        guesses [guessNum-1] = guess;
        Serial.println("WE ARE GOOD");
        
        return -1;
    }

  
}

// ********************************************* updateScreen *********************************************
void updateScreen (int code)
{  
  if (currLvl == 1) {
        if (code == 0)//Repeat of a character
        {
          for (int i = 0; i < 3; i ++)
          {
            lcd.setCursor(0,0);
            lcd.print("    REPEAT    ");
            delay(200);
            lcd.setCursor(0,0);
            lcd.print("              ");
            delay(200);
          }
          
        }
        
        else if (code == 1)//Correct character
        {
          for (int i = 0; i < phrase.length(); i ++)
          {
            if (phrase.charAt(i) == guesses [guessNum-1])
            {
              correct ++;
              Display[i] = guesses [guessNum-1];
              lcd.setCursor(0, 1); 

              for (int i = 0; i < phrase.length(); i++) {
                  lcd.print(Display[i]);
              }       

            }
          }
          
        }

        else if (code == -1)//Incorrect character
        {
          Serial.println("WRONGGG");
        
        }
    }

    else if (currLvl == 2) {
        if (code == 0)//Repeat of a character
        {
          for (int i = 0; i < 3; i ++)
          {
            lcd.setCursor(0,0);
            lcd.print("    REPEAT    ");
            delay(200);
            lcd.setCursor(0,0);
            lcd.print("              ");
            delay(200);
          }
          
        }
        
        else if (code == 1)//Correct character
        {
          for (int i = 0; i < phrase2.length(); i ++)
          {
            if (phrase2.charAt(i) == guesses [guessNum-1])
            {
              correct ++;
              Display[i] = guesses [guessNum-1];
              lcd.setCursor(0, 1); 

              for (int i = 0; i < phrase2.length(); i++) {
                  lcd.print(Display[i]);
              }       

            }
          }
          
        }

        else if (code == -1)//Incorrect character
        {
          Serial.println("WRONGGG");
        
        }
    }

    else if (currLvl == 3) {
        if (code == 0)//Repeat of a character
        {
          for (int i = 0; i < 3; i ++)
          {
            lcd.setCursor(0,0);
            lcd.print("    REPEAT    ");
            delay(200);
            lcd.setCursor(0,0);
            lcd.print("              ");
            delay(200);
          }
          
        }
        
        else if (code == 1)//Correct character
        {
          for (int i = 0; i < phrase3.length(); i ++)
          {
            if (phrase3.charAt(i) == guesses [guessNum-1])
            {
              correct ++;
              Display[i] = guesses [guessNum-1];
              lcd.setCursor(0, 1); 

              for (int i = 0; i < phrase3.length(); i++) {
                  lcd.print(Display[i]);
              }       

            }
          }
          
        }

        else if (code == -1)//Incorrect character
        {
          Serial.println("WRONGGG");
        
        }
    }


}

// ********************************************* Rand Function *********************************************
int impRandom() {

          const unsigned long a = 16807;
          const unsigned long m = 21474893647;
          const unsigned long q = 127773;
          const double r = 2836.0;
          double test, lo;
          int hi;
          hi = seed / (double)q;
          lo = seed - (double)q * (double)hi;
          test = (double)a*lo - r*(double)hi;
          if (test > 0.0) {
            seed = test;
          }
          else {
            seed = test + (double)m;
          }
          int out = seed / m;
          return out;
}
      

          


int set() {

        int Number = impRandom() % 20 + 1;

        if ( Number < 0) {
            Serial.println("This was negative");
            Serial.println(Number);
            return Number * -1;
        }

        else if (Number > 0) {
            Serial.println("This was pos");
            Serial.println(Number);
            return Number; //1-16
        }
}


// ********************************************* Screen.  Function *********************************************

void Screen() {              
                if (currLvl == 1) {     
                    lcd.clear(); // Change player one to "120bMan"
                    lcd.setCursor(0, 0);
                    lcd.print("P1<");
                    lcd.print(Letters2[Letter_Changer2]);
                    lcd.print(">");
                    lcd.print("      ");  
                    lcd.print("120B!");       
                    //lcd.print("P2<");
                    //lcd.print(Letters2[Letter_Changer2]);
                    //lcd.print(">");
                    lcd.setCursor(13, 16);
                    lcd.print("");
                    lcd.print(lives);
                    lcd.print("");
                    lcd.setCursor(7, 0);
                    lcd.print("L");
                    lcd.print(currLvl);
                    lcd.print("");

                    lcd.setCursor(0, 1);

                  
                    for (int i = 0; i < phrase.length(); i++) {
                        lcd.print(Display[i]);
                    }

                    Heart_Display();
                }
                

                else if (currLvl == 2) {
                    //Serial.println("WE AT TWOOO");
                    lcd.clear(); // Change player one to "120bMan"
                    lcd.setCursor(0, 0);
                    lcd.print("P1<");
                    lcd.print(Letters2[Letter_Changer2]);
                    lcd.print(">");
                    lcd.print("      ");  
                    lcd.print("120B!");       
                    //lcd.print("P2<");
                    //lcd.print(Letters2[Letter_Changer2]);
                    //lcd.print(">");
                    lcd.setCursor(13, 16);
                    lcd.print("");
                    lcd.print(lives);
                    lcd.print("");
                    lcd.setCursor(7, 0);
                    lcd.print("L");
                    lcd.print(currLvl);
                    lcd.print("");

                    lcd.setCursor(0, 1);
                  
                    for (int i = 0; i < phrase2.length(); i++) {
                        lcd.print(Display[i]);
                    } 

                    Heart_Display();

                } 

                else if (currLvl == 3) {

                    //Serial.println("WE AT TWOOO");
                    lcd.clear(); // Change player one to "120bMan"
                    lcd.setCursor(0, 0);
                    lcd.print("P1<");
                    lcd.print(Letters2[Letter_Changer2]);
                    lcd.print(">");
                    lcd.print("      ");  
                    lcd.print("120B!");       
                    //lcd.print("P2<");
                    //lcd.print(Letters2[Letter_Changer2]);
                    //lcd.print(">");
                    lcd.setCursor(13, 16);
                    lcd.print("");
                    lcd.print(lives);
                    lcd.print("");
                    lcd.setCursor(7, 0);
                    lcd.print("L");
                    lcd.print(currLvl);
                    lcd.print("");

                    lcd.setCursor(0, 1);
                  
                    for (int i = 0; i < phrase3.length(); i++) {
                        lcd.print(Display[i]);
                    } 

                    Heart_Display();
                }
                
                 
}



// ********************************************* Rand Function *********************************************
void Heart_Display() {
     if (lives == 6) {
          lcd.setCursor(6, 1);
          lcd.write(byte(0));
          lcd.setCursor(7, 1);
          lcd.write(byte(0));
          lcd.setCursor(8, 1);
          lcd.write(byte(0));
          lcd.setCursor(9, 1);
          lcd.write(byte(0));
          lcd.setCursor(10, 1);
          lcd.write(byte(0));
          lcd.setCursor(11, 1);
          lcd.write(byte(0)); 
      }

    else if (lives == 5) {
          lcd.setCursor(6, 1);
          lcd.write(byte(0));
          lcd.setCursor(7, 1);
          lcd.write(byte(0));
          lcd.setCursor(8, 1);
          lcd.write(byte(0));
          lcd.setCursor(9, 1);
          lcd.write(byte(0));
          lcd.setCursor(10, 1);
          lcd.write(byte(0));
     }

    else if (lives == 4) {
          lcd.setCursor(6, 1);
          lcd.write(byte(0));
          lcd.setCursor(7, 1);
          lcd.write(byte(0));
          lcd.setCursor(8, 1);
          lcd.write(byte(0));
          lcd.setCursor(9, 1);
          lcd.write(byte(0));
      }

    else if (lives == 3) {
          lcd.setCursor(6, 1);
          lcd.write(byte(0));
          lcd.setCursor(7, 1);
          lcd.write(byte(0));
          lcd.setCursor(8, 1);
          lcd.write(byte(0));
          lcd.setCursor(9, 1);
      }

    else if (lives == 2) {
          lcd.setCursor(6, 1);
          lcd.write(byte(0));
          lcd.setCursor(7, 1);
          lcd.write(byte(0));
      }

    else if (lives == 1) {
          lcd.setCursor(6, 1);
          lcd.write(byte(0));
      }

      
}

// ********************************************* Reset Function *********************************************
void Reset() {
    guessNum = 0;

    for (int i = 0; i < 20; i ++)
    {
      guesses[i] = '\0';
    }

    for (int i = 0; i < 20; i++) {
      Display[i] = '_';
    }

    // lcd.clear();
}


// ********************************************* States *********************************************
enum SM1_States {SM1_INIT, Level_1, Level_2, Level_3, End_Game} state1;
  int SM1_Tick(int state1) {
    switch (state1) {

        case SM1_INIT:
            if (currLvl == 1) {
                //Screen();
                Serial.println("HMMMMM");
                phrase = Lvl_One_WordBank[set()];
                Serial.println(phrase);
                // Serial.println(set());
                state1 = Level_1;
            }

            else if (currLvl == 2) {
                Reset();
                //Screen();
                Serial.println("INITI FUNCTINONNN");
                //phrase2 = "WWWW";
                int sewrt =set();
                phrase2 = Lvl_Two_WordBank[sewrt];
                //Serial.println(Lvl_Two_WordBank[set()]);
                Serial.println(Lvl_Two_WordBank[sewrt]);
                state1 = Level_2;
            }

            else if (currLvl == 3) {
                Reset();
                Serial.println("Levelll 33333");
                phrase3 = Lvl_Three_WordBank[set()]; // // Let's try and understand what prints from the RNG and why it does so, so we could print 
                                                   // someething out
                Serial.println(phrase3);
                state1 = Level_3;
            }
            
            break;

        case Level_1: 
            if (lives == 0) {  
                state1 = End_Game;
              }

            else if (correct < 3) {
              state1 = Level_1;
            }

            else if (correct == 3) {
               Serial.println("LEVELL ONEE COMPLETE");
               currLvl += 1;
               state1 = SM1_INIT; 
            }

            break;

        case Level_2:
            if (lives == 0) {  
                state1 = End_Game;
            }

            else if (correct < 7) {
                //Serial.println("LETSSS GOOO");
                state1 = Level_2;
            }

            else if (correct == 7) {
               //Serial.println("LEVELL TWOOO COMPLETE");
               currLvl += 1;
               state1 = SM1_INIT; 
            }
            
            break;

        case Level_3:
            if (lives == 0) {  
                state1 = End_Game;
            }

            else if (correct < 12) {
                state1 = Level_3;
            }

            else {
               Serial.println("LEVELL THREE COMPLETE");
               state1 = End_Game; 
            }
            
            break;

        case End_Game:
          state1 = End_Game;
          break;
    }

      switch(state1) {
        case SM1_INIT:
            break;

        case Level_1:
              break;

        case Level_2:
            break;

        case Level_3:
            break;

        case End_Game:
              if (lives > 1 && correct == 12) {   
                    Serial.println("YOUUU WONNNN");
                    lcd.clear();
                    lcd.setCursor(0,0);
                    lcd.print("VICTORY SCREESH!");

                    lcd.setCursor(0,1);
                    lcd.print("VICTORY SCREESH!");
                    break;
               }

              else if (lives == 0) {   
                      Serial.println("YOUUU LOSTTT");
                      lcd.clear();
                      lcd.setCursor(0,0);
                      lcd.print("IT'S OVER 9000!!");

                      lcd.setCursor(0,1);
                      lcd.print("IT'S OVER 9000!!");
                      break;
              }

              break;
            
          
      }
      return state1;
  }









enum SM2_States {SM2_INIT, Game} state2;
  int SM2_Tick(int state2) {
    switch (state2) {

        case SM2_INIT:
          state2 = Game;
          break;

        case Game:
          state2 = Game;
          break;
    }

      switch(state2) {
        case SM2_INIT:
            break;

        case Game:
              while (lives >= 1 && correct < 12) {     
                   Screen();             

                    if (analogRead(JoyStick_X2) > 800) {
                        ++Letter_Changer2; 
                        if (Letter_Changer2 == 26) {
                          Letter_Changer2 = 0;
                        }    
                        Serial.println(Letter_Changer2);          
                    }

                    else if (analogRead(JoyStick_X2) < 300) {
                        --Letter_Changer2;
                        if (Letter_Changer2 == -1) {
                          Letter_Changer2 = 25;
                        }  
                    }
   

                    else if (Button_Reader2(Joystick_Btn2)) {
                          updateScreen(correctness(Letters2[Letter_Changer2]));
                          guesses[guessNum] = Letters2[Letter_Changer2];
                          Serial.println(Letters2[Letter_Changer2]);              
                          Serial.println(phrase); 
                          Serial.println("Correct");
                          Serial.println(correct);

                    }


              break;
        }

      
          return state2;
    }
  }









  enum SM4_States { SM4_INIT, SHIGH, SLOW}; // PWM / DUTY CYCLE 
  int SM4_Tick(int state4) { // 20 / (9 + 1)
  switch (state4) { // State transitions
    case SM4_INIT:
      k = 0;
      state4 = HIGH;
      break;

    case SHIGH:
        if (k <= 1) { // This would have been H
          state4 = SHIGH;
        }

        else if (k > 1) { // This would have been H
          k = 0;
          state4 = SLOW;
        }
        break;

    case SLOW:
      if (k <= 9) { // This would have been L
        state4 = SLOW;
      }

      else if(k > 9) { // This would have been L
        state4 = SHIGH;
        k = 0;
      }

      break;

  }


  switch (state4) { // State Action
    case SM4_INIT:
      break;

    case SHIGH:

          if (currLvl == 2 && ServoCnt < 1) {    
    
            for(current = 2000; current <end; current+=increment){ // This is our pulse
                //Serial.println("WEEEE HIGHHH");

                digitalWrite(SERVO_PIN, HIGH);
                delayMicroseconds(current);
                digitalWrite(SERVO_PIN, LOW);
                delayMicroseconds(lenMicroSecondsOfPeriod - current); 
            }
                ++ServoCnt; 
                Serial.println(ServoCnt);
                k++;
                break;
          }


          else if (currLvl == 3 && ServoCnt2 < 1) {    
    
            for(current = 500; current <end; current+=increment){ // This is our pulse
                //Serial.println("WEEEE HIGHHH");

                digitalWrite(SERVO_PIN, HIGH);
                delayMicroseconds(current);
                digitalWrite(SERVO_PIN, LOW);
                delayMicroseconds(lenMicroSecondsOfPeriod - current); 
            }
                ++ServoCnt2; 
                Serial.println(ServoCnt2);
                k++;
                break;
          }          

      


    case SLOW:
        
        if (currLvl == 2 && ServoCnt < 2) {  
            for(current = end; current >first; current-=increment){
                //Serial.println("WEEEE LOWWWWW");
                
                digitalWrite(SERVO_PIN, HIGH);
                delayMicroseconds(current);
                digitalWrite(SERVO_PIN, LOW);
                delayMicroseconds(lenMicroSecondsOfPeriod - current); 
            }
                ++ServoCnt; 
                 Serial.println(ServoCnt);
                k++;
                break;
        }

         else if (currLvl == 3 && ServoCnt2 < 2) {  
            for(current = end; current >first; current-=increment){
                //Serial.println("WEEEE LOWWWWW");
                
                digitalWrite(SERVO_PIN, HIGH);
                delayMicroseconds(current);
                digitalWrite(SERVO_PIN, LOW);
                delayMicroseconds(lenMicroSecondsOfPeriod - current); 
            }
                ++ServoCnt2; 
                 Serial.println(ServoCnt2);
                k++;
                break;
        }


  }

  
 
  return state4;
}

  










  void setup() {
      
      lcd.createChar(0, Heart);

      seed = analogRead(A5);
      pinMode(Joystick_Btn, INPUT_PULLUP);
      pinMode(Joystick_Btn2, INPUT_PULLUP); 
      lcd.begin(16, 2);
      Serial.begin(9600);

      unsigned char i = 0;
      tasks[i].state = SM1_INIT;
      tasks[i].period = 100;
      tasks[i].elapsedTime = 0;
      tasks[i].TickFct = &SM1_Tick;
      i++;
      tasks[i].state = SM2_INIT;
      tasks[i].period = 300;
      tasks[i].elapsedTime = 0;
      tasks[i].TickFct = &SM2_Tick;
      i++;
      tasks[i].state = SM4_INIT;
      tasks[i].period = 100; // 200 / (4 + 1) = 40
      tasks[i].elapsedTime = 0;
      tasks[i].TickFct = &SM4_Tick;

      delay_gcd = 5;
  }


  void loop() {
      unsigned char i;
      for (i = 0; i < tasksNum; ++i) {
        if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
          tasks[i].state = tasks[i].TickFct(tasks[i].state);
          tasks[i].elapsedTime = millis(); 
        }
      }
}

