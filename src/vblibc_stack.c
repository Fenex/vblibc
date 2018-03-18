#include "vblibc_stack.h"

void
vb_stack_push (vb_stack_t **head, void *data)
{
  vb_stack_t *elem;
  
  elem = malloc(sizeof(vb_stack_t));
  elem->next = *head;
  elem->data = data;
  *head = elem;
  
  return;
}

void *
vb_stack_pop (vb_stack_t **head)
{
  vb_stack_t *elem;
  void *data;
  
  if (*head == NULL) {
    return NULL;
  }
  
  elem = *head;
  *head = elem->next;
  data = elem->data;
  free(elem);
  
  return data;
}

void
vb_stack_destroy (vb_stack_t **head)
{
  vb_stack_t *elem;
  vb_stack_t *rm;
  
  elem = *head;
  
  while (elem != NULL) {
    rm = elem;
    elem = elem->next;
    free(rm);
  }
  
  *head = elem;
  
  return;
}

int
vb_stack_deep (vb_stack_t *head)
{
  int len;
  vb_stack_t *point;
  
  for (len=0; head != NULL; len++) {
    head = head->next;
  }

  return len;
}
