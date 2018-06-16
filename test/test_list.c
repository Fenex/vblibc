#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "unity.h"
#include "vblibc_list.h"

#define L 500

static vb_list_t *list;
static char *str = "123456\0";

void setUp (void) { }
void tearDown (void) { }

void
test_vb_list_init (void)
{
  list = vb_list_init();

  TEST_ASSERT_EQUAL_INT(0, list->length);
  TEST_ASSERT_NULL(list->head);
}

// [] == list

void
test_vb_list_add_chars (void)
{
  int i;
  for (i=0; i<strlen(str); i++) {
    TEST_ASSERT_EQUAL_INT(i, list->length);
    vb_list_add(list, str + i);
    TEST_ASSERT_EQUAL_INT(i+1, list->length);
  }

  TEST_ASSERT_NOT_NULL(list->head);
}

// ['1', '2', '3', '4', '5', '6'] == list

void
test_vb_list_get_chars (void)
{
  TEST_ASSERT_EQUAL_INT('1', * (char *) vb_list_get(list, 0));
  TEST_ASSERT_EQUAL_INT('2', * (char *) vb_list_get(list, 1));
  TEST_ASSERT_EQUAL_INT('4', * (char *) vb_list_get(list, 3));
  TEST_ASSERT_EQUAL_INT('6', * (char *) vb_list_get(list, 5));

  TEST_ASSERT_NULL(vb_list_get(list, 6));
  TEST_ASSERT_NULL(vb_list_get(list, 938));

  TEST_ASSERT_EQUAL_INT(6, list->length);
  TEST_ASSERT_NOT_NULL(list->head);
}

// ['1', '2', '3', '4', '5', '6'] == list

void
test_vb_list_remove_chars_last (void)
{
  size_t size;
  char *ch;
  vb_list_item_t *p;

  size = list->length - 1;

  p = list->head;
  while (p->next->next != NULL)
    p = p->next;

  ch = (char *) vb_list_remove(list, size, NULL);
  TEST_ASSERT_EQUAL_INT('6', *ch);
  TEST_ASSERT_EQUAL_INT(size, list->length);
  TEST_ASSERT_NULL(p->next);

  TEST_ASSERT_EQUAL_INT('2', * (char *) vb_list_get(list, 1));
  TEST_ASSERT_EQUAL_INT('5', * (char *) vb_list_get(list, 4));

  TEST_ASSERT_NULL(vb_list_get(list, size));
  TEST_ASSERT_NULL(vb_list_get(list, 2997));
}

// ['1', '2', '3', '4', '5'] == list

void
test_vb_list_remove_chars_middle (void) {
  size_t size;
  char *ch;
  vb_list_item_t *p1, *p2;
  int i;

  size = list->length - 1;
  p1 = list->head->next;
  p2 = p1 ->next->next;

  ch = (char *) vb_list_remove(list, 2, NULL);
  TEST_ASSERT_EQUAL_INT('3', *ch);
  TEST_ASSERT_EQUAL_INT(size, list->length);
  TEST_ASSERT(p1->next == p2);

  TEST_ASSERT_EQUAL_INT('1', * (char *) vb_list_get(list, 0));
  TEST_ASSERT_EQUAL_INT('2', * (char *) vb_list_get(list, 1));
  TEST_ASSERT_EQUAL_INT('4', * (char *) vb_list_get(list, 2));
  TEST_ASSERT_EQUAL_INT('5', * (char *) vb_list_get(list, 3));

  TEST_ASSERT_NULL(vb_list_get(list, size));
  TEST_ASSERT_NULL(vb_list_get(list, 2997));
}

// ['1', '2', '4', '5'] == list

void
test_vb_list_remove_chars_first (void)
{
  size_t size;
  char *ch;
  vb_list_item_t *p;

  size = list->length - 1;
  p = list->head->next;
  ch = (char *) vb_list_remove(list, 0, NULL);
  TEST_ASSERT_EQUAL_INT('1', *ch);
  TEST_ASSERT_EQUAL_INT(size, list->length);
  TEST_ASSERT(list->head == p);

  TEST_ASSERT_EQUAL_INT('2', * (char *) vb_list_get(list, 0));
  TEST_ASSERT_EQUAL_INT('4', * (char *) vb_list_get(list, 1));
  TEST_ASSERT_EQUAL_INT('5', * (char *) vb_list_get(list, 2));

  TEST_ASSERT_NULL(vb_list_get(list, size));
  TEST_ASSERT_NULL(vb_list_get(list, 2427));
}

