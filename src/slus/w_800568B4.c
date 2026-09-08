#include "common.h"

#include "common.h"

#define S16_FIELD(ptr, offset) (*(s16 *)((u8 *)(ptr) + (offset)))
#define U16_FIELD(ptr, offset) (*(u16 *)((u8 *)(ptr) + (offset)))
#define S32_FIELD(ptr, offset) (*(s32 *)((u8 *)(ptr) + (offset)))

void func_800568B4(void *arg0) {
    register u8 *ptr ASM_REG("$6") = arg0;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 temp_v0;
    s32 temp_a0;
    u16 temp_a1;

    if (S16_FIELD(ptr, 0x50) != 0) {
        if (S32_FIELD(ptr, 0x58) != 0) {
            temp_a1 = U16_FIELD(ptr, 0x56);
            if ((S16_FIELD(ptr, 0x52) + S16_FIELD(ptr, 0x54)) < (s32) temp_a1) {
                S16_FIELD(ptr, 0x52) = U16_FIELD(ptr, 0x52) + U16_FIELD(ptr, 0x54);
                return;
            }
            S16_FIELD(ptr, 0x52) = temp_a1;
            return;
        }
        temp_v0 = S16_FIELD(ptr, 0x52) - S16_FIELD(ptr, 0x54);
        temp_a0 = -U16_FIELD(ptr, 0x56);
        if (temp_a0 < temp_v0) {
            S16_FIELD(ptr, 0x52) = U16_FIELD(ptr, 0x52) - U16_FIELD(ptr, 0x54);
            return;
        }
        S16_FIELD(ptr, 0x52) = temp_a0;
    }
}
