int isalnum(int ch)
{
    ch = (unsigned char)ch;
    return ( (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') );
}