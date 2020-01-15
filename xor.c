#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 2
#define M 2

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
        c->m[i][j] += a->m[i][k]*b->m[k][j]; 
      }
  return c;
}

void
mult_matrix_s(matrix *a, float s)
{
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
    {
      a->m[i][j] *= s;
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

matrix*
read_matrix(char *s)
{
  matrix *f = (matrix *)malloc(sizeof(matrix));
  int i = 0, j = 0;
  char *pt;
  pt = strtok(s, ",");
  while (pt)
  {
    f->m[i++][j] = atof(pt);
    if (i >= N)
    {
      i = 0;
      j++;
    }
    if (j >= M)
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

matrix*
read_matrix_from_file(const char *fname)
{
  FILE *f = fopen(fname, "r+");
  if (!f)
    return 0;
  char buf[32] = {0};
  fread(buf, 32, 1, f);
  matrix *m = read_matrix(buf);
  fclose(f);
  return m;
}

void
write_matrix_to_file(const char *fname, matrix *m)
{
  FILE *f = fopen(fname, "r+");
  if (!f)
    return;
  char buf[32] = {0};
  for (int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
    {
      if (i == (N - 1) && j == (N - 1) )
        fprintf(f, "%f", m->m[i][j]);
      else
        fprintf(f, "%f,", m->m[i][j]);
    }
  fputc('\n', f);
  fclose(f);
}

int
main(int argc, char **argv)
{
  matrix b = {.m = {0.}};
  const float eta = 0.2;
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

  if (!f)
    return 0;
  w = read_matrix_from_file("weight");  

  f = activation(x, w, &b);
  if (learn)
  {
//    delta = eta*(f0 - f)*x;
    add_matrix(f0, f, -1.);
    mult_matrix_s(f0, eta);
    delta = mult_matrix(f0, x);
    add_matrix(w, delta, 1.);
    write_matrix_to_file("weight", w);
  }
  printf("answer:\n");
  print_matrix(f);
  printf("weights:\n");
  print_matrix(w);

  free(x);
  free(delta);
  free(w);
  free(f0);
  free(f);
  return 0;
}
