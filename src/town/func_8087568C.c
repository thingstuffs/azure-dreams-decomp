/* Relinked copy of town/func_80875404 (func_80875404.c); retail differs only at relocation sites. */
#include "common.h"

typedef struct {
    s16 value[4];
} TestValues;

typedef void (*Callback)(s32);
typedef struct {
    Callback callback[4];
} CallbackTable;

extern s32 test_indexed_flag_bit(s16 value);
extern u8 D_80700018[];

/* Call the indexed callback at the first failed value test or the end of the list. */
void call_indexed_callback_failed_test(void)
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
    callbacks.callback[choice_index](choice_index);
}
