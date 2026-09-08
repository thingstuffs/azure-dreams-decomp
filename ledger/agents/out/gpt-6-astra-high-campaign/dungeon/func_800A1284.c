#include "common.h"

extern void func_800A08A0(s32 arg0);
extern s32 func_800A6DA4(s32 arg0, s32 arg1);

/* Initializes monster spawn rates with values 2 through 17 and a random number of value 1 entries. */
void func_800A69E4(void) {
    s32 repeat_count;
    s32 call_index;
    s32 scaled_value;

    repeat_count = func_800A6DA4(4, 8) & 0xFFFF;
    call_index = 0;
    scaled_value = 0x20000;
sequence_loop:
    func_800A08A0(scaled_value >> 0x10);
    scaled_value += 0x10000;
    call_index += 1;
    if (call_index < 0x10)
        goto sequence_loop;
    call_index = 0;
    if (call_index >= repeat_count)
        goto done;
repeat_loop:
    func_800A08A0(1);
    call_index += 1;
    if (call_index < repeat_count)
        goto repeat_loop;
done:
    ;
}
