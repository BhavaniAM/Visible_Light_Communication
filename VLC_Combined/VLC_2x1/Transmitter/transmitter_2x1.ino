#define LED_1 A0
#define LED_2 A1
#define PERIOD 30

char *a = "What did Svante Pääbo discover, for which he was awarded the Nobel prize in Physiology?\n";
//char *a = "10011";
int sl;
int tx, num_rep = 3;

void setup()
{
  Serial.begin(9600);
  Serial.println("Enter the number of transmitters (1 or 2)");
  while (Serial.available() == 0) {
  }
  tx = Serial.parseInt();
  
  pinMode(LED_1, OUTPUT);
  if(tx == 2)
    pinMode(LED_2, OUTPUT);
  sl = strlen(a);
  digitalWrite(LED_1, HIGH);
  if(tx == 2)
    digitalWrite(LED_2, HIGH);
  delay(1000);
}

void loop()
{
  int i, j, bin, nr;
  char ch;
  for(i = 0; i < sl; i++)
  {
    ch = a[i];
    digitalWrite(LED_1, LOW);
    if(tx == 2)
      digitalWrite(LED_2, LOW);
    delay(PERIOD);
    //begin byte
    for(j = 0; j < 8; j++)
    {
      for(nr = 0; nr < num_rep; nr++)
      {
        bin = ((ch << j) & 0x80) ? 1 : 0;
      Serial.print(bin);
      if(bin == 0)
      {
        digitalWrite(LED_1, 181);
        if(tx == 2)
          digitalWrite(LED_2, 181);
        delay(10);
        digitalWrite(LED_1, LOW);
        if(tx == 2)
          digitalWrite(LED_2, LOW);
        delay(20);
      }
      else
      {
        digitalWrite(LED_1, 181);
        if(tx == 2)
          digitalWrite(LED_2, 181);
        delay(20);
        digitalWrite(LED_1, LOW);
        if(tx == 2)
          digitalWrite(LED_2, LOW);
        delay(10);
      }
      }
    }
    //end of byte
    Serial.println();
    digitalWrite(LED_1, 181);
    if(tx == 2)
      digitalWrite(LED_2, 181);
    delay(PERIOD);
  }
  delay(1000);
}
