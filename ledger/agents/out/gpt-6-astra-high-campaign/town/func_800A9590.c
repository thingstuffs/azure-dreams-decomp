#include "common.h"

/* Global 32-bit "used"/flags word, same one touched by func_8004B530 /
 * func_8004F52C / func_800510DC family. Declared as an array (>8B) so gcc
 * uses %hi/%lo addressing with a SINGLE shared base register across the
 * read and write halves of the |= (see w_800510DC.c), matching retail's
 * one lui reused for both the load and the store. */
extern int D_800814A0[3];

extern int func_8009CFE0(void *, void *);
extern void func_8008F134(void *arg0);
extern void func_80033D08(void *arg0);

typedef void (*S_800A9590_Callback)(void *, void *, void *, void *);

/* Cleans up and flags the object when its check succeeds, otherwise invokes its callback. */
void func_800A6CF0(void *object, void *input, void *context)
{
    u8 *status_byte;
    S_800A9590_Callback callback;

    if (func_8009CFE0(object, input) != 0) {
        func_8008F134(object);
        status_byte = *(u8 **)((u8 *)object + 0x98);
        if (status_byte != 0) {
            *status_byte = 0;
        }
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }
    callback = *(S_800A9590_Callback *)((u8 *)object + 0x50);
    if (callback != 0) {
        callback(object, object, input, context);
    }
}
