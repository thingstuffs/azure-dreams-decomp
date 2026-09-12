#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D6C18_0_pre {
    u16 unk_00;
} S_800D6C18_0_pre;   /* the 0x2 bytes before arg0 in func_800D6C18, addressed as arg0[-1] */

typedef struct S_800D6C18_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    s16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u8 pad_18[0x3C];
    s16 unk_54;
    s16 unk_56;
} S_800D6C18_0;   /* arg0 in func_800D6C18 */

typedef struct S_800D6C18_1 {
    u8 pad_00[0x14];
    u32 unk_14;
} S_800D6C18_1;   /* temp_v1 in func_800D6C18 */

typedef struct S_800D6C18_2 {
    u8 pad_00[0x14];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_14;   /* overlapping accesses */
} S_800D6C18_2;   /* arg1 in func_800D6C18 */

typedef struct S_800D6C18_3 {
    u8 pad_00[0x44];
    s16 unk_44;
    u8 pad_46[0x6];
    s16 unk_4C;
} S_800D6C18_3;   /* var_a0 in func_800D6C18 */


M2C_UNK func_800D6AD4(); /* extern */
extern M2C_UNK D_800814A0;

/* Updates effect size and offsets, emits a sequence, and flags expiration. */
void func_800D6C18(void *effect, S_800D6C18_2 *size_state) {
    s16 display_size;
    s16 ticks_left;
    s32 index;
    s32 emit_offset;
    u32 size_step;
    S_800D6C18_1 *size_source;
    void *offset_pair;
    s32 *global_base;

    size_source = ((S_800D6C18_0 *)effect)->unk_14;
    if (((S_800D6C18_0 *)effect)->unk_0C >= 0xF) {
        size_step = size_source->unk_14;
        size_state->unk_14.at00.v = (s32) (size_state->unk_14.at00.v + ((s32) (size_step + (size_step >> 0x1F)) >> 1));
    }
    display_size = size_state->unk_14.at02.v + 0x10;
    ((S_800D6C18_0 *)effect)->unk_56 = display_size;
    ((S_800D6C18_0 *)effect)->unk_54 = display_size;
    if ((((S_800D6C18_0 *)effect)->unk_0C < 0x13) && !((u16) ((S_800D6C18_0 *)effect)->unk_0C & 1)) {
        index = 0;
        offset_pair = effect;
        do {
            if (((S_800D6C18_3 *)offset_pair)->unk_44 < 0) {
                ((S_800D6C18_3 *)offset_pair)->unk_44 = (s16) ((u16) ((S_800D6C18_3 *)offset_pair)->unk_44 + 1);
            }
            if (((S_800D6C18_3 *)offset_pair)->unk_44 > 0) {
                ((S_800D6C18_3 *)offset_pair)->unk_44 = (s16) ((u16) ((S_800D6C18_3 *)offset_pair)->unk_44 - 1);
            }
            if (((S_800D6C18_3 *)offset_pair)->unk_4C < 0) {
                ((S_800D6C18_3 *)offset_pair)->unk_4C = (s16) ((u16) ((S_800D6C18_3 *)offset_pair)->unk_4C + 1);
            }
            if (((S_800D6C18_3 *)offset_pair)->unk_4C > 0) {
                ((S_800D6C18_3 *)offset_pair)->unk_4C = (s16) ((u16) ((S_800D6C18_3 *)offset_pair)->unk_4C - 1);
            }
            index += 1;
            offset_pair += 2;
        } while (index < 4);
    }
    if ((((S_800D6C18_0 *)effect)->unk_0C == 0xF) && (((S_800D6C18_0 *)effect)->unk_10 == 0)) {
        index = 0;
        emit_offset = 0;
        do {
            s32 delta;
            s32 color;

            color = 0xE0E0E0;
            /*A*/
            func_800D6AD4((void *)((s8 *)effect - 0x20), color, 0, 0, emit_offset >> 0x10, (s16) index);
            delta = -0x40000;
            emit_offset += delta;
            ASM_KEEP(delta);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            index += 1;
        } while (index < 0x51);
    }
    ticks_left = (u16) ((S_800D6C18_0 *)effect)->unk_0C - 1;
    ((S_800D6C18_0 *)effect)->unk_0C = ticks_left;
    global_base = (s32 *) 0x80080000;
    if ((ticks_left << 0x10) <= 0) {
        ((S_800D6C18_0_pre *)effect)[-1].unk_00 = (u16) (((S_800D6C18_0_pre *)effect)[-1].unk_00 | 0x8000);
        global_base[0x14A0 / 4] |= 0x8000;
    }
}
