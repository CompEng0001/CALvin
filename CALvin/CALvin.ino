/* Cathode Activated Lamp (CALvin)
  DONE
  - Bluetooth Connectivity and android control
  - Random colour mode added
  - whileMode replaces multiple bools to one bool
  - Do while loops exit properly with string.replace();
  - Array of pins created for two LED RGBS, this replaces the previous design of LED RGBS stacked on one set of pins, brighter lights!
  - Added Calvin to expected string to disguise as smart voice :)
  - smartVoice now contains variations of Calvin that have appeared during testing.
  - using indexOf enables you to give a complex sentence and then extract the colour if present or colourmode
  - added emotional words to certian colours to further enchance the semantics of the complex sentences

  TO DO
  - Add wifi functionality, new script?
  - Link to Facebook messaging to recieve commands from new script?
  - Use speech for user to give their own colour patterns
  - Use speech to work out how fast the colour pattern was said ie - red,blue,green,....... red,blue,..green
*/

char c;
char colour[] = {'r', 'g', 'b', 'y', 'm', 'w', 'p', 'o'}; // colour array for switch statement randomColour()
char previousColour; // for random random check randomColour();
char* smartVoice[] = {"Calvin ", "calvin ", "Galvin ", "galvin ", "Kelvin ", "kelvin ", "Alvin ", "alvin "}; // an array of expected variations of Calvin
char* replaceLookUp[] = {"Emergency", "emergency", "Disco", "disco", "Random", "random", "Pattern", "pattern", "party", "help"}; // for string.replace
char* colourLookUp[] = {"Red", "red", "Green", "green", "Blue", "blue", "Yellow", "yellow", "Magenta", "magenta", "White", "white", "Purple", "purple", "Orange", "orange"};

// A list semantic sentences lookup words to determin the mood of someone -  need to get these to work using an array look up with indexOf.
char* semanticNegative [] = {"depressed", "sad", "not happy", "tough", "crying", "not ok", "not okay", "dark mood", "bad", "not good", "ugly"}; // light blue
char* semanticPositive [] = {"happy", "excited", "not sad", "good", "fine", "great", "fantastic", "light mood", "love", "cute"}; // light purple
char* semanticAggresive [] = {"angry", "furious", "enraged", "mad", "beside myself", "aggresive"}; // flashing red
char* semanticOther[] = {"jealous", "ill", "unwell", "poorly"}; // green

int colourPatternSize = 16;

String voiceCommand; // for serialListener() to pass to lightMode()

// assign an array digital pins to cathode pins
int redPin[] = {3, 9};
int greenPin[] = {5, 10};
int bluePin[] = {6, 11};

// for use with do while loops for lights sequences
bool whileMode = false;
bool CALvin = false;
bool colourMode = false;

//semantic bools
bool semanticN = false;
bool semanticP = false;
bool semanticO = false;
bool semanticA = false;

void setup()
{
  Serial.begin(9600); // set up baud rate

  for (int p = 0; p < 2; p++) // assign an array pins using for loop
  {
    pinMode(redPin[p], OUTPUT);
    pinMode(greenPin[p], OUTPUT);
    pinMode(bluePin[p], OUTPUT);
  }
  Serial.println("CALvin is alive");
  Serial.println("");
}

void loop()
{
  serialListener(); // call serial listener
  // Will only activate if Calvin || calvin was in the string
  if (CALvin == true)
  {
    lightMode();
  }

  CALvin = false;
  colourMode = false;
  voiceCommand = ""; // clear string
}

/*
   function for calling the serial read
*/
void serialListener()
{
  while (Serial.available())
  {
    delay(10);
    c = Serial.read();// reading the string sent by google voice
    if (c == '#')
    {
      break;
      delay(10);
    }

    voiceCommand += c;

    for (int i = 0; i < 7; i++) // iterate through expected variations of Calvin
    {
      // search from string(index) if true
      if ( voiceCommand.indexOf(smartVoice[i]))
      {
        CALvin = true;
      }
    }

    if (CALvin == true) // will replace Calvin || variations with ""
    {

      for (int s = 0; s < 7; s++)
      {
        voiceCommand.replace(smartVoice[s], ""); // deletes identifier eg calvin, kelvin
      }
      if (whileMode == true) // check for active embedded loops
      {
        for (int s = 0; s < 9; s++ )
        {
          voiceCommand.replace(replaceLookUp[s], ""); // replace mode with ""
        }
        whileMode = false;
      }
    }
    else
    {
    }
  }
}

void setColour(int red, int green, int blue)
{
  for (int p = 0; p < 2; p++ ) // setting the colour for an array of pins.
  {
    analogWrite(redPin[p], red);
    analogWrite(greenPin[p], green);
    analogWrite(bluePin[p], blue);
    delay(10);
  }
}

