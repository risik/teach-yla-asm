#include "yla_codegen.h"
#include "yla_symbol_table.h"
#include <stdlib.h>

typedef struct {
    unsigned char *code;
    size_t size;
    size_t count;
    
    symbol_table labels;
    symbol_table vars;
    
    int last_error;
} yla_codegen_impl;

/*
 * methods for control code generator
 */

#define CHECK_THIS_CODEGEN(o) { if (o == NULL) { return YLA_FATAL; } }
#define CHECK_IMPL(o)  { if (o == NULL) { return YLA_FATAL; } }

int yla_gen_init(yla_codegen* codegen, size_t code_size, size_t labels_size, size_t var_size)
{
    CHECK_THIS_CODEGEN(codegen);

    yla_codegen_impl* o = malloc(sizeof(yla_codegen_impl));

    o->last_error = YLA_SYMBOLIC_ERROR_OK;
    o->size = code_size;
    o->code = calloc(sizeof(yla_cop_type), code_size);
    o->count = 0;

    if (yla_symbol_init(&o->labels, labels_size) != YLA_OK) {
        o->last_error = YLA_CODEGEN_ERROR_INVALID_LABELS_SIZE;
        return YLA_ERROR;
    }

    if (yla_symbol_init(&o->vars, var_size) != YLA_OK) {
        o->last_error = YLA_CODEGEN_ERROR_INVALID_VARS_SIZE;
        return YLA_ERROR;
    }

    codegen->impl = o;

    return YLA_OK;
}

int yla_gen_done(yla_codegen* codegen)
{
    CHECK_THIS_CODEGEN(codegen);
    yla_codegen_impl *o = (yla_codegen_impl *)codegen->impl;

    int result = YLA_OK;

    free(o->code);

    if (yla_symbol_done(&o->labels)) {
        o->last_error = YLA_CODEGEN_ERROR_SOMETHING_WRONG;
        result = YLA_ERROR;
    }

    if (yla_symbol_done(&o->vars)) {
        o->last_error = YLA_CODEGEN_ERROR_SOMETHING_WRONG;
        result = YLA_ERROR;
    }

    free(o);
    
    return result;
}

int yla_gen_last_error(yla_codegen* codegen)
{
    CHECK_THIS_CODEGEN(codegen);
    yla_codegen_impl *o = (yla_codegen_impl *)codegen->impl;
    CHECK_IMPL(o);

    return o->last_error;
}

int yla_gen_pass2(yla_codegen* codegen)
{
    
}

int yla_gen_save(yla_codegen* codegen, FILE *os)
{
    
}

int yla_obj_command(yla_codegen* codegen, yla_cop_type cop)
{
    
}

int yla_obj_command_int(yla_codegen* codegen, yla_cop_type cop, yla_int_type operand)
{
    
}

int yla_obj_command_address(yla_codegen* codegen, yla_cop_type cop, char* operand)
{
    
}

int yla_obj_command_var(yla_codegen* codegen, yla_cop_type cop, char* operand)
{
    
}
