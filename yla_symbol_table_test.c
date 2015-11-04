/*
    Symbolic names table tests

    This file is part of YLA VM (Yet another Language for Academic purpose: Virtual Machine).
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

#include "yla_test.h"
#include "yla_symbol_table.h"

YLATEST_CASE_BEGIN(test_init_done)
    symbol_table symbol;
    YLATEST_ASSERT_TRUE(yla_symbol_init(&symbol, 10) == YLA_OK, "normal init");
    YLATEST_ASSERT_TRUE(yla_symbol_done(&symbol) == YLA_OK, "normal done");
YLATEST_CASE_END

YLATEST_CASE_BEGIN(test_init0)
    symbol_table symbol;
    YLATEST_ASSERT_FALSE(yla_symbol_init(&symbol, 0) == YLA_OK, "init with zero");
YLATEST_CASE_END

YLATEST_CASE_BEGIN(test_add_simple)
    symbol_table symbol;
    YLATEST_ASSERT_TRUE(yla_symbol_init(&symbol, 1) == YLA_OK, "normal init");

    YLATEST_ASSERT_TRUE(yla_symbol_add_name(&symbol, "aaa") == YLA_OK, "normal add");
    YLATEST_ASSERT_FALSE(yla_symbol_add_name(&symbol, "bbb") == YLA_OK, "add exceed");
    YLATEST_ASSERT_TRUE(YLA_SYMBOLIC_ERROR_TABLE_FULL == yla_symbol_last_error(&symbol), "check last error");
    YLATEST_ASSERT_TRUE(YLA_SYMBOLIC_ERROR_OK == yla_symbol_last_error(&symbol), "recheck last error");

    YLATEST_ASSERT_TRUE(yla_symbol_done(&symbol) == YLA_OK, "normal done");
YLATEST_CASE_END

YLATEST_BEGIN(yla_symbol_table_test)
  YLATEST_ADD_TEST_CASE(test_init_done)
  YLATEST_ADD_TEST_CASE(test_init0)
  YLATEST_ADD_TEST_CASE(test_add_simple)
YLATEST_END
