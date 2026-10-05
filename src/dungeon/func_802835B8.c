#include "common.h"
#include "shared/sys_flags.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct S_800165B8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800165B8_0;   /* alloc in func_800165B8 */

typedef struct S_800165B8_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x86];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x5];
    u16 unk_A2;
    u8 pad_A4[0x38];
    s32 unk_DC;
    s32 unk_E0;
} S_800165B8_1;   /* obj in func_800165B8 */

typedef struct S_800165B8_2 {
    u8 pad_00[0x10];
    u8 unk_10;
    u8 pad_11[0x1];
    u8 unk_12;
    u8 pad_13[0x3];
    u16 unk_16;
} S_800165B8_2;   /* room in func_800165B8 */

typedef struct S_800165B8_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
    u8 pad_27[0x1];
    s32 unk_28;
    void * unk_2C;
} S_800165B8_3;   /* state in func_800165B8 */

typedef struct S_800165B8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800165B8_4;   /* actor in func_800165B8 */

typedef struct S_800165B8_5 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x14];
    s8 unk_40;
    s8 unk_41;
    s8 unk_42;
    u8 pad_43[0x15];
    void * unk_58;
    void * unk_5C;
    u8 pad_60[0x28];
    s16 unk_88;
} S_800165B8_5;   /* entity in func_800165B8 */

typedef struct S_800165B8_6 {
    u8 pad_00[0xFA];
    u8 unk_FA;
} S_800165B8_6;   /* obj + i in func_800165B8 */

typedef struct S_800165B8_7 {
    u8 pad_00[0xC4];
    u16 unk_C4;
    u16 unk_C6;
} S_800165B8_7;   /* ddp in func_800165B8 */

typedef struct S_800165B8_8 {
    u8 pad_00[0x4];
    s16 unk_04;
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
} S_800165B8_8;   /* dce in func_800165B8 */

typedef struct S_800165B8_9 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800165B8_9;   /* base_83460 in func_800165B8 */

typedef struct S_800165B8_10 {
    u8 pad_00[0x3714];
    u16 unk_3714;
} S_800165B8_10;   /* base_8001 in func_800165B8 */



typedef struct {
    u8 bytes[13];
} __attribute__((packed)) Copy13;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Copy12;

