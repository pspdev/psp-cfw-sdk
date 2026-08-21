int isxdigit(int ch)
{
    ch = (unsigned char)ch;
    return ( ( ch >= '0' && ch <= '9' ) || ( ch >= 'a' && ch <= 'f' ) || ( ch >= 'A' && ch <= 'F' ) );
}