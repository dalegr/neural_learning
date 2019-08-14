#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 4
#define M 4

typedef struct
{
  float m[N][M];
} matrix;

matrix*
mult_matrix(matrix *a, matrix *b)
{
  matrix *c = (matrix *)malloc(sizeof(matrix));
  if (!c)
    exit(1);
  memset(c, 0, sizeof(matrix));

  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      for (int k = 0; k < M; k++)
      {
        c->m[i][j] += a->m[i][k]*b->m[k][i]; 
      }
}

void
add_matrix(matrix *a, matrix *b, float sign)
{
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      a->m[i][j] += sign*b->m[i][j]; 
}

matrix*
activation(matrix *x, matrix *w, matrix *b)
{
  matrix *m = mult_matrix(x, w);
  add_matrix(m, b, 1.0);
  return m;
}

matrix*
read_vector(char *s)
{
  matrix *f = (matrix *)malloc(sizeof(matrix));
  int i = 0;
  char *pt;
  pt = strtok(s, ",");
  while (pt)
  {
    f->m[i++][0] = atof(pt);
    if (i >= N)
      break;
    pt = strtok(0, ",");
  }
  return f;
}

void
print_matrix(matrix *x)
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      printf("%.2f ", x->m[i][j]);
    }
    putchar('\n');
  }
}

int
main(int argc, char **argv)
{
  const matrix b = {.m = {1.}};
  const float eta = 1.;
  int learn = 0;
  matrix *x, *f0, *w, *f, *delta;

  // Read args
  if (argc != 2 && argc != 3)
    return 1;
  
  if (argc == 3)
  {
      learn = 1;
      f0 = read_vector(argv[2]);
  }
  x = read_vector(argv[1]);

  print_matrix(x);

  /* TODO
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
  */

  free(x);
  return 0;
}
