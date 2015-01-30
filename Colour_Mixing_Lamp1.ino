//Name each output pin so it's easier to read
const int greenLEDpin = 11;
const int redLEDpin = 9;
const int blueLEDpin = 10;

//Declare variables for current state of button latch & previous state as well as button variable
int state = LOW;
int previous;
int button;

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  attachInterrupt(0, statechange, RISING);  //see this link for why: "arduino.cc/en/Reference/AttachInterrupt"
    
}

void loop()
{
  unsigned int rgbColour[3];

  if (state == HIGH)
  {  //The code below to cycle through RGB colours was borrowed from this fine person here:"https://gist.github.com/jamesotron/766994"
    // Start off with red.
    rgbColour[0] = 255;
    rgbColour[1] = 0;
    rgbColour[2] = 0;  

    // Choose the colours to increment and decrement.
    for (int decColour = 0; decColour < 3; decColour += 1) 
    {
      int incColour = decColour == 2 ? 0 : decColour + 1;

      // cross-fade the two colours.
      for(int i = 0; i < 255; i += 1) 
      {
        rgbColour[decColour] -= 1;
        rgbColour[incColour] += 1;

        analogWrite(redLEDpin, rgbColour[0]);
        analogWrite(greenLEDpin, rgbColour[1]);
        analogWrite(blueLEDpin, rgbColour[2]);
        delay(5);//change this to change how quickly colours fade in/out
      }
    }
  }
  else if (state == LOW) //LED is off if button state is low
  {
    analogWrite(redLEDpin, 0);
    analogWrite(greenLEDpin, 0);
    analogWrite(blueLEDpin, 0);
  }
}

void statechange() //flip flops LED state
{
  state = !state; //There could probably be a button de-bounce code in here, but i was too lazy which is why i used the capacitor. 
}
