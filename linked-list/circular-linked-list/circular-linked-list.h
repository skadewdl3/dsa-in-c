#include "./circular-linked-list-errors.h"
#include "./circular-linked-list-int.h"
#include "./circular-linked-list-char.h"

#define LL_destroy(LL) _Generic((LL),                             \
IntLL*: IntLL_destroy,                                             \
CharLL*: CharLL_destroy                                            \
)(LL)

#define LL_is_empty(LL) _Generic((LL),                            \
IntLL*: IntLL_is_empty,                                            \
CharLL*: CharLL_is_empty                                           \
)(LL)


#define LL_push(LL, value) _Generic((LL),                         \
IntLL*: IntLL_push,                                                \
CharLL*: CharLL_push                                               \
)(LL, value)


#define LL_unshift(LL, value) _Generic((LL),                      \
IntLL*: IntLL_unshift,                                             \
CharLL*: CharLL_unshift                                            \
)(LL, value)

#define LL_insert(LL, value, index) _Generic((LL),                \
IntLL*: IntLL_insert,                                              \
CharLL*: CharLL_insert                                             \
)(LL, value, index)

#define LL_pop(LL) _Generic((LL),                                 \
IntLL*: IntLL_pop,                                                 \
CharLL*: CharLL_pop                                                \
)(LL)


#define LL_shift(LL) _Generic((LL),                               \
IntLL*: IntLL_shift,                                               \
CharLL*: CharLL_shift                                              \
)(LL)


#define LL_delete(LL, index) _Generic((LL),                       \
IntLL*: IntLL_delete,                                              \
CharLL*: CharLL_delete                                             \
)(LL, index)

#define LL_reverse(LL) _Generic((LL),                             \
IntLL*: IntLL_reverse,                                             \
CharLL*: CharLL_reverse                                            \
)(LL)

#define LL_print(LL) _Generic((LL),                               \
IntLL*: IntLL_print,                                               \
CharLL*: CharLL_print                                              \
)(LL)

#define LL_get(LL, index) _Generic((LL),                          \
IntLL*: IntLL_get,                                                 \
CharLL*: CharLL_get                                                \
)(LL, index)


#define LL_set(LL, value, index) _Generic((LL),                   \
IntLL*: IntLL_set,                                                 \
CharLL*: CharLL_set                                                \
)(LL, value, index)
