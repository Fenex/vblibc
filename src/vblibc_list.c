#include "vblibc_list.h"

static vb_list_item_t *list_add(vb_list_t *, void *);
static vb_list_item_t *list_cut_item(vb_list_t *, size_t);
static int cmp_wrapper(const void *, const void *);
static int (*cmp_callback)(const void *, const void *);

vb_list_t *
vb_list_init ()
{
  vb_list_t *list = malloc(sizeof(vb_list_t));
  if (list != NULL) {
    list->head = NULL;
    list->length = 0;
  }

  return list;
}

static vb_list_item_t *
list_add (vb_list_t *self, void *data)
{
  vb_list_item_t *item;

  item = malloc(sizeof(vb_list_item_t));
  if (item == NULL)
    return NULL;

  item->data = data;
  item->next = NULL;

  if (self->head == NULL) {
    self->head = item;
  } else {
    vb_list_item_t *p = self->head;
    while (p->next != NULL)
      p = p->next;
    p->next = item;
  }
  
  self->length++;

  return item;
}

void *
vb_list_add (vb_list_t *self, void *data)
{
  vb_list_item_t *item;
  assert(self != NULL);

  item = list_add(self, data);
  return item == NULL ? NULL : item->data;
}

void
vb_list_clear (
  vb_list_t *self,
  void *(*dispose_callback)(const void *)
) {
  vb_list_item_t *item, *rm;
  assert(self != NULL);

  while (self->head != NULL)
    vb_list_remove(self, 0, dispose_callback);
}

void
vb_list_destroy (
  vb_list_t **self,
  void *(*dispose_callback)(const void *)
) {
  if (*self != NULL) {
    vb_list_clear(*self, dispose_callback);
    free(*self);
    *self = NULL;
  }
}

void *
vb_list_get (vb_list_t *self, size_t index)
{
  vb_list_item_t *item;
  
  assert(self != NULL);
  if (index >= self->length) return NULL;

  item = self->head;
  while (0 != index--) item = item->next;

  return item->data;
}

static vb_list_item_t *
list_cut_item (vb_list_t *self, size_t index)
{
  vb_list_item_t *p, *rm;

  if (index == 0) {
    rm = self->head;
    self->head = rm->next;
  } else {
    p = self->head;
    while (1 != index--) p = p->next;
    rm = p->next;
    p->next = rm->next;
  }

  self->length--;

  return rm;
}

void *
vb_list_remove (
  vb_list_t *self,
  size_t index,
  void *(*dispose_callback)(const void *)
) {
  vb_list_item_t *item;
  void *data;

  assert(self != NULL);
  if (index >= self->length) return NULL;

  item = list_cut_item(self, index);
  data = item->data;
  free(item);

  if (dispose_callback != NULL)
    return dispose_callback(data);
  else
    return data;
}

static int (*cmp_callback)(const void *, const void *) = NULL;

static int
cmp_wrapper(const void *a, const void *b) {
  vb_list_item_t *item_a, *item_b;
  item_a = *((vb_list_item_t **) a);
  item_b = *((vb_list_item_t **) b);
  
  return cmp_callback(item_a->data, item_b->data);
}

void
vb_list_qsort (
    vb_list_t *self,
    int (*compare)(const void *, const void *) )
{
  vb_list_item_t **items;
  vb_list_item_t *p;
  int i;

  assert(self != NULL);
  if (compare == NULL)
    return;

  cmp_callback = compare;
  
  items = malloc(sizeof(vb_list_item_t *) * self->length);
  if (items == NULL)
    return;

  p = self->head;
  for (i=0; p != NULL; i++) {
    *(items + i) = p;
    p = p->next;
  }

  qsort(items, self->length, sizeof(vb_list_item_t *), cmp_wrapper);

  self->head = *items;
  p = self->head;
  for (i=1; i<self->length; i++) {
    p->next = *(items + i);
    p = p->next;
  }
  p->next = NULL;

  free(items);
}
