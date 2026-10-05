#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern u8 D_801714D4[];
extern u8 D_80174108[];


typedef struct S_80172864_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    union { u8 n; u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
} S_80172864_0;   /* s0 in func_80172864 */


typedef struct S_80172864_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172864_2;   /* s1 in func_80172864 */

/* Advances a timed action through animation setup, execution, and cleanup. */
void func_80172864(void *action_data, void *unused, Rec_D_80082E80 *sprite, void *actor_data)
{
    register void *action = action_data;
    register void *actor = actor_data;
    u8 state;
    u16 timer;

    state = ((S_80172864_0 *)action)->unk_9B.n;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        timer = ((S_80172864_0 *)action)->unk_96.u;
        ((S_80172864_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 4 && !(sprite->unk_14.at00_u16.v & 0x8000)) {
            return;
        }
        state = ((S_80172864_0 *)action)->unk_9B.v;
        ((S_80172864_0 *)action)->unk_96.u = 0;
        ((S_80172864_0 *)action)->unk_9B.n = state + 1;
        return;

    case 1:
        if (((S_80172864_0 *)action)->unk_A2 != 0 &&
            !(sprite->unk_14.at00_u16.v & 0x8000)) {
            return;
        }
        sprite->unk_2C.as_pu8 = D_80174108;
        func_80047784(
            sprite,
            D_80174108[((gameWork.view.viewAngle + ((S_80172864_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        state = ((S_80172864_0 *)action)->unk_9B.n;
        ((S_80172864_0 *)action)->unk_96.u = 0;
        ((S_80172864_0 *)action)->unk_A2 = 0;
        ((S_80172864_0 *)action)->unk_9E = 0;
        ((S_80172864_0 *)action)->unk_9B.n = state + 1;
        return;

    case 2:
        timer = ((S_80172864_0 *)action)->unk_96.u + 1;
        ((S_80172864_0 *)action)->unk_96.u = timer;
        if ((s16)timer == 9 || (sprite->unk_14.at00_u16.v & 0x8000)) {
            func_8009C12C(actor, sprite, ((S_80172864_2 *)actor)->unk_2A, 1);
            ((S_80172864_0 *)action)->unk_96.u = 0;
            ((S_80172864_0 *)action)->unk_9B.n++;
        }
        if (((S_80172864_0 *)action)->unk_96.s != 6) {
            return;
        }
        func_800A56E0(0x808);
        return;

    case 3:
        state = ((S_80172864_0 *)action)->unk_9B.n;
        ((S_80172864_0 *)action)->unk_96.u = 0;
        ((S_80172864_0 *)action)->unk_9B.n = state + 1;
    case 4:
        if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        func_800AD594(actor, 0x100);
        ((S_80172864_0 *)action)->unk_8C = D_801714D4;
        dungeonStatus.unk_0C = 0;
        func_800A4ACC(actor);
        ((S_80172864_2 *)actor)->unk_46 &= 0x7FFF;

        return;
    }
}
