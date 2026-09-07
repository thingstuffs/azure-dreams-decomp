#include "common.h"

typedef struct {
    s16 x;
    s16 y;
} OffsetPair;

typedef struct {
    OffsetPair p[8];
} OffsetTable;

typedef struct {
    u8 bytes[12];
} Template12 __attribute__((packed));

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Position;

typedef struct {
    u8 pad0[6];
    s16 unk6;
    void *image;
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    s16 unk10;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    s16 scale_x;
    s16 scale_y;
} Sprite;

typedef struct {
    u8 pad0[0x8C];
    s32 vel_x;
    s32 vel_y;
    s32 vel_z;
    u8 pad98[8];
    s32 accel_z;
} Motion;

typedef struct {
    u8 pad0[4];
    void *object;
    u8 kind;
    u8 pad9;
    s16 state;
    s16 x;
    s16 y;
    s16 z;
    s16 old_x;
    s16 old_y;
    s16 old_z;
    s16 mid_x;
    s16 mid_y;
    s16 mid_z;
    u8 pad1E[2];
    s16 timer;
    u8 pad22[4];
    s16 table_index;
    u8 pad28[4];
    u16 counter;
} Work;

typedef struct {
    u8 pad0[8];
    void *field8;
} SearchContext;

typedef struct {
    u8 pad0[0x60];
    void *field60;
} DungeonState;

typedef struct {
    u8 pad0[10];
    u16 count;
    s32 fieldC;
} GlobalActor;

typedef struct {
    u8 pad0[8];
    Position *pos;
    Sprite *sprite;
    void (*update)(void);
    u8 pad14[0xC];
    Motion motion;
} Effect;

typedef struct {
    DungeonState *value;
    u8 pad4[8];
} DungeonStatePtr;

typedef struct {
    s16 value;
    u8 pad2[10];
} S16Global;

typedef struct {
    u16 value;
    u8 pad2[10];
} U16Global;

typedef struct {
    u32 value;
    u8 pad4[8];
} U32Global;

extern OffsetTable D_80024004;
extern void *D_80024068[];
extern u8 D_80020000[0x69C0];
extern u8 D_80080000[0x37A0];
extern DungeonStatePtr D_800814A8;
extern SearchContext D_80082E80;
extern S16Global D_80082E86;
extern S16Global D_800269B4;
extern Position D_80083780;
extern Template12 D_80026990;
extern Template12 D_8002699C;
extern Template12 D_800269A8;
extern GlobalActor D_80083460;
extern U32Global D_800814A0;
extern U16Global D_80082E94;

