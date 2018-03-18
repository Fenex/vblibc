#ifndef __VBLIBC_LIST_H
#define __VBLIBC_LIST_H

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * List structure that can be created by call `link vb_list_init` function
 */
typedef struct vb_list_t {
  /** First element of the list */
  struct vb_list_item_t *head;

  /** Length of the list */
  size_t length;
} vb_list_t;

/**
 * Describe element of the list
 */
typedef struct vb_list_item_t {
  /** Next element of the list */
  struct vb_list_item_t *next;
  
  /** Data that will be added to the list */
  void *data;
} vb_list_item_t;

/**
 * Creates new list
 * 
 * @return vb_list_t* 
 */
vb_list_t *vb_list_init();

/**
 * Appends data onto the list
 * 
 * @param self The input list
 * @param data The value to appends onto `self` list
 * @return NULL if an error has occurred, otherwise value of `data` param
 */
void *vb_list_add(
  vb_list_t *self,
  void *data
);

/**
 * Clears list
 * 
 * @param self The input list
 * @param dispose_callback The function will be called to each element
 */
void vb_list_clear(
  vb_list_t *self, void* (*dispose_callback)(const void *)
);

/**
 * Destroys list
 * 
 * @param p_self Pointer to the input list
 * @param dispose_callback The function will be called to each element
 */
void vb_list_destroy(
  vb_list_t **p_self,
  void* (*dispose_callback)(const void *)
);

/**
 * Gets data by index
 * 
 * @param self The input list
 * @param index Gets yourself data at the specified index
 * @return void* Point to yourself data
 */
void *vb_list_get(
  vb_list_t *self,
  size_t index
);

/**
 * Removes element by index
 * 
 * @param self The input list
 * @param index The specified index of the removing element
 * @param dispose_callback The function will be called to the removing element
 * @return void* A data contained in removed element
 */
void *vb_list_remove(
  vb_list_t *self,
  size_t index,
  void* (*dispose_callback)(const void *)
);

/**
 * Sort list using a callback compare function
 * 
 * @param self The input list that will be sorted
 * @param compare The function that compares two elements
 */
void vb_list_qsort(
  vb_list_t *self,
  int (*compare)(const void *, const void *)
);

#ifdef __cplusplus
}
#endif

#endif // !__VBLIBC_LIST_H
