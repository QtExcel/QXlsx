// DynArray2D.h
#ifndef DYNARRAY2D_H
#define DYNARRAY2D_H

// Code from https://www.qtcentre.org/threads/31440-two-dimensional-array-size-determined-dynamically
// Some code is fixed by j2doll

template <typename T> class DynArray2D
{
public:
    DynArray2D(int n, int m)
    {
        _n = n;
        _array = new T*[n];
        for(int i = 0; i < n; i++)
        {
            _array[i] = new T[m];
        }
    }

    void setValue(int n, int m, T v)
    {
        _array[n][m] = v;
    }

    T getValue(int n, int m)
    {
        return _array[n][m];
    }

    ~DynArray2D()
    {
        for (int i = 0 ; i < _n ; i++)
        {
            delete [] _array[i];
        }
        delete [] _array;
    }

protected:
    T **_array;
    int _n;
};


#endif // DYNARRAY2D_H
