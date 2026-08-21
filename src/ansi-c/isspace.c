int isspace(int ch)
{
    ch = (unsigned char)ch;
    return ( ch == ' ' || ch == '\f' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v' );
}