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

#ifndef _yla_obj_saver_h
#define _yla_obj_saver_h

#include <stdio.h>

#include "yla_obj.h"
#include "yla_type.h"

typedef struct {
    void *impl;
} object_file;

/**
 * Object saver have limitation.
 * Here max code size that can be stored in one object file
 */
#define YLA_OBJ_SAVER_MAX_CODE 4096

/**
 * Object saver have limitation.
 * Here max variable number that can be stored in one object file
 */
#define YLA_OBJ_SAVER_MAX_VARS 20

/**
 * Returns code for most functions
 * OK if all went OK
 * ERROR if some error occured. See last error code
 * FATAL some fatal error occurred. e.g. object_file pointer is NULL
 */
#define YLA_OBJ_SAVER_OK (0)
#define YLA_OBJ_SAVER_ERROR (1)
#define YLA_OBJ_SAVER_FATAL (-1)

/**
 * Last error codes
 * OK - nothong happend
 */
#define YLA_OBJ_SAVER_ERROR_OK (0)
#define YLA_OBJ_SAVER_ERROR_OVERCODE (1)
#define YLA_OBJ_SAVER_ERROR_OVERSYMBOL (2)
#define YLA_OBJ_SAVER_ERROR_TOO_LONG_LABEL (3)
#define YLA_OBJ_SAVER_ERROR_OVERREF (4)

/**
 * Initialize object file saver
 * @param ofile current object file structure.
 * @return 0: error, 1: ok, -1: fatal error
 **/
int yla_obj_init(object_file* ofile);

/**
 * Deinitialize object file saver
 * Calling this function after use required
 * @param ofile current object file structure.
 * @return 0: ok, 1: error, -1: fatal error
 **/ 
int yla_obj_done(object_file* ofile);

/**
 * Returns last error code.
 * @param ofile current object file structure.
 * @return integer value error code or -1: for fatal error
 **/
int yla_obj_last_error(object_file* ofile);

/**
 * Returns text by error code.
 * @param ofile current object file structure.
 * @param error_code code of error occurred
 * @param buf pointer to char to buffer to fill last error text
 * @param buf_len lenght of buffer to fill
 * @return 0 if all ok or required buffer lenght to error message is unsuite
 **/
int yla_obj_error_text(object_file* ofile, int error_code, char *buf, int buf_len);


/**
 * Save object file on disk
 * @param ofile current object file structure.
 * @return 0: ok, 1: error, -1: fatal error
 */
int yla_obj_save(object_file* ofile, FILE* file);

/**
 * Add label. This mean that current PC 
 * @param ofile current object file structure.
 * @return 0: ok, 1: error, -1: fatal error
 */
int yla_obj_add_label(object_file* ofile, char* name);

/**
 * Save no operand command
 * @param ofile current object file structure.
 * @param cop code of operation
 * @return 0: ok, 1: error, -1: fatal error
 */
int yla_obj_command(object_file* ofile, yla_cop_type cop);

/**
 * Save command with integer operand
 * @param ofile current object file structure.
 * @param cop code of operation
 * @param operand integer operand for this command
 * @return 0: ok, 1: error, -1: fatal error
 */
int yla_obj_command_int(object_file* ofile, yla_cop_type cop, yla_int_type operand);

/**
 * Save command with symbolic operand as offset.
 * Used for jumps, calls and other commands that required offset to symbolic name
 * @param ofile current object file structure.
 * @param cop code of operation
 * @param operand symbolic name for this command
 * @return 0: ok, 1: error, -1: fatal error
 */
int yla_obj_command_offset(object_file* ofile, yla_cop_type cop, char* operand);

/**
 * Save command with symbolic operand as address.
 * Used for call and other commands that required absolute address of symbolic name
 * @param ofile current object file structure.
 * @param cop code of operation
 * @param operand symbolic name for this command
 * @return 0: ok, 1: error, -1: fatal error
 */
int yla_obj_command_address(object_file* ofile, yla_cop_type cop, char* operand);

/**
 * Save command with symbolic operand as number of global variable.
 * Used for commands load/save variable
 * @param ofile current object file structure.
 * @param cop code of operation
 * @param operand symbolic name for this command
 * @return 0: ok, 1: error, -1: fatal error
 */
int yla_obj_command_var(object_file* ofile, yla_cop_type cop, char* operand);

#endif
