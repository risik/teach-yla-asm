/*
    Save YLA VM code header

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

#include "yla_vm_code.h"
#include "yla_vm_program.h"
#include "yla_common.h"

void put_commd(unsigned char** prg, yla_cop_type value)
{
	**prg = value;
	(*prg)++;
}

void put_value(unsigned char** prg, yla_int_type value)
{
    // NOTE: it's work OK only if yla_cop_type is 1 byte
    int i;
    unsigned int mask = 0xff;
    unsigned int int_value = value;

    mask <<= (8*(sizeof(unsigned int)-1));
    int_value <<= (8*(sizeof(unsigned int) - sizeof(yla_int_type)));

    for (i=0; i<sizeof(yla_int_type); ++i) {
        unsigned int only_value = (int_value & mask);
        only_value >>= (8*(sizeof(unsigned int)-1));
        put_commd(prg, only_value);
        int_value <<= 8;
    }
}

int yla_vm_save_header(
        size_t stack_size, 
        size_t vartable_size,
        size_t code_size,
        unsigned char *buffer,
        size_t buffer_size)
{
    if (buffer_size <= HEADER_SIZE) {
        return YLA_ERROR;
    }

    put_value(&buffer, MAGIC_CODE1);
    put_value(&buffer, MAGIC_CODE2);
    put_value(&buffer, MAGIC_CODE3);

    put_value(&buffer, stack_size);
    put_value(&buffer, vartable_size);
    put_value(&buffer, code_size);
}
