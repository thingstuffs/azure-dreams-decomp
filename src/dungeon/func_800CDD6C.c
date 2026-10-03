#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct S_800D34CC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800D34CC_0;   /* state in func_800D34CC */

typedef struct S_800D34CC_1_pre {
    u16 unk_00;
} S_800D34CC_1_pre;   /* the 0x2 bytes before entity in func_800D34CC, addressed as entity[-1] */


typedef struct S_800D34CC_2 {
    u8 pad_00[0xC];
    union {
        struct { s32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x2]; u8 v; } at02u;
    } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_800D34CC_2;   /* data in func_800D34CC */

typedef struct S_800D34CC_3 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800D34CC_3;   /* var_v0 in func_800D34CC */


s32 func_80042900();                 /* extern */
M2C_UNK func_8009A028();                      /* extern */
M2C_UNK func_8009A3D0();             /* extern */
void func_800A32A4(void *);                 /* extern */
M2C_UNK func_800A56C0();                            /* extern */
M2C_UNK func_800A56E0();                     /* extern */

void func_800D34CC(void *state, void *unused, void *data, void *entity) {
    M2C_UNK selectedValue;
    s16 countdown;
    s16 countdownNext;
    s32 value1C;
    s32 value1E;
    s32 byte1Next;
    s32 statusValue;
    u8 value24;
    u8 value25;
    u8 byte2;
    u8 stateId;
    u8 byte0;
    u8 byte1;

    stateId = ((S_800D34CC_0 *)state)->unk_9B;
    switch (stateId) {
    case 0:
        if (dungeonStatus.unk_0A != 0) {
            break;
        }
        ((EntityRec *)entity)->flags1C = (s32) (((EntityRec *)entity)->flags1C | 0x10000000);
        func_800A56E0(0x805);
        ((S_800D34CC_2 *)data)->unk_0C.at00.v = 0x808080;
        ((S_800D34CC_0 *)state)->unk_96 = 0x10;
        ((S_800D34CC_0 *)state)->unk_9B = (u8) (((S_800D34CC_0 *)state)->unk_9B + 1);
    case 1:
        byte0 = (u8) ((S_800D34CC_2 *)data)->unk_0C.at00.v;
        ((S_800D34CC_2 *)data)->unk_0C.at00u.v = (u8) (byte0 + ((0x20
            - byte0) / (s16) ((S_800D34CC_0 *)state)->unk_96));
        byte1 = ((S_800D34CC_2 *)data)->unk_0C.at01.v;
        countdown = ((S_800D34CC_0 *)state)->unk_96;
        byte1Next = byte1 + ((0x20 - byte1) / countdown);
        byte2 = ((S_800D34CC_2 *)data)->unk_0C.at02.v;
        ((S_800D34CC_2 *)data)->unk_0C.at01.v = (u8) byte1Next;
        ((S_800D34CC_2 *)data)->unk_0C.at02u.v = (u8) (byte2 + ((0x20
            - byte2) / (s16) ((S_800D34CC_0 *)state)->unk_96));
        value1C = ((S_800D34CC_2 *)data)->unk_1C;
        ((S_800D34CC_2 *)data)->unk_1C = (u16) (value1C - (value1C / (s16) ((S_800D34CC_0 *)state)->unk_96));
        value1E = ((S_800D34CC_2 *)data)->unk_1E;
        ((S_800D34CC_2 *)data)->unk_1E = (u16) (value1E - (value1E / (s16) ((S_800D34CC_0 *)state)->unk_96));
        countdownNext = (u16) ((S_800D34CC_0 *)state)->unk_96 - 1;
        ((S_800D34CC_0 *)state)->unk_96 = countdownNext;
        if (((countdownNext << 0x10) <= 0) || ((((S_800D34CC_2 *)data)->unk_14 & 0x8000) != 0)) {
            statusValue = ((s32)dungeonStatus.unk_10);
            if (statusValue == (entity - 0x20)) {
                dungeonStatus.unk_10 = (s32) (statusValue & 0x7FFFFFFF);
            }
            func_800A32A4(entity);
            if ((func_80042900(entity, 0x1B) << 0x10) == 0) {
                value24 = ((S_800D34CC_2 *)data)->unk_24;
                value25 = ((S_800D34CC_2 *)data)->unk_25;
                selectedValue = 0x3000;
                if (((EntityRec *)entity)->flags1C & 0x2000) {
                    selectedValue = 0x300;
                }
                func_8009A3D0(value24, value25, selectedValue);
            }
            func_8009A028(entity);
            (*(u16 *)((u8 *)entity + -2)) = (u16) (((S_800D34CC_1_pre *)entity)[-1].unk_00 | 0x8000);
            objectFlagBlock.flags |= 0x8000;
            func_800A56C0();
        }
    }
}

/* MECHANISM: The four-argument ABI yields s0=state, s1=data, and s2=entity in the retail 0x20 frame.
   Split byte/halfword RMWs and one held &D_80083460 base reproduce the widths, live ranges, and CFG.
   Naming the final two byte arguments fills the lw delay slot and removes the +1 displacement cascade. */
