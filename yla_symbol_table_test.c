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
    size_t size1 = 777;
    YLATEST_ASSERT_TRUE(yla_symbol_count(&symbol, &size1) == YLA_OK, "normal get count");
    YLATEST_ASSERT_TRUE(size1 == 0, "just after init count must be 0");

    YLATEST_ASSERT_TRUE(yla_symbol_add_name(&symbol, "aaa") == YLA_OK, "normal add");
    size_t size2 = 777;
    YLATEST_ASSERT_TRUE(yla_symbol_count(&symbol, &size2) == YLA_OK, "normal get count");
    YLATEST_ASSERT_TRUE(size2 == 1, "after add one count must be 1");

    YLATEST_ASSERT_FALSE(yla_symbol_add_name(&symbol, "bbb") == YLA_OK, "add exceed");
    YLATEST_ASSERT_TRUE(YLA_SYMBOLIC_ERROR_TABLE_FULL == yla_symbol_last_error(&symbol), "check last error");
    YLATEST_ASSERT_TRUE(YLA_SYMBOLIC_ERROR_OK == yla_symbol_last_error(&symbol), "recheck last error");
    size_t size3 = 777;
    YLATEST_ASSERT_TRUE(yla_symbol_count(&symbol, &size3) == YLA_OK, "normal get count");
    YLATEST_ASSERT_TRUE(size3 == 1, "after incorect added second count must be 1");

    int has_name1 = -1;
    YLATEST_ASSERT_TRUE(yla_symbol_has_name(&symbol, "aaa", &has_name1) == YLA_OK, "has_name must always OK");
    YLATEST_ASSERT_TRUE(has_name1 == 1, "added name not found");

    int has_name2 = -1;
    YLATEST_ASSERT_TRUE(yla_symbol_has_name(&symbol, "bbb", &has_name2) == YLA_OK, "has_name must always OK");
    YLATEST_ASSERT_TRUE(has_name2 == 0, "not added name not found");

    yla_int_type address1 = 666;
    YLATEST_ASSERT_TRUE(yla_symbol_get_address(&symbol, "aaa", &address1) == YLA_ERROR, "get address before set");
    YLATEST_ASSERT_TRUE(YLA_SYMBOLIC_ERROR_ADDRESS_UNKNOWN == yla_symbol_last_error(&symbol), "last error after get unknown address");
    YLATEST_ASSERT_TRUE(address1 == 666, "address == -1 before set");

    yla_int_type address2 = 777;
    YLATEST_ASSERT_TRUE(yla_symbol_set_address(&symbol, "aaa", 555) == YLA_OK, "normal set");
    YLATEST_ASSERT_TRUE(yla_symbol_get_address(&symbol, "aaa", &address2) == YLA_OK, "get address before set");
    YLATEST_ASSERT_TRUE(address2 == 555, "local address must be changed");

    size_t size4 = 777;
    YLATEST_ASSERT_TRUE(yla_symbol_count(&symbol, &size4) == YLA_OK, "normal get count");
    YLATEST_ASSERT_TRUE(size4 == 1, "must be 1 always");

    char* name_found = NULL;
    yla_int_type address3 = 777;
    YLATEST_ASSERT_TRUE(yla_symbol_get(&symbol, 0, &name_found, &address3) == YLA_OK, "normal get");
    YLATEST_ASSERT_TRUE(strcmp(name_found, "aaa") == 0, "symbolic name");
    YLATEST_ASSERT_TRUE(address3 == 555, "normal get");

    YLATEST_ASSERT_TRUE(yla_symbol_get(&symbol, 1, &name_found, &address3) == YLA_ERROR, "normal get");
    YLATEST_ASSERT_TRUE(yla_symbol_last_error(&symbol) == YLA_SYMBOLIC_ERROR_INDEX_TOO_LARGE, "must be error for icnorrect index");

    YLATEST_ASSERT_TRUE(yla_symbol_done(&symbol) == YLA_OK, "normal done");
YLATEST_CASE_END

YLATEST_CASE_BEGIN(test_add_duplicate)
    symbol_table symbol;
    YLATEST_ASSERT_TRUE(yla_symbol_init(&symbol, 5) == YLA_OK, "normal init");

    YLATEST_ASSERT_TRUE(yla_symbol_add_name(&symbol, "aaa1") == YLA_OK, "normal add");
    YLATEST_ASSERT_TRUE(yla_symbol_add_name(&symbol, "aaa1") == YLA_ERROR, "duplicate add");
    YLATEST_ASSERT_TRUE(yla_symbol_last_error(&symbol) == YLA_SYMBOLIC_ERROR_NAME_FOUND, "duplicate names not possible");

    size_t size = 777;
    YLATEST_ASSERT_TRUE(yla_symbol_count(&symbol, &size) == YLA_OK, "normal get count");
    YLATEST_ASSERT_TRUE(size == 1, "must be 1 always");

    YLATEST_ASSERT_TRUE(yla_symbol_done(&symbol) == YLA_OK, "normal done");
YLATEST_CASE_END

YLATEST_CASE_BEGIN(test_add_many)
    symbol_table symbol;
    YLATEST_ASSERT_TRUE(yla_symbol_init(&symbol, 5) == YLA_OK, "normal init");

    YLATEST_ASSERT_TRUE(yla_symbol_add_name(&symbol, "aaa1") == YLA_OK, "normal add");
    YLATEST_ASSERT_TRUE(yla_symbol_add_name(&symbol, "aaa2") == YLA_OK, "normal add");
    YLATEST_ASSERT_TRUE(yla_symbol_add_name(&symbol, "aaa3") == YLA_OK, "normal add");
    YLATEST_ASSERT_TRUE(yla_symbol_add_name(&symbol, "aaa4") == YLA_OK, "normal add");
    YLATEST_ASSERT_TRUE(yla_symbol_add_name(&symbol, "aaa5") == YLA_OK, "normal add");
    YLATEST_ASSERT_TRUE(yla_symbol_add_name(&symbol, "aaa6") == YLA_ERROR, "exceed add");
    YLATEST_ASSERT_TRUE(YLA_SYMBOLIC_ERROR_TABLE_FULL == yla_symbol_last_error(&symbol), "check last error");

    size_t size = 777;
    YLATEST_ASSERT_TRUE(yla_symbol_count(&symbol, &size) == YLA_OK, "normal get count");
    YLATEST_ASSERT_TRUE(size == 5, "must be 5 always");

    YLATEST_ASSERT_TRUE(yla_symbol_done(&symbol) == YLA_OK, "normal done");
YLATEST_CASE_END

YLATEST_BEGIN(yla_symbol_table_test)
  YLATEST_ADD_TEST_CASE(test_init_done)
  YLATEST_ADD_TEST_CASE(test_init0)
  YLATEST_ADD_TEST_CASE(test_add_simple)
  YLATEST_ADD_TEST_CASE(test_add_duplicate)
  YLATEST_ADD_TEST_CASE(test_add_many)
YLATEST_END
