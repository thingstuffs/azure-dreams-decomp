#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

void func_800165B8(void) {
    u8 pos_x;
    u8 pos_y;
    u16 flags;
    register void *alloc ASM_REG("$23");
    u8 *actor_tmp;
    u8 *actor;
    register u8 *call_actor ASM_REG("$4");
    u8 *state;
    u8 *obj;
    register u8 *entity ASM_REG("$19");
    u8 *room;
    register s16 first_height ASM_REG("$16");
    s16 height;
    register s32 direction ASM_REG("$17");
    register s16 *delta_x ASM_REG("$20");
    register u8 *delta_page ASM_REG("$2");
    s16 *delta_y;
    s32 delta;
    s32 i;
    s32 offset_index;
    u32 index4;
    s32 x_arg;
    s32 y_arg;
    s32 state_value;
    register s32 *descending ASM_REG("$18");
    s32 *cf8;
    register u8 *ddp ASM_REG("$8");
    register u8 *dd_addr ASM_REG("$2");
    u8 tile;
    u8 actor_x;
    u8 actor_y;
    register u16 value ASM_REG("$3");
    register u16 arg3 ASM_REG("$7");
    register u8 *base_8001 ASM_REG("$17");
    register u8 *dce_page ASM_REG("$16");
    register u8 *dce ASM_REG("$16");
    u8 *base_83460;
    register u8 *bc_base ASM_REG("$4");
    register s32 bc_one ASM_REG("$5");
    register u8 *bc_state ASM_REG("$6");
    register u8 *bc_obj ASM_REG("$7");
    register u8 *small_base ASM_REG("$6");
    register s32 height_const ASM_REG("$6");
    register s32 temp_v0 ASM_REG("$2");
    register u8 *final_base ASM_REG("$4");
    register s32 final_value ASM_REG("$3");
    register u16 final_flags ASM_REG("$2");
    register s32 constant_2c ASM_REG("$3");
    register s32 entity_mask ASM_REG("$4");
    register s32 entity_value ASM_REG("$3");
    register u32 copy_addr ASM_REG("$6");
    register s32 copy_tail ASM_REG("$2");
    register u8 *loop_a3 ASM_REG("$7");

    D_800DCF5A = 1;
    alloc = func_8003FE78(0, D_80083498, 0x53);
    FIELD(alloc, void *, 0x10) = D_80089AA0;
    func_8004491C(alloc, D_80045340);
    actor_tmp = &D_80083780;
    FIELD(alloc, void *, 8) = actor_tmp;
    actor = actor_tmp;
    func_8003DB4C(actor, 6);
    state = D_80082E80;
    FIELD(alloc, void *, 0xC) = state;
    func_8003DB4C(state, 0xC);
    D_800814A8 = obj = (u8 *)alloc + 0x20;
    D_800E3D7C = obj;
    FIELD(obj, s8, 0x13) = 0;
    entity = obj;
    room = D_80082E60;

    if (!(FIELD(room, u16, 0x16) & 1)) {
outer:
        do {
        } while (func_800A4E2C(&pos_x, &pos_y) < 0);
        if (D_80012090 != 0) {
            goto selected;
        }
        if (func_80033BC0(0x1389) != 0) {
            goto selected;
        }
        call_actor = actor;
        if (D_8008146C != 0x1F) {
            i = 7;
            goto setup;
        }
        height_const = -0x400;
        ASM_KEEP(height_const);
        direction = -1;
        first_height = func_800BCB04((pos_x << 6) | 0x20,
                                     (pos_y << 6) | 0x20, height_const);
        delta_page = (u8 *)0x80070000;
        ASM_KEEP(delta_page);
        delta_x = (s16 *)(delta_page - 0x3328);
        delta_y = D_8006CCE8;
height_loop:
        func_8009A350(pos_x, pos_y, (s16)direction, &flags);
        height_const = -0x400;
        if (flags & 0x8000) {
            goto outer;
        }
        offset_index = direction & 7;
        {
            u8 yv;

            yv = pos_y;
            x_arg = (pos_x << 6) + 0x20;
            x_arg += delta_x[offset_index] << 6;
            x_arg &= 0xFFE0;
            ASM_KEEP_NV(x_arg);
            y_arg = ((s32)yv << 6) + 0x20;
            y_arg += delta_y[offset_index] << 6;
            y_arg &= 0xFFE0;
        }
        height = func_800BCB04(x_arg, y_arg, height_const);
        delta = (height & 0xFF) - (first_height & 0xFF);
        if (delta < 0) {
            delta = -delta;
        }
        direction++;
        if (delta >= 0x21) {
            goto outer;
        }
        if (direction < 2) {
            goto height_loop;
        }
        call_actor = actor;
        i = 7;
        goto setup;
    }

    pos_x = FIELD(room, u8, 0x10);
    pos_y = FIELD(room, u8, 0x12);
selected:
    call_actor = actor;
    i = 7;
setup:
    {
        u8 setup_x;
        u8 setup_y;

        setup_x = pos_x;
        setup_y = pos_y;
        FIELD(state, u8, 0x24) = setup_x;
        FIELD(state, u8, 0x25) = setup_y;
        func_800A2B04(call_actor, setup_x, setup_y);
    }
    func_8009A21C(pos_x, pos_y, 0x300);
    height = func_800BCB04(FIELD(actor, u16, 2), FIELD(actor, u16, 6), -0x400);
    actor_x = pos_x;
    actor_y = pos_y;
    FIELD(actor, s16, 0xA) = height;
    FIELD(entity, s16, 0x88) = height;
    FIELD(entity, s16, 0x8A) = height;
    temp_v0 = FIELD(obj, u16, 0xA2);
    FIELD(state, s32, 0xC) = 0x2C808080;
    FIELD(obj, u16, 0xA2) = temp_v0 | 0x10;
    state_value = D_80080A80;
    FIELD(entity, void *, 0x5C) = alloc;
    FIELD(entity, void *, 0x58) = alloc;
    FIELD(state, s16, 0x1E) = 0x1000;
    FIELD(state, s16, 0x1C) = 0x1000;
    FIELD(state, s32, 0x28) = state_value;
    func_80094988(obj, entity, actor_x, actor_y);

    entity_mask = 0xFFEFFFFF;
    ASM_KEEP(entity_mask);
    {
        register u8 *descending_page ASM_REG("$2");
        register s32 *descending_base ASM_REG("$2");

        descending_page = (u8 *)0x800E0000;
        ASM_KEEP(descending_page);
        descending_base = (s32 *)(descending_page + 0x3D80);
        ASM_KEEP(descending_base);
        entity_value = FIELD(entity, s32, 0x14);
        ASM_KEEP(entity_value);
        descending = descending_base + 7;
        ASM_KEEP(descending);
        entity_value &= entity_mask;
        FIELD(entity, s32, 0x14) = entity_value;
    }
dungeon_loop:
    call_actor = state;
    bc_state = (u8 *)0;
    ASM_KEEP_NV(bc_state);
    ddp = (u8 *)0x800E0000;
    ASM_KEEP_NV(ddp);
    ddp -= 0x2F88;
    dd_addr = (u8 *)((u32)i + (u32)ddp);
    ASM_KEEP_DEP_NV(dd_addr, ddp);
    func_800489F4(call_actor, *dd_addr, (s32)bc_state, (s32)bc_state);
    call_actor = state;
    bc_state = (u8 *)0;
    ASM_KEEP_NV(bc_state);
    loop_a3 = bc_state;
    ASM_KEEP_DEP_NV(loop_a3, bc_state);
    ddp = (u8 *)0x800E0000;
    ASM_KEEP_NV(ddp);
    temp_v0 = FIELD(state, s32, 8);
    ASM_KEEP_NV(temp_v0);
    ddp -= 0x2F58;
    *descending = temp_v0;
    descending--;
    dd_addr = (u8 *)((u32)i + (u32)ddp);
    ASM_KEEP_DEP_NV(dd_addr, ddp);
    func_800489F4(call_actor, *dd_addr, (s32)bc_state, (s32)loop_a3);
    index4 = (u32)i << 2;
    cf8 = D_800E3CF8;
    *(s32 *)((u8 *)cf8 + index4) = FIELD(state, s32, 8);
    func_800489F4(state, *(&D_800DD090 + i), 0, 0);
    i--;
    *(s32 *)((u8 *)D_800E3D48 + index4) = FIELD(state, s32, 8);
    if (i >= 0) {
        goto dungeon_loop;
    }
    D_800E3D18 = cf8;

    if ((func_80042900(entity, 0xA) << 16) != 0) {
        FIELD(state, void *, 0x2C) = D_800DD274;
        func_8003DB94(state,
            *(void **)((u8 *)D_800DD274 +
                (((D_80083228 + FIELD(entity, s16, 0x2A) + 0x100) >> 7) & 0x1C)),
            0);
        bc_base = D_80083498;
        goto common_tail;
    }

    func_800489F4(state, 0xB0, 0, 1);
    FIELD(state, void *, 0x2C) = D_800DCFB0;
    bc_base = D_80083498;
common_tail:
    bc_one = 1;
    bc_state = state + 0x2C;
    bc_obj = obj + 0x2A;
    ASM_KEEP(bc_one);
    ASM_KEEP(bc_state);
    ASM_KEEP(bc_obj);
    temp_v0 = -1;
    FIELD(obj, s16, 0x94) = temp_v0;
    i = 0;
    FIELD(obj, s16, 0x118) = 0;
    FIELD(entity, s16, 0x2A) = 0x400 - (((u16)D_80083228 + 0x100) & 0xE00);
    func_800BC26C(bc_base, bc_one, bc_state, bc_obj);
    {
        register s32 mask_ffef ASM_REG("$3");

        mask_ffef = 0xFFEFFFFF;
        call_actor = obj;
        temp_v0 = 0xFF;
        FIELD(obj, s8, 0x9A) = temp_v0;
        FIELD(entity, s32, 0x1C) &= mask_ffef;
    }
    func_80096088(call_actor, entity);
    FIELD(state, u16, 0x14) |= 0x8000;
    small_base = (u8 *)0x80010000;
    do {
        tile = small_base[i + 0x2D6C];
        FIELD(obj + i, u8, 0xFA) = tile;
        if (tile == 2) {
            FIELD(obj + i, u8, 0xFA) = 1;
        }
        i++;
    } while (i < 2);

    constant_2c = 0x2C808080;
    base_8001 = (u8 *)0x80010000;
    ASM_KEEP_NV(base_8001);
    ddp = (u8 *)0x80080000;
    ASM_KEEP(ddp);
    temp_v0 = FIELD(obj, u16, 0xA2);
    ASM_KEEP(temp_v0);
    ddp += 0x3160;
    ASM_KEEP(ddp);
    temp_v0 |= 0x10;
    FIELD(obj, u16, 0xA2) = temp_v0;
    FIELD(entity, s32, 0x14) |= 0x4000;
    dce_page = (u8 *)0x800E0000;
    ASM_KEEP(dce_page);
    copy_addr = 0x8001020C;
    ASM_KEEP_NV(copy_addr);
    *(Copy12 *)(entity + 0x34) = *(Copy12 *)copy_addr;
    copy_tail = *(s8 *)(copy_addr + 12);
    ASM_KEEP(copy_tail);
    FIELD(entity, s8, 0x40) = copy_tail;
    FIELD(entity, s8, 0x42) = 0;
    FIELD(entity, s8, 0x41) = 0;
    FIELD(obj, s32, 0xDC) = constant_2c;
    FIELD(obj, s32, 0xE0) = constant_2c;

    {
        u32 fb_x;
        u32 fb_y;
        u16 idx1;
        u16 idx2;
        u16 c6v;
        register u16 *dd264p ASM_REG("$3");

        dd264p = D_800DD264;
        fb_x = FIELD(state, u8, 0x24);
        ASM_KEEP_NV(fb_x);
        idx1 = *(u16 *)(base_8001 + 0x20A2);
        fb_y = FIELD(state, u8, 0x25);
        ASM_KEEP_DEP_NV(idx1, fb_y);
        value = dd264p[(s16)idx1];
        base_83460 = D_80083460;
        FIELD(ddp, u16, 0xC4) = value;
        idx2 = *(u16 *)(base_8001 + 0x20A0);
        *(u16 *)(dce_page - 0x31A0) = value;
        arg3 = D_800DD26C[(s16)idx2];
        c6v = FIELD(ddp, u16, 0xC6);
        dce = dce_page - 0x31A0;
        FIELD(dce, s16, 4) = 0;
        FIELD(dce, u16, 2) = c6v;
        D_800E4938[0] = 0;
        *(void **)&D_800E4938[1] = alloc;
        D_800E4938[2] = 0;
        FIELD(base_83460, u16, 2) |= 2;
        FIELD(dce, u16, 6) = arg3;
        FIELD(state, s8, 0x26) =
            func_8009FB34(fb_x, fb_y, base_83460, arg3);
    }
    FIELD(obj, s8, 0x9C) = -2;
    func_8009D380();
    {
        s32 lift_a1;

        call_actor = actor;
        lift_a1 = FIELD(dce, s16, 6);
        D_800E3540 = 0;
        D_80081484 = 0;
        D_80081470 = 0;
        func_800172A0(call_actor, lift_a1);
    }
    final_base = (u8 *)0x80080000;
    ASM_KEEP(final_base);
    final_flags = FIELD(base_8001, u16, 0x3714);
    ASM_KEEP(final_flags);
    final_value = -0x24;
    FIELD(final_base, s8, 0x2A3B) = final_value;
    if (final_flags & 4) {
        func_800A6C00(final_base);
    }
}
