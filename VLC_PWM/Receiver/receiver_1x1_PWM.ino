#define LDR A0
#define threshold 130

const unsigned long PERIOD = 30;

bool previous_state;
bool current_state;

void setup()
{
  Serial.begin(9600);
  pinMode(LDR, INPUT);
}

void loop()
{
  int i, y, summ = 0, num;
  current_state = get_ldr();
  if(!current_state && previous_state)
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
  previous_state = current_state;
}

int get_samples()
{
  int samp = 0, j = 0;
  unsigned long current_time = millis();
  while(millis() - current_time <= 30)
  {
    samp = samp + get_ldr();
    j++;
  }
  float avg = (float)samp/j;
  //Serial.println(avg);
  return (avg > 0.5) ? 1:0;
}

int get_ldr()
{
  int ldr, val = 0;
  ldr = analogRead(LDR);
  //Serial.println(ldr);
  if(ldr > threshold)
    val = 1;
  else
    val = 0;
  return val;
}
