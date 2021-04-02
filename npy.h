// C code to write .npy files
#pragma once

// Example usage:
//   FILE* f = fopen(path, "wb");
//   skip_npy_header(f);
//   ...write binary data...
//   write_npy_header(f, ndim, shape, dtype);
//   fclose(f);

#include <stdio.h>

// Lifted from numpy/ndarraytypes.h
enum NPY_TYPES { NPY_BOOL=0,
                 NPY_BYTE, NPY_UBYTE,
                 NPY_SHORT, NPY_USHORT,
                 NPY_INT, NPY_UINT,
                 NPY_LONG, NPY_ULONG,
                 NPY_LONGLONG, NPY_ULONGLONG,
                 NPY_FLOAT, NPY_DOUBLE, NPY_LONGDOUBLE,
                 NPY_CFLOAT, NPY_CDOUBLE, NPY_CLONGDOUBLE,
                 NPY_OBJECT=17,
                 NPY_STRING, NPY_UNICODE,
                 NPY_VOID
};

// Skip space for the header at the beginning of a file.
// Call this if you don't know the shape prior to writing the data.
void skip_npy_header(FILE* f);

// Write an .npy header at the beginning of the file
void write_npy_header(FILE* f, const int ndim, const int* shape, const int dtype);
