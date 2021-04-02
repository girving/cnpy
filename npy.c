// C code to write .npy files

#include "npy.h"
#include <stdlib.h>

static void dtype_info(const int dtype, int* bytes, char* letter) {
  switch (dtype) {
    #define CASE(T, dtype, let) case dtype: *bytes = sizeof(T); *letter = let; break;
    CASE(_Bool,              NPY_BOOL,       'b')
    CASE(signed char,        NPY_BYTE,       'i')
    CASE(unsigned char,      NPY_UBYTE,      'u')
    CASE(short,              NPY_SHORT,      'i')
    CASE(unsigned short,     NPY_USHORT,     'u')
    CASE(int,                NPY_INT,        'i')
    CASE(unsigned int,       NPY_UINT,       'u')
    CASE(long,               NPY_LONG,       'i')
    CASE(unsigned long,      NPY_ULONG,      'u')
    CASE(long long,          NPY_LONGLONG,   'i')
    CASE(unsigned long long, NPY_ULONGLONG,  'u')
    CASE(float,              NPY_FLOAT,      'f')
    CASE(double,             NPY_DOUBLE,     'f')
    CASE(long double,        NPY_LONGDOUBLE, 'f')
    #undef CASE
    default:
      fprintf(stderr, "npy.c: invalid dtype %d\n", dtype);
      exit(1);
  }
}

// Padded header size to enable easy skipping
#define NPY_HEADER_SIZE 256

void skip_npy_header(FILE* f) {
  fseek(f, NPY_HEADER_SIZE, SEEK_SET);
}

void write_npy_header(FILE* f, const int ndim, const int* shape, const int dtype) {
  // Grab dtype info
  int bytes;
  char letter;
  dtype_info(dtype, &bytes, &letter);

  // Move to beginning of file in case we just wrote the binary data
  fseek(f, 0, SEEK_SET);

  // Write header
  const uint16_t header_size = NPY_HEADER_SIZE - 10;
  fwrite("\x93NUMPY\x01\x00", 1, 8, f);
  fwrite(&header_size, 1, 2, f);
  fprintf(f, "{'descr': '<%c%d', 'fortran_order': False, 'shape': (", letter, bytes);
  for (int i = 0; i < ndim; i++)
    fprintf(f, "%d,", shape[i]);
  fputs("), }", f);

  // Pad with spaces out to NPY_HEADER_SIZE-1, and finish with a newline
  fprintf(f, "%*s\n", NPY_HEADER_SIZE - 1 - (int)ftell(f), "");
}
