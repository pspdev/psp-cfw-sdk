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
 

typedef unsigned int size_t;

extern size_t strnlen(const char *s, size_t len);

// Copy String Buffer
char *strncpy(char *to, const char *from, unsigned int n)
{
    char *oto = to;
    
    // Position
    unsigned int position = 0;
    
    // Copy Bytes
    while(from[position] != 0 && n)
    {
        // Copy Byte
        to[position] = from[position];
        
        // Change Position
        position++;

        // decrease counter
        n--;
    }
    
    // Terminate String
    to[position] = 0;
    
    return oto;
}
