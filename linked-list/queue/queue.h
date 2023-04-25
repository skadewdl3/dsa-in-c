#include "./queue-errors.h"
#include "./queue-int.h"
#include "./queue-char.h"

#define Queue_destroy(Q) _Generic((Q),                             \
IntQ*: Queue_destroy,                                             \
CharQ*: Queue_destroy                                            \
)(Q)

#define Queue_enqueue(Q) _Generic((Q),                             \
IntQ*: Queue_enqueue,                                             \
CharQ*: Queue_enqueue                                            \
)(Q)
