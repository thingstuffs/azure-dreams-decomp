#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_801720D8_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_801720D8_1;   /* work in func_801720D8 */


extern void func_80047784(void *, u8, s32);
extern s32 func_800A2BDC(void *);
extern s32 func_800A6D30(void);
extern u8 D_80174AE4[];

/* Start the actor's hit reaction: clear its flags, give it a random spin and arm the matching sprite frame. */
void func_801720D8(void *work, void *part_a, void *part_b, void *actor) {
    s32 value;

    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 = (u8)(((Rec_D_800E3D7C *)actor)->unk_71.as_u8 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2BDC(actor) << 16) == 0)) {
        ((S_801720D8_1 *)work)->unk_8C = 0;
        ((S_801720D8_1 *)work)->unk_9A = 0x17;
        ((S_801720D8_1 *)work)->unk_9B = 0;
        if (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x400) {
            value = ((Rec_D_800E3D7C *)actor)->unk_14.as_s32;
            if (!(value & 0x80000000)) {
                value |= 0x80000000;
                ((Rec_D_800E3D7C *)actor)->unk_14.as_s32 = (s32)value;
                ((Rec_D_800E3D7C *)actor)->unk_2A.as_u16 = (u16)(((Rec_D_800E3D7C *)actor)->unk_2A.as_u16 + ((func_800A6D30() & 7) << 9));
            }
        }
        ((S_801720D8_1 *)work)->unk_96 = 0;
        dungeonStatus.unk_0A = (u16)(((u16)dungeonStatus.unk_0A) + 1);
        ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 = (u8)(((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 - 1);
        (*(void * *)((u8 *)part_b + 0x2C)) = D_80174AE4;
        func_80047784(part_b, D_80174AE4[((gameWork.viewAngle + (s16)((Rec_D_800E3D7C *)actor)->unk_2A.as_u16 + 0x100) >> 9) & 7], 0);
    }
}
