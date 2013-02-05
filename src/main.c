#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "basic.h"

void execute_optimized_bf(char * code);

int read_file(char ** buffer, const char * path)
{
  FILE * file;
  size_t size;
  
  file = fopen(path, "rb");

  fseek(file, 0L, SEEK_END);
  size = ftell(file);
  fseek(file, 0L, SEEK_SET);

  *buffer = malloc(size + 1);
  fread(*buffer, 1, size, file);
  (*buffer)[size] = 0;
 
  fclose(file);

  return 0;
}

int main(int argc, char ** argv)
{
  char * buffer;
  time_t start, end;

  start = time(NULL);

  if(read_file(&buffer, argv[1]) == 0)
    {
      execute_optimized_bf(buffer);
    }
  else
    printf("error while loading file!");

  end = time(NULL);
  printf("\nexecution time: %i seconds\n", ((int)end - (int)start));

  return 0;
}
