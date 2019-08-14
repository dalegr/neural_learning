#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float
activation(float x, float w, float b)
{
  return x*w + b;
}

int
main(int argc, char **argv)
{
  const float b = 1.;
  const float eta = 1.;
  int learn = 0;
  float x, f0, w, f, delta;

  // Read args
  if (argc != 2 && argc != 3)
    return 1;
  
  if (argc == 3)
  {
      learn = 1;
      f0 = atof(argv[2]);
  }
  x = atof(argv[1]);

  FILE *file = fopen("weight", "r+");
  if (!f)
    return 0;
  fread(&w, sizeof(w), 1, file);

  f = activation(x, w, b);
  if (learn)
  {
    delta = eta*(f0 - f)*x;
    w += delta;
    fseek(file, 0, SEEK_SET);
    fwrite(&w, sizeof(w), 1, file);
  }
  printf("answer = %f\nweight = %f\n", f, w);

  fclose(file);
  return 0;
}
