int global_data = 42;

int lib_func3()
{
    return global_data;
}

int lib_func2(int x)
{
    int z = x*x;
    return z;
}

int lib_func1(int x, int y)
{
    int z;
    z = global_data + lib_func2(x) + lib_func2(y);
    return z;
}

