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

#ifndef _yla_vm_code_h
#define _yla_vm_code_h

#include <stddef.h>

/**
 * Save yla vm's header to pr
 */
int yla_vm_save_header(
        size_t stack_size, 
        size_t vartable_size,
        size_t code_size,
        unsigned char *buffer,
        size_t buffer_size);

#endif
