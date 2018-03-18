#include "unity.h"
#include "vblibc_stack.h"

#define L 5

vb_stack_t *stack = NULL;
int values[L] = {-81, 5, 9, 22, 86};

void setUp (void) { }
void tearDown (void) { }

static void
push_value_for_test (int index) {
  int deep;
  vb_stack_push(&stack, values + index);

  deep = vb_stack_deep(stack);
  TEST_ASSERT_EQUAL_INT(index + 1, deep);
}

static void
pop_value_for_test (int index) {
  int deep;
  
  void *value = vb_stack_pop(&stack);
  TEST_ASSERT_EQUAL_INT(*(values + index), *((int *)value));

  deep = vb_stack_deep(stack);
  TEST_ASSERT_EQUAL_INT(index, deep);
}

void
test_vb_stack_deep_empty ()
{
  int deep = vb_stack_deep(stack);
  TEST_ASSERT_EQUAL_INT(0, deep);
}

void
test_vb_stack_push ()
{
  int i;
  for (i=0; i<L; i++)
    push_value_for_test(i);
}

void
test_vb_stack_pop ()
{
  int i;
  for (i=L-1; i>=0; i--) {
    pop_value_for_test(i);
  }
}

void
test_vb_stack_try_pop_empty ()
{
  test_vb_stack_deep_empty();
  void *value = vb_stack_pop(&stack);
  TEST_ASSERT_NULL(value);
}
