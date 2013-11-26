int mainnew()
{
    int n = 1000;
    int** a = new int*[n];
    int** b = new int*[n];

    for(int i = 0; i < n; i++)
    {
        a[i] = new int[n];
        b[i] = new int[n];
    }


    for(int i = 0; i < n; i++)
    {
        delete [] a[i];
        delete [] b[i];
    }

    delete []a;
    delete []b;

    return 0;
}