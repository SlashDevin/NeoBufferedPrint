NeoBufferedPrint
======

Intermediate printing class for reducing the number of writes.  This can dramatically improve performance on IoT-type devices.
I
Goal
======

To reduce the number of `write`/`Print` calls to the destination.  This can have a dramatic impact on the performance of Print classes that do a lot of work for individual writes (e.g., WiFiClient).

Create an instance with the desired buffer size, attached to the destination:

```
WiFiClient           client;              // Original destination
NeoBufferedPrint<64> allAtOnce( client ); // Intermediate buffer
```

The destination can be any class derived from `Print`.  This includes

*  [Serial](https://www.arduino.cc/en/Reference/Serial), [AltSoftSerial](https://github.com/PaulStoffregen/AltSoftSerial) or [NeoSWSerial](https://github.com/SlashDevin/NeoSWSerial)
*  LED/LCD and other display libraries (e.g., [LiquidCrystal](https://www.arduino.cc/en/Reference/LiquidCrystal))
*  I2C libraries (e.g., [Wire](https://www.arduino.cc/en/Reference/Wire))
*  File instances from SD card libraries (e.g., [SdFat](https://github.com/greiman/SdFat) (recommended) or [SD](https://www.arduino.cc/en/Reference/SD) (older))
*  EthernetClient & Server from the [Ethernet library](https://www.arduino.cc/en/Reference/Ethernet)
*  WiFiClient & Server from the [WiFi library](https://www.arduino.cc/en/Reference/WiFi)

Then use this instance instead of the original destination:

```
    allAtOnce.print( F("GET /IoT/wifipost.php?") );

    // An example time structure from the Time library:
    //    2018-MAR-28 23:45:56
    tmElements_t tm = { 56, 45, 23, 1, 28, 3, (uint8_t)(2018-1970) };

    allAtOnce.print( F("time=") );
    if (tm.Hour < 10)
      allAtOnce.print( '0' );           // leading zero
    allAtOnce.print( tm.Hour );

    if (tm.Minute < 10)
      allAtOnce.print( '0' );
    allAtOnce.print( tm.Minute );

    if (tm.Second < 10)
      allAtOnce.print( '0' );           // leading zero
    allAtOnce.print( tm.Second );

    allAtOnce.println( F(" HTTP/1.1") );
    allAtOnce.println( F("Host: website.com") );
    allAtOnce.println( F("Connection: close") );
    allAtOnce.println();
```

When the individual print operations are finished, be sure to call `flush()`:

```
    allAtOnce.flush();
```

Any remaining bytes will be written with one operation.  This will guarantee the minimum number of writes, as determined by the buffer size.

The instance destructor will also perform an automatic flush:

```
  if (client.connect( server, port )) {
    Serial.println( F("Connecting...") );

    NeoBufferedPrint<64> allAtOnce( client ); // A local variable

    allAtOnce.print( F("GET /IoT/wifipost.php?") );

        ...
        
    allAtOnce.println( F(" HTTP/1.1") );
    allAtOnce.println( F("Host: ") );
    allAtOnce.println(server);
    allAtOnce.flush();
      // Force this part to go out

    clientGet.println( F("User - Agent: ESP8266 / 1.0") );

    allAtOnce.println( F("Connection: close") );
    allAtOnce.println();\
      // These last two lines will get written by the allAtOnce destructor,
      //    because it goes out-of-scope of this "if" statement block.

  } else {
    // if you couldn't make a connection
    Serial.println("Connection failed");
  }
```

Acknowledgements
==========

This is a reduced-functionality version of the [BufferedPrinter class](https://github.com/Chris--A/PrintEx/blob/master/src/tools/BufferedPrinter.h) by [Chris--A](https://github.com/Chris--A) (aka [pyro_65](https://forum.arduino.cc/index.php?action=profile;u=54891) on the Arduino forum)