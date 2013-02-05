#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "basic.h"

enum
  {
    BF_ADD = '+', /* add */
    BF_SUB = '-', /* subtract */
    BF_ALE = '<', /* arrow left */
    BF_ARI = '>', /* arrow right */
    BF_BLE = '[', /* bracket left */
    BF_BRI = ']', /* bracket right */

    BF_PRINT_CH = '.', /* print character */
    BF_GET_CH = ',' /* read character */
  };

void execute_bf(char * code)
{
  FILE * output;
  int i;
  char * buffer = malloc(30000);
  char * bufferptr = buffer;
  
  memset(buffer, 0, 30000);

  output = stdout;
  
  for(; *code != 0; code++)
    {
      switch(*code)
	{
	case BF_ADD:
	  (*bufferptr)++;
	  break;
	  
	case BF_SUB:
	  (*bufferptr)--;
	  break;
	  
	case BF_ALE:
	  bufferptr--;
	  break;
	  
	case BF_ARI:
	  bufferptr++;
	  break;
	  
	case BF_BLE:
	  if(*bufferptr == 0)
	    {
	      code++;
	      for(i = 1; i > 0; code++)
		{
		  if(*code == '[')
		    i++;
		  else if(*code == ']')
		    i--;
		}
	      code--;
	    }
	  break;

	case BF_BRI:
	  if(*bufferptr != 0)
	    {
	      code--;
	      for(i = 1; i != 0; code--)
		{
		  if(*code == '[')
		    i--;
		  else if(*code == ']')
		    i++;
		}
	      code++;
	    }
	  break;

	case BF_PRINT_CH:
	  fprintf(output, "%c", *bufferptr);
	  break;

	case BF_GET_CH:
	  *bufferptr = getchar();
	  break;
	}
    }
  free(buffer);
  fclose(output);
}
