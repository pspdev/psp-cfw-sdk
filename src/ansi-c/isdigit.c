int isdigit(int ch)
{
    ch = (unsigned char)ch;
    return ( ch >= '0' && ch <= '9' );
}