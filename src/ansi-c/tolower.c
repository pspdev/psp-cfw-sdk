int tolower(int ch)
{
    ch = (unsigned char)ch;
    if((ch >= 'A') && (ch <= 'Z'))
        ch = 'a' + (ch - 'A');

    return ch;
}