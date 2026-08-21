extern int isspace(int ch);
extern unsigned long strtoul(const char *nptr, char **endptr, register int base);

long strtol (const char *__restrict __n, char **__restrict __end_PTR, int __base)
{
  register const char *p;
  int result;

  /*
   * Skip any leading blanks.
   */
  p = __n;
  while (isspace((unsigned char)*p)) {
    p += 1;
  }

  /*
   * Check for a sign.
   */
  if (*p == '-') {
    p += 1;
    result = -1*(strtoul(p, __end_PTR, __base));
  } else {
    if (*p == '+') {
      p += 1;
    }
    result = strtoul(p, __end_PTR, __base);
  }

  if ((result == 0) && (__end_PTR != 0) && (*__end_PTR == p)) {
    *__end_PTR = (char *)__n;
  }

  return result;
}