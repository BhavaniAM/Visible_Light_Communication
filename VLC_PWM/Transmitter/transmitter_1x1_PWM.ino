#define LED A0
#define PERIOD 30

char *a = "New string to test if the set-up is working.\n";
int sl;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  sl = strlen(a);
  digitalWrite(LED, HIGH);
  delay(1000);
}

void loop()
{
  int i, j, bin;
  char ch;
  for(i = 0; i < sl; i++)
  {
    ch = a[i];
    digitalWrite(LED, LOW);
    delay(PERIOD);
    //begin byte
    for(j = 0; j < 8; j++)
    {
      bin = ((ch << j) & 0x80) ? 1 : 0;
      Serial.print(bin);
      if(bin == 0)
      {
        digitalWrite(LED, HIGH);
        delay(10);
        digitalWrite(LED, LOW);
        delay(20);
      }
      else
      {
        digitalWrite(LED, HIGH);
        delay(20);
        digitalWrite(LED, LOW);
        delay(10);
      }
    }
    //end of byte
    Serial.println();
    digitalWrite(LED, HIGH);
    delay(PERIOD);
  }
  delay(1000);
}
