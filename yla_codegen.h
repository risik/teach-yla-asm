#ifndef _yla_codegen_h
#define _yla_codegen_h

#include "yla_type.h"
#include <stddef.h>
#include <stdio.h>

typedef struct {
    void *impl;
} yla_codegen;

#define YLA_CODEGEN_ERROR_OK (0)
#define YLA_CODEGEN_ERROR_SOMETHING_WRONG (1)
#define YLA_CODEGEN_ERROR_INVALID_LABELS_SIZE (2)
#define YLA_CODEGEN_ERROR_INVALID_VARS_SIZE (3)

/*
 * methods for control code genrator
 */

/** 
 * Initilize code generator. Have to call before using.
 * @param codegen this code generator
 * @param code_size size of code
 * @param labels_size size of symbol table
 * @param var_size size of var table
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_gen_init(yla_codegen* codegen, size_t code_size, size_t labels_size, size_t var_size);

/** 
 * Deinitilize code generator. Have to call after using.
 * @param codegen this code generator
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_gen_done(yla_codegen* codegen);

/**
 * Returns last error code.
 * @param codegen this code generator
 * @return one of YLA_CODEGEN_ERROR*
 */
int yla_gen_last_error(yla_codegen* codegen);

/**
 * Switch to the next pass.
 * @param codegen this code generator
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_gen_pass2(yla_codegen* codegen);

/**
 * Save stores program to the file provided
 * @param codegen this code generator
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_gen_save(yla_codegen* codegen, FILE *os);

/**
 * Save no operand command
 * @param codegen this code generator
 * @param cop code of operation
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_obj_command(yla_codegen* codegen, yla_cop_type cop);

/**
 * Save command with integer operand
 * @param codegen this code generator
 * @param cop code of operation
 * @param operand integer operand for this command
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_obj_command_int(yla_codegen* codegen, yla_cop_type cop, yla_int_type operand);

/**
 * Save command with symbolic operand as address.
 * Used for callS, jumps and other commands that required absolute address of symbolic name
 * @param codegen this code generator
 * @param cop code of operation
 * @param operand symbolic name for this command
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_obj_command_address(yla_codegen* codegen, yla_cop_type cop, char* operand);

/**
 * Save command with symbolic operand as number of global variable.
 * Used for commands load/save variable
 * @param codegen this code generator
 * @param cop code of operation
 * @param operand symbolic name for this command
 * @return execution status YLA_OK, YLA_ERROR or YLA_FATAL
 */
int yla_obj_command_var(yla_codegen* codegen, yla_cop_type cop, char* operand);

#endif
