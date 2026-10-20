/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad[0x54];
    s32 (*callback)(s32);
} CallbackOwner;

extern u8 D_A0700000[0x1000];
extern CallbackOwner *D_A0700F58[4];

extern s32 func_80700304(s32, s32, s32, s32);
extern s32 func_80700590(s32, u8 *);
extern s32 func_80700DC0(s16);

typedef struct S_808B2B98_0 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_808B2B98_0;   /* record in func_808B2B98 */

s32 func_808B2B98(s32 initial_index, s32 input1, s32 input2, s32 input3) {
    s32 value;
    s32 offset;
    s32 index;
    u8 *byte_ptr;
    S_808B2B98_0 *record;
    s32 result;

    index = initial_index;
    if (func_80700304(initial_index, input1, input2, input3) > 0) {
        value = *(s16 *)(D_A0700000 + (index * 2) + 0xF34);
        offset = value;
        offset /= 32;
        byte_ptr = *(u8 **)0xA0700F40;
        byte_ptr += offset;
        offset <<= 5;
        offset = value - offset;
        *byte_ptr |= 1 << offset;
        return func_80700590(offset, byte_ptr);
    }
    D_A0700F58[0]->callback(2);
    record = *(void **)0xA0700F40;
    record->unk_0E = (u8) record->unk_0E;
    result = func_80700DC0(*(s16 *)0xA0700F2A);
    if (result == 0) {
        if (D_A0700F58[0]->callback(2) != 0) {
            index += 1;
        }
        *(s32 *)0xA0700F3C = index;
    } else {
        index = *(s32 *)0xA0700F3C;
    }
    value = index;
    return value;
}
