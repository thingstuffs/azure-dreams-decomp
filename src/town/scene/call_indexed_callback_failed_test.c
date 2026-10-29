/* Relinked copy of town/func_80875404 (func_80875404.c); retail differs only at relocation sites. */
#include "town/scene.h"
#include "town/scene/flags.h"

typedef struct {
    s16 value[4];
} TestValues;

typedef s32 (*Callback)(s32);
typedef struct {
    Callback callback[4];
} CallbackTable;

extern u8 D_80700018[];

/* Call the indexed callback at the first failed value test or the end of the list. */
s32 call_indexed_callback_failed_test(void)
{
    TestValues test_values;
    CallbackTable callbacks;
    s32 choice_index;

    test_values = *(TestValues *)(D_80700018 + 0xBD4);
    callbacks = *(CallbackTable *)(D_80700018 + 0xBDC);
    choice_index = 0;
    while (test_values.value[choice_index] != 0) {
        if (test_indexed_flag_bit(test_values.value[choice_index]) == 0) {
            break;
        }
        choice_index++;
    }
    return callbacks.callback[choice_index](choice_index);
}
