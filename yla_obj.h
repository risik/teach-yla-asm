/*
    Defines for object file.

    This file is part of YLA ASM:
    Yet another Language for Academic purpose: assembler and linker.

    YLA VM is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef _yla_obj_h
#define _yla_obj_h

#include "yla_type.h"

/**
 * Define max lenght of symbolic names in the object file.
 */
#define YLA_OBJ_NAME_MAX_LENGHT 20

/**
 * Define max number of symbolic names that can be stored in the object file
 */
#define YLA_OBJ_NAME_TABLE_SIZE 100

/**
 * Define max size of using symbolic names table in the object file
 */
#define YLA_OBJ_NAME_REF_TABLE_SIZE 200


/**
 * Magic prefix: 6 bytes filled in with text: ylaobj
 */
#define YLA_OBJ_MAGIC_SIZE 3
#define YLA_OBJ_MAGIC1 0x796c
#define YLA_OBJ_MAGIC2 0x616f
#define YLA_OBJ_MAGIC3 0x626a

/*
Header structure:
  magic1,magic2,magic3,
  version,header_size,
  symbol_table_size,code_size,var_table_size
each field is yla_int
*/

#define YLA_OBJ_HEADER_SIZE ((MAGIC_SIZE + 5) * sizeof(yla_int_type))

#endif
