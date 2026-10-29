/* Relinked copy of town/func_80875404 (func_80875404.c); retail differs only at relocation sites. */
#include "common.h"
#include "town/scene.h"

typedef struct {
    s16 value[4];
} TestValues;

typedef s32 (*Callback)(s32);
typedef struct {
    Callback callback[4];
} CallbackTable;

extern s32 func_80700DC0(s16 value);
extern u8 D_A06FF53C[];

/* Call the indexed callback at the first failed value test or the end of the list. */
s32 dispatch_first_failed_entry(void)
{
    TestValues test_values;
    CallbackTable callbacks;
    s32 choice_index;

    test_values = *(TestValues *)(D_A06FF53C + 0xBD4);
    callbacks = *(CallbackTable *)(D_A06FF53C + 0xBDC);
    choice_index = 0;
    while (test_values.value[choice_index] != 0) {
        if (func_80700DC0(test_values.value[choice_index]) == 0) {
            break;
        }
        choice_index++;
    }
    return callbacks.callback[choice_index](choice_index);
}
