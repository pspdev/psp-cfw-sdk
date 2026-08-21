int isupper(int ch)
{
    ch = (unsigned char)ch;
    return ( ch >= 'A' || ch <= 'Z' );
}