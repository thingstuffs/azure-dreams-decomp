#include "common.h"

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
    s8 unk_9A;
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

typedef struct S_800165B8_11 {
    u8 pad_00[0x2A3B];
    s8 unk_2A3B;
} S_800165B8_11;   /* final_base in func_800165B8 */



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
extern s16 func_800BCB04(s32, s32, s32);
extern void func_8009A350(u8, u8, s16, u16 *);
extern void func_800A2B04(void *, u8, u8);
extern void func_8009A21C(u8, u8, s32);
extern void func_80094988(void *, void *, u8, u8);
extern void func_800489F4(void *, u8, s32, s32);
extern s32 func_80042900(void *, s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_800BC26C(void *, s32, void *, void *);
extern void func_80096088(void *, void *);
extern s8 func_8009FB34(s32, s32, void *, u16);
extern void func_8009D380(void);
extern void func_800172A0(void *, s16);
extern void func_800A6C00(void *);

extern s32 D_80012090;
extern s16 D_8008146C;
extern s32 D_80080A80;
extern s16 D_80083228;
extern s8 D_800DCF5A;
extern s8 D_80082A3B;
extern u16 D_80013714;
extern s32 D_800E3540;
extern s32 D_80081484;
extern s32 D_80081470;
extern void *D_800814A8;
extern u8 *D_800E3D7C;
extern void *D_800E3D18;
extern u8 D_80083498[];
extern u8 D_80089AA0[];
extern u8 D_80045340[];
extern u8 D_80083780;
extern u8 D_80082E80[];
extern u8 D_80082E60[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern u8 D_800DD078;
extern volatile u8 D_800DD090;
extern u8 D_800DD0A8;
extern s32 D_800E3D80[];
extern s32 D_800E3CF8[];
extern s32 D_800E3D48[];
extern void *D_800DD274[];
extern u8 D_800DCFB0[];
extern u16 D_800DD264[];
extern u16 D_800DD26C[];
extern u8 D_80083160[];
extern u8 D_80083460[];
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
    register u8 *call_target ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    u8 *state;
    u8 *obj;
    u8 *entity;
    u8 *room;
    s16 first_height;
    s16 height;
    register s32 direction ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s16 *delta_x ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *delta_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s16 *delta_y;
    s32 height_diff;
    s32 entry_index;
    s32 offset_index;
    u32 entry_offset;
    s32 sample_x;
    s32 sample_y;
    s32 state_config;
    register s32 *reverse_entries ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 *state_entries;
    u8 *table_base;
    register u8 *entry_addr ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 tile;
    u8 actor_x;
    u8 actor_y;
    u16 display_setting;
    register u16 lift_height ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 *settings_page;
    u8 *display_page;
    u8 *display_state;
    u8 *map_state;
    register u8 *bind_base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    s32 bind_count;
    register u8 *bind_state ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 *bind_angle;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 *defaults_page;
    register s32 height_limit ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 init_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 *status_page;
    s32 status_value;
    u16 init_flags;
    register s32 neutral_color ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 entity_mask;
    s32 entity_flags;
    register u32 copy_addr ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 copy_tail;
    u8 *zero_arg;

    D_800DCF5A = 1;
    allocation = func_8003FE78(0, D_80083498, 0x53);
    ((S_800165B8_0 *)allocation)->unk_10 = D_80089AA0;
    func_8004491C(allocation, D_80045340);
    actor_storage = &D_80083780;
    ((S_800165B8_0 *)allocation)->unk_08 = actor_storage;
    actor = actor_storage;
    func_8003DB4C(actor, 6);
    state = D_80082E80;
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
            entry_index = 7;
            goto initialize_position;
        }
        height_limit = -0x400;
        ASM_KEEP(height_limit);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        direction = -1;
        first_height = func_800BCB04((pos_x << 6) | 0x20,
                                     (pos_y << 6) | 0x20, height_limit);
        delta_page = (u8 *)0x80070000;
        ASM_KEEP(delta_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        delta_x = (s16 *)(delta_page - 0x3328);
        delta_y = D_8006CCE8;
check_neighbor:
        func_8009A350(pos_x, pos_y, (s16)direction, &flags);
        height_limit = -0x400;
        if (flags & 0x8000) {
            goto retry_position;
        }
        offset_index = direction & 7;
        {
            u8 sample_tile_y;

            sample_tile_y = pos_y;
            sample_x = (pos_x << 6) + 0x20;
            sample_x += delta_x[offset_index] << 6;
            sample_x &= 0xFFE0;
            ASM_KEEP_NV(sample_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            sample_y = ((s32)sample_tile_y << 6) + 0x20;
            sample_y += delta_y[offset_index] << 6;
            sample_y &= 0xFFE0;
        }
        height = func_800BCB04(sample_x, sample_y, height_limit);
        height_diff = (height & 0xFF) - (first_height & 0xFF);
        if (height_diff < 0) {
            height_diff = -height_diff;
        }
        direction++;
        if (height_diff >= 0x21) {
            goto retry_position;
        }
        if (direction < 2) {
            goto check_neighbor;
        }
        call_target = actor;
        entry_index = 7;
        goto initialize_position;
    }

    pos_x = ((S_800165B8_2 *)room)->unk_10;
    pos_y = ((S_800165B8_2 *)room)->unk_12;
position_selected:
    call_target = actor;
    entry_index = 7;
initialize_position:
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
    init_value = ((S_800165B8_1 *)obj)->unk_A2;
    ((S_800165B8_3 *)state)->unk_0C = 0x2C808080;
    ((S_800165B8_1 *)obj)->unk_A2 = init_value | 0x10;
    state_config = D_80080A80;
    ((S_800165B8_5 *)entity)->unk_5C = allocation;
    ((S_800165B8_5 *)entity)->unk_58 = allocation;
    ((S_800165B8_3 *)state)->unk_1E = 0x1000;
    ((S_800165B8_3 *)state)->unk_1C = 0x1000;
    ((S_800165B8_3 *)state)->unk_28 = state_config;
    func_80094988(obj, entity, actor_x, actor_y);

    entity_mask = 0xFFEFFFFF;
    {
        register s32 *entries_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

        entries_base = (s32 *)((u8 *)&D_800E3D80);
           /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        entity_flags = ((S_800165B8_5 *)entity)->unk_14;
        reverse_entries = entries_base + 7;
        entity_flags &= entity_mask;
        ((S_800165B8_5 *)entity)->unk_14 = entity_flags;
    }
load_entries:
    call_target = state;
    bind_state = (u8 *)0;
    ASM_KEEP_NV(bind_state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    table_base = (u8 *)0x800E0000;
    ASM_KEEP_NV(table_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    table_base -= 0x2F88;
    entry_addr = (u8 *)((u32)entry_index + (u32)table_base);
    ASM_KEEP_DEP_NV(entry_addr, table_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_800489F4(call_target, *entry_addr, (s32)bind_state, (s32)bind_state);
    call_target = state;
    bind_state = (u8 *)0;
    zero_arg = bind_state;
    ASM_KEEP_DEP_NV(zero_arg, bind_state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    table_base = (u8 *)0x800E0000;
    ASM_KEEP_NV(table_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    init_value = ((S_800165B8_3 *)state)->unk_08;
    table_base -= 0x2F58;
    *reverse_entries = init_value;
    reverse_entries--;
    entry_addr = (u8 *)((u32)entry_index + (u32)table_base);
    ASM_KEEP_DEP_NV(entry_addr, table_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_800489F4(call_target, *entry_addr, (s32)bind_state, (s32)zero_arg);
    entry_offset = (u32)entry_index << 2;
    state_entries = D_800E3CF8;
    *(s32 *)((u8 *)state_entries + entry_offset) = ((S_800165B8_3 *)state)->unk_08;
    func_800489F4(state, *(&D_800DD090 + entry_index), 0, 0);
    entry_index--;
    *(s32 *)((u8 *)D_800E3D48 + entry_offset) = ((S_800165B8_3 *)state)->unk_08;
    if (entry_index >= 0) {
        goto load_entries;
    }
    D_800E3D18 = state_entries;

    if ((func_80042900(entity, 0xA) << 16) != 0) {
        (*(void * *)((u8 *)state + 0x2C)) = D_800DD274;
        func_8003DB94(state,
            *(void **)((u8 *)D_800DD274 +
                (((D_80083228 + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100) >> 7) & 0x1C)),
            0);
        bind_base = D_80083498;
    } else {
        func_800489F4(state, 0xB0, 0, 1);
        ((S_800165B8_3 *)state)->unk_2C = D_800DCFB0;
        bind_base = D_80083498;
    }
    bind_count = 1;
    bind_state = state + 0x2C;
    bind_angle = obj + 0x2A;
    ASM_KEEP(bind_count);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    init_value = -1;
    (*(s16 *)((u8 *)obj + 0x94)) = init_value;
    (*(s16 *)((u8 *)obj + 0x118)) = 0;
    ((S_800165B8_5 *)entity)->unk_2A = 0x400 - (((u16)D_80083228 + 0x100) & 0xE00);
    func_800BC26C(bind_base, bind_count, bind_state, bind_angle);
    {
        s32 clear_flag_mask;

        clear_flag_mask = 0xFFEFFFFF;
        call_target = obj;
        init_value = 0xFF;
        ((S_800165B8_1 *)obj)->unk_9A = init_value;
        ((S_800165B8_5 *)entity)->unk_1C &= clear_flag_mask;
    }
    func_80096088(call_target, entity);
    ((S_800165B8_3 *)state)->unk_14 |= 0x8000;
    defaults_page = (u8 *)0x80010000;
    for (entry_index = 0; entry_index < 2; entry_index++) {
        tile = defaults_page[entry_index + 0x2D6C];
        ((S_800165B8_6 *)(obj + entry_index))->unk_FA = tile;
        if (tile == 2) {
            ((S_800165B8_6 *)(obj + entry_index))->unk_FA = 1;
        }
    }

    neutral_color = 0x2C808080;
    settings_page = (u8 *)0x80010000;
    ASM_KEEP_NV(settings_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    table_base = (u8 *)0x80080000;
    ASM_KEEP(table_base);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    init_value = ((S_800165B8_1 *)obj)->unk_A2;
    table_base += 0x3160;
    init_value |= 0x10;
    ((S_800165B8_1 *)obj)->unk_A2 = init_value;
    ((S_800165B8_5 *)entity)->unk_14 |= 0x4000;
    display_page = (u8 *)0x800E0000;
    ASM_KEEP(display_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    copy_addr = 0x8001020C;
    ASM_KEEP_NV(copy_addr);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    *(Copy12 *)(entity + 0x34) = *(Copy12 *)copy_addr;
    copy_tail = *(s8 *)(copy_addr + 12);
    ASM_KEEP(copy_tail);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    ((S_800165B8_5 *)entity)->unk_40 = copy_tail;
    ((S_800165B8_5 *)entity)->unk_42 = 0;
    ((S_800165B8_5 *)entity)->unk_41 = 0;
    ((S_800165B8_1 *)obj)->unk_DC = neutral_color;
    ((S_800165B8_1 *)obj)->unk_E0 = neutral_color;

    {
        u32 tile_x;
        u32 tile_y;
        u16 display_index;
        u16 height_index;
        u16 display_value;
        register u16 *display_values ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

        display_values = D_800DD264;
        tile_x = ((S_800165B8_3 *)state)->unk_24;
        ASM_KEEP_NV(tile_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        display_index = *(u16 *)(settings_page + 0x20A2);
        tile_y = ((S_800165B8_3 *)state)->unk_25;
        ASM_KEEP_DEP_NV(display_index, tile_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        display_setting = display_values[(s16)display_index];
        map_state = D_80083460;
        ((S_800165B8_7 *)table_base)->unk_C4 = display_setting;
        height_index = *(u16 *)(settings_page + 0x20A0);
        *(u16 *)(display_page - 0x31A0) = display_setting;
        lift_height = D_800DD26C[(s16)height_index];
        display_value = ((S_800165B8_7 *)table_base)->unk_C6;
        display_state = display_page - 0x31A0;
        ((S_800165B8_8 *)display_state)->unk_04 = 0;
        (*(u16 *)((u8 *)display_state + 2)) = display_value;
        D_800E4938[0] = 0;
        *(void **)&D_800E4938[1] = allocation;
        D_800E4938[2] = 0;
        ((S_800165B8_9 *)map_state)->unk_02 |= 2;
        ((S_800165B8_8 *)display_state)->unk_06.s = lift_height;
        ((S_800165B8_3 *)state)->unk_26 =
            func_8009FB34(tile_x, tile_y, map_state, lift_height);
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
    status_page = (u8 *)0x80080000;
    init_flags = ((S_800165B8_10 *)settings_page)->unk_3714;
    ASM_KEEP(init_flags);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    status_value = -0x24;
    ((S_800165B8_11 *)status_page)->unk_2A3B = status_value;
    if (init_flags & 4) {
        func_800A6C00(status_page);
    }
}
