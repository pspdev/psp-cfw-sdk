int iscntrl(int ch)
{
    ch = (unsigned char)ch;
    return ( ch < ' ' || ch == 0x7F );
}