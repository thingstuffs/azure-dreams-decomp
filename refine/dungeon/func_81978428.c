#include "common.h"

typedef struct S_81978428_0 {
    u8 pad_00[0xF4];
    s32 unk_F4;
} S_81978428_0;   /* init_page in func_81978428 */

typedef struct S_81978428_1 {
    u16 unk_00;
} S_81978428_1;   /* self->part4 in func_81978428 */

typedef struct S_81978428_2 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0xE];
    u16 unk_A6;
    u8 unk_A8;
} S_81978428_2;   /* case0_global in func_81978428 */

typedef struct S_81978428_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_81978428_3;   /* angle_global in func_81978428 */

typedef struct S_81978428_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x3778];
    s32 unk_3780;
} S_81978428_4;   /* copy_page in func_81978428 */

typedef struct S_81978428_5 {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
} S_81978428_5;   /* player in func_81978428 */

typedef struct S_81978428_6 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_81978428_6;   /* work in func_81978428 */

typedef struct S_81978428_7 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_81978428_7;   /* fallback in func_81978428 */

typedef struct S_81978428_8 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_81978428_8;   /* case3_object in func_81978428 */

typedef struct S_81978428_9 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_81978428_9;   /* after_object in func_81978428 */

typedef struct S_81978428_10 {
    u8 pad_00[0xC];
    u32 unk_0C;
} S_81978428_10;   /* after_aux in func_81978428 */

typedef struct S_81978428_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
    u8 pad_10[0x1490];
    u32 unk_14A0;
} S_81978428_11;   /* tail_page in func_81978428 */

typedef struct S_81978428_12_pre {
    u16 unk_00;
} S_81978428_12_pre;   /* the 0x2 bytes before self in func_81978428, addressed as self[-1] */



typedef struct {
    void *part0;
    void *part4;
    u8 kind;
    u8 effect;
    s16 state;
    u8 pad0C[2];
    u16 angle;
    u16 counter;
    u8 pad12[2];
    void *object;
    s16 timer;
    s16 flag;
} State81978428;

typedef struct {
    s16 pad0;
    u16 x;
    s16 pad4;
    u16 y;
    s16 pad8;
    s16 z;
    u8 pad0C[8];
} Scratch81978428;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec81978428;

extern void *D_80024038[6];

extern u8 D_800814A8[12];
extern s32 D_800814A0[3];
extern u8 D_80082E80[];
extern u16 D_80082E94[5];
extern u8 D_80083460[16];
extern Vec81978428 D_80083780;
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];

extern void func_800243C0(void *, void *);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern void *func_800A05A4();
extern u16 func_800BCAD0(void *);
extern s32 func_800A45D8(u16, u16, s16);
extern void func_80025A9C(void *, void *, void *);
extern void func_80025508(void *, void *);
extern void func_8009CE1C(void *, s32, u8, s32, s16, void *, s32);
extern void func_80025F5C(void) __attribute__((noreturn));
extern void func_800260F8(void) __attribute__((noreturn));
extern void func_80026040(void) __attribute__((noreturn));
extern void func_80026150(void) __attribute__((noreturn));
extern void func_80026154(void) __attribute__((noreturn));

