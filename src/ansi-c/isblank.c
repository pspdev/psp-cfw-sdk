int isblank(int ch)
{
    ch = (unsigned char)ch;
    return ( ch == ' ' || ch == '\t' );
}