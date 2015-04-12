#ifndef TYPES_H
#define TYPES_H

#ifndef NULL
#define NULL	0
#endif

#ifndef bool
#define bool	int
#endif

enum
{
	false = 0,
	true = 1
};

typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int 		uint32_t;

#endif