#ifndef NEOBUFFERED_PRINT_H
#define NEOBUFFERED_PRINT_H

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

template <size_t N>
class NeoBufferedPrint : public Print
{
  public:
    NeoBufferedPrint( Print &output )
      : _out( output ), _count( 0 )
        {};
    ~NeoBufferedPrint() { flush(); };

    size_t write( uint8_t b )
    {
      _buffer[ _count++ ] = b;

      //  When the buffer is full, flush it all at once to the output stream
      if (_count == N)
        flush();

      return 1;
    }

    using Print::write; // pull in all the other write methods

    virtual void flush()
    {
      if (_count) {
        _out.write( _buffer, _count );
        _count = 0;
      }
    }

  protected:
    Print    &_out;
    uint8_t   _buffer[ N ];
    uint16_t  _count;
};

#endif
