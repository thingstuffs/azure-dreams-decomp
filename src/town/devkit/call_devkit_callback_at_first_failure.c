#include "common.h"
#include "town/scene/flags.h"

typedef struct {
    s16 value[4];
} TestValues;

typedef s32 (*Callback)(s32);
typedef struct {
    Callback callback[4];
} CallbackTable;

extern u8 devkit_globals_page[];

/* Call the indexed callback at the first failed value test or the end of the list. */
s32 call_devkit_callback_at_first_failure(void)
{
    TestValues test_values;
    CallbackTable callbacks;
    s32 choice_index;

    test_values = *(TestValues *)(devkit_globals_page + 0xBD4);
    callbacks = *(CallbackTable *)(devkit_globals_page + 0xBDC);
    choice_index = 0;
    while (test_values.value[choice_index] != 0) {
        if (test_indexed_flag_bit(test_values.value[choice_index]) == 0) {
            break;
        }
        choice_index++;
    }
    return callbacks.callback[choice_index](choice_index);
}
