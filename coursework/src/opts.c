#include <unistd.h>
#include <opts.h>

int get_opt_flags(int argc, char **argv)
{
  int ch;
  int flags = 0;


  while ((ch = getopt(argc, argv, "alRi")) != -1)
  {
    switch (ch)
    {
    case 'a':
      flags |= a_OPT;
      break;
    case 'l':
      flags |= l_OPT;
      break;
    case 'R':
      flags |= R_OPT;
      break;
    case 'i':
      flags |= i_OPT;
      break;
    }
  }

  return flags;
}