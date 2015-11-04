#ifndef _yla_vm_program_h
#define _yla_vm_program_h

#include "yla_type.h"

#define MAGIC_SIZE 3
#define MAGIC_CODE1 0x796c
#define MAGIC_CODE2 0x615f
#define MAGIC_CODE3 0x766d

#define HEADER_SIZE ((MAGIC_SIZE + 3) * sizeof(yla_int_type))
#define MAX_CODE_SIZE ((size_t)65535)
#define MAX_STACK_SIZE ((size_t)65535)
#define MAX_VARTABLE_SIZE ((size_t)65535)

/*
Executable program structure:
magic1: yla_int_type
magic2: yla_int_type
magic3: yla_int_type
stack_size: yla_int_type
vartable_size: yla_int_type
code_size: yla_int_type
code: array of char
*/

#endif
