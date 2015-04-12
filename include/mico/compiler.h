#ifndef MICO_COMPILER_H
#define MICO_COMPILER_H


/* Simple shorthand for a section definition */
#define __section(S)	@#S

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

#endif