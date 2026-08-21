int toascii(int ch)
{
    ch = (unsigned char)ch;
    return ( ch & 0x7F );
}