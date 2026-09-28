#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"


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

    ((EntityRec *)actor)->unk_71 = (u8)(((EntityRec *)actor)->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2BDC(actor) << 16) == 0)) {
        ((S_801720D8_1 *)work)->unk_8C = 0;
        ((S_801720D8_1 *)work)->unk_9A = 0x17;
        ((S_801720D8_1 *)work)->unk_9B = 0;
        if (((EntityRec *)actor)->flags1C & 0x400) {
            value = ((EntityRec *)actor)->flags14;
            if (!(value & 0x80000000)) {
                value |= 0x80000000;
                ((EntityRec *)actor)->flags14 = (s32)value;
                ((EntityRec *)actor)->facing = (u16)(((u16)((EntityRec *)actor)->facing) + ((func_800A6D30() & 7) << 9));
            }
        }
        ((S_801720D8_1 *)work)->unk_96 = 0;
        dungeonStatus.unk_0A = (u16)(((u16)dungeonStatus.unk_0A) + 1);
        ((EntityRec *)actor)->unk_6D = (u8)(((u8)((EntityRec *)actor)->unk_6D) - 1);
        (*(void * *)((u8 *)part_b + 0x2C)) = D_80174AE4;
        func_80047784(part_b, D_80174AE4[((gameWork.view.viewAngle + (s16)((u16)((EntityRec *)actor)->facing) + 0x100) >> 9) & 7], 0);
    }
}
