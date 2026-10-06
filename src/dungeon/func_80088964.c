#include "shared/dungeon_actor_callbacks.h"
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"

extern u8 D_800E3CD0[9];
void func_800945E8();
void func_800948BC();
void func_80099844();
extern M2C_UNK D_800E0672;


typedef struct S_8008E0C4_0 {
    u8 pad_00[0x8C];
    void ** unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8008E0C4_0;   /* context in func_8008E0C4 */

typedef struct S_8008E0C4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8008E0C4_1;   /* input in func_8008E0C4 */

typedef struct S_8008E0C4_2 {
    u8 unk_00;
} S_8008E0C4_2;   /* D_800E3CD0 in func_8008E0C4 */


void func_8008E0C4(S_8008E0C4_0 *context, void *unused, S_8008E0C4_1 *input, EntityRec *entity) {
    GameWork *work;
    u16 remaining;
    s32 state;

    work = &gameWork;
    state = context->unk_9B;
    switch (state) {
    case 0:
        if (input->unk_14 & 0xE000) {
            func_80099844(entity, &D_800E0672);
            context->unk_96 = 0x80;
            context->unk_9B++;
        }
        break;

    case 1:
        remaining = context->unk_96 - 1;
        context->unk_96 = remaining;
        if ((remaining << 0x10) > 0) {
            break;
        }
        if (*(u16 *)0x80013714 & 4) {
            if (((S_8008E0C4_2 *)D_800E3CD0)->unk_00 == 0) {
                ((S_8008E0C4_2 *)D_800E3CD0)->unk_00 = state;
                func_80040AA0(3);
                break;
            }
        } else {
            func_800945E8(context);
            func_800948BC();
            D_80082E60.flags16 = 0xC000;
            func_80041094(6, 0, 0, 0, 0xC000);
            context->unk_9B++;
            break;
        }
        break;

    case 2:
        break;

    case 0x10:
        if (input->unk_14 & 0xE000) {
            entity->unk_28 = entity->unk_29;
            entity->facing = 0x400 - ((((u16)work->view.viewAngle) + 0x100) & 0xE00);
            context->unk_8C =func_8008ACDC;
            dungeonStatus.unk_0A = ((u16)dungeonStatus.unk_0A) - 1;
        }
        break;
    }
}
