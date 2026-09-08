#include "common.h"

/* Set the object's value, preserve its previous value, and reset its state. */
void func_80023A50(s32 object_addr, s32 value) {
    s32 *state_fields;
    s32 previous_value;

    if (object_addr != 0) {
        state_fields = (s32 *)(object_addr + 0x20);
        previous_value = *(s32 *)((u8 *)state_fields + 0x88);
        *(s32 *)((u8 *)state_fields + 0x84) = 0;
        *(s32 *)((u8 *)state_fields + 0x80) = 3;
        *(s32 *)((u8 *)state_fields + 0x88) = value;
        *(s32 *)((u8 *)state_fields + 0x8C) = previous_value;
    }
}
