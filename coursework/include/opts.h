#ifndef __OPTS_H__
#define __OPTS_H__

#define NO_OPT (0)
#define a_OPT (1 << 0)
#define l_OPT (1 << 1)
#define R_OPT (1 << 2)
#define i_OPT (1 << 3)
#define MUL_ARG_OPT (1 << 4) // 인자 여러 개 들어오는 경우 사용

int get_opt_flags(int, char **);
#endif