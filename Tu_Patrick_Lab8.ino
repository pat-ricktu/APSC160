/* Name: Patrick Tu
Purpose: Create a Simon Game using arduino programming. */

/*
  Lab 8 Simon game template
  Do not modify this template (circuit)
*/

//preprocessor directives
int const Button0 = 7;
int const Button1 = 6;
int const Button2 = 5;
int const Button3 = 4;
  
int const RedLED = 12;
int const YellowLED = 11;
int const BlueLED = 10;
int const GreenLED = 9;
  
int const LoseLED = 13;
int const WinLED = 8;
 
//symbolic constants

#define one_second 1000
#define half_second 500
#define quarter_second 250

#define FALSE 0

#define LOSE 1
#define WIN 2
#define DNE 3

#define rounds_to_win 5

int rounds_played = 0; //initialize rounds_played as 0
int sequence[rounds_to_win]; //array for random sequence
int gamestate; //state of the game

//function prototypes
void start(void);
void randomizeSequence(void);
void gameStart(void); 
int CheckPushedButton(void);
void userInput(void);
void Lose(void);
void Win(void);

//indicates when a new game starts            
void start(void){
  
  for(int index = 0; index < 3; index++){ //flickering lights 3 times
  	digitalWrite(RedLED, HIGH);
  	digitalWrite(YellowLED, HIGH);  
  	digitalWrite(BlueLED, HIGH);  
  	digitalWrite(GreenLED, HIGH);  
  	digitalWrite(LoseLED, HIGH);  
  	digitalWrite(WinLED, HIGH); 
    
  	delay(quarter_second/2); //turns all LEDs on for short time
  
  	digitalWrite(RedLED, LOW);
  	digitalWrite(YellowLED, LOW);  
  	digitalWrite(BlueLED, LOW);  
  	digitalWrite(GreenLED, LOW);  
  	digitalWrite(LoseLED, LOW);  
  	digitalWrite(WinLED, LOW);
    
  	delay(quarter_second/2); //turns all LEDs off for short time
  }
  
  delay(one_second); //delay 1 second before game starts
}

//create random sequence function
void randomizeSequence(void){
  
  randomSeed(analogRead(A0)); //creates a randomized pattern
  
  for(int index = 0; index < rounds_to_win; index++){ //5 rounds to win, so 5 different LEDs 
  	sequence[index] = random(4,8); //Button0 = 4, Button3 = 7; 8 isn't included
  }
}

//game start function
void gameStart(void){
  
  //light up an LED from randomized sequence
  for(int index = 0; index <= rounds_played; index++){
      	digitalWrite(sequence[index] + 5, HIGH); //LEDs have a higher pin of +5 for each one
      	delay(half_second); //LED on for 0.5 seconds
    
      	digitalWrite(sequence[index] + 5, LOW);
      	delay(quarter_second); //LED off for 0.25 seconds
  }
}

//check for which buttons are pushed
int CheckPushedButton(void){

  if(digitalRead(Button0) == HIGH){
    while(digitalRead(Button0) == HIGH){
    }//Do nothing if the button is held
    	digitalWrite(RedLED, HIGH); //LED on
    	delay(quarter_second/2);
    	digitalWrite(RedLED, LOW); //LED off
    
  	return Button0; //if Red LED button is pushed, return value 
  }
  
  else if(digitalRead(Button1) == HIGH){
    while(digitalRead(Button1) == HIGH){
    }//Do nothing if the button is held
    	digitalWrite(YellowLED, HIGH); //LED on
    	delay(quarter_second/2);
    	digitalWrite(YellowLED, LOW); //LED off
  			
    return Button1; //if Yellow LED button is pushed, return value
  }
  
  else if(digitalRead(Button2) == HIGH){
    while(digitalRead(Button2) == HIGH){
    }//Do nothing if the button is held
    	digitalWrite(BlueLED, HIGH); //LED on
    	delay(quarter_second/2); 
    	digitalWrite(BlueLED, LOW); //LED off
  			
    return Button2; //if Blue LED button is pushed, return value
  }
  
  else if(digitalRead(Button3) == HIGH){
    while(digitalRead(Button3) == HIGH){
    }//Do nothing if the button is held
    	digitalWrite(GreenLED, HIGH); //LED on
    	delay(quarter_second/2);
    	digitalWrite(GreenLED, LOW); //LED off
    
  	return Button3; //if Green LED button is pushed, return value
  }
  
  else{
  	return FALSE; //if no buttons are pushed, return nothing (0)
  }
}

//reads the user input function
void userInput(void){
  for(int index = 0; index <= rounds_played; index++){
    gamestate = DNE; //set the game to DNE as the user hasn't won/lost
    
    while(gamestate == DNE){ //repeat until user wins/loses
      int ButtonPressed = CheckPushedButton(); //var ButtonPressed gets the return value
      
      if(ButtonPressed != FALSE){ //if a button was pressed, execute the code
    	if(ButtonPressed == sequence[index]){ //checks to see if the correct button was pushed
          	gamestate = WIN; //terminate loop
     	}
    
    	else{ //if the wrong button was pressed
          	Lose(); //play lose function
          	gamestate = LOSE; //terminate loop
     	}
      }   
    }
  }
  if(gamestate == WIN){ //if user wins
  	Win(); //play win function
  }
}
 
//lose function
void Lose(void){
  
  //flash lose led 3 times
  for(int index = 0; index < 3; index++){
  	digitalWrite(LoseLED, HIGH);
    delay(quarter_second); //LED on for 0.25 seconds
    
    digitalWrite(LoseLED, LOW);
    delay(quarter_second); //LED off for 0.25 seconds
    
  }
  //reset game
  rounds_played = 0;
  gamestate = DNE;
  randomizeSequence(); //randomize sequence again
  start(); //play start function
}

//win function                 
void Win(void){
  
  //flash win led 3 times
  for(int index = 0; index < 3; index++){
    digitalWrite(WinLED, HIGH);
    delay(quarter_second); //LED on for 0.25 seconds
    digitalWrite(WinLED, LOW);
    delay(quarter_second); //LED off for 0.25 seconds
    
  }
  
  //increment to the next round
  if(rounds_played < rounds_to_win){
  rounds_played++;
    
  }
  //reset game once user wins 5 times
  if(rounds_played == rounds_to_win){
  rounds_played = 0;
  gamestate = DNE;
  randomizeSequence(); //randomize sequence again
  start(); //play start function
  }
}	


//initialization
void setup()
{
 
 pinMode(Button0, INPUT); //Red LED button
 pinMode(Button1, INPUT); //Yellow LED button
 pinMode(Button2, INPUT); //Blue LED button
 pinMode(Button3, INPUT); //Green LED button
  
 pinMode(RedLED, OUTPUT);
 pinMode(YellowLED, OUTPUT);
 pinMode(BlueLED, OUTPUT);
 pinMode(GreenLED, OUTPUT);
  
 pinMode(LoseLED, OUTPUT); 
 pinMode(WinLED, OUTPUT);
}


//main program loop for the Simon game
void loop()
{
  //if rounds_played = 0, start game
  if(rounds_played == 0){
    start();
    randomizeSequence();
  }
  
  //continue looping until user wins 5 rounds
  while (rounds_played != rounds_to_win){
    gameStart();
    userInput();
  }
}
