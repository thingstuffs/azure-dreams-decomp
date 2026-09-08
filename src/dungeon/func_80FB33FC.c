#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172BFC_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172BFC_0;   /* arg0 in func_80172BFC */





extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(s32, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern s32 D_80170F6C;
extern u8 D_80175288[];

/* Advances the actor action animation and handles completion. */
void func_80172BFC(void *action, s32 actor_id, void *animation, void *actor) {
    s32 state;

    state = ((S_80172BFC_0 *)action)->unk_9B;
    ((S_80172BFC_0 *)action)->unk_96--;
    switch (state) {
        case 0:
            if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000) {
                ((S_80172BFC_0 *)action)->unk_9B = 0xFF;
                ((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v |= 0x6000;
                func_8009C12C(actor, animation, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
                return;
            }
            (*(u8 * *)((u8 *)animation + 0x2C)) = D_80175288;
            func_80047784(animation,
                D_80175288[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((S_80172BFC_0 *)action)->unk_9B++;
            return;

        case 1:
            if (((((Rec_D_80082E80 *)animation)->unk_04.as_s8 == 3) &&
                 (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x1000)) ||
                (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0x8000)) {
                func_800A56E0(0x804);
                func_8009C12C(actor, animation, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
                ((S_80172BFC_0 *)action)->unk_9B = 0xFF;
            }
            return;

        case 0xFF:
            if (((Rec_D_80082E80 *)animation)->unk_14.at00_u16.v & 0xE000) {
                func_800A2B04(actor_id, ((Rec_D_80082E80 *)animation)->unk_24, ((Rec_D_80082E80 *)animation)->unk_25);
                func_800AD594(actor, 0x100);
                ((S_80172BFC_0 *)action)->unk_8C = &D_80170F6C;
                D_8008346C = 0;
                func_800A4ACC(actor);
                if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 == 0) {
                    ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
                    return;
                }
                D_800E3DE8 = (u8 *)actor - 0x20;
            }
            return;
    }
}
