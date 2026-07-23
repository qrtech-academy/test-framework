# QAcademy Test Framework
A lightweight C++17 test framework designed for educational use. Tests are registered automatically via macros and assertion failures report the expression, values, and source location.

---

## Features
* Automatic test registration; no manual setup required.
* Colored output: green on success, red on failure.
* Assertion failures show actual values and source file/line.
* Simple to integrate as a Git submodule.

---

## Macros

| Macro | Description |
|---|---|
| `TEST(suite, name)` | Define a test case belonging to a suite |
| `EXPECT_TRUE(expr)` | Fail if `expr` is not true |
| `EXPECT_FALSE(expr)` | Fail if `expr` is not false |
| `EXPECT_EQ(a, b)` | Fail if `a != b` |
| `EXPECT_NE(a, b)` | Fail if `a == b` |
| `EXPECT_NEAR(a, b, tol)` | Fail if `\|a - b\| > tol` |

---

## Namespace
All framework functions live in the `qacademy::test` namespace. The only function students call directly is `runAllTests()`:

```cpp
qacademy::test::runAllTests();
```

The macros (`TEST`, `EXPECT_*`) handle everything else automatically; no other namespace interaction is needed.

---

## Writing tests
Include `qacademy/test/test.hpp` and use the `TEST` macro to define test cases. Each test case belongs to a named suite:

```cpp
#include "qacademy/test/test.hpp"

/**
 * @brief Test the default constructor.
 *
 *        Create an empty MyClass instance, expect the instance to be valid.
 */
TEST(MyClass, DefaultConstructor)
{
    MyClass obj{};
    EXPECT_EQ(obj.value(), 0);
    EXPECT_TRUE(obj.isValid());
}

/**
 * @brief Test floating-point addition.
 *
 *        Add two numbers and expect the result to be within tolerance.
 */
TEST(MyClass, Addition)
{
    EXPECT_NEAR(1.0 + 2.0, 3.0, 1e-9);
}

/**
 * @brief Run all test cases.
 *
 * @return 0 on success, or -1 on failure.
 */
int main()
{
    return qacademy::test::runAllTests() ? 0 : -1;
}
```

Failure output:
```
Test case MyClass.DefaultConstructor failed: EXPECT_EQ(obj.value(), 0) failed: 3 != 0 (main.cpp:10)
```

---

## Integration as a Git submodule
Add `qacademy-test` to your project:

```bash
git submodule add <url> qacademy-test
git submodule update --init --recursive
```

In your Makefile, build the library and link against it:

```makefile
QACADEMY_TEST_DIR := qacademy-test
QACADEMY_TEST_LIB := $(QACADEMY_TEST_DIR)/libqacademy_test.a

$(QACADEMY_TEST_LIB):
	$(MAKE) -C $(QACADEMY_TEST_DIR) lib

$(TARGET): $(QACADEMY_TEST_LIB) $(SRC)
	g++ $(SRC) -o $(TARGET) -std=c++17 -I$(QACADEMY_TEST_DIR)/include -L$(QACADEMY_TEST_DIR) -lqacademy_test
```

---

## Building the library

```bash
make lib   # Builds libqacademy_test.a.
make       # Builds and runs the bundled example.
make clean # Removes all build artifacts.
```

## Formatting
Sources are formatted with `clang-format` (see [`.clang-format`](./.clang-format)):

```bash
make format       # Formats all sources in place.
make format-check # Checks formatting without modifying files; used in CI.
```


## License

[MIT](./LICENSE)

---

