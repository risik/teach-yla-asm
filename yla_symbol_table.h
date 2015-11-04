/*
    Symbolic names table

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

#ifndef _yla_symbol_table_h
#define _yla_symbol_table_h

#include <stddef.h>

#include "yla_common.h"
#include "yla_type.h"

typedef struct {
    void *impl;
} symbol_table;

/**
 * Define max lenght of symbolic names in the object file.
 */
#define YLA_SYMBOLIC_MAX_LENGHT 20

#define YLA_SYMBOLIC_ERROR_OK (0)
#define YLA_SYMBOLIC_ERROR_TABLE_FULL (1)
#define YLA_SYMBOLIC_ERROR_NAME_NOT_FOUND (2)
#define YLA_SYMBOLIC_ERROR_NAME_FOUND (3)
#define YLA_SYMBOLIC_ERROR_NAME_TOO_LONG (4)
#define YLA_SYMBOLIC_ERROR_INDEX_TOO_LARGE (5)

/**
 * Initilize symbol table.
 * Call this function before using symbol table.
 * @param table self table
 * @param max_count maximum symbols in the table
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_symbol_init(symbol_table *table, size_t max_count);

/**
 * Deinitilize symbol table.
 * Call this function after using symbol table.
 * @param table self table
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_symbol_done(symbol_table *table);

/**
 * Returns last error code.
 * @param table self table
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_symbol_last_error(symbol_table *table);

/**
 * Add new symbol name.
 * Returns error if symbol name already exists.
 * @param table self table
 * @param name symbolic name to add
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_symbol_add_name(symbol_table *table, char* name);

/**
 * Find if name already added or no
 * @param table self table
 * @param name symbolic name to find
 * @param result pointer to save result
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_symbol_has_name(symbol_table *table, char* name, int *result);

/**
 * Set new address to known name
 * @param table self table
 * @param name symbolic name to set address
 * @param address to set
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_symbol_set_address(symbol_table *table, char* name, yla_int_type address);

/**
 * Get address to provided name
 * @param table self table
 * @param name symbolic name to get adrress
 * @param address pointer to save address to
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_symbol_get_address(symbol_table *table, char* name, yla_int_type *address);

/**
 * Get count of symbolic names in the table
 * @param table self table
 * @param count pointer to save address to
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_symbol_count(symbol_table *table, size_t *count);

/**
 * Retrieve name and address by count
 * @param table self table
 * @param name pointer to char* to save name to
 * @param address pointer to save address to
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_symbol_get(symbol_table *table, size_t index, char **name, yla_int_type *address);

#endif
