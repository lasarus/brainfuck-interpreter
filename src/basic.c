#include <stdlib.h>
#include <stdio.h>

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
  char * buffer = malloc(1024);
  char * bufferptr = buffer;

  for(;*code != 0; code++)
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
	      int i = 1;

	      for(code++; i != 0; code++)
		{
		  if(*code == '[')
		    i++;
		  else if(*code == ']')
		    i--;
		}
	    }
	  break;

	case BF_BRI:
	  if(*bufferptr)
	    {
	      int i = 1;

	      for(code--; i != 0; code--)
		{
		  if(*code == '[')
		    i--;
		  else if(*code == ']')
		    i++;
		}
	    }
	  break;

	case BF_PRINT_CH:
	  printf("%c", *bufferptr);
	  break;

	case BF_GET_CH:
	  *bufferptr = getchar();
	  break;
	}
    }
  free(buffer);
}
