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

void func_800165B8(void) {
    u8 pos_x;
    u8 pos_y;
    u16 flags;
    void *alloc;
    u8 *actor_tmp;
    u8 *actor;
    register u8 *call_actor ASM_REG("$4");   /* MATCH pin: retail branch polarity depends on it */
    u8 *state;
    u8 *obj;
    u8 *entity;
    u8 *room;
    s16 first_height;
    s16 height;
    register s32 direction ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    register s16 *delta_x ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *delta_page ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
    s16 *delta_y;
    s32 delta;
    s32 i;
    s32 offset_index;
    u32 index4;
    s32 x_arg;
    s32 y_arg;
    s32 state_value;
    register s32 *descending ASM_REG("$18");   /* MATCH pin: load-bearing for the whole function shape */
    s32 *cf8;
    u8 *ddp;
    register u8 *dd_addr ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
    u8 tile;
    u8 actor_x;
    u8 actor_y;
    u16 value;
    register u16 arg3 ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u8 *base_8001;
    u8 *dce_page;
    u8 *dce;
    u8 *base_83460;
    register u8 *bc_base ASM_REG("$4");   /* MATCH pin: retail branch polarity depends on it */
    register s32 bc_one ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u8 *bc_state ASM_REG("$6");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register u8 *bc_obj ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u8 *small_base;
    register s32 height_const ASM_REG("$6");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 temp_v0 ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
    u8 *final_base;
    s32 final_value;
    u16 final_flags;
    register s32 constant_2c ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 entity_mask;
    s32 entity_value;
    register u32 copy_addr ASM_REG("$6");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 copy_tail;
    u8 *loop_a3;

    D_800DCF5A = 1;
    alloc = func_8003FE78(0, D_80083498, 0x53);
    ((S_800165B8_0 *)alloc)->unk_10 = D_80089AA0;
    func_8004491C(alloc, D_80045340);
    actor_tmp = &D_80083780;
    ((S_800165B8_0 *)alloc)->unk_08 = actor_tmp;
    actor = actor_tmp;
    func_8003DB4C(actor, 6);
    state = D_80082E80;
    ((S_800165B8_0 *)alloc)->unk_0C = state;
    func_8003DB4C(state, 0xC);
    D_800814A8 = obj = (u8 *)alloc + 0x20;
    D_800E3D7C = obj;
    ((S_800165B8_1 *)obj)->unk_13 = 0;
    entity = obj;
    room = D_80082E60;

    if (!(((S_800165B8_2 *)room)->unk_16 & 1)) {
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
        ASM_KEEP(height_const);   /* MATCH pin: retail schedule: same instructions, different order without it */
        direction = -1;
        first_height = func_800BCB04((pos_x << 6) | 0x20,
                                     (pos_y << 6) | 0x20, height_const);
        delta_page = (u8 *)0x80070000;
        ASM_KEEP(delta_page);   /* MATCH pin: load-bearing for the whole function shape */
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
            ASM_KEEP_NV(x_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
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

    pos_x = ((S_800165B8_2 *)room)->unk_10;
    pos_y = ((S_800165B8_2 *)room)->unk_12;
selected:
    call_actor = actor;
    i = 7;
setup:
    {
        u8 setup_x;
        u8 setup_y;

        setup_x = pos_x;
        setup_y = pos_y;
        ((S_800165B8_3 *)state)->unk_24 = setup_x;
        ((S_800165B8_3 *)state)->unk_25 = setup_y;
        func_800A2B04(call_actor, setup_x, setup_y);
    }
    func_8009A21C(pos_x, pos_y, 0x300);
    height = func_800BCB04(((S_800165B8_4 *)actor)->unk_02, ((S_800165B8_4 *)actor)->unk_06, -0x400);
    actor_x = pos_x;
    actor_y = pos_y;
    ((S_800165B8_4 *)actor)->unk_0A = height;
    ((S_800165B8_5 *)entity)->unk_88 = height;
    (*(s16 *)((u8 *)entity + 0x8A)) = height;
    temp_v0 = ((S_800165B8_1 *)obj)->unk_A2;
    ((S_800165B8_3 *)state)->unk_0C = 0x2C808080;
    ((S_800165B8_1 *)obj)->unk_A2 = temp_v0 | 0x10;
    state_value = D_80080A80;
    ((S_800165B8_5 *)entity)->unk_5C = alloc;
    ((S_800165B8_5 *)entity)->unk_58 = alloc;
    ((S_800165B8_3 *)state)->unk_1E = 0x1000;
    ((S_800165B8_3 *)state)->unk_1C = 0x1000;
    ((S_800165B8_3 *)state)->unk_28 = state_value;
    func_80094988(obj, entity, actor_x, actor_y);

    entity_mask = 0xFFEFFFFF;
    {
        u8 *descending_page;
        register s32 *descending_base ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */

        descending_page = (u8 *)0x800E0000;
        ASM_KEEP(descending_page);   /* MATCH pin: load-bearing for the whole function shape */
        descending_base = (s32 *)(descending_page + 0x3D80);
        ASM_KEEP(descending_base);   /* MATCH pin: keeps a constant in a register as retail does */
        entity_value = ((S_800165B8_5 *)entity)->unk_14;
        descending = descending_base + 7;
        entity_value &= entity_mask;
        ((S_800165B8_5 *)entity)->unk_14 = entity_value;
    }
dungeon_loop:
    call_actor = state;
    bc_state = (u8 *)0;
    ASM_KEEP_NV(bc_state);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ddp = (u8 *)0x800E0000;
    ASM_KEEP_NV(ddp);   /* MATCH pin: load-bearing for the whole function shape */
    ddp -= 0x2F88;
    dd_addr = (u8 *)((u32)i + (u32)ddp);
    ASM_KEEP_DEP_NV(dd_addr, ddp);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_800489F4(call_actor, *dd_addr, (s32)bc_state, (s32)bc_state);
    call_actor = state;
    bc_state = (u8 *)0;
    loop_a3 = bc_state;
    ASM_KEEP_DEP_NV(loop_a3, bc_state);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ddp = (u8 *)0x800E0000;
    ASM_KEEP_NV(ddp);   /* MATCH pin: load-bearing for the whole function shape */
    temp_v0 = ((S_800165B8_3 *)state)->unk_08;
    ddp -= 0x2F58;
    *descending = temp_v0;
    descending--;
    dd_addr = (u8 *)((u32)i + (u32)ddp);
    ASM_KEEP_DEP_NV(dd_addr, ddp);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_800489F4(call_actor, *dd_addr, (s32)bc_state, (s32)loop_a3);
    index4 = (u32)i << 2;
    cf8 = D_800E3CF8;
    *(s32 *)((u8 *)cf8 + index4) = ((S_800165B8_3 *)state)->unk_08;
    func_800489F4(state, *(&D_800DD090 + i), 0, 0);
    i--;
    *(s32 *)((u8 *)D_800E3D48 + index4) = ((S_800165B8_3 *)state)->unk_08;
    if (i >= 0) {
        goto dungeon_loop;
    }
    D_800E3D18 = cf8;

    if ((func_80042900(entity, 0xA) << 16) != 0) {
        (*(void * *)((u8 *)state + 0x2C)) = D_800DD274;
        func_8003DB94(state,
            *(void **)((u8 *)D_800DD274 +
                (((D_80083228 + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100) >> 7) & 0x1C)),
            0);
        bc_base = D_80083498;
        goto common_tail;
    }

    func_800489F4(state, 0xB0, 0, 1);
    ((S_800165B8_3 *)state)->unk_2C = D_800DCFB0;
    bc_base = D_80083498;
common_tail:
    bc_one = 1;
    bc_state = state + 0x2C;
    bc_obj = obj + 0x2A;
    ASM_KEEP(bc_one);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_v0 = -1;
    (*(s16 *)((u8 *)obj + 0x94)) = temp_v0;
    i = 0;
    (*(s16 *)((u8 *)obj + 0x118)) = 0;
    ((S_800165B8_5 *)entity)->unk_2A = 0x400 - (((u16)D_80083228 + 0x100) & 0xE00);
    func_800BC26C(bc_base, bc_one, bc_state, bc_obj);
    {
        s32 mask_ffef;

        mask_ffef = 0xFFEFFFFF;
        call_actor = obj;
        temp_v0 = 0xFF;
        ((S_800165B8_1 *)obj)->unk_9A = temp_v0;
        ((S_800165B8_5 *)entity)->unk_1C &= mask_ffef;
    }
    func_80096088(call_actor, entity);
    ((S_800165B8_3 *)state)->unk_14 |= 0x8000;
    small_base = (u8 *)0x80010000;
    do {
        tile = small_base[i + 0x2D6C];
        ((S_800165B8_6 *)(obj + i))->unk_FA = tile;
        if (tile == 2) {
            ((S_800165B8_6 *)(obj + i))->unk_FA = 1;
        }
        i++;
    } while (i < 2);

    constant_2c = 0x2C808080;
    base_8001 = (u8 *)0x80010000;
    ASM_KEEP_NV(base_8001);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ddp = (u8 *)0x80080000;
    ASM_KEEP(ddp);   /* MATCH pin: retail immediate-load split depends on it */
    temp_v0 = ((S_800165B8_1 *)obj)->unk_A2;
    ddp += 0x3160;
    temp_v0 |= 0x10;
    ((S_800165B8_1 *)obj)->unk_A2 = temp_v0;
    ((S_800165B8_5 *)entity)->unk_14 |= 0x4000;
    dce_page = (u8 *)0x800E0000;
    ASM_KEEP(dce_page);   /* MATCH pin: retail immediate-load split depends on it */
    copy_addr = 0x8001020C;
    ASM_KEEP_NV(copy_addr);   /* MATCH pin: keeps a constant in a register as retail does */
    *(Copy12 *)(entity + 0x34) = *(Copy12 *)copy_addr;
    copy_tail = *(s8 *)(copy_addr + 12);
    ASM_KEEP(copy_tail);   /* MATCH pin: keeps a constant in a register as retail does */
    ((S_800165B8_5 *)entity)->unk_40 = copy_tail;
    ((S_800165B8_5 *)entity)->unk_42 = 0;
    ((S_800165B8_5 *)entity)->unk_41 = 0;
    ((S_800165B8_1 *)obj)->unk_DC = constant_2c;
    ((S_800165B8_1 *)obj)->unk_E0 = constant_2c;

    {
        u32 fb_x;
        u32 fb_y;
        u16 idx1;
        u16 idx2;
        u16 c6v;
        register u16 *dd264p ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */

        dd264p = D_800DD264;
        fb_x = ((S_800165B8_3 *)state)->unk_24;
        ASM_KEEP_NV(fb_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
        idx1 = *(u16 *)(base_8001 + 0x20A2);
        fb_y = ((S_800165B8_3 *)state)->unk_25;
        ASM_KEEP_DEP_NV(idx1, fb_y);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        value = dd264p[(s16)idx1];
        base_83460 = D_80083460;
        ((S_800165B8_7 *)ddp)->unk_C4 = value;
        idx2 = *(u16 *)(base_8001 + 0x20A0);
        *(u16 *)(dce_page - 0x31A0) = value;
        arg3 = D_800DD26C[(s16)idx2];
        c6v = ((S_800165B8_7 *)ddp)->unk_C6;
        dce = dce_page - 0x31A0;
        ((S_800165B8_8 *)dce)->unk_04 = 0;
        (*(u16 *)((u8 *)dce + 2)) = c6v;
        D_800E4938[0] = 0;
        *(void **)&D_800E4938[1] = alloc;
        D_800E4938[2] = 0;
        ((S_800165B8_9 *)base_83460)->unk_02 |= 2;
        ((S_800165B8_8 *)dce)->unk_06.s = arg3;
        ((S_800165B8_3 *)state)->unk_26 =
            func_8009FB34(fb_x, fb_y, base_83460, arg3);
    }
    ((S_800165B8_1 *)obj)->unk_9C = -2;
    func_8009D380();
    {
        s32 lift_a1;

        call_actor = actor;
        lift_a1 = ((S_800165B8_8 *)dce)->unk_06.u;
        D_800E3540 = 0;
        D_80081484 = 0;
        D_80081470 = 0;
        func_800172A0(call_actor, lift_a1);
    }
    final_base = (u8 *)0x80080000;
    final_flags = ((S_800165B8_10 *)base_8001)->unk_3714;
    ASM_KEEP(final_flags);   /* MATCH pin: keeps a statement from moving across a call/branch */
    final_value = -0x24;
    ((S_800165B8_11 *)final_base)->unk_2A3B = final_value;
    if (final_flags & 4) {
        func_800A6C00(final_base);
    }
}
