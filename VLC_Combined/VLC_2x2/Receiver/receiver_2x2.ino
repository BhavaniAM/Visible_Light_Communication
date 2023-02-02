#define LDR_1 A0
#define LDR_2 A1

#define threshold_1 180
#define threshold_2 200

const unsigned long PERIOD = 30;

bool previous_state_1;
bool current_state_1;

bool previous_state_2;
bool current_state_2;
int rx = 2, num_rep = 3;

void setup()
{
  Serial.begin(9600);
  
  pinMode(LDR_1, INPUT);
  if(rx == 2)
    pinMode(LDR_2, INPUT);
}

void loop()
{
  int i, y, summ = 0, num, nr, fin_y = 0;
  current_state_1 = get_ldr_1();
  if(rx == 2)
    current_state_2 = get_ldr_2();
  if((!current_state_1 && previous_state_1)|| (!current_state_2 && previous_state_2))
  {
    delay(PERIOD);
    for(i = 0; i < 8; i++)
    {
      fin_y = 0;
      for(nr = 0; nr < num_rep; nr++)
      {
        y = get_samples();
        fin_y = fin_y + y;
        //Serial.print(y);
      }
      if(fin_y > 1)
        y = 1;
      else
        y = 0;
      //Serial.print(y);
      num = 7 - i;
      for(int j = 0; j < num; j++)
        y = y * 2;
      summ = summ + y;
    }
    //Serial.println();
    Serial.print(char(summ));
    //end of byte
  }
  previous_state_1 = current_state_1;
  if(rx == 2)
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
    if(rx == 2)
    {
      samp = samp + get_ldr_2();
      j++;
    }
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
