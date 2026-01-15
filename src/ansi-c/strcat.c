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


// Concatenates string s + append
char *strcat(char *s, const char *append)
{
    if (!s || !append) {
        return 0;
    }

    char *pRet = s;
    while(*s)
    {
        s++;
    }

    while(*append)
    {
        *s++ = *append++;
    }

    *s = 0;

    return pRet;
}
