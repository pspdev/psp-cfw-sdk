/*
 * This file is part of PRO CFW.

 * PRO CFW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * PRO CFW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PRO CFW. If not, see <http://www.gnu.org/licenses/ .
 */

char * hex64(unsigned long long v)
{
    unsigned int hi = (unsigned int)(v >> 32);
    unsigned int lo = (unsigned int)v;

    // Result String
    static char result[17];
    
    // Iterate Nibbles
    unsigned int i = 0; for(; i < 16; i++)
    {
        // Fetch Nibble
        char nibble = i < 8 ? (char)((lo >> (i << 2)) & 0xF) : 
                              (char)((hi >> ((i-8) << 2)) & 0xF);
        
        // Number
        if(nibble >= 0 && nibble <= 9) nibble += '0';
        
        // Character
        else nibble += 'A' - 0xA;
        
        // Copy Character
        result[15 - i] = nibble;
    }
    
    // Terminate String
    result[16] = 0;
    
    // Return String
    return result;
}
