#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"

struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern void *D_8008ACDC[];
extern u8 D_800E3CD0[9];
extern u16 D_80082E76;
M2C_UNK func_800945E8();
M2C_UNK func_800948BC();
M2C_UNK func_80099844();
extern M2C_UNK D_800E0672;


typedef struct S_8008E0C4_0 {
    u8 pad_00[0x8C];
    void ** unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8008E0C4_0;   /* arg0 in func_8008E0C4 */

typedef struct S_8008E0C4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8008E0C4_1;   /* arg2 in func_8008E0C4 */

typedef struct S_8008E0C4_2 {
    u8 unk_00;
} S_8008E0C4_2;   /* D_800E3CD0 in func_8008E0C4 */


typedef struct S_8008E0C4_4 {
    u8 pad_00[0xC8];
    u16 unk_C8;
} S_8008E0C4_4;   /* global_base in func_8008E0C4 */

typedef struct S_8008E0C4_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8008E0C4_5;   /* counter_base in func_8008E0C4 */

void func_8008E0C4(S_8008E0C4_0 *arg0, void *unused, S_8008E0C4_1 *arg2, EntityRec *arg3) {
    S_8008E0C4_4 *global_base;
    S_8008E0C4_5 *counter_base;
    u16 temp_v0;
    s32 temp_v1;

    global_base = ((struct S_8003E2D8 *)&gameWork);
    temp_v1 = arg0->unk_9B;
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state_0;
        }
        return;
    }
    if (temp_v1 == 2) {
        return;
    }
    if (temp_v1 == 0x10) {
        goto state_16;
    }
    return;

state_0:
    if (arg2->unk_14 & 0xE000) {
        func_80099844(arg3, &D_800E0672);
        arg0->unk_96 = 0x80;
        arg0->unk_9B++;
    }
    return;

state_1:
    temp_v0 = arg0->unk_96 - 1;
    arg0->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        return;
    }
    ASM_KEEP(temp_v1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if ((u16) *((s16 *)&D_80013714) & 4) {
        if (((S_8008E0C4_2 *)D_800E3CD0)->unk_00 == 0) {
            ((S_8008E0C4_2 *)D_800E3CD0)->unk_00 = temp_v1;
            func_80040AA0(3);
            return;
        }
    } else {
        func_800945E8(arg0);
        func_800948BC();
        D_80082E76 = 0xC000;
        func_80041094(6, 0, 0, 0, 0xC000);
        arg0->unk_9B++;
        return;
    }
    return;

state_16:
    if (arg2->unk_14 & 0xE000) {
        counter_base = ((s32 *)(&dungeonStatus));
        arg3->unk_28 = arg3->unk_29;
        arg3->facing = 0x400 - ((global_base->unk_C8 + 0x100) & 0xE00);
        arg0->unk_8C = D_8008ACDC;
        counter_base->unk_0A = counter_base->unk_0A - 1;
    }
}
