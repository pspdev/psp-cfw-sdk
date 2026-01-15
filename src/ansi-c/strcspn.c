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

extern int strlen(char*);

// Search Needle in Haystack
int strcspn(char * str1, char * str2)
{
    // Iterate Symbols from Haystack
    unsigned int i = 0;
    for(; i < strlen(str1); i++)
       {
        // Iterate Symbols from Needle
        unsigned int j = 0; for(; j < strlen(str2); j++)
           {
            // Match found
            if(str1[i] == str2[j]) break;
        }
    }
    
    // Return Offset
    return i;
}