// ['2', '4', '5'] == list

void
test_vb_list_clear (void)
{
  vb_list_clear(list, NULL);
  TEST_ASSERT_NULL(list->head);
  TEST_ASSERT_EQUAL_INT(0, list->length);

  /* try clear already cleared list */
  vb_list_clear(list, NULL);
  TEST_ASSERT_NULL(list->head);
  TEST_ASSERT_EQUAL_INT(0, list->length);

  /* try remove undefined elements of a cleared list */
  TEST_ASSERT_NULL(vb_list_remove(list, 0, NULL));
  TEST_ASSERT_NULL(vb_list_remove(list, 1, NULL));
}

// [] == list

void
test_vb_list_add_value_by_addr (void)
{
  int value1 = 8, value2 = 21;
  int *valt;

  vb_list_add(list, &value1);
  vb_list_add(list, &value2);
  vb_list_add(list, (void *)567);

  valt = vb_list_get(list, 0);
  TEST_ASSERT_EQUAL_INT(8, *valt);
  TEST_ASSERT_EQUAL_INT(3, list->length);
}

// [(addr -> 8), (addr -> 21), 567] == list

void
test_vb_list_destroy (void)
{
  vb_list_destroy(&list, NULL);
  TEST_ASSERT_NULL(list);

  // try destroy already destroyed list
  vb_list_destroy(&list, NULL);
}

// NULL == list

typedef struct stest_t {
  char arr[42]; //unused
  int index;
  int value;
  struct stest_t *foo; //unused
  void *bar; //unused
} stest_t;

static int compare (int a, int b)
{
  return a > b ? 1 : (a < b ? -1 : 0);
}

static int compare_arr_int (const void *a, const void *b)
{
  int *ia = (int *) a;
  int *ib = (int *) b;

  return compare(*ia, *ib);
}

static int compare_data (const void *a, const void *b)
{
  return compare(((stest_t *) a)->value, ((stest_t *) b)->value);
}

// NULL == list

void
test_vb_list_qsort (void)
{
  int arr[L];
  int i;
  stest_t *t;
  
  srand(time(NULL)); // set random start value

  // create an array with random int values
  for (i=0; i<L; i++) *(arr + i) = rand();

  // create new list obj
  list = vb_list_init();

  // fill an array
  for (i=0; i<L; i++) {
    t = (stest_t *) malloc(sizeof(stest_t));
    if (t == NULL) {
      /** can't get a free memory ???
       * 
       * Okay, let's free memory that we already got.
       * We will have to ignore the test =(
       */
        vb_list_clear(list, NULL);
        TEST_IGNORE_MESSAGE ("malloc fail\r\n");
        return;
    }
    t->index = i;
    t->value = *(arr + i);
    vb_list_add(list, t);
  }

  TEST_ASSERT_EQUAL_INT(L, list->length);

  //check for correct get values
  for (i=0; i<L; i++) {
    t = vb_list_get(list, i);
    TEST_ASSERT_EQUAL_INT(*(arr + i), t->value);
  }

  qsort(arr, L, sizeof(int), compare_arr_int);
  vb_list_qsort(list, compare_data);
  
  for (i=0; i<L; i++) {
    t = vb_list_get(list, i);
    TEST_ASSERT_EQUAL_INT(*(arr + i), t->value);
  }
}

// [{int}, {int}, ...] == list

static int touch = 0;
static void* dispose_callback(void *data)
{
  touch++;
  free(data);
  return NULL;
}

void
test_vb_list_destroy_with_dispose_callback (void)
{
  int length = list->length;
  vb_list_destroy(&list, &dispose_callback);

  TEST_ASSERT_EQUAL_INT(length, touch);
  TEST_ASSERT_NULL(list);
}

// NULL == list



