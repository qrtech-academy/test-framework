/**
 * @file Test framework API.
 */
#pragma once

#include "qacademy/test/impl/case.hpp"
#include "qacademy/test/impl/helpers.hpp"
#include "qacademy/test/impl/registry.hpp"

/**
 * @brief Define a test case.
 *
 * @param[in] suite Test suite.
 * @param[in] name  Test name.
 */
#define TEST(suite, name)                                                                  \
    static void suite##_##name##_testFunc();                                               \
    namespace                                                                              \
    {                                                                                      \
    struct suite##_##name##_registrar                                                      \
    {                                                                                      \
        suite##_##name##_registrar()                                                       \
        {                                                                                  \
            qacademy::test::impl::Case testCase{#suite, #name, suite##_##name##_testFunc}; \
            qacademy::test::impl::Registry::instance().add(testCase);                      \
        }                                                                                  \
    } suite##_##name##_instance;                                                           \
    }                                                                                      \
    static void suite##_##name##_testFunc()

/**
 * @brief Expect expression to be true.
 *
 * @param[in] expr Expression to evaluate.
 */
#define EXPECT_TRUE(expr)                                                                   \
    qacademy::test::impl::expectEq(static_cast<bool>(expr), true, "EXPECT_TRUE(" #expr ")", \
                                   __FILE__, __LINE__)

/**
 * @brief Expect expression to be false.
 *
 * @param[in] expr Expression to evaluate.
 */
#define EXPECT_FALSE(expr)                                                                    \
    qacademy::test::impl::expectEq(static_cast<bool>(expr), false, "EXPECT_FALSE(" #expr ")", \
                                   __FILE__, __LINE__)

/**
 * @brief Expect two values to be equal.
 *
 * @param[in] a First value.
 * @param[in] b Second value.
 */
#define EXPECT_EQ(a, b) \
    qacademy::test::impl::expectEq((a), (b), "EXPECT_EQ(" #a ", " #b ")", __FILE__, __LINE__)

/**
 * @brief Expect two values to not be equal.
 *
 * @param[in] a First value.
 * @param[in] b Second value.
 */
#define EXPECT_NE(a, b) \
    qacademy::test::impl::expectNe((a), (b), "EXPECT_NE(" #a ", " #b ")", __FILE__, __LINE__)

/**
 * @brief Expect two values to be within a given tolerance of each other.
 *
 * @param[in] a First value.
 * @param[in] b Second value.
 * @param[in] tol Tolerance.
 */
#define EXPECT_NEAR(a, b, tol)                                                                 \
    qacademy::test::impl::expectNear((a), (b), (tol), "EXPECT_NEAR(" #a ", " #b ", " #tol ")", \
                                     __FILE__, __LINE__)

namespace qacademy::test
{
/**
 * @brief Run all tests.
 *
 * @return True if all tests succeeded, false otherwise.
 */
bool runAllTests();

} // namespace qacademy::test
