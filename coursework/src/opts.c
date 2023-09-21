#include <unistd.h>
#include <opts.h>

int get_opt_flags(int argc, char **argv)
{
  int ch;
  int flags = NO_OPT;

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

  if ((flags == NO_OPT && argc == 3) || (flags != NO_OPT && argc > 3))
  {
    flags |= MUL_ARG_OPT;
  }

  return flags;
}