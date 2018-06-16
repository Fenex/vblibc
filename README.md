# vblibc
The repository contains two tiny C libraries: 
* vblibc_list.h - simple singly linked list
* vblibc_stack.h - simple stack
* vblibc_string.h - functions for work with strings

You can see tests as examples to know how to use libs.

## vblibc_list.h
A simple singly linked list.

All available functions with short description shown below.
See [vblibc_list.h](/src/vblibc_list.h) for more details.
```C
vb_list_init(); // init new singly linked list
vb_list_add(stack ,value); // appends new value onto the list
vb_list_clear(stack, dispose_callback); // removes all values from the list
vb_list_destroy(stack, dispose_callback); // removes all values from the list and destroys the list
vb_list_get(stack, index); // gets value by index
vb_list_remove(stack, index); // removes value by index
vb_list_qsort(stack, compare_callback); // sorts the list using callback compare function
```

## vblibc_stack.h
A simple stack.

All available functions shown below.
See [vblibc_stack.h](/src/vblibc_stack.h) for more details.
```C
vb_stack_push(stack, value);
vb_stack_pop(stack);
vb_stack_destroy(stack);
vb_stack_deep(stack);
```

## vblibc_string.h
Functions for work with strings

All available functions shown below.
See [test_string.c](/test/test_string.c) for know how to use.
```C
vb_string_is_starts_with(string_base, search_string); // similar to `String.prototype.startsWith` in JavaScript
vb_string_is_ends_with(string_base, search_string); // similar to `String.prototype.endsWith` in JavaScript
```

## Run tests
Project use ceedling for running tests.

* Install Ruby and ceedling;
* Run commands:
```
# clone the repository
%work%/$> git clone https://github.com/Fenex/vblibc.git 

# create ceedling files
%work%/$> ceedling new vblibc

# change current directory
%work%/$> cd vblibc

# run tests
%work%/vblibc/$> ceedling
```