extern void *func_8003FE78(s32, void *, s32);
extern void func_8004491C(void *, void *);
extern void func_8003DB4C(void *, s32);
extern s16 func_800A4E2C(u8 *, u8 *);
extern s32 func_80033BC0(s32);
extern s16 func_800BCB04(s32 x, s32 y, s16 min_height);
extern void func_8009A350(u8, u8, s16, u16 *);
extern void func_800A2B04(void *, u8, u8);
extern void func_8009A21C(s16 x, s16 y, u16 flags);
extern void func_80094988(void *, void *, u8, u8);
extern void func_800489F4(void *, u8, s32, s32);
extern s32 func_80042900(void *, s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_800BC26C(void *, s32, void *, void *);
extern void func_80096088(void *, void *);
extern s8 func_8009FB34(s32, s32, void *, u16);
extern void func_8009D380(void);
extern void func_800172A0(void *, s16);
extern void *func_800A6C00(void);

extern s32 D_80012090;
extern s16 D_8008146C;
extern s32 D_80080A80;
extern s8 D_800DCF5A;
extern s8 D_80082A3B;
extern s32 D_800E3540;
extern s32 D_80081484;
extern s32 D_80081470;
extern void *D_800E3D18;
extern u8 D_80089AA0[];
extern u8 D_80082E60[];
extern u8 D_800DD078;
extern u8 D_800DD090;
extern u8 D_800DD0A8;
extern s32 D_800E3D80[];
extern s32 D_800E3CF8[];
extern s32 D_800E3D48[];
extern void *D_800DD274[];
extern u8 D_800DCFB0[];
extern u16 D_800DD264[];
extern u16 D_800DD26C[];
extern u8 D_800DCE60[];
extern s32 D_800E4938[];

/* Initialize the dungeon actor and its state at a position_selected starting position. */
void func_800165B8(void) {
    u8 pos_x;
    u8 pos_y;
    u16 flags;
    void *allocation;
    u8 *actor_storage;
    u8 *actor;
    u8 *call_target;
    u8 *state;
    u8 *obj;
    u8 *entity;
    u8 *room;
    s16 first_height;
    s16 height;
    s16 *delta_x;
    u8 *delta_page;
    s16 *delta_y;
    s32 height_diff;
    s32 entry_index;
    s32 offset_index;
    s32 sample_x;
    s32 sample_y;
    s32 state_config;
    u8 *table_base;
    u8 tile;
    u8 actor_x;
    u8 actor_y;
    u16 display_setting;
    s32 lift_height;
    u8 *display_state;
    s32 bind_count;
    register u8 *bind_state ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 *bind_angle;
    u8 *defaults_page;
    u16 init_flags;
    s32 neutral_color;
    s32 object_color;
    s32 entity_mask;
    s32 copy_tail;
    s32 final_flags;

    table_base = (u8 *)&gameWork;
    D_800DCF5A = 1;
    allocation = func_8003FE78(0, ((u8 *)(&D_80083498)), 0x53);
    ((S_800165B8_0 *)allocation)->unk_10 = D_80089AA0;
    func_8004491C(allocation, func_80045340);
    actor_storage = ((u8 *)(&D_80083780.x.v));
    ((S_800165B8_0 *)allocation)->unk_08 = actor_storage;
    actor = actor_storage;
    func_8003DB4C(actor, 6);
    state = ((u8 *)(&D_80082E80));
    ((S_800165B8_0 *)allocation)->unk_0C = state;
    func_8003DB4C(state, 0xC);
    D_800814A8 = obj = (u8 *)allocation + 0x20;
    D_800E3D7C = obj;
    ((S_800165B8_1 *)obj)->unk_13 = 0;
    entity = obj;
    room = D_80082E60;

    if (!(((S_800165B8_2 *)room)->unk_16 & 1)) {
retry_position:
        do {
        } while (func_800A4E2C(&pos_x, &pos_y) < 0);
        if (D_80012090 != 0) {
            goto position_selected;
        }
        if (func_80033BC0(0x1389) != 0) {
            goto position_selected;
        }
        call_target = actor;
        if (D_8008146C != 0x1F) {
            goto initialize_position;
        }
        bind_state = (u8 *)(-0x400);
        first_height = func_800BCB04((pos_x << 6) | 0x20,
                                     (pos_y << 6) | 0x20, (s32)bind_state);
        entry_index = -1;
        delta_x = dirStepX;
        delta_y = dirStepY;
check_neighbor:
        func_8009A350(pos_x, pos_y, (s16)entry_index, &flags);
        bind_state = (u8 *)(-0x400);
        if (flags & 0x8000) {
            goto retry_position;
        }
        offset_index = entry_index & 7;
        {
            u8 sample_tile_y;
            s32 sample_y_sum;

            sample_tile_y = pos_y;
            sample_x = (pos_x << 6) + 0x20;
            sample_x += delta_x[offset_index] << 6;
            sample_x &= 0xFFE0;
            sample_y = ((s32)sample_tile_y << 6) + 0x20;
            sample_y_sum = sample_y + (delta_y[offset_index] << 6);
            sample_y = sample_y_sum & 0xFFE0;
        }
        height = func_800BCB04(sample_x, sample_y, (s32)bind_state);
        height_diff = (height & 0xFF) - (first_height & 0xFF);
        if (height_diff < 0) {
            height_diff = -height_diff;
        }
        entry_index++;
        if (height_diff >= 0x21) {
            goto retry_position;
        }
        if (entry_index < 2) {
            goto check_neighbor;
        }
        call_target = actor;
        goto initialize_position;
    }

    pos_x = ((S_800165B8_2 *)room)->unk_10;
    pos_y = ((S_800165B8_2 *)room)->unk_12;
position_selected:
    call_target = actor;
initialize_position:
    entry_index = 7;
    {
        u8 setup_x;
        u8 setup_y;

        setup_x = pos_x;
        setup_y = pos_y;
        ((S_800165B8_3 *)state)->unk_24 = setup_x;
        ((S_800165B8_3 *)state)->unk_25 = setup_y;
        func_800A2B04(call_target, setup_x, setup_y);
    }
    func_8009A21C(pos_x, pos_y, 0x300);
    height = func_800BCB04(((S_800165B8_4 *)actor)->unk_02, ((S_800165B8_4 *)actor)->unk_06, -0x400);
    actor_x = pos_x;
    actor_y = pos_y;
    ((S_800165B8_4 *)actor)->unk_0A = height;
    ((S_800165B8_5 *)entity)->unk_88 = height;
    (*(s16 *)((u8 *)entity + 0x8A)) = height;
    delta_page = (u8 *)(((S_800165B8_1 *)obj)->unk_A2);
    ((S_800165B8_3 *)state)->unk_0C = 0x2C808080;
    ((S_800165B8_1 *)obj)->unk_A2 = (s32)delta_page | 0x10;
    state_config = D_80080A80;
    ((S_800165B8_5 *)entity)->unk_5C = allocation;
    ((S_800165B8_5 *)entity)->unk_58 = allocation;
    ((S_800165B8_3 *)state)->unk_1E = 0x1000;
    ((S_800165B8_3 *)state)->unk_1C = 0x1000;
    ((S_800165B8_3 *)state)->unk_28 = state_config;
    func_80094988(obj, entity, actor_x, actor_y);

    entity_mask = 0xFFEFFFFF;
    ((S_800165B8_5 *)entity)->unk_14 &= entity_mask;
    do {
        func_800489F4(state, (&D_800DD078)[entry_index], 0, 0);
        D_800E3D80[entry_index] = ((S_800165B8_3 *)state)->unk_08;
        func_800489F4(state, (&D_800DD0A8)[entry_index], 0, 0);
        D_800E3CF8[entry_index] = ((S_800165B8_3 *)state)->unk_08;
        func_800489F4(state, (&D_800DD090)[entry_index], 0, 0);
        D_800E3D48[entry_index] = ((S_800165B8_3 *)state)->unk_08;
        entry_index--;
    } while (entry_index >= 0);
    D_800E3D18 = D_800E3CF8;

    if ((func_80042900(entity, 0xA) << 16) != 0) {
        (*(void * *)((u8 *)state + 0x2C)) = D_800DD274;
        func_8003DB94(state,
            *(void **)((u8 *)D_800DD274 +
                (((gameWork.view.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100) >> 7) & 0x1C)),
            0);
    } else {
        func_800489F4(state, 0xB0, 0, 1);
        ((S_800165B8_3 *)state)->unk_2C = D_800DCFB0;
    }
    bind_count = 1;
    bind_angle = obj + 0x2A;
    (*(s16 *)((u8 *)obj + 0x94)) = -1;
    (*(s16 *)((u8 *)obj + 0x118)) = 0;
    ((S_800165B8_5 *)entity)->unk_2A = 0x400 - (((u16)gameWork.view.viewAngle + 0x100) & 0xE00);
    func_800BC26C((u8 *)&D_80083498, bind_count, state + 0x2C, bind_angle);
    {
        s32 clear_flag_mask;

        clear_flag_mask = 0xFFEFFFFF;
        ((S_800165B8_1 *)obj)->unk_9A = 0xFF;
        ((S_800165B8_5 *)entity)->unk_1C &= clear_flag_mask;
    }
    func_80096088(obj, entity);
    ((S_800165B8_3 *)state)->unk_14 |= 0x8000;
    defaults_page = (u8 *)0x80010000;
    for (entry_index = 0; entry_index < 2; entry_index++) {
        tile = defaults_page[entry_index + 0x2D6C];
        ((S_800165B8_6 *)(obj + entry_index))->unk_FA = tile;
        if (tile == 2) {
            ((S_800165B8_6 *)(obj + entry_index))->unk_FA = 1;
        }
    }

    object_color = 0x2C808080;
    entry_index = (s32)0x80010000;
    delta_page = (u8 *)(((S_800165B8_1 *)obj)->unk_A2);
    delta_page = (u8 *)(((s32)delta_page) | (0x10));
    ((S_800165B8_1 *)obj)->unk_A2 = (s32)delta_page;
    ((S_800165B8_5 *)entity)->unk_14 |= 0x4000;
    bind_state = (u8 *)(0x8001020C);
    *(Copy13 *)(entity + 0x34) = *(Copy13 *)(u32)bind_state;
    ((S_800165B8_5 *)entity)->unk_42 = 0;
    ((S_800165B8_5 *)entity)->unk_41 = 0;
    ((S_800165B8_1 *)obj)->unk_DC = object_color;
    ((S_800165B8_1 *)obj)->unk_E0 = object_color;

    {
        u32 tile_y;
        s32 display_index;
        u16 height_index;
        u16 display_value;

        u16 *display_table = D_800DD264;
        call_target = (u8 *)(u32)((S_800165B8_3 *)state)->unk_24;
        display_index = *(u16 *)((u8 *)entry_index + 0x20A2);
        tile_y = ((S_800165B8_3 *)state)->unk_25;
        display_setting = display_table[(s16)display_index];
        bind_state = (u8 *)&dungeonStatus;
        ((S_800165B8_7 *)table_base)->unk_C4 = display_setting;
        height_index = *(u16 *)((u8 *)entry_index + 0x20A0);
        *(u16 *)D_800DCE60 = display_setting;
        lift_height = D_800DD26C[(s16)height_index];
        display_value = ((S_800165B8_7 *)table_base)->unk_C6;
        display_state = D_800DCE60;
        ((S_800165B8_8 *)display_state)->unk_04 = 0;
        (*(u16 *)((u8 *)display_state + 2)) = display_value;
        D_800E4938[0] = 0;
        final_flags = ((DungeonGlobalStatus *)bind_state)->flags;
        *(void **)&D_800E4938[1] = allocation;
        D_800E4938[2] = 0;
        final_flags |= 2;
        ((DungeonGlobalStatus *)bind_state)->flags = final_flags;
        ((S_800165B8_8 *)display_state)->unk_06.s = lift_height;
        ((S_800165B8_3 *)state)->unk_26 =
            func_8009FB34((s32)call_target, tile_y, bind_state, lift_height);
    }
    ((S_800165B8_1 *)obj)->unk_9C = -2;
    func_8009D380();
    {
        s32 actor_lift;

        call_target = actor;
        actor_lift = ((S_800165B8_8 *)display_state)->unk_06.u;
        D_800E3540 = 0;
        D_80081484 = 0;
        D_80081470 = 0;
        func_800172A0(call_target, actor_lift);
    }
    init_flags = ((S_800165B8_10 *)(u8 *)entry_index)->unk_3714;
    D_80082A3B = -0x24;
    if (init_flags & 4) {
        func_800A6C00();
    }
}
