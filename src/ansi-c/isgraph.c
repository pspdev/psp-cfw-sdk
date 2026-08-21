int isgraph(int ch)
{
    ch = (unsigned char)ch;
    return ( ch >= '!' && ch <= '~' );
}