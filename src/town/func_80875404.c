#include "common.h"

typedef struct {
    s16 value[4];
} TestValues;

typedef void (*Callback)(s32);
typedef struct {
    Callback callback[4];
} CallbackTable;

extern s32 func_807018AC(s16 value);
extern u8 D_80700000[];

/* Call the indexed callback at the first failed value test or the end of the list. */
void func_80875404(void)
{
    TestValues test_values;
    CallbackTable callbacks;
    s32 choice_index;

    test_values = *(TestValues *)(D_80700000 + 0xBD4);
    callbacks = *(CallbackTable *)(D_80700000 + 0xBDC);
    choice_index = 0;
    while (test_values.value[choice_index] != 0) {
        if (func_807018AC(test_values.value[choice_index]) == 0) {
            break;
        }
        choice_index++;
    }
    callbacks.callback[choice_index](choice_index);
}
