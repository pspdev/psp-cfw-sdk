int toupper(int ch)
{
    ch = (unsigned char)ch;
    if((ch >= 'a') && (ch <= 'z'))
        ch = 'A' + (ch - 'a');

    return ch;
}