extern s32 func_8003DF74(void *, void *, void *, s32);
extern Effect *func_8003FC64(s32);
extern void func_8004491C(Effect *, void *);
extern void func_80045340(void);
extern void func_80025648(void);
extern void func_80024A5C(void);
extern void func_800257B0(void);
extern void func_80025A80(void);
extern void func_80025724(void);
extern void func_8002553C(Work *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800542BC(void);
extern void func_8002694C(void) __attribute__((noreturn));
extern void func_800268B8(void) __attribute__((noreturn));
extern void func_80024AF8(Work *, s32, s32, s32, s32, s32);
extern void func_80024CA4(Work *, s32, s32, s32, s32, s32);
extern void func_80024F80(Work *, s32, s32, s32, s32, s32);
extern u32 func_80069EF8(void);

void func_8196C568(Work *work, s32 arg1, s32 arg2)
{
    OffsetTable offsets;
    Effect *effect;
    Sprite *sprite;
    Motion *motion;
    register s32 i;
    Position *pos;
    register Position *base ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    register Work *active ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    register DungeonState *dungeon ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    void **state_table;
    u8 *page_v0;
    register u8 *page_v1 ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 *page_a0;
    u8 *page_a3;
    u8 *copy_hold;
    register SearchContext *search ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    void *object;
    register u16 next_state ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u16 table_value;
    register s32 call_arg1 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 call_arg2;
    u16 dungeon_count;
    u8 object_kind;
    s16 init_timer;
    register s32 state;
    register u32 random;
    u16 coord_y;
    static void *const keepalive[] = {
        &&state0, &&state1, &&state2, &&state2, &&state4
    };

    copy_hold = (u8 *)0x80020000;
    offsets = D_80024004;
    work->counter++;
    state = work->state;
    if ((u32)state >= 5) {
        return;
    }
    state_table = D_80024068;
    goto *state_table[state];

state0:
    page_v0 = (u8 *)0x80080000;
    ASM_KEEP_NV(page_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    dungeon = *(DungeonState **)(page_v0 + 0x14A8);
    init_timer = 33;
    page_a0 = (u8 *)0x80020000;
    *(s32 *)&dungeon->pad0[0xF4] = 0;
    ASM_KEEP(dungeon);   /* MATCH pin: keeps a statement from moving across a call/branch */
    *(s16 *)&dungeon->pad0[0x96] = init_timer;
    page_v1 = (u8 *)0x80080000;
    ASM_KEEP_NV(page_v1);   /* MATCH pin: keeps a statement from moving across a call/branch */
    *(s16 *)(page_v1 + 0x2E86) = 6;
    next_state = (u16)work->state;
    *(s16 *)(page_a0 + 0x69B4) = 1;
    next_state++;
    work->state = next_state;
    ASM_KEEP(next_state);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    object = work->object;
    if ((*(u16 *)object & 0x80) == 0) {
        return;
    }
    active = work;
    page_a3 = (u8 *)0x80080000;
    dungeon = *(DungeonState **)(page_a3 + 0x14A8);
    active->timer = 45;
    dungeon_count = *(u16 *)&dungeon->pad0[0xA6];
    call_arg1 = arg1;
    dungeon_count--;
    *(u16 *)&dungeon->pad0[0xA6] = dungeon_count;
    object_kind = active->kind;
    call_arg2 = arg2;
    dungeon->pad0[0xA8] = object_kind;
    dungeon = *(DungeonState **)(page_a3 + 0x14A8);
    table_value = ((*(u16 *)&dungeon->pad0[0x2A]) >> 9) & 7;
    active->state++;
    active->counter = 0;
    active->table_index = table_value;
    func_8002553C(active, call_arg1, call_arg2);
    func_800A56E0(0x300);
    func_800542BC();
    func_8002694C();
    return;

state1:
    if (work->timer < 39) {
        search = &D_80082E80;
        if (func_8003DF74(search->field8, search, &work->x, 0)) {
        if (work->timer == 38) {
            effect = func_8003FC64(0x212);
            if (effect != 0) {
                *(s16 *)&effect->motion.pad0[0x2C] = 33;
                effect->update = func_80025648;
                func_8004491C(effect, func_80045340);
                sprite = effect->sprite;
                sprite->unk10 = 32;
                sprite->flags |= 0xC;
                sprite->unk6 = -4;
                pos = effect->pos;
                pos->x = work->x;
                coord_y = work->y;
                pos->y = coord_y;
                pos->z = work->z;
                base = &D_80083780;
                pos->x += base->x;
                pos->y += base->y;
                pos->z += base->z;
                sprite->scale_x = 0x900;
                sprite->scale_y = 0x604;
                sprite->b = 0x80;
                sprite->g = 0x80;
                sprite->r = 0x80;
                *(Template12 *)&effect->motion.pad0[0x38] = D_80026990;
                sprite->image = &effect->motion.pad0[0x38];
            }
        }

        if (work->timer < 6) {
        effect = func_8003FC64(0x212);
        if (effect != 0) {
            *(s16 *)&effect->motion.pad0[0x2C] = 1;
            effect->update = func_80024A5C;
            func_8004491C(effect, func_80045340);
            sprite = effect->sprite;
            sprite->unk10 = 32;
            sprite->flags |= 0xC;
            sprite->unk6 = -4;
            pos = effect->pos;
            pos->x = work->x;
            coord_y = work->y;
            pos->y = coord_y;
            pos->z = work->z;
            base = &D_80083780;
            pos->x += base->x;
            pos->y += base->y;
            pos->z += base->z;
            sprite->scale_x = 0x1800;
            sprite->scale_y = 0x1000;
            sprite->b = 0x80;
            sprite->g = 0x80;
            sprite->r = 0x80;
            *(Template12 *)&effect->motion.pad0[0x38] = D_8002699C;
            sprite->image = &effect->motion.pad0[0x38];
        }
        }

        if (work->timer < 7) {
            for (i = 0; i < 2; i++) {
                func_80024AF8(work, arg1, arg2, work->x, work->y, work->z);
            }
        }
        if (work->timer < 3) {
            i = 0;
            work->mid_x = (work->x + work->old_x) / 2;
            work->mid_y = (work->y + work->old_y) / 2;
            work->mid_z = (work->z + work->old_z) / 2;
            for (; i < 2; i++) {
                func_80024AF8(work, arg1, arg2,
                              work->mid_x, work->mid_y, work->mid_z);
            }
        }
        work->old_x = work->x;
        work->old_y = work->y;
        work->old_z = work->z;
        }
    }
    work->timer--;
    if (work->timer > 0) {
        return;
    }
    work->timer = 16;
    work->state++;
    func_8002694C();
    return;

state2:
    if (D_800814A8.value->field60 != 0) {
        if (work->timer >= 13) {
            search = &D_80082E80;
            if (func_8003DF74(search->field8, search, &work->x, 0)) {
            for (i = 0; i < 4; i++) {
                func_80024CA4(work, arg1, arg2, work->x, work->y, work->z);
            }
            for (i = 0; i < 4; i++) {
                func_80024F80(work, arg1, arg2, work->x, work->y, work->z);
            }
            arg1 = work->timer;
            if (arg1 == 16) {
                effect = func_8003FC64(0x212);
                if (effect != 0) {
                    motion = &effect->motion;
                    *(s16 *)&motion->pad0[0x2C] = 30;
                    *(s16 *)&motion->pad0[0x2E] = 30;
                    effect->update = func_800257B0;
                    func_8004491C(effect, func_80045340);
                    sprite = effect->sprite;
                    sprite->unk10 = 32;
                    sprite->flags |= 0xC;
                    motion->vel_z = (s32)0xFFF20000;
                    motion->accel_z = 0x00020000;
                    motion->vel_x = (s32)offsets.p[work->table_index].x << 19;
                    motion->vel_y = (u16)offsets.p[work->table_index].y << 19;
                    random = func_80069EF8();
                    motion->vel_x += (s32)0xFFFC0000 + ((random & 0x1FFF) << 6);
                    random = func_80069EF8();
                    motion->vel_y += (s32)0xFFFC0000 + ((random & 0x1FFF) << 6);
                    random = func_80069EF8();
                    motion->vel_z += (s32)0xFFFC0000 + ((random & 0x1FFF) << 6);
                    pos = effect->pos;
                    pos->x = work->x;
                    coord_y = work->y;
                    pos->y = coord_y;
                    pos->z = work->z - 16;
                    base = &D_80083780;
                    pos->x += base->x;
                    pos->y += base->y;
                    pos->z += base->z;
                    sprite->scale_y = 0x1000;
                    sprite->scale_x = 0x1000;
                    sprite->b = 0x80;
                    sprite->g = 0x80;
                    sprite->r = 0x80;
                    *(Template12 *)&effect->motion.pad0[0x38] = D_800269A8;
                    sprite->image = &effect->motion.pad0[0x38];
                }
            if (work->timer == arg1) {
                effect = func_8003FC64(0x212);
                if (effect != 0) {
                    motion = &effect->motion;
                    *(s16 *)&motion->pad0[0x2C] = 30;
                    *(s16 *)&motion->pad0[0x2E] = 30;
                    effect->update = func_80025A80;
                    func_8004491C(effect, func_80045340);
                    sprite = effect->sprite;
                    sprite->unk10 = 32;
                    sprite->flags |= 0xC;
                    motion->vel_z = (s32)0xFFF20000;
                    motion->accel_z = 0x00020000;
                    motion->vel_x = (s32)offsets.p[work->table_index].x << 18;
                    motion->vel_y = (u16)offsets.p[work->table_index].y << 18;
                    random = func_80069EF8();
                    motion->vel_x += (s32)0xFFF80000 + ((random & 0x3FFF) << 6);
                    random = func_80069EF8();
                    motion->vel_y += (s32)0xFFF80000 + ((random & 0x3FFF) << 6);
                    random = func_80069EF8();
                    motion->vel_z += (s32)0xFFF80000 + ((random & 0x3FFF) << 6);
                    pos = effect->pos;
                    pos->x = work->x;
                    coord_y = work->y;
                    pos->y = coord_y;
                    pos->z = work->z - 16;
                    base = &D_80083780;
                    pos->x += base->x;
                    pos->y += base->y;
                    pos->z += base->z;
                    sprite->scale_y = 0x1000;
                    sprite->scale_x = 0x1000;
                    sprite->b = 0x80;
                    sprite->g = 0x80;
                    sprite->r = 0x80;
                    *(Template12 *)&effect->motion.pad0[0x38] = D_800269A8;
                    {
                        void *image;
                        image = &effect->motion.pad0[0x38];
                        sprite->image = image;
                    }
                    func_800268B8();
                    return;
                }
            }
            }
            }
        }
    } else {
        if (work->timer == 16) {
            effect = func_8003FC64(0x212);
            if (effect != 0) {
                motion = &effect->motion;
                *(s16 *)&motion->pad0[0x2C] = 7;
                *(s16 *)&motion->pad0[0x2E] = 7;
                effect->update = func_80025724;
                func_8004491C(effect, func_80045340);
                sprite = effect->sprite;
                sprite->unk10 = 32;
                sprite->flags |= 0xC;
                pos = effect->pos;
                pos->x = work->x;
                coord_y = work->y;
                pos->y = coord_y;
                pos->z = work->z;
                base = &D_80083780;
                pos->x += base->x;
                pos->y += base->y;
                pos->z += base->z;
                sprite->scale_x = 0x1800;
                sprite->scale_y = 0x1000;
                sprite->b = 0x80;
                sprite->g = 0x80;
                sprite->r = 0x80;
                *(Template12 *)&effect->motion.pad0[0x38] = D_8002699C;
                sprite->image = &effect->motion.pad0[0x38];
            }
        }
        if (work->timer >= 13) {
            for (i = 0; i < 2; i++) {
                func_80024AF8(work, arg1, arg2,
                              work->x, work->y, (s16)(work->z - 8));
            }
        }
    }

    if ((D_80082E94.value & 0x8000) == 0) {
        work->timer--;
        if (work->timer >= 0) {
            return;
        }
    }
    work->state = 4;
    func_8002694C();
    return;

state4:
    if (D_800269B4.value == 0) {
        D_80083460.fieldC = 0;
        D_80082E86.value = 0;
        D_80083460.count--;
        ((u16 *)work)[-1] |= 0x8000;
        D_800814A0.value |= 0x8000;
        func_8002694C();
    }
    D_800269B4.value = 0;
}
