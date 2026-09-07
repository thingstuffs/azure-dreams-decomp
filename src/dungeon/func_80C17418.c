#include "common.h"

typedef struct {
    u8 pad00[4];
    u16 flags4;
} SubActor;

typedef struct {
    u8 pad00[0x2C];
    void (*f2C)(void);
} ActorBase;

typedef struct {
    u8 pad00[0x8C];
    void (*f8C)(void);
    union {
        u32 word90;
        struct {
            u16 half90;
            u16 half92;
        } h;
    } u90;
    u8 pad94[2];
    u16 f96;
    u16 flags98;
    u8 pad9A;
    u8 state9B;
    u8 pad9C[8];
    u8 *fA4;
    s16 fA8;
} State;

typedef struct {
    u8 pad00[0xC];
    u32 fC;
    u32 f10;
    u32 f14;
} Position;

typedef struct {
    u8 pad00[0x14];
    u16 flags14;
    u8 pad16[0xE];
    u8 f24;
    u8 f25;
    u8 pad26[6];
    void (*f2C)(void);
} Actor;

typedef struct {
    u8 pad00[8];
    u8 slots[9];
    u8 pad11[11];
    u32 flags1C;
    u8 pad20[10];
    s16 f2A;
    u8 pad2C[26];
    u16 f46;
    u8 pad48[24];
    void *f60;
    u8 pad64[9];
    s8 f6D;
    u8 pad6E[4];
    s8 f72;
    s8 f73;
} Entity;

typedef union {
    Entity entity;
    s8 bytes[sizeof(Entity)];
} EntityAlias;

typedef struct {
    u8 pad00[0x12];
    u8 f12;
    u8 pad13;
} ItemInfo;

typedef struct {
    u8 pad00[0xA6];
    u16 fA6;
} MainObj;

typedef struct {
    u8 pad00[0xA];
    u16 fA;
    u32 fC;
} Global83460;

extern void *D_80170838[];
extern ItemInfo D_8006DE24[];
extern MainObj *D_800814A8;
extern s16 D_80083228[];
extern Global83460 D_80083460;
extern s32 D_8008346C[];
extern u8 D_801713A8[];
extern u8 D_801744E4[];
extern u8 D_801744DC[];
extern u8 D_80174494[];
extern u8 D_8017449C[];

extern void *func_800A05A4(Entity *, u8, u8, s16, s32);
extern s32 func_800A94A0(Entity *, u8 *, s32, u16 *);
extern void func_800A2B04(Position *, u8, u8);
extern void func_800A4ACC(Entity *);
extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800DAE44(Position *, s32);

