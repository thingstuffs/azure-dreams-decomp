#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80083460.h"

typedef struct S_80173280_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
} S_80173280_0;   /* arg0 in func_80173280 */

typedef struct S_80173280_2 {
    u8 * unk_00;
} S_80173280_2;   /* (u8 *)obj - 0x14 in func_80173280 */

typedef struct S_80173280_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80173280_3;   /* tile in func_80173280 */


typedef struct S_80173280_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80173280_6;   /* global in func_80173280 */

typedef struct S_80173280_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80173280_7;   /* kindp in func_80173280 */


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void *func_800A05A4(void *, s32, s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void D_80170CF8(void *, s32, s32, s32, s32, s32, s32);

extern u8 D_801717F4[];
extern u8 D_80175988[];

/* Advances action setup, target effects, animation timing, and cleanup. */
void func_80173280(void *actor, EntityRec *motion, void *tile_arg, EntityRec *action)
{
    s16 particle_index;
    s32 offset_y;
    s32 offset_x;
    void *target_obj;
    u8 *kind_data;
    s32 state;
    s16 effect_flags;
    s16 action_dep;

    state = ((S_80173280_0 *)actor)->unk_9B;
    effect_flags = 0;
    switch (state) {
    case 0:
    if (action->flags1C & 0x2000) {
        u32 kind = (action->unk_46 & 0x3FFF) - 1;

        switch (kind) {
        case 6:
            effect_flags = 1;
        case 2:
            goto kind_3;
        case 5:
            effect_flags = 1;
        case 1:
            goto kind_2;
        case 4:
            effect_flags = 1;
        case 0:
            goto kind_1;
        case 3:
        default:
            goto kind_default;
        }
    } else {
        switch (action->unk_46 & 0x3FFF) {
        case 2:
            goto kind_2;
        case 1:
            goto kind_1;
        case 3:
            goto kind_3;
        default:
            goto kind_default;
        }
    }

kind_3:
    kind_data = (u8 *)action + 0xE;
    goto use_kind;
kind_2:
    kind_data = (u8 *)action + 0xB;
    goto use_kind;
kind_1:
    kind_data = (u8 *)action + 8;
    goto use_kind;
kind_default:
    kind_data = 0;

use_kind:
    if (*kind_data != 0) {
        *(u16 *)((u8 *)actor + 0x98) =
            ((S_80173280_0 *)actor)->unk_98 & 0xFF7F;
        if (effect_flags) {
            target_obj = D_800814A8;
            action->target = target_obj;
            state = (s32)((S_80173280_2 *)((u8 *)target_obj - 0x14))->unk_00;
            action->unk_72 = ((u8 *)state)[0x24];
            action->unk_73 = ((u8 *)state)[0x25];
        } else {
            u8 *kind_table;
            u8 kind;
            u8 *kind_entry;

            kind = *kind_data;
            kind_table = (u8 *)D_8006DE24;
            kind_entry = (u8 *)((u32)(kind * 20) + (u32)kind_table);

            if (kind_entry[0x12] == 2) {
                target_obj = action->target;
                if (target_obj != 0) {
                    state = (s32)((S_80173280_2 *)((u8 *)target_obj - 0x14))->unk_00;
                    action->unk_72 = ((u8 *)state)[0x24];
                    action->unk_73 = ((u8 *)state)[0x25];
                }
            } else {
                s32 x = (s32)func_800A05A4(action, ((S_80173280_3 *)tile_arg)->unk_24, ((S_80173280_3 *)tile_arg)->unk_25,
                              action->facing, 0x10);
                s32 y;

                *(void * volatile *)((u8 *)action + 0x60) = (void *)x;
                x = action->unk_72;
                y = action->unk_73;
                if (x < 0) {
                    x = -x;
                }
                if (y < 0) {
                    y = -y;
                }
                action->unk_72 = x;
                action->unk_73 = y;
            }
        }
        if (func_800A94A0(action, kind_data, effect_flags, (u8 *)actor + 0x98)) {
            ((S_80173280_0 *)actor)->unk_96.s = 0x18;
            ((S_80173280_0 *)actor)->unk_9E = 4;
            ((S_80173280_0 *)actor)->unk_9B++;
            return;
        }
        return;
    }

    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, ((S_80173280_3 *)tile_arg)->unk_24, ((S_80173280_3 *)tile_arg)->unk_25);
    {
        u8 *active_actor = D_800814A8;
        ((Rec_D_80083460 *)((u8 *)(&dungeonStatus)))->unk_0C = 0;
        ((S_80173280_6 *)active_actor)->unk_A6--;
    }
    func_800A4ACC(action);
    (*(u8 *)&action->unk_6D)--;
    ((S_80173280_0 *)actor)->unk_8C = D_801717F4;
    action->unk_73 = 0;
    action->unk_72 = 0;
    action->unk_46 &= 0x7FFF;
    return;

case 1:
    if (func_8003F270()) {
        ((S_80173280_3 *)tile_arg)->unk_14 |= 0x800;
        return;
    }
    ((S_80173280_3 *)tile_arg)->unk_14 &= 0xF7FF;
    ((S_80173280_0 *)actor)->unk_9B++;
    func_800A56E0(0x703);

case 2:
    particle_index = 0;
    do {
        effect_flags = func_80069EF8() & 0xFF;
        effect_flags |= 0x80;
        offset_x = (s16)((func_80069EF8() & 0x7F) - 0x40);
        offset_y = (s16)((func_80069EF8() & 0x7F) - 0x40);
        D_80170CF8((u8 *)actor - 0x20, 0, 0x00808080, effect_flags, offset_x, offset_y,
                   (s16)((func_80069EF8() & 0x7F) - 0x40));
        particle_index++;
    } while (particle_index < 5);

    ((S_80173280_0 *)actor)->unk_9E--;
    if ((s16)((S_80173280_0 *)actor)->unk_9E == 1) {
        ((S_80173280_3 *)tile_arg)->unk_14 |= 0x800;
    }
    if (((S_80173280_0 *)actor)->unk_96.u == 5) {
        ((S_80173280_3 *)tile_arg)->unk_14 &= 0xF7FF;
    }
    ((S_80173280_0 *)actor)->unk_96.s--;
    if ((s16)((S_80173280_0 *)actor)->unk_96.s > 0 &&
        !(((S_80173280_3 *)tile_arg)->unk_14 & 0xE000)) {
        return;
    }
    ((S_80173280_0 *)actor)->unk_98 |= 0x80;
    ((S_80173280_0 *)actor)->unk_9B++;
    ((S_80173280_3 *)tile_arg)->unk_14 |= 0x800;
    ((S_80173280_0 *)actor)->unk_96.s = 0x14;
    return;

case 3:
    kind_data = ((u8 *)(&dungeonStatus));
    if (((S_80173280_7 *)kind_data)->unk_0C == 0) {
        ((S_80173280_0 *)actor)->unk_96.s = 0;
    }
    ((S_80173280_0 *)actor)->unk_96.s--;
    if ((s16)((S_80173280_0 *)actor)->unk_96.s <= 0) {
        *(u16 *)((u8 *)actor + 0x96) = 0;
        ((S_80173280_3 *)tile_arg)->unk_14 &= 0xF7FF;
    }
    if (!(((S_80173280_3 *)tile_arg)->unk_14 & 0xE000)) {
        return;
    }
    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, ((S_80173280_3 *)tile_arg)->unk_24, ((S_80173280_3 *)tile_arg)->unk_25);
    if (((S_80173280_3 *)tile_arg)->unk_2C != D_80175988) {
        u8 *frame_table = D_80175988;
        (*(u8 * *)((u8 *)tile_arg + 0x2C)) = frame_table;
        func_80047784(tile_arg,
            frame_table[((gameWork.view.viewAngle + action->facing + 0x100) >> 9) & 7],
            0);
        ((S_80173280_3 *)tile_arg)->unk_14 &= 0xF7FF;
    }
    if (((S_80173280_7 *)kind_data)->unk_0C != 0) {
        return;
    }
    ((S_80173280_7 *)kind_data)->unk_0A--;
    ((S_80173280_0 *)actor)->unk_8C = D_801717F4;
    func_800A4ACC(action);
    action->unk_73 = 0;
    action->unk_72 = 0;
    (*(u8 *)&action->unk_6D)--;
    action->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);
        return;
    default:
        return;
    }
}
