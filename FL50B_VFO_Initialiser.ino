/*
Arduino Nano EEPROM initialiser script for FL-50B transmitter.

*/

#include <Wire.h>
#include <EEPROM.h>

const int NUMBER_OF_BANDS = 5; // number of selectable bands

// Combined typedef and struct for band parameter records: the parameters associated with each band
typedef struct
{
    boolean active;
    uint32_t Hz;
    uint32_t radix;
} BandParameters;

BandParameters Band[NUMBER_OF_BANDS]; // array of band parameters per band
byte BandIndexCurrent;                // index into Band array (representing the current band)

int t = 0, second_counter = 0;

void setup()
{
    Serial.begin(9600);
    Serial.println("setup()");

    // print EEPROM size
    int ee_len = EEPROM.length();
    Serial.print("EEPROM length =");
    Serial.println(ee_len);

    Serial.print("Band[] length =");
    //Serial.println(sizeof(BandParameters) * NUMBER_OF_BANDS);

    // clear the EEPROM contents
    for (int j = 0; j < ee_len; j++)
    {
        EEPROM.write(j, 0);
    }

    // initialise Band array
    for (int n = 0; n < NUMBER_OF_BANDS; n = n + 1)
        Band[n].active = 0; // make sure all are inactive to start with
    Band[0] = (BandParameters){1, 3560000ULL, 100};
    Band[1] = (BandParameters){1, 7030000ULL, 100};
    Band[2] = (BandParameters){1, 14060000ULL, 100};
    Band[3] = (BandParameters){1, 21060000ULL, 100};
    Band[4] = (BandParameters){1, 28060000ULL, 100};
    //  Band[5]  = (BandParameters){1,   7030000ULL,  100};
    //  Band[6]  = (BandParameters){1,  10116000ULL,  100};
    //  Band[7]  = (BandParameters){1,  14060000ULL,  100};
    //  Band[8]  = (BandParameters){1,  18096000ULL,  100};
    //  Band[9]  = (BandParameters){1,  21060000ULL,  100};
    //  Band[10] = (BandParameters){1,  24906000ULL,  100};
    //  Band[11] = (BandParameters){1,  28060000ULL,  100};
    //  Band[12] = (BandParameters){1,  50060000ULL,  100};
    //  Band[13] = (BandParameters){1,  70200000ULL,  100};
    //  Band[14] = (BandParameters){1, 144060000ULL,  100};

    // write the current band index (into Band[]) into EEPROM byte 0
    byte b = 0;
    EEPROM.write(0, b);

    // put the entire Band array into EEPROM
    int element_len = sizeof(BandParameters);
    for (int i = 0; i < NUMBER_OF_BANDS; i = i + 1)
    {
        EEPROM.put(1 + (i * element_len), Band[i]);
    };

    // dump out the Band array for diagnostics
    for (int n = 0; n < NUMBER_OF_BANDS; n = n + 1)
    {
        Serial.print((int)Band[n].active);
        Serial.print(" ");
        Serial.print(Band[n].Hz);
        Serial.print(" ");
        Serial.print((long)Band[n].radix);
        Serial.println();
    }

    t = millis();
}

void loop()
{
    /*
  if((millis() - t) > 1000){
    t=millis();
    second_counter++;
    Serial.println(second_counter);
  }
      */
}
