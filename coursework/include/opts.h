#ifndef __OPTS_H__
#define __OPTS_H__

#define NO_OPT (0)
#define a_OPT (1 << 0)
#define l_OPT (1 << 1)
#define R_OPT (1 << 2)
#define i_OPT (1 << 3)

int get_opt_flags(int, char **);
#endif