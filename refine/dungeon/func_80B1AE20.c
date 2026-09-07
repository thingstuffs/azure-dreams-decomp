#include "common.h"

typedef struct S_80172620_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172620_0;   /* arg0 in func_80172620 */

typedef struct S_80172620_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172620_1;   /* arg2 in func_80172620 */

typedef struct S_80172620_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172620_2;   /* arg3 in func_80172620 */



extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(s32, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern s32 D_80170E54;
extern u8 D_801739F0[];

/* Advance the actor's animation state and clean up when it finishes. */
void func_80172620(void *action, s32 actor_id, void *sprite, void *actor) {
    s32 state;

    state = ((S_80172620_0 *)action)->unk_9B;
    ((S_80172620_0 *)action)->unk_96--;
    switch (state) {
        case 0:
            if (((S_80172620_1 *)sprite)->unk_14 & 0x8000) {
                ((S_80172620_0 *)action)->unk_9B = 0xFF;
                ((S_80172620_1 *)sprite)->unk_14 |= 0x6000;
                func_8009C12C(actor, sprite, ((S_80172620_2 *)actor)->unk_2A, 1);
                return;
            }
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801739F0;
            func_80047784(sprite,
                D_801739F0[((D_80083228 + ((S_80172620_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_80172620_0 *)action)->unk_9B++;
            return;

        case 1:
            if (((((S_80172620_1 *)sprite)->unk_04 == 6) &&
                 (((S_80172620_1 *)sprite)->unk_14 & 0x1000)) ||
                (((S_80172620_1 *)sprite)->unk_14 & 0x8000)) {
                func_800A56E0(0x808);
                func_8009C12C(actor, sprite, ((S_80172620_2 *)actor)->unk_2A, 1);
                ((S_80172620_0 *)action)->unk_9B = 0xFF;
            }
            return;

        case 0xFF:
            if (((S_80172620_1 *)sprite)->unk_14 & 0xE000) {
                func_800A2B04(actor_id, ((S_80172620_1 *)sprite)->unk_24, ((S_80172620_1 *)sprite)->unk_25);
                func_800AD594(actor, 0x100);
                ((S_80172620_0 *)action)->unk_8C = &D_80170E54;
                D_8008346C = 0;
                func_800A4ACC(actor);
                if (((S_80172620_2 *)actor)->unk_6D == 0) {
                    ((S_80172620_2 *)actor)->unk_46 &= 0x7FFF;
                    return;
                }
                D_800E3DE8 = (u8 *)actor - 0x20;
            }
            return;
    }
}
