#include "common.h"

typedef struct CallbackNode {
    void (*callback)();
} CallbackNode;

#ifndef NULL
#define NULL 0
#endif

void func_800AE600(CallbackNode *arg0) {
    if (arg0->callback != NULL) {
        arg0->callback(arg0);
    }
}