/* Advances the object effect through placement, animation, and cleanup states. */
void func_81978428(State81978428 *state, s32 *position_out)
{
    static void *const state_labels[] = {
        &&case0, &&case1, &&case2, &&case3, &&case4, &&case5,
    };
    State81978428 *self = state;
    s32 *position = position_out;
    void *target_pos;
    s32 step_count;
    register u8 *map_or_y_steps ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    register u8 *player_page ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    s16 *x_steps;
    u8 *data_page;
    Scratch81978428 fallback_pos;
    register void *spawned_object ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u16 timer;
    s32 state_index;
    s32 direction_offset;
    register s32 tile_step ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 zero ASM_REG("$0");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

    timer = self->counter;
    state_index = self->state;
    timer++;
    self->counter = timer;
    if ((u32)state_index >= 6) {
        goto done;
    }
    {
        void *volatile *state_table = D_80024038;
        goto *state_table[state_index];
    }

case0:
    {
        u8 *init_page = (u8 *)0x80080000;
        u8 *player_page;
        u8 *player_state;
        u8 *facing_player;
        u16 next_state;

        ASM_KEEP(init_page);   /* MATCH pin: retail schedule: same instructions, different order without it */
        next_state = self->state;
        init_page = *(u8 **)(init_page + 0x14A8);
        self->counter = 0;
        next_state++;
        self->state = next_state;
        ((S_81978428_0 *)init_page)->unk_F4 = 0;
        func_800243C0((u8 *)self->part0 - 0x20, self->part4);
        if ((((S_81978428_1 *)(self->part4))->unk_00 & 0x80) == 0) {
            goto done;
        }
        player_page = (u8 *)0x80080000;
        ASM_KEEP(player_page);   /* MATCH pin: keeps a constant in a register as retail does */
        player_state = *(u8 **)(player_page + 0x14A8);
        self->timer = 10;
        ((S_81978428_2 *)player_state)->unk_96 = 8;
        ((S_81978428_2 *)player_state)->unk_A6--;
        ((S_81978428_2 *)player_state)->unk_A8 = self->kind;
        facing_player = *(u8 **)(player_page + 0x14A8);
        self->angle = ((S_81978428_3 *)facing_player)->unk_2A;
        self->state++;
        if (func_80053EF0(4) != 2) {
            func_800A56E0(0x300);
            self->flag = 0;
            func_80026154();
        }
        func_800A56E0(0x4300);
        self->flag = 0;
        func_80026154();
    }

case1:
    timer = self->timer;
    timer--;
    self->timer = timer;
    if ((s32)((u32)timer << 16) > 0) {
        goto done;
    }

    {
        u8 *copy_page = (u8 *)0x80080000;
        u8 *player;
        s32 spawn_angle;
        s32 player_x;
        register s32 spawn_mode ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
#ifndef NON_MATCHING
        register s32 *stack_args ASM_REG("$29");   /* MATCH pin: keeps a constant in a register as retail does */
#endif

        player_page = (u8 *)0x80080000;
        ASM_KEEP(copy_page);   /* MATCH pin: retail immediate-load split depends on it */
        ASM_KEEP(player_page);   /* MATCH pin: load-bearing for the whole function shape */
        player_x = ((S_81978428_4 *)copy_page)->unk_3780;
        player = *(u8 **)(player_page + 0x14A8);
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        copy_page += 0x3780;
        ASM_KEEP(copy_page);   /* MATCH pin: retail immediate-load split depends on it */
        position[0] = player_x;
        position[1] = ((S_81978428_4 *)copy_page)->unk_04;
        position[2] = (s32)((S_81978428_5 *)player)->unk_88.s << 16;
        spawn_angle = ((S_81978428_5 *)player)->unk_2A.s;
        ASM_KEEP(spawn_angle);   /* MATCH pin: retail register colouring depends on it */
        spawn_mode = 8;
#ifndef NON_MATCHING
        stack_args[4] = spawn_mode;
#endif
        spawned_object = (void *)0x80080000;
        ASM_KEEP_NV(spawned_object);   /* MATCH pin: keeps a statement from moving across a call/branch */
        map_or_y_steps = (u8 *)spawned_object + 0x2E80;
        ASM_KEEP_NV(map_or_y_steps);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
#ifndef NON_MATCHING
        spawned_object = func_800A05A4(player, map_or_y_steps[0x24], map_or_y_steps[0x25], spawn_angle);
#else
        spawned_object = func_800A05A4(player, map_or_y_steps[0x24], map_or_y_steps[0x25],
                                spawn_angle, spawn_mode);
#endif
    }
    self->object = spawned_object;
    if (spawned_object != 0) {
        target_pos = *(void **)((u8 *)spawned_object - 0x18);
        ASM_KEEP(target_pos);   /* MATCH pin: retail basic-block layout depends on it */
        {
            register State81978428 *state_arg ASM_REG("$4") = self;   /* MATCH pin: retail delay-slot contents depend on it */
            ASM_TAILSLOT_PIN_TIED(state_arg);   /* MATCH pin: retail delay-slot contents depend on it */
            func_80025F5C();
        }
    }

    target_pos = &fallback_pos;
    ASM_KEEP(target_pos);   /* MATCH pin: retail basic-block layout depends on it */
    step_count = zero;
    {
        u8 tile_x;
        u8 tile_y;

        data_page = (u8 *)0x80070000;
        ASM_KEEP(data_page);   /* MATCH pin: load-bearing for the whole function shape */
        x_steps = (s16 *)(data_page - 0x3328);
        tile_x = map_or_y_steps[0x24];
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        data_page = (u8 *)0x80070000;
        ASM_KEEP(data_page);   /* MATCH pin: load-bearing for the whole function shape */
        ((S_81978428_6 *)target_pos)->unk_02.s = (tile_x << 6) + 0x20;
        tile_y = map_or_y_steps[0x25];
        map_or_y_steps = data_page - 0x3318;
        ((S_81978428_6 *)target_pos)->unk_06.s = (tile_y << 6) + 0x20;
    }

loop:
    {
        u8 *player;

        player = *(u8 **)(player_page + 0x14A8);
        direction_offset = (((S_81978428_5 *)player)->unk_2A.u >> 8) & 0xE;
        tile_step = *(s16 *)((u32)direction_offset + (u32)x_steps);
        ((S_81978428_6 *)target_pos)->unk_02.u += tile_step << 6;
        direction_offset = (((S_81978428_5 *)player)->unk_2A.u >> 8) & 0xE;
        tile_step = *(s16 *)((u32)direction_offset + (u32)map_or_y_steps);
        ((S_81978428_6 *)target_pos)->unk_06.u += tile_step << 6;
        ((S_81978428_6 *)target_pos)->unk_0A.s = ((S_81978428_5 *)player)->unk_88.u;
    }
    ((S_81978428_6 *)target_pos)->unk_0A.s = func_800BCAD0(target_pos);
    if (((S_81978428_6 *)target_pos)->unk_0A.u >= 0x201) {
        u8 *player;
        player = *(u8 **)(player_page + 0x14A8);
        ((S_81978428_6 *)target_pos)->unk_0A.s = ((S_81978428_5 *)player)->unk_88.u;
    }

    if ((func_800A45D8(((S_81978428_6 *)target_pos)->unk_02.s, ((S_81978428_6 *)target_pos)->unk_06.s,
                        ((S_81978428_6 *)target_pos)->unk_0A.u) << 16) != 0) {
        u8 *player;

        player = *(u8 **)(player_page + 0x14A8);
        direction_offset = (((S_81978428_5 *)player)->unk_2A.u >> 8) & 0xE;
        tile_step = *(s16 *)((u32)direction_offset + (u32)x_steps);
        ((S_81978428_6 *)target_pos)->unk_02.u -= tile_step << 6;
        direction_offset = (((S_81978428_5 *)player)->unk_2A.u >> 8) & 0xE;
        tile_step = *(s16 *)((u32)direction_offset + (u32)map_or_y_steps);
        ((S_81978428_6 *)target_pos)->unk_06.u -= tile_step << 6;
        ASM_KEEP(map_or_y_steps);   /* MATCH pin: load-bearing for the whole function shape */
        ((S_81978428_6 *)target_pos)->unk_0A.s = ((S_81978428_5 *)player)->unk_88.u;
        ((S_81978428_6 *)target_pos)->unk_0A.s = func_800BCAD0(target_pos);
        if (((S_81978428_6 *)target_pos)->unk_0A.u < 0x201) {
            goto position_ready;
        }
        {
            u8 *height_player;
            height_player = *(u8 **)(player_page + 0x14A8);
            ((S_81978428_6 *)target_pos)->unk_0A.s = ((S_81978428_7 *)height_player)->unk_88;
            func_80025F5C();
        }
    }
    step_count++;
    if (step_count < 8) {
        goto loop;
    }

position_ready:
    func_80025A9C(self, position, target_pos);
    {
        u16 next_state = self->state;
        register u16 wait_frames ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        ASM_KEEP(next_state);   /* MATCH pin: retail basic-block layout depends on it */
        wait_frames = 0x10;
        self->timer = wait_frames;
        func_800260F8();
    }

case2:
    timer = self->timer;
    timer--;
    self->timer = timer;
    if ((s32)((u32)timer << 16) > 0) {
        goto done;
    }
    {
        u16 next_state = 0x18;
        void *spawned_object;

        self->timer = next_state;
        next_state = self->state;
        spawned_object = self->object;
        next_state++;
        self->state = next_state;
        if (spawned_object != 0) {
            func_80025508(self, *(void **)((u8 *)spawned_object - 0x18));
            self->flag = 0;
            func_80026154();
        }
    }
    goto done;

case3:
    {
        u8 *tinted_object = self->object;

        if (tinted_object != 0) {
            u8 *reloaded_object;
            register u8 *tint_data ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
            s16 tint_timer;

            ((S_81978428_8 *)tinted_object)->unk_1C |= 0x10000000;
            tint_timer = self->timer;
            reloaded_object = *(u8 *volatile *)((u8 *)self + 0x14);
            tint_data = *(u8 **)(reloaded_object - 0x14);
            if (tint_timer >= 0xC) {
                u8 blue = tint_data[0xE] + 8;
                tint_data[0xE] = blue;
                if (tint_data[0xC] >= 0xE1) {
                    tint_data[0xC] = 0xE0;
                    func_80026040();
                }
            } else {
                u8 blue = tint_data[0xE] - 8;
                tint_data[0xE] = blue;
                if (blue < 0x80) {
                    tint_data[0xE] = 0x80;
                }
            }
        }
    }

    {
        u32 map_flags = 0x80080000;
        map_flags = *(u16 *)(map_flags + 0x2E94);
        if ((map_flags & 0x8000) == 0) {
            timer = self->timer;
            timer--;
            self->timer = timer;
            if ((s32)((u32)timer << 16) >= 0) {
                goto done;
            }
        }
    }

    {
        u8 *effect_object = self->object;

        if (effect_object != 0) {
            s32 effect_size = 10;
            s32 effect_scale;
            ASM_KEEP(effect_size);   /* MATCH pin: load-bearing for the whole function shape */
            effect_scale = effect_size;
            func_8009CE1C(self->object, effect_size, self->effect, effect_scale,
                          (s16)((self->angle << 9) + 0x800), self->part0, 1);
            {
                u32 clear_tint_mask = 0xEFFFFFFF;
                u32 neutral_color = 0x00808080;
                u8 *reset_object = self->object;
                register u8 *color_data ASM_REG("$6") =
                    *(u8 **)(reset_object - 0x14);

                ((S_81978428_9 *)reset_object)->unk_1C &= clear_tint_mask;
                ((S_81978428_10 *)color_data)->unk_0C = neutral_color;
            }
        }
    }
case4:
    data_page = (u8 *)0x80080000;
    if (self->flag != 0) {
        self->state++;
        func_80026150();
    }
    goto cleanup;

case5:
    data_page = (u8 *)0x80080000;
    if (self->flag != 0) {
        goto done;
    }

cleanup:
    data_page += 0x3460;
    ((S_81978428_11 *)data_page)->unk_0C = 0;
    ((S_81978428_11 *)data_page)->unk_0A--;
    ((S_81978428_12_pre *)self)[-1].unk_00 |= 0x8000;
    data_page = (u8 *)0x80080000;
    ASM_KEEP(data_page);   /* MATCH pin: load-bearing for the whole function shape */
    ((S_81978428_11 *)data_page)->unk_14A0 |= 0x8000;
    func_80026154();

done:
    self->flag = 0;
    (void)state_labels;
}
