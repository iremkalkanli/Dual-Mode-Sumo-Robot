//OPPONENT SENSORS
int LSens = A2;
int RSens = A4;
int MSens = A3;

int LFSens = A5;
int RFSens = 4;

//EDGE & CONTRAST SENSORS
int Redge = A1;
int Ledge = A0;

//TRIMPOTS
int SPD = A7;
int TRN = A6;

//LED & BUZZER
int Buzzer = 9;
int ArduLed = 8;

// DIPSWITCH & BUTTON
int Button = 10; // Can be used as start pin too.
int DS1 = 5;
int DS2 = 6;
int DS3 = 7;

//VALUES
int Speed =50;
int MaxSpeed = 50; // Idle Speed while no sensor giving data.
int TurnSpeed = 55; // Left and Right Forward Turning Speed
int EdgeTurn = 500; // Turning Time variable when minisumo sees white line
int Duration; // Turning Time at minisumo starting.
int LastValue = 5; // Last Value Variable for remembering last Opponent sensor sense.

//motor kontrol
int RPwm = 11;
int RDir = 13;

int LPwm = 3;
int LDir = 12; 

//SETUP-------------------------------------------------
void setup() {
  
  pinMode(LSens, INPUT);    // Left Opponent Sensor Input
  pinMode(RSens, INPUT);    // Right Opponent Sensor Input
  pinMode(MSens, INPUT);    // Middle Opponent Sensor Input
  
  pinMode(Buzzer, OUTPUT);  // Buzzer Declared as Output
  pinMode(ArduLed, OUTPUT); // Buzzer Declared as Output
  pinMode(Button, INPUT); // Buzzer Declared as Output
  
  pinMode(RPwm, OUTPUT);  // Four PWM Channel Declared as Output
  pinMode(RDir, OUTPUT); 
  pinMode(LPwm, OUTPUT); 
  pinMode(LDir, OUTPUT); 
  
  digitalWrite(Buzzer, LOW); // Buzzer Pin Made Low for Silence :)
  digitalWrite(ArduLed, LOW);  // Arduino Mode Led Made Low
  digitalWrite(DS1, HIGH); // 3 Dipswitch Pin Pullups Made
  digitalWrite(DS2, HIGH);
  digitalWrite(DS3, HIGH);
  
  digitalWrite(RFSens, HIGH); 
  digitalWrite(MSens, HIGH); 
  
  Serial.begin(9600);
  
  tone(9, 523, 300);
  delay(300);
  noTone(9); 
}

//setMotor---------------------------------------
void setMotor(float Lval, float Rval, int timex){
  Lval = Lval*2.5;
  Rval = Rval*2.5; 
  
  if (Lval >=0) { 
    analogWrite(LPwm, Lval);  
    digitalWrite(LDir, HIGH);       
  } 
  else {
    Lval=abs(Lval); 
    digitalWrite(LDir, LOW);  
    analogWrite(LPwm, Lval); 
  }
  
  if (Rval >=0) {    
    analogWrite(RPwm, Rval);  
    digitalWrite(RDir, HIGH);       
  } 
  else {
    Rval=abs(Rval);     
    digitalWrite(RDir, LOW);  
    analogWrite(RPwm, Rval); 
  }      
  delay(timex);
}

//LOOP-----------------------------------------
void loop() {
  digitalWrite(RPwm, LOW);
  digitalWrite(LPwm, LOW);
  tone(Buzzer, 18, 100); 

  Start:
    /// Edge Sensor Control Routine ///
    digitalWrite(ArduLed, LOW);
   if (analogRead(Ledge)>100 && analogRead(Redge)< 100) {
     digitalWrite(Buzzer, LOW);
     digitalWrite(ArduLed, HIGH);
     setMotor(-35, -35,350); // Geri   
     setMotor(35, -35, EdgeTurn); // Left Backward, Right Forward, Turning Time Based on ETRN Trimpot
     LastValue=5;
   }
   else  if (analogRead(Ledge)< 100 && analogRead(Redge)> 100) {
     digitalWrite(Buzzer, LOW);
     digitalWrite(ArduLed, HIGH);
     setMotor(-35, -35,350); // Back 35 Milliseconds
     setMotor(-35, 35, EdgeTurn); // Right Backward, Left Forward, Turning Time Based on ETRN Trimpot
     LastValue=5;
  }
  else  if (analogRead(Ledge)> 100 && analogRead(Redge)> 100) {
     digitalWrite(Buzzer, LOW);
     digitalWrite(ArduLed, HIGH);
     setMotor(-35, -35,350); // Back 35 Milliseconds    
     setMotor(35, -35, EdgeTurn); // Right Backward, Left Forward, Turning Time Based on ETRN Trimpot
     LastValue=5; 
    
  }else
    /// Opponent Sensor Control Routine ///
    //while (digitalRead(Button)==LOW) {Set_Motor(0, 0, 20); digitalWrite(Buzzer, LOW); LastValue=3;} digitalWrite(Buzzer, LOW);
    if (digitalRead(MSens)==HIGH) {setMotor(35, 35,1); digitalWrite(Buzzer, HIGH); LastValue=5;} else
    if (digitalRead(LSens)== HIGH) {setMotor(-35, 35,1); digitalWrite(Buzzer, HIGH); LastValue=7;} else
    if (digitalRead(RSens)==HIGH) {setMotor(35, -35,1); digitalWrite(Buzzer, HIGH); LastValue=3;} else
    {
    digitalWrite(Buzzer, LOW);
    //Speed=(analogRead(SPD)/10.3); Speed=100-Speed; 
    if (LastValue==5) { setMotor(20, 20,1);} else // Forward, Based on SPD (A7) Trimpot
    if (LastValue==7) { setMotor(-20, 40,2);} else  // Left Turning Based on SPD (A7) Trimpot
    if (LastValue==3) { setMotor(40, -20,2);}  // Right Turning Based on SPD (A7) Trimpot
    }
  goto Start;
}
