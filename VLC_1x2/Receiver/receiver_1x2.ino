#define LDR_1 A0
#define LDR_2 A1

#define threshold_1 290
#define threshold_2 250

const unsigned long PERIOD = 30;

bool previous_state_1;
bool current_state_1;

bool previous_state_2;
bool current_state_2;

void setup()
{
  Serial.begin(9600);
  pinMode(LDR_1, INPUT);
  pinMode(LDR_2, INPUT);
}

void loop()
{
  int i, y, summ = 0, num;
  current_state_1 = get_ldr_1();
  current_state_2 = get_ldr_2();
  if((!current_state_1 && previous_state_1)|| (!current_state_2 && previous_state_2))
  {
    delay(PERIOD);
    for(i = 0; i < 8; i++)
    {
      y = get_samples();
      //Serial.print(y);
      num = 7 - i;
      for(int j = 0; j < num; j++)
        y = y * 2;
      summ = summ + y;
    }
    Serial.print(char(summ));
    //end of byte
  }
  previous_state_1 = current_state_1;
  previous_state_2 = current_state_2;
}

int get_samples()
{
  int samp = 0, j = 0;
  unsigned long current_time = millis();
  while(millis() - current_time <= 30)
  {
    samp = samp + get_ldr_1();
    j++;
    samp = samp + get_ldr_2();
    j++;
  }
  float avg = (float)samp/j;
  //Serial.println(avg);
  return (avg > 0.5) ? 1:0;
}

int get_ldr_1()
{
  int ldr, val = 0;
  ldr = analogRead(LDR_1);
  //Serial.println(ldr);
  if(ldr > threshold_1)
    val = 1;
  else
    val = 0;
  return val;
}

int get_ldr_2()
{
  int ldr, val = 0;
  ldr = analogRead(LDR_2);
  //Serial.println(ldr);
  if(ldr > threshold_2)
    val = 1;
  else
    val = 0;
  return val;
}
