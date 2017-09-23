int lib_func2(int x)
{
    int z = x*x;
    return z;
}

int lib_func1(int x, int y)
{
    int z;
    z = lib_func2(x) + lib_func2(y);
    return z;
}

