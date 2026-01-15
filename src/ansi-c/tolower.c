int tolower(int s)
{
    if((s >= 'A') && (s <= 'Z'))
        s = 'a' + (s - 'A');

    return s;
}