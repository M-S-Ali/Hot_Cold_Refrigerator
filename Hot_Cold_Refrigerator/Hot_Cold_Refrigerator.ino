#define led_hot 7
#define led_cold 6
#define pot A0
#define pwr_rly 5
#define p_rly 3 // relay connected to possitive of peltier
#define n_rly 4 // relay connected to negative of peltier
#define t_sns A5 // temperature sensor
#define on_sw 12
#define auto_sw 11

void heat_cabin();
void cool_cabin();

int temp, des_temp, t_flag;

void setup(){
  pinMode(led_hot, OUTPUT);
  pinMode(led_cold, OUTPUT);
  pinMode(pot, INPUT);
  pinMode(t_sns, INPUT);
  pinMode(pwr_rly, OUTPUT);
  pinMode(p_rly, OUTPUT);
  pinMode(n_rly, OUTPUT);
  pinMode(on_sw, INPUT);
  pinMode(auto_sw, INPUT);
  
  Serial.begin(9600);
}

void loop(){
  des_temp = map(analogRead(pot),0,1024,20,358);
  temp = analogRead(t_sns);
  
  if(des_temp>189)
    t_flag=1;
  else
    t_flag=-1;

  if(digitalRead(on_sw) == LOW)
    digitalWrite(pwr_rly,LOW);
  else{
    if (((des_temp-10)*t_flag)>temp*t_flag)
      digitalWrite(pwr_rly,HIGH);
    else if (((des_temp-10)*t_flag)<temp*t_flag)
      digitalWrite(pwr_rly,LOW);
  }
  
  if(t_flag == 1)
    heat_cabin();
  else
    cool_cabin();
  
  delay(2000);
  Serial.println(des_temp);
  Serial.println(temp);
}

void heat_cabin(){
  digitalWrite(led_hot,HIGH);
  digitalWrite(led_cold,LOW);
  digitalWrite(p_rly,HIGH);
  delay(300);
  digitalWrite(n_rly,HIGH);
  delay(300);
}

void cool_cabin(){
  digitalWrite(led_cold,HIGH);
  digitalWrite(led_hot,LOW);
  digitalWrite(p_rly,LOW);
  delay(300);
  digitalWrite(n_rly,LOW);
  delay(300);
}