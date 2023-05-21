// #include "./singly-linked-list-errors.h"
#include "./stack-int.h"
#include "./stack-char.h"

#define Stack_destroy(Stack) _Generic((Stack),                             \
IntStack*: IntStack_destroy,                                             \
CharStack*: CharStack_destroy                                             \
)(Stack)

#define Stack_is_empty(Stack) _Generic((Stack),                            \
IntStack*: IntStack_is_empty,                                            \
CharStack*: CharStack_is_empty                                            \
)(Stack)


#define Stack_push(Stack, value) _Generic((Stack),                         \
IntStack*: IntStack_push,                                                \
CharStack*: CharStack_push                                                 \
)(Stack, value)


#define Stack_pop(Stack) _Generic((Stack),                                 \
IntStack*: IntStack_pop,                                                 \
CharStack*: CharStack_pop                                                   \
)(Stack)


#define Stack_print(Stack) _Generic((Stack),                               \
IntStack*: IntStack_print,                                               \
CharStack*: CharStack_print                                               \
)(Stack)

#define Stack_peek(Stack) _Generic((Stack),                               \
IntStack*: IntStack_peek,                                               \
CharStack*: CharStack_peek                                               \
)(Stack)

