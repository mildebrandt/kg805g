/*tidy.c -- clean up the .tsv output from tshark for a serial-over-USB
  session. input from stdin, output to stdout.

  Copyright (c) 2019 Dan Clemmensen, licensed to you under GPL v3.

  input lines:
    source\tinfo\tdata\n
  for each line:
     get dirchar (first char of source is 'h' or not),
     get bulk char (fourth char of info is 'B' or not),
     get start of data
     If dir changed,
       print existing buffer and start a new one
     remove the colons from the data and append to buffer
  at end, print buffer

  output line starts with '<' or '>' for direction, followed by the hex chars
  sent or received.
*/
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char separator = '\t';



int main()
{
  char buff[1000];
  char *inpt=buff;
  size_t buflen=1000;
  int len;
  char outbuff[1000];
  int dir=2;    //2= unknown, 1=from host, 0= to host
  int newdir=0;
  int ndx=0;
  char *pt;
  char chr;

  while (-1!=(len=getline(&inpt,&buflen,stdin)))
  { if(buff[len-1]=='\n') 
      buff[len-1]='\0';
    pt=strchr(buff,separator);
    if((pt[5]=='B') && (0!=*(pt=1+strchr(pt+1,separator))))
    { newdir= buff[0]=='h';
      if(newdir!=dir)
      { if (ndx)
        { outbuff[ndx]=0;
          printf("%c%s\n",dir?'>':'<',outbuff);
        }
        dir=newdir;
        ndx=0;
      }
      while(0!=(chr=*pt++))
        if(chr!=':')
          outbuff[ndx++]=chr;
    }  
  }
  outbuff[ndx]=0;
  if(ndx)
    printf("%c%s\n",dir?'>':'<',outbuff);  //last line
  return 0;
}
