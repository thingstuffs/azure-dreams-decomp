#include "common.h"
typedef struct { u8 pad[0x3714]; u16 flags; } SysPage;
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef s32 M2C_UNK;

typedef struct S_8008C7B4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_8008C7B4_0;   /* arg0 in func_8008C7B4 */

typedef struct S_8008C7B4_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8008C7B4_1;   /* flags in func_8008C7B4 */


extern M2C_UNK func_80048A44();
extern M2C_UNK func_8009F644();
extern s32 func_800A5C70(void);
extern u8 D_800DCFB0;
extern M2C_UNK D_800DD0B8;

/* Reset state, update control flags, and select the entity's directional sprite. */
void func_8008C7B4(void *state, s32 mode, void *sprite, EntityRec *entity) {
    void *entity_arg;
    s32 control_needed;
    u8 *flags;
    s32 initial_state;

    initial_state = 0x1C;
    ((S_8008C7B4_0 *)state)->unk_9A = initial_state;
    flags = (u8 *)&gameWork;
    ((S_8008C7B4_0 *)state)->unk_9B = 0;
    ((S_8008C7B4_0 *)state)->unk_8C = 0;
    if (((SysPage *)0x80010000)->flags & 2) {
        goto set_control;
    }
    entity_arg = entity;
    if (!(((S_8008C7B4_1 *)flags)->unk_08 & 0x20)) {
        goto after_control;
    }
    control_needed = func_800A5C70();
    entity_arg = entity;
    if (control_needed == 0) {
        goto after_control;
    }
set_control:
    {

        dungeonStatus.flags = (u16)(dungeonStatus.flags | 0x80);
    }
         /* MATCH: keep the control arm's a0 reload after its store. */
    do {
        entity_arg = entity;
    } while (0);
after_control:
    func_8009F644(entity_arg, 0x10, 0, 0);
    {
        u8 *direction_table;

        if (entity->flags1C & 0x100000) {

            direction_table = (u8 *)&D_800DD0B8;
        } else {

            direction_table = &D_800DCFB0;
        }
        (*(u8 **)((u8 *)sprite + 0x2C)) = direction_table;
        {
            u8 *direction_entry;

            initial_state = ((s32)(gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
            direction_entry = direction_table + initial_state;
            func_80048A44(sprite, *direction_entry, 0, 1);
        }
    }
}
