#    This file is part of YLA VM (Yet another Language for Academic purpose: Assembler).
#
#    YLA VM is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Foobar is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

CC     = gcc
CFLAGS = -g

LN     = gcc
LNFLAGS=

RM     = rm -rf

ASMEXE=ylaasm
TESTEXE=tests

OBJ=\
yla_vm_code.o\
yla_symbol_table.o\
yla_codegen.o

MAINOBJ=yla_asm_main.o

TESTOBJ=\
yla_tests_asm.o\
yla_test_test.o\
yla_symbol_table_test.o

.SUFFIXES: .o .c .l
.PHONY: clean test

$(ASMEXE): $(OBJ) $(MAINOBJ)
	$(LN) -o $@ $(OBJ) $(MAINOBJ)

clean:
	$(RM) $(TESTOBJ) $(OBJ) $(MAINOBJ) $(TESTEXE) $(ASMEXE)

test: $(TESTEXE)
	./$(TESTEXE)

$(TESTEXE): $(OBJ) $(TESTOBJ)
	$(LN) -o $@ $(OBJ) $(TESTOBJ)
