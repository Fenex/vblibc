#ifndef __VBLIBC_STACK_H
#define __VBLIBC_STACK_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The Stack structure.
 */
typedef struct vb_stack_t {
  /** Next item in the stack */
  struct vb_stack_t *next;

  /** Value of the item */
  void *data;
} vb_stack_t;

/**
 * Inserts an object at the top of the stack
 * 
 * @param head The input head of the stack
 * @param data The object to push onto the stack
 */
void vb_stack_push(vb_stack_t** head, void* data);

/**
 * Removes and returns the object at the top of the stack
 * 
 * @param head The input head of the stack
 * @return void* The object at the top of the stack
 */
void* vb_stack_pop(vb_stack_t** head);

/**
 * Destroys the stack
 * 
 * @note Don't forget dispose (free) memory by points `vb_stack_t->data` if necessary.
 * @param head The input head of the stack
 */
void vb_stack_destroy(vb_stack_t** head);

/**
 * Get deep of the stack
 * 
 * @param head The input head of the stack
 * @return Deep of the stack
 */
int vb_stack_deep(vb_stack_t* head);

#ifdef __cplusplus
}
#endif

#endif /* !__VBLIBC_STACK_H */