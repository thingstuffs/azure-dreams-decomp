#include "common.h"

typedef struct {
    s16 x;
    s16 y;
} OffsetPair;

#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))

extern void *memcpy(void *, const void *, u32);

extern s32 func_8003DF74();
extern void func_8004491C();
extern void func_80045340(void);
extern s32 func_80069EF8(void);
extern void D_80024488();
extern s32 func_800A4778();
extern void func_800A56E0();
extern u8 *func_8003FC64();
extern s32 func_800644B8();
extern s32 func_80064584();
extern void func_8003DB94();
extern void func_8002407C();
extern void func_800245A8(void);

extern u8 D_80024038[32];
extern void *D_80024058[9];
extern u8 D_800252FC[12];
extern s16 D_80025308[6];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_800DDC40[];
extern u8 D_800DEAE0[];
extern s32 D_8008346C[3];
extern s32 D_800814A0[3];

/* Updates a moving effect, its particles, target color animation, and cleanup. */
void func_800248C4(u8 *effect_data, u8 *effect_pos, u8 *effect_display) {
    s16 origin_offset[4];
    OffsetPair direction_offsets[8];
    register u8 *display ASM_REG("$17") = effect_display;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *owner;
    u8 *entity;
    register u8 *source ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *copy_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *copy_source ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s16 *flag_base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void **jump_table;
    s32 state;
    s32 state_in_range;

    static void *const keepalive[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4,
        &&done, &&done, &&done, &&state8
    };

    owner = PTR_AT(effect_data, 0x00);
#ifdef NON_MATCHING
    copy_page = D_80024038 - 0x4038;
#else
    copy_page = (u8 *)0x80020000;
#endif
    ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    copy_source = copy_page + 0x4038;
    ASM_KEEP(copy_source);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    memcpy(direction_offsets, copy_source, 12);
    memcpy((u8 *)direction_offsets + 12, copy_source + 12, 12);
    memcpy((u8 *)direction_offsets + 24, copy_source + 24, 8);
    ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    state = S16_AT(effect_data, 0x0A);
    entity = owner - 0x20;
    state_in_range = (u32)state < 9U;
    source = PTR_AT(entity, 0x08);
       /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    if (!state_in_range) {
        goto done;
    }
#ifdef NON_MATCHING
    jump_table = (void **)((u8 *)D_80024058 - 0x4058);
#else
#endif
    jump_table = (void **)&D_80024058;
       /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    goto *jump_table[state];

state0:
    S32_AT(display, 0x0C) = 0x00808080;
    U16_AT(display, 0x1E) = 0x1000;
    U16_AT(display, 0x1C) = 0x1000;
    ASM_KEEP(display);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
    copy_page = D_800252FC - 0x52FC;
#else
    copy_page = (u8 *)0x80020000;
#endif
    ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    copy_source = copy_page + 0x52FC;
    ASM_KEEP(copy_source);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    memcpy(effect_data + 0x94, copy_source, 12);
    ASM_USE_NV(copy_page);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    {
        u8 *copy_dest = effect_data + 0x94;
        ASM_KEEP(copy_dest);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        PTR_AT(display, 0x08) = copy_dest;
    }
    {
        u32 owner_bits;
        s32 next_state;

#ifdef NON_MATCHING
        flag_base = (s16 *)((u8 *)D_80025308 - 0x5308);
#else
        flag_base = (s16 *)0x80020000;
#endif
        owner_bits = U16_AT(owner, 0x2A);
        ASM_KEEP(owner_bits);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        next_state = 1;
        *(s16 *)((u8 *)flag_base + 0x5308) = next_state;
        next_state = U16_AT(effect_data, 0x0A);
        ASM_KEEP_DEP_NV(owner_bits, next_state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        owner_bits = (owner_bits >> 9) & 7;
        next_state++;
        ASM_KEEP(next_state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        S16_AT(effect_data, 0x7E) = owner_bits;
        S16_AT(effect_data, 0x0A) = next_state;
    }

state1:
    {
        u8 *record = PTR_AT(entity, 0x0C);
        u16 source_z;
        u16 next_z;
        s32 has_origin;

        has_origin = func_8003DF74(PTR_AT(record, 0x08), record, origin_offset, 0);
        if (has_origin == 0 && !(U16_AT(PTR_AT(entity, 0x0C), 0x14) & 0x8000)) {
            goto done;
        }

        U16_AT(effect_pos, 0x02) = U16_AT(source, 0x02);
        U16_AT(effect_pos, 0x06) = U16_AT(source, 0x06);
        source_z = U16_AT(source, 0x0A);
        U16_AT(effect_pos, 0x0A) = source_z;

        if (!(U16_AT(PTR_AT(entity, 0x0C), 0x14) & 0x8000)) {
            U16_AT(effect_pos, 0x02) += (u16)origin_offset[0];
            U16_AT(effect_pos, 0x06) += (u16)origin_offset[1];
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            next_z = U16_AT(effect_pos, 0x0A);
            source_z = (u16)origin_offset[2];
            next_z += source_z;
        } else {
            next_z = (u16)(source_z - 0x40);
        }
        U16_AT(effect_pos, 0x0A) = next_z;

        {
            u8 *task = effect_data - 0x20;

            if (!(U8_AT(effect_data, 0x7A) & 4)) {
                func_8004491C(task, func_80045340);
                U16_AT(display, 0x10) = 0x20;
                U8_AT(display, 0x0E) = 0x14;
                U8_AT(display, 0x0D) = 0x14;
                U8_AT(display, 0x0C) = 0x14;
                U16_AT(display, 0x14) |= 0x0C;
                U8_AT(effect_data, 0x7A) |= 4;
            }
        }

        if (!(U16_AT(PTR_AT(effect_data, 0x04), 0x00) & 0x80)) {
            goto done;
        }

        if (PTR_AT(owner, 0x60) != 0) {
            u8 *sprite;
            s32 delta;

            {
                register u32 target ASM_REG("$3") =
                    (u32)PTR_AT(owner, 0x60);
                register u8 *target_pos ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                u32 table;

                target_pos = PTR_AT((u8 *)target, -0x18);
                table = (u32)D_800DDC40;
                target = U8_AT((u8 *)target, 0x13);
                target += table;
                table = U8_AT((u8 *)target, 0x00);
                target = U16_AT(target_pos, 0x0A);
                table += 0x20;
                target -= table;

                table = (u32)D_8006CCD8;
                S16_AT(effect_data, 0x78) = target;
                target = S16_AT(effect_data, 0x7E);
                sprite = PTR_AT(owner, -0x14);
                target <<= 1;
                target += table;
                table = U8_AT(sprite, 0x24);
                target = U8_AT((u8 *)target, 0x00);
                table += target;
                U8_AT(effect_data, 0xA0) = table;

                table = (u32)D_8006CCE8;
                target = S16_AT(effect_data, 0x7E);
                target <<= 1;
                target += table;
                table = U8_AT(sprite, 0x25);
                target = U8_AT((u8 *)target, 0x00);
                table += target;
                U8_AT(effect_data, 0xA1) = table;
            }

            {
                s32 owner_axis = S8_AT(owner, 0x72);
                register u32 sprite_axis ASM_REG("$3") = U8_AT(sprite, 0x24);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                if (owner_axis != sprite_axis) {
                    delta = owner_axis - sprite_axis;
                } else {
                    owner_axis = S8_AT(owner, 0x73);
                    sprite_axis = U8_AT(sprite, 0x25);
                    delta = owner_axis - sprite_axis;
                }
            }
            if (delta < 0) {
                delta = -delta;
            }
            U8_AT(effect_data, 0x7B) = (u8)((delta * 2) - 1);
        } else {
            s32 height = U16_AT(owner, 0x88);
            U8_AT(effect_data, 0x7B) = 0x20;
            S16_AT(effect_data, 0x78) = (s16)(height - 0x50);
        }

        S32_AT(effect_pos, 0x0C) = direction_offsets[S16_AT(effect_data, 0x7E)].x << 16;
        S32_AT(effect_pos, 0x10) = (u16)direction_offsets[S16_AT(effect_data, 0x7E)].y << 16;
        S32_AT(effect_pos, 0x14) = ((S16_AT(effect_data, 0x78) << 16) -
            S32_AT(effect_pos, 0x08)) / S8_AT(effect_data, 0x7B);
        {
            u32 raw_timer = U8_AT(effect_data, 0x7B);
            s32 timer_copy;
            s32 duration_squared;
            register u32 raw_reload ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            s32 timer_reload;
            s32 next_state;

            ASM_KEEP(raw_timer);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            timer_reload = (s32)(raw_timer << 24) >> 24;
            timer_copy = timer_reload;
            ASM_KEEP(timer_copy);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            duration_squared = timer_reload * timer_copy;
            *(volatile s16 *)(effect_data + 0x82) = 0;
            raw_reload = *(volatile u8 *)(effect_data + 0x7B);
            next_state = U16_AT(effect_data, 0x0A);
            ASM_KEEP(raw_reload);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            timer_reload = (s32)(raw_reload << 24) >> 24;
            next_state++;
            S16_AT(effect_data, 0x0A) = next_state;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            S16_AT(effect_data, 0x88) = timer_reload;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            S16_AT(effect_data, 0x8A) = duration_squared;
        }
        goto done;
    }

state2:
    {
        for (entity = 0; (s32)entity < 4; entity++) {
            s32 random = func_80069EF8();
            u8 *task;
            s32 particle_color;
            s32 particle_param;

            task = effect_data - 0x20;
            ASM_KEEP(task);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            particle_color = 0x002020E0;
            ASM_KEEP(particle_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            random &= 0xFF;
            particle_param = random | 0x80;
            D_80024488(task, S16_AT(effect_data, 0x7E), particle_color, particle_param, 0, 0, 0);
        }

        if (S16_AT(effect_data, 0x92) == 0) {
            S16_AT(effect_data, 0x92) = 1;
            U8_AT(effect_data, 0x9C) += 0x18;
        } else {
            S16_AT(effect_data, 0x92) = 0;
            U8_AT(effect_data, 0x9C) -= 0x18;
        }

        {
            s32 timer = S16_AT(effect_data, 0x88);
            s32 remaining = S8_AT(effect_data, 0x7B);
            timer -= remaining;
            U8_AT(display, 0x0C) = (((timer * timer) * 7) << 5) /
                S16_AT(effect_data, 0x8A) + 0x14;
        }
        {
            s32 timer = S16_AT(effect_data, 0x88);
            s32 remaining = S8_AT(effect_data, 0x7B);
            timer -= remaining;
            U8_AT(display, 0x0D) = ((timer * timer) << 7) /
                S16_AT(effect_data, 0x8A) + 0x14;
        }
        {
            s32 timer = S16_AT(effect_data, 0x88);
            s32 remaining = S8_AT(effect_data, 0x7B);
            timer -= remaining;
            U8_AT(display, 0x0E) = ((timer * timer) << 7) /
                S16_AT(effect_data, 0x8A) + 0x14;
        }

        if ((func_800A4778(U16_AT(effect_pos, 0x02), U16_AT(effect_pos, 0x06),
                S16_AT(effect_pos, 0x0A), PTR_AT(owner, 0x60)) << 16) != 0) {
            goto enter_state8;
        }

        U8_AT(effect_data, 0x7B)--;
        if (S8_AT(effect_data, 0x7B) <= 0) {
            if (PTR_AT(owner, 0x60) != 0) {
                register u8 *target_pos ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                S16_AT(effect_data, 0x0A) = 3;
                S16_AT(effect_data, 0x82) = 0;
                target_pos = PTR_AT(PTR_AT(owner, 0x60), -0x18);
                U16_AT(effect_pos, 0x02) = U16_AT(target_pos, 0x02);
                U16_AT(effect_pos, 0x06) = U16_AT(target_pos, 0x06);
                U16_AT(effect_pos, 0x0A) = U16_AT(effect_data, 0x78);
                func_800A56E0(0x300);
                goto done;
            }

enter_state8:
            S16_AT(effect_data, 0x0A) = 8;
            S16_AT(effect_data, 0x82) = 0;
            U8_AT(display, 0x0E) = 0;
            U8_AT(display, 0x0D) = 0;
            U8_AT(display, 0x0C) = 0;
            goto done;
        }

        S32_AT(effect_pos, 0x00) += S32_AT(effect_pos, 0x0C);
        S32_AT(effect_pos, 0x04) += S32_AT(effect_pos, 0x10);
        S32_AT(effect_pos, 0x08) += S32_AT(effect_pos, 0x14);
        goto done;
    }

state3:
    {
        if (S16_AT(effect_data, 0x92) == 0) {
            S16_AT(effect_data, 0x92) = 1;
            U8_AT(effect_data, 0x9C) += 0x18;
        } else {
            S16_AT(effect_data, 0x92) = 0;
            U8_AT(effect_data, 0x9C) -= 0x18;
        }

        source = func_8003FC64(0x212);
        if (source != 0) {
            register u8 *target_pos ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 trig;

            entity = source + 0x20;
               /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            {
                u16 spawn_count = U16_AT(effect_data, 0x82);
                S16_AT(entity, 0x0A) = 0x80;
                S16_AT(entity, 0x02) = 8 - spawn_count;
            }
            {
                s32 spawn_counter = S16_AT(effect_data, 0x82);
                S16_AT(entity, 0x0C) = spawn_counter << 9;
            }
            target_pos = PTR_AT(PTR_AT(owner, 0x60), -0x18);
            S32_AT(entity, 0x4C) = S32_AT(target_pos, 0x00);
            S32_AT(entity, 0x50) = S32_AT(target_pos, 0x04);
            S32_AT(source, 0x10) = (s32)func_800245A8;
            func_8004491C(source, func_80045340);

            {
                u8 *spawn_display = PTR_AT(source, 0x0C);
                U16_AT(spawn_display, 0x10) = 0x20;
                U16_AT(spawn_display, 0x14) |= 0x0C;
            }
            display = PTR_AT(source, 0x08);

            trig = func_800644B8(S16_AT(entity, 0x0C));
            S32_AT(display, 0x00) = S32_AT(entity, 0x4C) +
                (S16_AT(entity, 0x0A) * trig * 0x10);
            trig = func_80064584(S16_AT(entity, 0x0C));
            S32_AT(display, 0x04) = S32_AT(entity, 0x50) +
                (S16_AT(entity, 0x0A) * trig * 0x10);
            S32_AT(display, 0x08) = S32_AT(effect_pos, 0x08) +
                (D_800DDC40[U8_AT(PTR_AT(owner, 0x60), 0x13)] << 16);

            {
                u8 *spawn_display = PTR_AT(source, 0x0C);
                U16_AT(spawn_display, 0x1E) = 0x1000;
                U16_AT(spawn_display, 0x1C) = 0x1000;
                U8_AT(spawn_display, 0x0E) = 0x14;
                U8_AT(spawn_display, 0x0D) = 0x14;
                U8_AT(spawn_display, 0x0C) = 0x14;
                func_8003DB94(spawn_display, D_800DEAE0, 0);
            }
        }

        S16_AT(effect_data, 0x82)++;
        if (S16_AT(effect_data, 0x82) == 8) {
            S16_AT(effect_data, 0x0A) = 4;
            S16_AT(effect_data, 0x82) = 0;
        }
        goto done;
    }

state4:
    {
        s32 fade_frame;

        U16_AT(effect_data, 0x82)++;
        fade_frame = S16_AT(effect_data, 0x82);
        if (fade_frame < 20) {
            U8_AT(display, 0x0C) = ((20 - S16_AT(effect_data, 0x82)) * 0xE0) / 20;
            U8_AT(display, 0x0D) = ((20 - S16_AT(effect_data, 0x82)) * 0x80) / 20;
            U8_AT(display, 0x0E) = ((20 - S16_AT(effect_data, 0x82)) * 0x80) / 20;

            if (S16_AT(effect_data, 0x92) == 0) {
                S16_AT(effect_data, 0x92) = 1;
                U8_AT(effect_data, 0x9C) += 0x18;
            } else {
                S16_AT(effect_data, 0x92) = 0;
                U8_AT(effect_data, 0x9C) -= 0x18;
            }

            for (entity = 0; (s32)entity < 4; entity++) {
                s32 random = func_80069EF8();
                u8 *task;
                s32 particle_color;
                s32 particle_param;

                task = effect_data - 0x20;
                ASM_KEEP(task);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                particle_color = 0x002020E0;
                ASM_KEEP(particle_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                random &= 0xFF;
                particle_param = random | 0x80;
                D_80024488(task, S16_AT(effect_data, 0x7E), particle_color, particle_param, 0, 0, 0);
            }
        }

        if (S16_AT(effect_data, 0x82) >= 50) {
            u8 *target = PTR_AT(owner, 0x60);
            register u8 *target_display ASM_REG("$5");

            S32_AT(target, 0x1C) |= 0x10000000;
            target_display = PTR_AT(target, -0x14);
            if (S16_AT(effect_data, 0x82) >= 76) {
                U8_AT(target_display, 0x0E) += 3;
                U8_AT(target_display, 0x0D) += 3;
                U8_AT(target_display, 0x0C) -= 4;
            } else {
                U8_AT(target_display, 0x0E) -= 3;
                U8_AT(target_display, 0x0D) -= 3;
                U8_AT(target_display, 0x0C) += 4;
            }
        }

        if (S16_AT(effect_data, 0x82) >= 101) {
            u8 *target = PTR_AT(owner, 0x60);
            register u8 *target_display ASM_REG("$5") = PTR_AT(target, -0x14);

            S32_AT(target, 0x1C) &= 0xEFFFFFFF;
            U8_AT(target_display, 0x0E) = 0x80;
            U8_AT(target_display, 0x0D) = 0x80;
            U8_AT(target_display, 0x0C) = 0x80;
            func_8002407C(PTR_AT(owner, 0x60), U8_AT(effect_data, 0x09), owner);
            S16_AT(effect_data, 0x0A) = 8;
            S16_AT(effect_data, 0x82) = 0x1E;
        }
        goto done;
    }

state8:
    {
        u16 old_frame = U16_AT(effect_data, 0x82);
        s16 next_frame = (s16)(old_frame + 1);

        U16_AT(effect_data, 0x82) = (u16)next_frame;
        if (next_frame >= 31) {
            {
                s32 effect_active = D_80025308[0];
                U16_AT(effect_data, 0x82) = old_frame;
                if (effect_active == 0) {
                    D_8008346C[0] = 0;
                    U16_AT(effect_data, -2) |= 0x8000;
                    D_800814A0[0] |= 0x8000;
                } else {
                    D_80025308[0] = 0;
                }
            }
        }
    }

done:
    (void)keepalive;
}
