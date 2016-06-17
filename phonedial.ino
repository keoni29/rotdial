/* Phone dial input - By Koen van Vliet <8by8mail@gmail.com>
 * Get input from a rotary dial found in old phones.
 *
 * Notes on rotary dial wireing:
 *  The rest wire typically the red wire in dials from dutch PTT phones
 *  The count pulse wire is typically the blue wire
 *  The common (ground) wire is typically the yellow wire
 *  
 *  Wire up the rest and pulse wire to I/O pins on the arduino (specified below)
 *  Use 10k pullup resistors to 5V on both pins.
 *
 * Notes on light ring wireing:
 *  Wire the positive lead of the LED to a resistor and the other end of the resistor to an I/O pin.
 *  Next wire all negative leads of the LED's to ground. The I/O pins can be specified below.
 */

#define rest  2      /* Typically the red wire in dials from dutch PTT phones */
#define pulse  3     /* Typically the blue wire */

// Led light ring     0   1   2   3   4  5  6   7   8   9
const uint8_t ring[] = { 13, A3, A2, A1, A0, 8, 9, 10, 11, 12 };

void initRing()
{
  for( uint8_t i = 0; i < sizeof(ring); i++ )
  {
    pinMode(ring[i],OUTPUT);
  }
}

void clearRing()
{
  for( uint8_t i = 0; i < sizeof(ring); i++ )
  {
    digitalWrite(ring[i], LOW);
  }
}

void ledRing(uint8_t led)
{
  digitalWrite(ring[led], HIGH);
}

void setup()
{
  pinMode(rest, INPUT); 
  pinMode(pulse, INPUT);
  Serial.begin(9600);
  Serial.println("--Arduino telephone dial input--");
  clearRing();
}

void loop()
{
  uint8_t counter;
  boolean pulseactive;
  
  Serial.println("Waiting for input...");  
  while( digitalRead(rest) == 1 ){}       // Do nothing while the dial sits idle
  while( digitalRead(pulse) == 1 ){}      // Wait until the pulse-line is logic 0
  delay(40);
  Serial.println("Dial activity!");
  clearRing();
  counter = 0;
  pulseactive = false;
  while( digitalRead(rest) == 0 )       // Count pulses while dial rotates
  {
    if( pulseactive == false )
    {
      if( digitalRead(pulse) == 1 )
      {
        pulseactive = true;
      }
    } 
    else 
    {
      if( digitalRead(pulse) == 0 )    // When pulse line goes from high to low a pulse is complete.
      {
        counter ++;                    // The counter increments every pulse
        Serial.print("+");
        pulseactive = false;
        delay(70);
      }
    }
  }
  Serial.println( "END" );
  
  if( counter == 0 || counter > 10 )
  {
    Serial.print("Dial invalid. Ignoring input ");
    Serial.println( counter );
  }
  else
  {
    if( counter == 10 )
    {
        counter = 0;
    }
    Serial.print("Received number ");
    Serial.print( counter );
    ledRing(counter);
    Serial.println("!");
  }
}

