// Test .npy writing

#include <math.h>
#include "npy.h"

int main() {
  // sqrt(range(10))
  const int size = 10;
  const int ndim = 1;
  const int shape[ndim] = {size};
  float data[size];
  for (int i = 0; i < size; i++)
    data[i] = sqrtf(i);

  // Write .npy file
  FILE* f = fopen("sqrts.npy", "wb");
  skip_npy_header(f);
  fwrite(data, sizeof(float), size, f);
  write_npy_header(f, ndim, shape, NPY_FLOAT);
  fclose(f);

  // Done!
  return 0;
}
