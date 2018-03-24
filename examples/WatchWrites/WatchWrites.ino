#include <NeoBufferedPrint.h>

//  Copyright (C) 2018, SlashDevin
//
//  This file is part of NeoBufferedPrint
//
//  NeoBufferedPrint is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  NeoBufferedPrint is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with NeoBufferedPrint.  If not, see <http://www.gnu.org/licenses/>.

//  This is the HelloWorld.ino example, minus the flush calls.  It also
//    overrides the NeoBufferedPrint 'flush()' method so you can see
//    when the actual writes occur.
//  With a buffer size of 64, the message "Hello World\n\r" (13 bytes) gets 
//    written about 5 times, once every 5 seconds.
//  The message is broken up at different places, because one loop
//    iteration generates 13 characters.  5 times 13 is 65,
//    so one character is saved for the next interval.  The
//    break gradually moves back one character at a time.


//  Inherit from the generic NeoBufferedPrint class so we can
//     override the flush method.  Then we can see when it *really*
//     gets called to write the buffer to Serial.

template <size_t N, class NBP = NeoBufferedPrint<N>>
class WatchWrites : public NBP
{
  public:
    WatchWrites( Print & output ) : NBP( output ) {};

    void flush()
    {
      if (NBP::_count > 0) {
        Serial.println();
        Serial.print( F("Writing ") );
        Serial.println( NBP::_count );
        NBP::flush();
      }
    }
};

WatchWrites<64> allAtOnce( Serial );


void setup()
{
  Serial.begin( 9600 );
}


void loop()
{
  allAtOnce.print( "He" );      // RAM string (char[] or char *)
  allAtOnce.print( F("llo") );  // FLASH string (F macro saves RAM)
  allAtOnce.print( (char) 32 ); // ASCII space character
  allAtOnce.write( 'W' );       // single character

  uint8_t byteArray[] = { 'o', 'r', 'l', 'd' };
  allAtOnce.write( byteArray, sizeof(byteArray) );
  allAtOnce.println();

  delay( 1000 );
}