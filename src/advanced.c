#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "basic.h"

typedef struct element
{
  char id;
  int data;
} element_t;

element_t * optimize_code(char * code)
{
  element_t * elements = malloc(strlen(code) * sizeof(element_t));
  element_t * element_count = elements;
  element_t * element_count2 = elements;
  int i;

  code--;
  while(*++code != 0)
    {
      switch(*code)
	{
	case '+':
	case '-':
	case '<':
	case '>':
	  if((*(element_count - 1)).id == *code)
	    {
	      (*(element_count - 1)).data += 1;
	    }
	  else
	    {
	      (*element_count).id = *code;
	      (*element_count).data = 1;
	      element_count++;
	    }
	  break;

	case '[':
	case ']':
	case '.':
	case ',':
	  (*element_count).id = *code;
	  (*element_count).data = 0;
	  element_count++;
	  break;
	}
    }
  (*element_count).id = 0;
  (*element_count).data = 0;

  element_count = elements;
  while((*element_count).id != 0)
    {
      printf("%c%c%c%c\n", (*(element_count - 1)).id, (*(element_count + 0)).id, (*(element_count + 1)).id, (*(element_count + 2)).id);
      if((*(element_count + 0)).id == '[' &&
	 (*(element_count + 1)).id == '-' &&
	 (*(element_count + 2)).id == ']')
	{
	  (*element_count2).id = 's';
	  (*element_count2).data = 0;

	  element_count += 2;
	}
      else if((*(element_count + 0)).id == '[' &&
	      (*(element_count + 1)).id == '>' &&
	      (*(element_count + 2)).id == ']')
	{
	  (*element_count2).id = 'f';
	  (*element_count2).data = (*(element_count + 1)).data;

	  element_count += 2;
	}
      else if((*(element_count + 0)).id == '[' &&
	      (*(element_count + 1)).id == '<' &&
	      (*(element_count + 2)).id == ']')
	{
	  (*element_count2).id = 'b';
	  (*element_count2).data = (*(element_count + 1)).data;

	  element_count += 2;
	}
      else if((*element_count).id == '[')
	{
	  element_t * tmp_element_count = element_count;
	  tmp_element_count = element_count;
	  tmp_element_count++;
	  for(i = 1; i > 0; tmp_element_count++)
	    {
	      if((*tmp_element_count).id == '[')
		i++;
	      else if((*tmp_element_count).id == ']')
		i--;
	    }
	  tmp_element_count--;

	  (*element_count2).data = tmp_element_count - element_count;
	}
      else if((*element_count).id == ']')
	{
	  element_t * tmp_element_count = element_count;
	  tmp_element_count = element_count;
	  tmp_element_count--;
	  for(i = 1; i > 0; tmp_element_count--)
	    {
	      if((*tmp_element_count).id == ']')
		i++;
	      else if((*tmp_element_count).id == '[')
		i--;
	    }

	  (*element_count2).data = tmp_element_count - element_count;
	}
      element_count2++;
      element_count++;
    }
  elements = realloc(elements, ((size_t)element_count2 - (size_t)elements) * sizeof(element_t));

  return elements;
}

void execute_optimized_bf(char * code)
{
  int stop = 1;
  FILE * output;
  char * buffer = malloc(30000);
  char * bufferptr = buffer;

  element_t * elements_buffer, * elements;
  
  memset(buffer, 0, 30000);

#ifdef PRINT
  output = fopen("output.b", "w");
#else
  output = stdout;
#endif
  
  elements_buffer = optimize_code(code);
  elements = elements_buffer;

#ifdef PRINT
  while(1)
    {
      if((*elements).id == 0)
	{
	  break;
	}
      fprintf(output, "%c", (*elements).id);

      elements++;
    }

  elements = elements_buffer;
#endif

  while(stop)
    {
      switch((*elements).id)
	{
	case '+':
	  (*bufferptr) += (*elements).data;
	  break;
	  
	case '-':
	  (*bufferptr) -= (*elements).data;
	  break;

	case '>':
	  bufferptr += (*elements).data;
	  break;
	  
	case '<':
	  bufferptr -= (*elements).data;
	  break;
	  
	case '[':
	  if(*bufferptr == 0)
	    {
	      elements += (*elements).data;
	    }
	  break;

	case ']':
	  if(*bufferptr != 0)
	    {
	      elements += (*elements).data;
	    }
	  break;

	case '.':
	  fprintf(output, "%c", *bufferptr);
	  break;

	case ',':
	  *bufferptr = getchar();
	  break;

	case 's':
	  (*bufferptr) = (*elements).data;
	  break;

	case 'b':
	  while(*(bufferptr -= (*elements).data) != 0);
	  break;
	  
	case 'f':
	  while(*(bufferptr += (*elements).data) != 0);
	  break;

	case 0:
	  stop = 0;
	  break;
	}
      elements++;
    }
  
  free(buffer);
  free(elements_buffer);
  
#ifdef PRINT
  fclose(output);
#endif
}
