/*
    Save object file

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

#include "yla_obj_saver.h"

#include "yla_obj.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/**
 * This structure define one record in symvolic table.
 * Field name: symbolic name
 * Field address: real address (in this object file) there this label declared
 * address=0xffff (-1) means that label undeclared
 * any other address value means that label declared
 */
typedef struct {
    char name[YLA_OBJ_NAME_MAX_LENGHT];
    yla_int_type address;
} symbol_record;

/**
 * This table contains symbolic names
 * Field table: symbolic names array
 * Field count: count of names currently filled
 */
typedef struct {
    symbol_record table[YLA_OBJ_NAME_TABLE_SIZE];
    size_t count;
} symbol_table;

/**
 * Type of reference
 */
typedef enum {
    RefAbsolute,
    RefOffset
} reference_type;

/**
 * Reference record
 * Field address: address in code where reference 
 * Field type: reference type
 */
typedef struct {
    yla_int_type address;
    reference_type type;
} reference_record;

/**
 * This table contains addresses in code which have refs to symbolic names.
 * As for storing conception index of symbolic names stored in the code.
 */
typedef struct {
    reference_record table[YLA_OBJ_NAME_REF_TABLE_SIZE];
    size_t count;
} reference_table;

/**
 * Array for storing generated code
 * Field code: vm's code to store
 * Field PC: current PC
 */
typedef struct {
    yla_cop_type memory[YLA_OBJ_SAVER_MAX_CODE];
    size_t PC;
} code_table;

/**
 * Array for storing variables
 * Field code: vm's code to store
 */
typedef struct {
    char name[YLA_OBJ_NAME_MAX_LENGHT];
} var_table_record;

/**
 * This table contains global variables
 */
typedef struct {
    var_table_record table[YLA_OBJ_SAVER_MAX_VARS];
    size_t count;
} var_table;

/**
 * Implementation of 
 */
typedef struct {
    symbol_table symbol;
    reference_table reference;
    code_table code;
    var_table var;
    int last_error;
} object_file_impl;

#define CHECK_OFILE_NULL(o) { if (o == NULL) { return YLA_OBJ_SAVER_FATAL; } }

//
// private functions declaration
//
int yla_obj_put_cop_arg(object_file_impl* o, yla_cop_type cop, yla_int_type value);
int yla_obj_put_cop(object_file_impl* o, yla_cop_type cop);
int yla_obj_find_symbol(symbol_table *symbol, char *name);

//
// implementation
//
int yla_obj_init(object_file* ofile)
{
    CHECK_OFILE_NULL(ofile);
    object_file_impl* o = malloc(sizeof(object_file_impl));

    o->last_error = YLA_OBJ_SAVER_ERROR_OK;

    memset(&o->code.memory, 0, YLA_OBJ_SAVER_MAX_CODE*sizeof(yla_cop_type));
    o->code.PC = 0;

    memset(&o->reference.table, 0, YLA_OBJ_NAME_REF_TABLE_SIZE*sizeof(reference_record));
    o->reference.count = 0;
    
    memset(&o->symbol.table, 0, YLA_OBJ_NAME_TABLE_SIZE*sizeof(symbol_record));
    o->symbol.count = 0;

    ofile->impl = o;
}

int yla_obj_done(object_file* ofile)
{
    CHECK_OFILE_NULL(ofile);
    free(ofile->impl);
}

int yla_obj_save(object_file* ofile, FILE* file)
{
    // TODO (risik): implement
}

int yla_obj_add_label(object_file* ofile, char* name)
{
    CHECK_OFILE_NULL(ofile);
    object_file_impl* o = (object_file_impl*)ofile->impl;

    symbol_table *symbol = &o->symbol;
    size_t index = yla_obj_find_symbol(symbol, name);
    if (index < 0) {
        return yla_obj_add_symbol(symbol, o->code.PC);
    }
    symbol->table[index].address = o->code.PC;
}

int yla_obj_command(object_file* ofile, yla_cop_type cop)
{
    CHECK_OFILE_NULL(ofile);
    object_file_impl* o = (object_file_impl*)ofile->impl;

    return yla_obj_put_cop(o, cop);
}

int yla_obj_command_int(object_file* ofile, yla_cop_type cop, yla_int_type operand)
{
    CHECK_OFILE_NULL(ofile);
    object_file_impl* o = (object_file_impl*)ofile->impl;

    return yla_obj_put_cop_arg(o, cop, operand);
}

int yla_obj_command_offset(object_file* ofile, yla_cop_type cop, char* operand)
{
    // TODO (risik): implement
}

int yla_obj_command_address(object_file* ofile, yla_cop_type cop, char* operand)
{
    // TODO (risik): implement
}

int yla_obj_command_var(object_file* ofile, yla_cop_type cop, char* operand)
{
    // TODO (risik): implement
}

//
// private functions code genrration
//
int yla_obj_put_byte(object_file_impl* o, unsigned char byte)
{
    if (o->code.PC + 1 >= YLA_OBJ_SAVER_MAX_CODE) {
        o->last_error = YLA_OBJ_SAVER_ERROR_OVERCODE;
        return YLA_OBJ_SAVER_ERROR;
    }
    o->code.memory[o->code.PC++] = byte;
}

int yla_obj_put_cop(object_file_impl* o, yla_cop_type cop)
{
    // NOTE: it's work OK only if yla_cop_type is 1 byte
    return yla_obj_put_byte(o, (unsigned char)cop);
}

int yla_obj_put_int(object_file_impl* o, yla_int_type value)
{
    int i;
    unsigned int mask = 0xff;
    unsigned int int_value = value;

    mask <<= (8*(sizeof(unsigned int)-1));
    int_value <<= (8*(sizeof(unsigned int) - sizeof(yla_int_type)));

    for (i=0; i<sizeof(yla_int_type); ++i) {
        unsigned int only_value = (int_value & mask);
        only_value >>= (8*(sizeof(unsigned int)-1));
        unsigned char byte_value = (unsigned char)only_value;
        int res;
        if (res = yla_obj_put_byte(o, only_value) != YLA_OBJ_SAVER_OK) {
            return res;
        };
        int_value <<= 8;
    }
}

int yla_obj_put_cop_arg(object_file_impl* o, yla_cop_type cop, yla_int_type value)
{
    int res = yla_obj_put_cop(o, cop);
    if (res != YLA_OBJ_SAVER_OK) {
        return res;
    }
    return yla_obj_put_int(o, value);
}

//
// private functions symbolic table
//
int yla_obj_find_symbol(symbol_table *symbol, char *name)
{
    int i;
    symbol_record *record = symbol->table;
    for (i=0; i<symbol->count; i++, record++) {
        if (strncmp(record->name, name, YLA_OBJ_NAME_MAX_LENGHT) == 0) {
            return i;
        }
    }
    return -1;
}