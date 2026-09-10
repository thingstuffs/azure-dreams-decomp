#include "common.h"

#include "common.h"

#define S16_FIELD(ptr, offset) (*(s16 *)((u8 *)(ptr) + (offset)))
#define U16_FIELD(ptr, offset) (*(u16 *)((u8 *)(ptr) + (offset)))
#define S32_FIELD(ptr, offset) (*(s32 *)((u8 *)(ptr) + (offset)))

/* Steps an enabled value toward its positive or negative limit. */
void func_800568B4(void *state) {
    u8 *fields = state;
    s32 next_value;
    s32 lower_limit;
    u16 upper_limit;

    if (S16_FIELD(fields, 0x50) != 0) {
        if (S32_FIELD(fields, 0x58) != 0) {
            upper_limit = U16_FIELD(fields, 0x56);
            if ((S16_FIELD(fields, 0x52) + S16_FIELD(fields, 0x54)) < (s32) upper_limit) {
                S16_FIELD(fields, 0x52) = U16_FIELD(fields, 0x52) + U16_FIELD(fields, 0x54);
                return;
            }
            S16_FIELD(fields, 0x52) = upper_limit;
            do {
                return;
            } while (0);
        }
        next_value = S16_FIELD(fields, 0x52) - S16_FIELD(fields, 0x54);
        lower_limit = -U16_FIELD(fields, 0x56);
        if (lower_limit < next_value) {
            do {
                S16_FIELD(fields, 0x52) = U16_FIELD(fields, 0x52) - U16_FIELD(fields, 0x54);
            } while (0);
            return;
        }
        S16_FIELD(fields, 0x52) = lower_limit;
    }
}
