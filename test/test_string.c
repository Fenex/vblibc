#include "unity.h"
#include "vblibc_string.h"

void setUp (void) { }
void tearDown (void) { }

void
test_vb_string_is_ends_with ()
{
  TEST_ASSERT_FALSE(vb_string_is_ends_with("qwertyu", ""));
  TEST_ASSERT_FALSE(vb_string_is_ends_with("qwertyu", "ty"));
  TEST_ASSERT_FALSE(vb_string_is_ends_with("qwertyu", "Qwertyu"));
  TEST_ASSERT_FALSE(vb_string_is_ends_with("1234", "11234"));
  TEST_ASSERT_FALSE(vb_string_is_ends_with("123", NULL));
  TEST_ASSERT_FALSE(vb_string_is_ends_with(NULL, "123"));
  TEST_ASSERT_FALSE(vb_string_is_ends_with(NULL, NULL));

  TEST_ASSERT_TRUE(vb_string_is_ends_with("1234", "1234"));
  TEST_ASSERT_TRUE(vb_string_is_ends_with("1234", "234"));
  TEST_ASSERT_TRUE(vb_string_is_ends_with("1234", "4"));
}

void
test_vb_string_is_starts_with ()
{
  TEST_ASSERT_FALSE(vb_string_is_starts_with("qwertyu", ""));
  TEST_ASSERT_FALSE(vb_string_is_starts_with("qwertyu", "we"));
  TEST_ASSERT_FALSE(vb_string_is_starts_with("qwertyu", "qwertyU"));
  TEST_ASSERT_FALSE(vb_string_is_starts_with("1234", "123455"));
  TEST_ASSERT_FALSE(vb_string_is_starts_with("123", NULL));
  TEST_ASSERT_FALSE(vb_string_is_starts_with(NULL, "123"));
  TEST_ASSERT_FALSE(vb_string_is_starts_with(NULL, NULL));

  TEST_ASSERT_TRUE(vb_string_is_starts_with("1234", "1234"));
  TEST_ASSERT_TRUE(vb_string_is_starts_with("1234", "123"));
  TEST_ASSERT_TRUE(vb_string_is_starts_with("1234", "1"));
}
