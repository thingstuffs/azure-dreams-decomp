#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct S_80172334_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
} S_80172334_0;   /* arg0 in func_80172334 */



M2C_UNK func_80047784();         /* extern */
extern u8 D_80175F20;

/* Advance the timer and reset the state and directional sprite after 60 ticks. */
void func_80172334(void *state, M2C_UNK unused, void *sprite, EntityRec *orientation) {
    u16 ticks;

    ticks = ((S_80172334_0 *)state)->unk_A6 + 1;
    ((S_80172334_0 *)state)->unk_A6 = ticks;
    if ((u32) (ticks & 0xFFFF) >= 0x3DU) {
        u8 *direction_table = &D_80175F20;

        ((S_80172334_0 *)state)->unk_A6 = 0x3CU;
        dungeonStatus.unk_0A = ((u16)dungeonStatus.unk_0A) + 1;
        ((S_80172334_0 *)state)->unk_8C = 0;
        ((S_80172334_0 *)state)->unk_9A = 0x17;
        ((S_80172334_0 *)state)->unk_9B = 0;
        (*(u8 **)((u8 *)sprite + 0x2C)) = direction_table;
        func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + orientation->facing + 0x100) >> 9) & 7) + direction_table), 0);
    }
}
