int ispunct(int ch)
{
    ch = (unsigned char)ch;
    return ( ( ch >= '!' && ch <= '/' ) || ( ch >= ':' && ch <= '@' ) || ( ch >= '[' && ch <= '`' ) || ( ch >= '{' && ch <= '~' ) );
}