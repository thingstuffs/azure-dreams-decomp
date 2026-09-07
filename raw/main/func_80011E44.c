#include "common.h"

extern void func_8004E994();

/* Each of the three loops walks an array of pointer-fields inside *arg0
 * (0xB4C: 3 entries, 0xB58: 4 entries, 0xB68: 10 entries). Each entry holds
 * a pointer to some other object; the loop clears the pointed-to word to 0.
 * The first loop also notifies func_8004E994 with the old value before
 * clearing it (likely a deregister/free callback). */
void func_80024E44(void *arg0) {
    s32 i;
    void *p1;
    void *p2;

    for (i = 0; i < 3; i++) {
        func_8004E994(*(*(s32 **) ((u8 *) arg0 + i * 4 + 0xB4C)));
        *(*(s32 **) ((u8 *) arg0 + i * 4 + 0xB4C)) = 0;
    }

    i = 0;
    p1 = arg0;
    for (; i < 4; i++) {
        *(*(s32 **) ((u8 *) p1 + 0xB58)) = 0;
        p1 = (u8 *) p1 + 4;
    }

    i = 0;
    p2 = arg0;
    for (; i < 0xA; i++) {
        *(*(s32 **) ((u8 *) p2 + 0xB68)) = 0;
        p2 = (u8 *) p2 + 4;
    }
}
