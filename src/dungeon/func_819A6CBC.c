#include "common.h"
#include "m2c_compat.h"

typedef struct S_800244BC_0_pre {
    u16 unk_00;
} S_800244BC_0_pre;   /* the 0x2 bytes before arg0 in func_800244BC, addressed as arg0[-1] */

typedef struct S_800244BC_0 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_800244BC_0;   /* arg0 in func_800244BC */

typedef struct S_800244BC_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_800244BC_1;   /* temp_v1 in func_800244BC */

typedef struct S_800244BC_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800244BC_2;   /* arg1 in func_800244BC */

typedef struct S_800244BC_3 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800244BC_3;   /* temp_v0 in func_800244BC */

typedef struct S_800244BC_4 {
    u8 pad_00[0x24];
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u8 pad_2A[0x6];
    s16 unk_30;
    s16 unk_32;
    u8 pad_34[0x4];
    s32 unk_38;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
} S_800244BC_4;   /* temp_s0 in func_800244BC */


typedef struct {
    u8 pad[0xC];
    u32 word0;
    u32 word1;
} CopySource __attribute__((packed));

typedef struct {
    u8 pad[0x24];
    u32 word0;
    u32 word1;
} CopyDestination __attribute__((packed));

/* cfail-repair: tf7-phase1-cache-v3 */
extern s16 D_80083780[];
extern s32 D_800814A0[3];
extern s32 D_80082E80[];
extern u8 D_80083498[];
s32 func_8003DE58();       /* extern */
void *func_8003FD64();                 /* extern */
s32 func_800644B8(s32, s16 *); /* extern */
s16 func_80066460(); /* extern */
s32 rand();                                /* extern */
void func_800478B8(M2C_UNK);                         /* extern */
extern M2C_UNK D_80024E4C;

/* Move toward the target while spawning effects, then mark the sequence complete. */
void func_800244BC(void *object, S_800244BC_2 *position, M2C_UNK context) {
    s16 target_pos[3];
    s16 phase;
    s32 effects_left;
    S_800244BC_4 *effect_data;
    void *effect;
    S_800244BC_1 *owner;

    owner = ((S_800244BC_0 *)object)->unk_00;
    ((S_800244BC_0 *)object)->unk_48 = (u16) (((S_800244BC_0 *)object)->unk_48 - 1);
    owner->unk_52 = (u16) (owner->unk_52 | 0x8000);
    phase = ((S_800244BC_0 *)object)->unk_4C;
    if (phase == 1) {
        goto approach_target;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto init_motion;
        }
        return;
    }
    if (phase == 2) {
        goto settle_target;
    }
    return;

init_motion:
    ((S_800244BC_0 *)object)->unk_48 = 0xAU;
    ((S_800244BC_0 *)object)->unk_4C = (s16) ((u16) ((S_800244BC_0 *)object)->unk_4C + 1);

approach_target:
    if (func_8003DE58(D_80082E80[2], D_80082E80, target_pos, 0) != 0) {
        func_800478B8(context);
        position->unk_00.at00.v = (s32) (position->unk_00.at00.v + (((target_pos[0] + D_80083780[1]) - position->unk_00.at02.v) << 0xE));
        position->unk_04.at00.v = (s32) (position->unk_04.at00.v + (((target_pos[1] + D_80083780[3]) - position->unk_04.at02.v) << 0xE));
        position->unk_08.at00.v = (s32) (position->unk_08.at00.v + (((target_pos[2] + D_80083780[5]) - position->unk_08.at02.v) << 0xE));
        effects_left = 0;
        position->unk_08.at00.v = (s32) (position->unk_08.at00.v - (func_800644B8(((s16) ((S_800244BC_0 *)object)->unk_48 << 0xB) / 10, D_80083780) << 9));
        do {
            effect = func_8003FD64(0x302, D_80083498);
            effect_data = effect + 0x20;
            if (effect != NULL) {
                ((S_800244BC_3 *)effect)->unk_10 = &D_80024E4C;
                effect_data->unk_3C = 0;
                effect_data->unk_3E = (s16) ((rand() & 3) + 2);
                effect_data->unk_32 = 0x1F;
                effect_data->unk_30 = 0x1F;
                effect_data->unk_40 = func_80066460(0, 1, 0x2C0, 0x100);
                effect_data->unk_38 = 0x404040;
                memcpy((u8 *) effect + 0x24, (u8 *) object + 0xC, 8);
                effect_data->unk_24 = (u16) position->unk_00.at02.v;
                effect_data->unk_26 = (u16) position->unk_04.at02.v;
                effect_data->unk_28 = (u16) position->unk_08.at02.v;
                ((S_800244BC_3 *)effect)->unk_20 = (void *) ((S_800244BC_0 *)object)->unk_00;
            }
            effects_left -= 1;
        } while (effects_left >= 0);
    }
    if ((s16) ((S_800244BC_0 *)object)->unk_48 <= 0) {
        ((S_800244BC_0 *)object)->unk_48 = 8U;
        ((S_800244BC_0 *)object)->unk_4C = (s16) ((u16) ((S_800244BC_0 *)object)->unk_4C + 1);
        return;
    }

    return;

settle_target:
    if (func_8003DE58(D_80082E80[2], D_80082E80, target_pos, 0) != 0) {
        func_800478B8(context);
        position->unk_00.at00.v = (s32) (position->unk_00.at00.v + (((target_pos[0] + D_80083780[1]) - position->unk_00.at02.v) << 0xF));
        position->unk_04.at00.v = (s32) (position->unk_04.at00.v + (((target_pos[1] + D_80083780[3]) - position->unk_04.at02.v) << 0xF));
        position->unk_08.at00.v = (s32) (position->unk_08.at00.v + (((target_pos[2] + D_80083780[5]) - position->unk_08.at02.v) << 0xF));
    }
    if ((s16) ((S_800244BC_0 *)object)->unk_48 <= 0) {
        ((S_800244BC_0_pre *)object)[-1].unk_00 = (u16) (((S_800244BC_0_pre *)object)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
