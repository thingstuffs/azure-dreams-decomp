#include "common.h"

typedef struct S_8004FC2C {
    void (*func)(void *self);
} S_8004FC2C;

extern void handleAnimatedSelectionMenuInput(void *a0);

/* Call the object's callback, then run its follow-up routine. */
void updateAnimatedSelectionMenu(S_8004FC2C *object) {
    object->func(object);
    handleAnimatedSelectionMenuInput(object);
}
