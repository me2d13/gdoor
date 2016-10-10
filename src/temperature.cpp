#include "Arduino.h"
#include <DHT22.h>
#include "temperature.h"
#include "com.h"
#include "log.h"

// Data wire is plugged into port 7 on the Arduino
// Connect a 4.7K resistor between VCC and the data pin (strong pullup)

/* Sw installed using commands

platformio lib list
platformio lib search "i2c" --framework="arduino"
platformio lib install 115
platformio lib show 115

cat ~/.platformio/lib/DHT22_ID115/README
cat ~/.platformio/lib/DHT22_ID115/examples/Serial/Serial.ino


*/

// Setup a DHT22 instance
DHT22 myDHT22(DHT22_PIN);

void setupTemperature(void)
{
  
}

void readTemperature()
{ 
  DHT22_ERROR_t errorCode;
  
  // The sensor can only be read from every 1-2s, and requires a minimum
  // 2s warm-up after power-on.
  delay(2000);
  
  debug("Requesting temperature data...");
  errorCode = myDHT22.readData();
  switch(errorCode)
  {
    case DHT_ERROR_NONE:
      //Serial.print("Got Data ");
      //Serial.print(myDHT22.getTemperatureC());
      //Serial.print("C ");
      //Serial.print(myDHT22.getHumidity());
      //Serial.println("%");
      
      // Alternately, with integer formatting which is clumsier but more compact to store and
	  // can be compared reliably for equality:
	  //	  
      char buf[128];
      int temperature;
      int humidity;
      temperature = myDHT22.getTemperatureCInt();
      humidity = myDHT22.getHumidityInt();
      sprintf(buf, "Integer-only reading: Temperature %hi.%01hi C, Humidity %i.%01i %% RH",
    		  temperature/10, abs(temperature%10),
			  humidity/10, humidity%10);
      debug(buf);
      sendMessageIntInt(TEMPERATURE_UNIT_NAME, temperature, humidity);
      break;
    case DHT_ERROR_CHECKSUM:
      debug("Temperature checksum error");
      /*Serial.print("check sum error ");
      Serial.print(myDHT22.getTemperatureC());
      Serial.print("C ");
      Serial.print(myDHT22.getHumidity());
      Serial.println("%");*/
      break;
    case DHT_BUS_HUNG:
      debug("Temperature error: BUS Hung ");
      break;
    case DHT_ERROR_NOT_PRESENT:
      debug("Temperature error: Not Present ");
      break;
    case DHT_ERROR_ACK_TOO_LONG:
      debug("Temperature error: ACK time out ");
      break;
    case DHT_ERROR_SYNC_TIMEOUT:
      debug("Temperature error: Sync Timeout ");
      break;
    case DHT_ERROR_DATA_TIMEOUT:
      debug("Temperature error: Data Timeout ");
      break;
    case DHT_ERROR_TOOQUICK:
      debug("Temperature error: Polled to quick ");
      break;
  }
}

void processTemperature() {
	  if (compareReceivedTopic("GET")) {
		  readTemperature();
	  } else {
	    debug("Unknown TEMPERATURE command (use GET)");
	  }
}