void func_80172C18(State *state, Position *pos, Actor *actor, Entity *ent)
{
    static void *const keepalive[] = {
        &&slot1, &&slot2, &&slot3, &&slot4, &&slot5, &&slot6, &&slot7
    };
    u8 *slot;
    s32 state_index;
    s32 special;
    u8 *actor_parts;
    SubActor *sub_actor;
    ActorBase *actor_base;

    special = 0;
    state_index = state->state9B;
    actor_parts = state->fA4;
    sub_actor = (SubActor *)(actor_parts + 0x20);
    actor_base = (ActorBase *)(actor_parts + 0x28);

    if (state_index == 1) {
        goto state1;
    }
    if (state_index < 2) {
        if (state_index == 0) {
            goto state0;
        }
        goto end;
    }
    if (state_index == 2) {
        goto state2;
    }
    if (state_index == 3) {
        goto state3;
    }
    goto end;

state0:
    if (ent->flags1C & 0x2000) {
        s32 selector;

        selector = (ent->f46 & 0x3FFF) - 1;
        if ((u32)selector >= 7) {
            goto slot4;
        }
        (void)keepalive;
        goto *D_80170838[selector];
slot7:
        special = 1;
        goto slot3;
slot6:
        special = 1;
        goto slot2;
slot5:
        special = 1;
        goto slot1;
    }

    {
        s32 type;

        type = ent->f46 & 0x3FFF;
        if (type == 2) {
            goto slot2;
        }
        if (type < 3) {
            slot = 0;
            if (type == 1) {
                goto normal_slot1;
            }
            goto have_slot;
        }
        if (type != 3) {
            slot = 0;
            goto have_slot;
        }
    }

slot3:
    slot = &ent->slots[6];
    goto have_slot;
slot2:
    slot = &ent->slots[3];
    goto have_slot;
normal_slot1:
slot1:
    slot = &ent->slots[0];
    goto have_slot;
slot4:
    slot = 0;

have_slot:
    if (*slot != 0) {
        s32 special_test;
        u16 state_flags;
        u8 *link_base;

        state_flags = state->flags98;
        state_flags &= 0xFF7F;
        state->flags98 = state_flags;
        special_test = special;
        ASM_KEEP(special_test);   /* MATCH pin: retail basic-block layout depends on it */
        if (special_test) {
            link_base = (u8 *)D_800814A8;
            ent->f60 = link_base;
            goto copy_link;
        }
        if (D_8006DE24[*slot].f12 == 2) {
            link_base = ent->f60;
            if (link_base != 0) {
copy_link:
                {
                    register u8 *link ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

                    link = *(u8 **)(link_base - 0x14);
                    ent->f72 = link[0x24];
                    ent->f73 = link[0x25];
                }
            }
        } else {
            s32 offset_y;
            s32 offset_x;

            *(void * volatile *)&ent->f60 = func_800A05A4(
                ent, actor->f24, actor->f25, ent->f2A, 0x10);
            offset_x = __builtin_abs(ent->f72);
            offset_y = __builtin_abs(ent->f73);
            ent->f72 = offset_x;
            ent->f73 = offset_y;
        }

        sub_actor->flags4 &= 0x7FFF;
        actor_base->f2C = (void (*)(void))D_801744E4;
        func_80047784(
            actor_base,
            D_801744E4[((D_80083228[0] + ent->f2A + 0x100) >> 9) & 7],
            0);
        if (!func_800A94A0(ent, slot, special, &state->flags98)) {
            goto end;
        }
        actor->flags14 &= 0xF7FF;
        func_800DAE44(pos, 5);
        func_800A56E0(0x703);
        state->state9B++;
        state->flags98 |= 8;
        ent->flags1C &= 0xF7FFFFFF;
        ent->flags1C &= 0xFFFBFFFF;
        goto end;
    }

    pos->f14 = 0;
    pos->f10 = 0;
    pos->fC = 0;
    func_800A2B04(pos, actor->f24, actor->f25);
    {
        MainObj *main_obj;

        main_obj = D_800814A8;
        D_8008346C[0] = 0;
        main_obj->fA6--;
    }
    func_800A4ACC(ent);
    ent->f6D--;
    state->f8C = (void (*)(void))D_801713A8;
    ent->f73 = 0;
    ent->f72 = 0;
    ent->f46 &= 0x7FFF;
    goto end;

state1:
    state->u90.h.half92 += (-0x60 - (s16)state->u90.h.half92) >> 3;
    if (actor->flags14 & 0xE000) {
        actor->f2C = (void (*)(void))D_801744DC;
        func_80047784(
            actor,
            D_801744DC[((D_80083228[0] + ent->f2A + 0x100) >> 9) & 7],
            0);
        state->f96 = state_index;
        state->state9B++;
    }
    goto end;

state2:
    if (func_8003F270()) {
        actor->flags14 |= 0x800;
        goto end;
    }
    actor->flags14 &= 0xF7FF;
    state->state9B++;

state3:
    state->u90.h.half92 +=
        (-0x30 - (s16)state->u90.h.half92) >> 3;
    state->f96--;
    if ((s16)state->f96 > 0) {
        if (!(actor->flags14 & 0xE000)) {
            goto no_flag80;
        }
    }
    state->flags98 |= 0x80;
no_flag80:
    if (!(state->flags98 & 0x4000)) {
        if (state->fA8 == 2) {
            goto set_flag4000;
        }
    }
    if (!(actor->flags14 & 0x8000)) {
        goto no_flag4000;
    }
set_flag4000:
    state->flags98 |= 0x4000;
no_flag4000:
    if (!(actor->flags14 & 0xE000)) {
        goto end;
    }

    sub_actor->flags4 |= 0x8000;
    pos->f14 = 0;
    pos->f10 = 0;
    pos->fC = 0;
    func_800A2B04(pos, actor->f24, actor->f25);
    state->flags98 &= 0xFFF7;
    ent->flags1C |= 0x08000000;
    ent->flags1C |= 0x00040000;

    if (actor->f2C != (void (*)(void))D_80174494 &&
        actor->f2C != (void (*)(void))D_8017449C) {
        state->fA8 = 0;
        state->flags98 &= 0xBFFF;
        actor->f2C = (void (*)(void))D_80174494;
        func_80047784(
            actor,
            D_80174494[((D_80083228[0] + ent->f2A + 0x100) >> 9) & 7],
            state->fA8);
    }
    {
        Global83460 *global;

        global = &D_80083460;
        if (global->fC != 0) {
            goto end;
        }
        if (!(state->flags98 & 0x4000)) {
            goto end;
        }
        global->fA--;
    }
    actor->flags14 &= 0xF7FF;
    state->f8C = (void (*)(void))D_801713A8;
    func_800A4ACC(ent);
    if (ent->f6D > 0) {
        ent->f6D--;
    }
    ent->f73 = 0;
    ent->f72 = 0;
    ent->f46 &= 0x7FFF;
    func_800A56E0(0xB4);

end:
    return;
}
