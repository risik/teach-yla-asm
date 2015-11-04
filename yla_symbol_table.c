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

#include "yla_symbol_table.h"

#include <stdlib.h>
#include <string.h>

/**
 * This structure define one record in symbolic table.
 * Field name: symbolic name
 * Field address: real address (in this object file) there this label declared
 * address=0xffff (-1) means that label undeclared
 * any other address value means that label declared
 */
typedef struct {
    char name[YLA_SYMBOLIC_MAX_LENGHT];
    yla_int_type address;
} symbol_record;

/**
 * This table contains symbolic names
 * Field table: symbolic names array
 * Field count: count of names currently filled
 */
typedef struct {
    symbol_record *table;
    size_t count;
    size_t size;
    int last_error;
} symbol_table_impl;

#define CHECK_THIS_TABLE(o) { if (o == NULL) { return YLA_FATAL; } }

size_t yla_symbol_find(symbol_table_impl *o, char* name);

int yla_symbol_init(symbol_table *table, size_t size)
{
    CHECK_THIS_TABLE(table);
    // table size == 0 not acceptable
    if (size == 0) {
        return YLA_FATAL;
    }

    symbol_table_impl* o = malloc(sizeof(symbol_table_impl));

    o->last_error = YLA_SYMBOLIC_ERROR_OK;
    o->size = size;
    o->table = calloc(sizeof(symbol_record), size);
    o->count = 0;

    table->impl = o;

    return YLA_OK;
}

int yla_symbol_done(symbol_table *table)
{
    CHECK_THIS_TABLE(table);
    symbol_table_impl *o = (symbol_table_impl *)table->impl;

    free(o->table);
    free(table->impl);
}

int yla_symbol_last_error(symbol_table *table)
{
    CHECK_THIS_TABLE(table);
    symbol_table_impl *o = (symbol_table_impl *)table->impl;

    int result = o->last_error;
    
    o->last_error = YLA_SYMBOLIC_ERROR_OK;
    
    return result;
}

int yla_symbol_add_name(symbol_table *table, char* name)
{
    CHECK_THIS_TABLE(table);
    symbol_table_impl *o = (symbol_table_impl *)table->impl;
    
    // find and fail if found
    if (yla_symbol_find(o, name) != -1) {
        o->last_error = YLA_SYMBOLIC_ERROR_NAME_FOUND;
        return YLA_ERROR;
    }
    
    // add new
    if (o->count >= o->size) {
        o->last_error = YLA_SYMBOLIC_ERROR_TABLE_FULL;
        return YLA_ERROR;
    }

    // check name length
    if (strlen(name) >= YLA_SYMBOLIC_MAX_LENGHT - 1) {
        o->last_error = YLA_SYMBOLIC_ERROR_NAME_TOO_LONG;
        return YLA_ERROR;
    }

    symbol_record *record = &o->table[o->count++];

    strncpy(record->name, name, YLA_SYMBOLIC_MAX_LENGHT);
    record->address = -1;

    return YLA_OK;
}

int yla_symbol_has_name(symbol_table *table, char* name, int *result)
{
    CHECK_THIS_TABLE(table);
    symbol_table_impl *o = (symbol_table_impl *)table->impl;
    
    // find and fail if found
    if (yla_symbol_find(o, name) != -1) {
        *result = 0;
        return YLA_OK;
    }
    
    *result = 1;
    return YLA_OK;
}

int yla_symbol_set_address(symbol_table *table, char* name, yla_int_type address)
{
    CHECK_THIS_TABLE(table);
    symbol_table_impl *o = (symbol_table_impl *)table->impl;

    size_t index = yla_symbol_find(o, name);
    if (index == -1) {
        o->last_error = YLA_SYMBOLIC_ERROR_NAME_NOT_FOUND;
        return YLA_ERROR;
    }

    symbol_record *record = &o->table[index];
    record->address = address;

    return YLA_OK;
}

int yla_symbol_get_address(symbol_table *table, char* name, yla_int_type *address)
{
    CHECK_THIS_TABLE(table);
    symbol_table_impl *o = (symbol_table_impl *)table->impl;

    size_t index = yla_symbol_find(o, name);
    if (index == -1) {
        o->last_error = YLA_SYMBOLIC_ERROR_NAME_NOT_FOUND;
        return YLA_ERROR;
    }

    *address = o->table[index].address;

    return YLA_OK;
}

int yla_symbol_count(symbol_table *table, size_t *count)
{
    CHECK_THIS_TABLE(table);
    symbol_table_impl *o = (symbol_table_impl *)table->impl;

    *count = o->count;
}

int yla_symbol_get(symbol_table *table, size_t index, char **name, yla_int_type *address)
{
    CHECK_THIS_TABLE(table);
    symbol_table_impl *o = (symbol_table_impl *)table->impl;

    if (index >= o->count) {
        o->last_error = YLA_SYMBOLIC_ERROR_INDEX_TOO_LARGE;
        return YLA_ERROR;
    }

    symbol_record* record = &o->table[index];

    *name = record->name;
    *address = record->address;

    return YLA_OK;
}

// internal functions
size_t yla_symbol_find(symbol_table_impl *o, char* name)
{
    int i;
    for (i=0; i<o->count; i++) {
        if (strncpy(o->table[i].name, name, YLA_SYMBOLIC_MAX_LENGHT) == 0) {
            return i;
        }
    }
    return -1;
}
