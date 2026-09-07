#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004491C();
extern M2C_UNK func_80044A50();
extern M2C_UNK D_80083460;
extern M2C_UNK D_800C6AEC;

typedef struct S_800ACD74_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_800ACD74_0;   /* arg0 in func_800ACD74 */

typedef struct S_800ACD74_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    s8 unk_0F;
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
} S_800ACD74_1;   /* arg2 in func_800ACD74 */

typedef struct S_800ACD74_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800ACD74_2;   /* arg3 in func_800ACD74 */

/* Resets object state, runs object setup, and updates property and status flags. */
void func_800ACD74(void *object_state, void *unused_context, S_800ACD74_1 *properties, S_800ACD74_2 *status) {
    void *object;
    u16 *global_state;

    ((S_800ACD74_0 *)object_state)->unk_9A = 0x13;
    ((S_800ACD74_0 *)object_state)->unk_9B = 0;
    ((S_800ACD74_0 *)object_state)->unk_8C = 0;
    properties->unk_14 = (u16)(properties->unk_14 & 0xF7FF);
    ((S_800ACD74_0 *)object_state)->unk_96 = 0;
    object = object_state - 0x20;
    global_state = (u16 *)&D_80083460;
    global_state[5] = (u16)(global_state[5] + 1);
    func_80044A50(object);
    func_8004491C(object, &D_800C6AEC);
    properties->unk_0F = 0;
    properties->unk_0E = 0;
    properties->unk_0D = 0;
    properties->unk_0C = 0;
    properties->unk_10 = 0x20;
    properties->unk_12 = (u16)(properties->unk_12 - 0x80);
    status->unk_1C = (s32)(status->unk_1C | 0x10000000);
}
