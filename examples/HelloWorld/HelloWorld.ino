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

//  This example program shows how to instantiate a buffered printing object.
//
//  The message "Hello World\n\r" (13 bytes) will get written once per second.
//  Only *one* write to Serial is executed, even though *six* writes to 
//    'allAtOnce' were executed.  This can have a dramatic impact on 
//    the performance of Print classes that do a lot of work for 
//    individual writes (e.g., WiFiClient).


NeoBufferedPrint<64> allAtOnce( Serial );


void setup()
{
  Serial.begin( 9600 );
}

void loop()
{
  allAtOnce.print( "He" );                         // 1: RAM string (char[] or char *)
  allAtOnce.print( F("llo") );                     // 2: FLASH string (F macro saves RAM)
  allAtOnce.print( (char) 32 );                    // 3: ASCII space character
  allAtOnce.write( 'W' );                          // 4: single character

  uint8_t byteArray[] = { 'o', 'r', 'l', 'd' };
  allAtOnce.write( byteArray, sizeof(byteArray) ); // 5: four bytes from an array

  allAtOnce.println();                             // 6: empty println

  allAtOnce.flush();
  
  delay( 1000 );
}