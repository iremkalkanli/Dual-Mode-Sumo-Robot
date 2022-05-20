//MOTOR Kontrol
int RPwm = 11;//sağ motorun hızı
int RDir = 13;//sağ motorun yönü
int LPwm = 3;//sol motorun hızı
int LDir = 12;//sol motorun yönü

//EDGE & CONTRAST SENSORS
int Redge = A1;//saha dışına çıkmaması için gereken sensörler
int Ledge = A0;

void Set_Motor (float Lval, float Rval){
  Lval = Lval*2.5; //Motorun hız değerlerinin ataması yapılır.
  Rval = Rval*2.5; 

  //Motorun hız değerine göre yön belirlenir.Motor hızının
  //pozitif veya negatif olma durumuna göre her iki motora da yön ataması yapılır.
  
  //Sol motor hızı pozitif ise sağa yönelmesi için LDir ataması LOW yapılır.Eğer negatif ise
  //sola yönelmesi için LDir ataması HIGH yapılır.
  
  //Sağ motor hızı negatif ise sola yönelmesi için RDir ataması LOW yapılır.Eğer pozitif ise
  //sağa yönelmesi için RDir ataması HIGH yapılır.
  
  if (Lval >=0) { 
      analogWrite(LPwm, Lval);  
      digitalWrite(LDir, LOW);       
      } else {
      Lval=abs(Lval); 
      digitalWrite(LDir, HIGH);  
      analogWrite(LPwm, Lval); 
      }
   if (Rval >=0) {    
      analogWrite(RPwm, Rval);  
      digitalWrite(RDir, HIGH);       
      } else {
      Rval=abs(Rval);     
      digitalWrite(RDir, LOW);  
      analogWrite(RPwm, Rval); 
      }   
     
}

void setup() {

pinMode(RPwm, OUTPUT);  // 4 tane kanal çıktı olarak atandı
pinMode(RDir, OUTPUT); 
pinMode(LPwm, OUTPUT); 
pinMode(LDir, OUTPUT); 


}

void loop() {
  //Zeminin renk kontrolleri olasılıklara göre okunur.
  //Eğer edge değerleri 100'den büyük ise siyah zeminde bulunduğu, 100'den küçükse beyaz zeminde bulunduğu anlamına gelir.
  // Değerlere uygun şekilde robotun hareketi belirlenir.
  Start:
 if(analogRead(Ledge)>100 &&analogRead(Redge)>100){//Sol ve sağ sensör siyah zeminde olduğu için motorun düz gitmesi istenir.
 forward();
 }if(analogRead(Ledge)<100&&analogRead(Redge)>100){//Sol sensör beyaz zeminde, sağ sensör siyah zeminde olduğu için motorun sağa gitmesi istenir.
 right();
 } if(analogRead(Ledge)>100&&analogRead(Redge)<100){//Sol sensör siyah zeminde, sağ sensör beyaz zeminde olduğu için motorun sola gitmesi istenir.
 left();
 }
 if(analogRead(Ledge)<100&&analogRead(Redge)<100){//Sol ve sağ sensör beyaz zeminde olduğu için motorun geri gitmesi istenir.
 back();
 }
 goto Start;

}

//Motorların uygun yöne ilerleyebilmesi için gerekli fonksiyonlar yazılarak, sağ ve sol yön atamaları yapılır.
void forward(){
  Set_Motor(-50,50);
  }
 void left(){
  Set_Motor(0,50); 
  }
 void right(){
  Set_Motor(-50,0);
  }
  void back(){
  Set_Motor(50,-50);
  }
