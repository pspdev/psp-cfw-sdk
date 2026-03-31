/*
 * Basic Sprintf functions thanks to Fanjita and Noobz
 */ 

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

void numtohex8(char *dst, int n)
{
   int i;
   static char hex[]="0123456789ABCDEF";
   for (i=0; i<8; i++)
   {
      dst[i]=hex[(n>>((7-i)*4))&15];
   }
}

void numtohex4(char *dst, int n)
{
   int i;
   static char hex[]="0123456789ABCDEF";
   for (i=4; i<8; i++)
   {
      dst[i-4]=hex[(n>>((7-i)*4))&15];
   }
}

void numtohex2(char *dst, int n)
{
   int i;
   static char hex[]="0123456789ABCDEF";
   for (i=6; i<8; i++)
   {
      dst[i-6]=hex[(n>>((7-i)*4))&15];
   }
}

// limited sprintf function - avoids pulling in large library
int writeFormat(char *xibuff, size_t xcount, const char *xifmt, uint32_t xidata)
{
  // check for empty format
  if (xifmt[0] == '\0')
  {
    *xibuff = '?';
    return(1);
  }
  else
  {
    if ((xifmt[0] == '0') &&
        (xifmt[1] == '8') &&
        (xifmt[2] == 'l') &&
        (xifmt[3] == 'X') &&
        (xcount > 8))
    {
      numtohex8(xibuff, xidata);
      return(8);
    }
    else if ((xifmt[0] == '0') &&
             (xifmt[1] == '4') &&
             (xifmt[2] == 'X') &&
             (xcount > 4))
    {
      numtohex4(xibuff, xidata);
      return(4);
    }
    else if ((xifmt[0] == '0') &&
             (xifmt[1] == '2') &&
             (xifmt[2] == 'X') &&
             (xcount > 2))
    {
      numtohex2(xibuff, xidata);
      return(2);
    }
    else if (xifmt[0] == 'c' && xcount > 1)
    {
      *xibuff = (unsigned char)xidata;
      return(1);
    }
    else if (xifmt[0] == 's')
    {
      const char *lptr   = (const char *)xidata;
      int         lcount = 0;

      /***********************************************************************/
      /* Artificially limit %s format to 150 bytes, as a cheap way to        */
      /* avoid log buffer overflow.                                          */
      /***********************************************************************/
      while ((*lptr != 0) && (lcount < xcount))
      {
        *xibuff++ = *lptr++;
        lcount++;
      }
      return(lcount);
    }
    else if (xifmt[0] == 'd')
    {
      char lbuff[15];
      int  lnumbuff = 0;
      int  lcount = 0;
      int  lchar;
      int lnum   = (int)xidata;
      if (lnum < 0)
      {
        *xibuff++ = '-';
        lcount++;
        lnum = 0 - lnum;
      }

      lchar = lnum % 10;
      lbuff[0] = lchar + 48;
      lnumbuff++;
      lnum -= lchar;

      while (lnum > 0)
      {
        lnum  = lnum / 10;
        lchar = lnum % 10;
        lbuff[lnumbuff++] = lchar + 48;
        lnum -= lchar;
      }

      while (lnumbuff > 0 && lcount < xcount)
      {
        *xibuff++ = lbuff[--lnumbuff];
        lcount++;
      }

      return(lcount);
    }
    else if ((xifmt[0] == 'p') && xcount > 8)
    {
      numtohex8(xibuff, xidata);
      return(8);
    }

    return(0);
  }
}

void vsnprintf(char *xobuff, size_t xsize, const char *xifmt, va_list args)
{
  char lfmt[10];
  char *lfmtptr;

  while (*xifmt != '\0' && xsize)
  {
    if (*xifmt != '%')
    {
      *xobuff++ = *xifmt++;
    }
    else
    {
      xifmt++;  // skip the %
      lfmtptr = lfmt;
      while ((*xifmt == '0')
          || (*xifmt == '2')
          || (*xifmt == '4')
          || (*xifmt == '8')
          || (*xifmt == 'l')
          || (*xifmt == 'X')
          || (*xifmt == 'd')
          || (*xifmt == 'p')
          || (*xifmt == 's')
          || (*xifmt == 'c'))
      {
        *lfmtptr ++ = *xifmt++;
      }
      *lfmtptr = '\0';

      size_t xidata = va_arg(args, size_t);

      int n = writeFormat(xobuff, xsize, lfmt, xidata);
      if (n < xsize) {
        xsize -= n;
        xobuff += n;
      }
      else {
        xsize = 0;
      }

    }
  }

  *xobuff = '\0';
}

void vsprintf(char *xobuff, const char *xifmt, va_list args){
    vsnprintf(xobuff, (size_t)-1, xifmt, args);
}

void snprintf(char *xobuff, size_t xsize, const char *xifmt, ...){
    va_list args;
    va_start(args, xifmt);
    vsnprintf(xobuff, xsize, xifmt, args);
}


void sprintf(char *xobuff, const char *xifmt, ...){
    va_list args;
    va_start(args, xifmt);
    vsnprintf(xobuff, (size_t)-1, xifmt, args);
}
