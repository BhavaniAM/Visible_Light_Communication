#define LED_PIN 3
#define LDR_PIN A0
#define THRESHOLD 220
#define PERIOD 30

bool previous_state;
bool current_state;

void setup() 
{
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
  current_state = get_ldr();
  //Serial.print(current_state);
  if(!current_state && previous_state)
  {
    print_byte(get_byte());
  }
  previous_state = current_state;
}

bool get_ldr()
{
  int voltage = analogRead(LDR_PIN);
  //Serial.println(voltage);
  return voltage > THRESHOLD ? true : false;
}

char get_byte()
{
  char ret = 0;
  delay(PERIOD*1.5);
  for(int i = 0; i < 8; i++)
  {
   ret = ret | get_ldr() << i; 
   delay(PERIOD);
  }
  return ret;
}
void print_byte(char my_byte)
{
  char buff[2];
  sprintf(buff, "%c", my_byte);
  Serial.println(buff);
}
