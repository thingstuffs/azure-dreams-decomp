#include "common.h"

typedef struct {
    s32 word[2];
} __attribute__((packed)) Packed8;

typedef void (*Callback)(s32);
typedef struct {
    Callback callback[4];
} CallbackTable;

extern s32 func_807018AC(s16 value);
extern u8 D_80700000[];

/* Call the indexed callback at the first failed value test or the end of the list. */
void func_80875404(void)
{
    Packed8 test_values;
    CallbackTable callbacks;
    s32 value_offset;
    register s16 *value_base ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s16 *saved_base;
    register s32 choice_index ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 *next_value;
    s32 callback_offset;

    test_values = *(Packed8 *)(D_80700000 + 0xBD4);
    callbacks = *(CallbackTable *)(D_80700000 + 0xBDC);
    choice_index = 0;
    if (*(s16 *)&test_values != 0) {
        value_base = (s16 *)&test_values;
        value_offset = 0;
check_value:
        callback_offset = choice_index * 4;
        saved_base = value_base;
        if (func_807018AC(*(s16 *)(value_offset + (s32)value_base)) == 0) {
            goto dispatch;
        }
        value_offset += 2;
        choice_index += 1;
        next_value = (s16 *)(value_offset + (s32)saved_base);
        if (*next_value == 0) {
            goto end_values;
        }
        goto check_value;
    }
end_values:
    callback_offset = choice_index * 4;
dispatch:
    callbacks.callback[choice_index](choice_index);
}
