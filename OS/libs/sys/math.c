// https://stackoverflow.com/questions/3068397/finding-the-length-of-an-integer-in-c
int numLen(unsigned x)
{
    // this is either a fun exercise in optimization
    // or it's extremely premature optimization.
    if (x >= 100000)
    {
        if (x >= 10000000)
        {
            if (x >= 1000000000)
                return 10;
            if (x >= 100000000)
                return 9;
            return 8;
        }
        if (x >= 1000000)
            return 7;
        return 6;
    }
    else
    {
        if (x >= 1000)
        {
            if (x >= 10000)
                return 5;
            return 4;
        }
        else
        {
            if (x >= 100)
                return 3;
            if (x >= 10)
                return 2;
            return 1;
        }
    }
}

int pow(int base, int exp)
{
    int result = 1;
    while (exp > 0)
    {
        if (exp & 1)
            result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

int reverse(int n)
{
    int reverse = 0;
    while (n != 0)
    {
        reverse = reverse * 10 + (n % 10);
        
        n /= 10;
    }
    return reverse;
}