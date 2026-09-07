#include "common.h"

typedef struct S_80172CC0_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
    u8 pad_49[0x28];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80172CC0_0;   /* state in func_80172CC0 */

typedef struct S_80172CC0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172CC0_1;   /* arg2 in func_80172CC0 */

typedef struct S_80172CC0_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80172CC0_2;   /* entry in func_80172CC0 */

typedef struct S_80172CC0_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_80172CC0_3;   /* arg0 in func_80172CC0 */

typedef struct S_80172CC0_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80172CC0_4;   /* (u8 *)state + ((S_80172CC0_0 *)state)->unk_8A.s in func_80172CC0 */



extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern s32 func_80173678();

extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_80175DC4;
extern s32 D_80175DCC;
extern s32 D_80175DD4;

void func_80172CC0(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    void *state = arg3;
    s32 call_mode;
    s32 result;
    s16 step;
    s32 x;
    s32 y;
    s32 kind;
    s32 count;
    unsigned long table_index;
    u8 *selected;
    u8 *current;
    u8 *entry;

    if (((S_80172CC0_0 *)state)->unk_71.s <= 0) {
        return;
    }
    count = ((S_80172CC0_0 *)state)->unk_71.u;
    if (!(((S_80172CC0_0 *)state)->unk_8A.s < count)) {
        return;
    }

    kind = ((S_80172CC0_0 *)state)->unk_48;
    if (kind == 0xE) {
        goto kind_0e;
    }
    if ((s32)kind < 0xF) {
        if (kind == 0xD) {
            goto kind_0d;
        }
        goto setup;
    }
    if (kind == 0xF) {
        goto kind_0f;
    }
    goto setup;

kind_0d:
    current = ((S_80172CC0_1 *)arg2)->unk_2C;
    selected = (u8 *)&D_80175DC4;
    goto selected_kind;

kind_0e:
    current = ((S_80172CC0_1 *)arg2)->unk_2C;
    selected = (u8 *)&D_80175DCC;
    goto selected_kind;

kind_0f:
    current = ((S_80172CC0_1 *)arg2)->unk_2C;
    selected = (u8 *)&D_80175DD4;

selected_kind:
    if (current != selected) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = selected;
        table_index =
            ((D_80083228 + ((S_80172CC0_0 *)state)->unk_2A + 0x100) >> 9) & 7;
        table_index += (unsigned long)selected;
        func_80047784(arg2, *(u8 *)table_index, 0);
    }

setup:
    call_mode = 0x3000;
    x = ((S_80172CC0_1 *)arg2)->unk_24;
    y = ((S_80172CC0_1 *)arg2)->unk_25;
    if (((S_80172CC0_0 *)state)->unk_1C & 0x2000) {
        call_mode = 0x300;
    }
    func_8009A3D0(x, y, call_mode);

    step = func_800A0818(x, y,
        ((S_80172CC0_4 *)((u8 *)state + ((S_80172CC0_0 *)state)->unk_8A.s))->unk_74,
        ((S_80172CC0_4 *)((u8 *)state + ((S_80172CC0_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)arg0 + 0x98);
    result = (s16)func_8009A66C(step, arg2, state, 0x20);

    entry = (u8 *)state + ((S_80172CC0_0 *)state)->unk_8A.s;
    ((S_80172CC0_1 *)arg2)->unk_24 = ((S_80172CC0_2 *)entry)->unk_74;
    call_mode = 0x3000;
    entry = (u8 *)state + ((S_80172CC0_0 *)state)->unk_8A.s;
    ((S_80172CC0_1 *)arg2)->unk_25 = ((S_80172CC0_2 *)entry)->unk_7C;
    ((S_80172CC0_0 *)state)->unk_8A.u++;
    {
        s32 next_x = ((S_80172CC0_1 *)arg2)->unk_24;
        s32 next_y = ((S_80172CC0_1 *)arg2)->unk_25;

        if (((S_80172CC0_0 *)state)->unk_1C & 0x2000) {
            call_mode = 0x300;
        }
        func_8009A21C(next_x, next_y, call_mode);
    }

    ASM_KEEP(result);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ((S_80172CC0_0 *)state)->unk_2A = step;
    if (result == 3) {
        if (!(D_80083462 & 0x80) && !(((S_80172CC0_1 *)arg2)->unk_14 & 0x8000)) {
            func_80173678(arg0, arg1, arg2, state);
            ((S_80172CC0_3 *)arg0)->unk_8C = 0;
            goto finish_state;
        }
    }

    ((S_80172CC0_3 *)arg0)->unk_9A = 0xF;
    ((S_80172CC0_3 *)arg0)->unk_8C = 0;

finish_state:
    (*(s32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (D_80083462 & 0x80) {
        ((S_80172CC0_3 *)arg0)->unk_96 = 0;
        return;
    }

    ((S_80172CC0_3 *)arg0)->unk_96 = 8;
    x = ((S_80172CC0_0 *)state)->unk_71.u;
    if (x > 0) {
        ((S_80172CC0_3 *)arg0)->unk_96 = 8 / x;
    }
}

/* MECHANISM: The 0x38 frame comes from the held s1 state and a guarded s0 signed result from the s16 callee.
   Scoped coordinate reloads and mode initialization reproduce the post-call schedule without the +4-word cascade.
   An unsigned-long index compound assignment selects retail's index+base addu operand order. */