void lightMode()
{
  if (voiceCommand.length() > 0)
  { Serial.println(voiceCommand); // prints for debugging

    if (voiceCommand.indexOf("red") > 0 || voiceCommand.indexOf("Red") > 0  )// why does this not work?
    {
      if (voiceCommand.indexOf("blue") > 0 || voiceCommand.indexOf("Blue") > 0)
      {
        setColour(255, 0, 255);
      }
      else
      {
        setColour(255, 0, 0);
      }
    }

    else if (voiceCommand.indexOf("angry") > 0 || voiceCommand.indexOf("frustrated") > 0 || voiceCommand.indexOf("annoyed") > 0 ) // why does this not work?
    {
      setColour(255, 0, 0);
    }
    else if (voiceCommand.indexOf("green") > 0 || voiceCommand.indexOf("Green") > 0 || voiceCommand.indexOf("ill") > 0 || voiceCommand.indexOf("unwell") > 0 || voiceCommand.indexOf("sick") > 0 || voiceCommand.indexOf("man flu") > 0 )
    {
      setColour(0, 255, 0);
    }
    else if (voiceCommand.indexOf("blue") > 0 || voiceCommand.indexOf("Blue") > 0 || voiceCommand.indexOf("sad") > 0 || voiceCommand.indexOf("depressed") > 0    )
    {
      setColour(0, 0, 255);
    }
    else if (voiceCommand.indexOf("yellow")  > 0 || voiceCommand.indexOf("Yellow") > 0 )
    {
      setColour(255, 255, 0);
    }
    else if (voiceCommand.indexOf("magenta") > 0 || voiceCommand.indexOf("Magenta") > 0 || voiceCommand.indexOf("happy") > 0  || voiceCommand.indexOf("excited") > 0  )
    {
      setColour(255, 0, 255);
    }
    else if (voiceCommand.indexOf("white") > 0 || voiceCommand.indexOf("White") > 0 || voiceCommand.indexOf("torch") > 0 )
    {
      setColour(255, 255, 255);
    }
    else if (voiceCommand.indexOf("olive") > 0 || voiceCommand.indexOf("Olive") > 0 )
    {
      setColour(128, 128, 0);
    }
    else if (voiceCommand.indexOf("purple") > 0 || voiceCommand.indexOf("Purple") > 0 )
    {
      setColour(128, 0, 128);
    }
    else if (voiceCommand.indexOf("orange") > 0 || voiceCommand.indexOf("Orange") > 0)
    {
      setColour(255, 170, 0);
    }
    else if (voiceCommand.indexOf("disco") > 0 || voiceCommand.indexOf("Disco") > 0 || voiceCommand.indexOf("party") > 0 )
    {
      disco();
    }
    else if (voiceCommand.indexOf("emergency") > 0 || voiceCommand.indexOf("Emergency") > 0 || voiceCommand.indexOf("help") > 0 )
    {
      emergency();
    }
    else if (voiceCommand.indexOf("random") > 0 || voiceCommand.indexOf("Random") > 0 )
    {
      randomColour();
    }
    else if (voiceCommand.indexOf("off") > 0 || voiceCommand.indexOf("sleep") > 0  || voiceCommand.indexOf("good night") > 0 )
    {
      setColour(0, 0, 0);
    }
  }
}
/* Creates a random colour function that uses switch cases from an array of colours
   Added random random, so that no two colours in sequence are the same.
*/
void randomColour()
{
  whileMode = true;
  do
  {
    for (int i = 0; i < 5; i++)
    {
      char switchColour = colour[random(0, 7)]; // set random amount of colour to cycle

      do
      {
        switchColour = colour[random(0, 7)]; // set random amount of colour to cycle
      } while (switchColour == previousColour); // makes sure new random is different to last random

      previousColour = switchColour; // set new previous colour
      Serial.println(switchColour);
      switch (switchColour) // switch colour
      {
        case 'r':
          setColour(255, 0, 0);
          delay(100);
          break;
        case 'g':
          setColour(0, 255, 0);
          delay(100);
          break;
        case 'b':
          setColour(0, 0, 255);
          delay(100);
          break;
        case 'y':
          setColour(255, 255, 0);
          delay(100);
          break;
        case 'm':
          setColour(255, 0, 255);
          delay(100);
          break;
        case 'w':
          setColour(255, 255, 255);
          delay(100);
          break;
        case 'p':
          setColour(128, 0, 128);
          delay(100);
          break;
        case 'o':
          setColour(250, 128, 0);
          delay(100);
          break;
      }
    }

    serialListener();
  } while (whileMode == true);
  lightMode();
}

/*
   function for colours flashing to replicate a disco - preset colours never change
*/
void disco()
{
  whileMode = true;
  do
  {
    setColour(255, 0, 0);
    delay(100);
    setColour(0, 255, 0);
    delay(100);
    setColour(255, 255, 255);
    delay(100);
    setColour(255, 0, 255);
    delay(100);
    serialListener();
  } while (whileMode == true);

  lightMode();
}

/*
  function for red, blue flashing like emergency services.
*/
void emergency()
{
  whileMode = true;
  do
  {
    setColour(255, 0, 0);
    delay(100);
    setColour(0, 0, 255);
    delay(100);
    serialListener();
  } while (whileMode == true);

  lightMode();

}


