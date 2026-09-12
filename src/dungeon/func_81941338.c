#include "common.h"

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Packed12;

extern volatile void *jtbl_80024048[];
__asm__(".set jtbl_80024048, 0x80024048");
extern void *D_800814A8[4];
extern u8 D_80082E80[32];
extern u8 D_80083780[32];
extern D_80083460_t D_80083460;
extern u8 D_8002492C[16];
extern u8 D_80025704[16];
extern u8 D_80025710[16];
extern u16 D_8002571C[8];
extern u8 D_80045340[16];
extern u8 D_800256EC[16];
extern u8 D_800DED28[];
extern u8 D_800DEB28[];
extern u8 D_800DE870[];
extern s32 D_800814A0[];

extern s32 func_800249F0(void *, void *, void *, void *, s32, s32, s32, s32);
extern s32 func_800243D8(void *, void *, void *);
extern s32 func_800B8FC8(void *, void *, void *, s32, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern s32 func_80069EF8(void);
extern s32 func_80024798(void *, s32, s32, s32, s32, s32, s32);
extern void *func_8003FC64(s32);
extern s32 func_8004491C(void *, void *);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern void func_8003DB94(void *, void *, void *);
extern void func_800256AC(void) __attribute__((noreturn));
extern void func_80024FC4() __attribute__((noreturn));
extern void func_80025228() __attribute__((noreturn));
extern void func_8002555C() __attribute__((noreturn));
extern u8 D_800248B8;

/* Updates a dungeon effect, spawning particles and fading the actor model through its states. */
void func_81941338(void *effect, void *effect_pos, void *effect_data)
{
    register void *effect_base ASM_REG("$21") = effect;
    void *position = effect_pos;
    register void *effect_context ASM_REG("$18") = effect_data;
    static void *const state_labels[] = { &&init, &&wait_ready, &&emit_trail, &&emit_burst, &&finish };
    s32 enabled;
    void *sprite;
    void *particle;
    u8 *world_offset;
    u8 *spawn_data;
    u8 *particle_script;
    s32 particle_index;
    s32 initial_color;
    s32 particle_color;
    s32 particle_alpha;
    register void *init_object ASM_REG("$4");
    register void *init_data ASM_REG("$5");
    s32 state;
    s16 timer;
    u16 old_state;
    s32 particle_level;
    s32 particle_x;
    s16 texture_rect[6];
    s32 component;
    register u32 bits ASM_REG("$2");

    ASM_KEEP_NV(effect_base);

    F(effect_base, u16, 0x2A) = (u16)(F(effect_base, u16, 0x2A) + 1);
    state = F(effect_base, s16, 0xA);
    effect_context = effect_data;
    if ((u32)state >= 5) {
        return;
    }
    (void)state_labels;
    goto *jtbl_80024048[(u32)state];

init:
    enabled = 1;
    initial_color = 0x00808080;
    F(D_800814A8[0], s32, 0xF4) = 0;
    F(D_80082E80, u16, 6) = 6;
    F(effect_base, void *, 0x64) = func_800249F0(effect_base, position, effect_context, D_80025704,
                                                enabled, 0x1000, 0x1000, initial_color);
    F(effect_base, void *, 0x68) = func_800249F0(effect_base, position, effect_context, D_80025710,
                                                2, 0xE00, 0xE00, 0x00E0E0E0);
    old_state = F(effect_base, u16, 0xA);
    F(D_8002571C, u16, 0) = (u16)enabled;
    F(effect_base, u16, 0xA) = (u16)(old_state + 1);

wait_ready:
    if ((F(F(effect_base, void *, 4), u16, 0) & 0x80) == 0) {
        return;
    }
    init_object = effect_base;
    {
        void *actor = D_800814A8[0];
        bits = 0x14;
        F(effect_base, u16, 0x20) = (u16)bits;
        F(actor, u16, 0xA6) = (u16)(F(actor, u16, 0xA6) - 1);
        F(actor, u8, 0xA8) = F(effect_base, u8, 8);
    }
    component = F(D_800814A8[0], u16, 0x2A);
    F(effect_base, u16, 0xA) = (u16)(F(effect_base, u16, 0xA) + 1);
    F(effect_base, u16, 0x26) = (u16)component;
    func_800243D8(init_object, position, effect_context);
    if (F(effect_base, void *, 0x68) != 0) {
        texture_rect[0] = 0x340;
        texture_rect[1] = 0x100;
        texture_rect[2] = 0x40;
        texture_rect[3] = 0x40;
        texture_rect[4] = 0x360;
        texture_rect[5] = 0x120;
        func_800B8FC8(F(effect_base, void *, 0x68), texture_rect, &texture_rect[4], 0, 1);
    }
    if (F(effect_base, void *, 0x64) == 0) {
        return;
    }
    {
        texture_rect[0] = 0x340;
        texture_rect[1] = 0x100;
        texture_rect[2] = 0x40;
        texture_rect[3] = 0x40;
        texture_rect[4] = 0x360;
        texture_rect[5] = 0x120;
        func_800B8FC8(F(effect_base, void *, 0x64), texture_rect, &texture_rect[4], 1, 1);
    }
    func_800256AC();

emit_trail:
    timer = (s16)((u16)F(effect_base, u16, 0x20) - 1);
    F(effect_base, u16, 0x20) = (u16)timer;
    if (timer <= 0) {
        F(effect_base, u16, 0x20) = 0x10;
        F(effect_base, u16, 0xA) = (u16)(F(effect_base, u16, 0xA) + 1);
    }
    if (F(effect_base, s16, 0x20) == 0x13) {
        if (func_80053EF0(4) != 2) {
            func_800A56E0(0x300);
        } else {
            func_800A56E0(0x4300);
        }
    }
    if (F(effect_base, s16, 0x20) >= 11) {
        goto emit_flash;
    }
    {
        u8 *dungeon = D_80082E80;
        if (func_8003DF74(F(dungeon, void *, 8), dungeon,
                          (u8 *)effect_base + 0xC, 0) == 0) {
            goto emit_flash;
        }
    }
    particle_index = 0;
    do {
        bits = (u32)func_80069EF8();
        particle_color = 0x200000;
        ASM_KEEP_NV(particle_color);
        bits &= 0x7F;
        particle_alpha = (s32)(bits | 0x60);
        particle_level = F(effect_base, s16, 0x26);
        particle_x = F(effect_base, s16, 0xC);
        particle_color |= 0x20F0;
        func_80024798((u8 *)D_800814A8[0] - 0x20,
                      particle_level, particle_color,
                      particle_alpha,
                      particle_x, F(effect_base, s16, 0xE),
                      F(effect_base, s16, 0x10));
        particle_index++;
    } while (particle_index < 4);
    particle_index = 0;
    spawn_data = D_8002492C;
    world_offset = D_80083780;
    effect_context = 0x80;
    do {
        particle = func_8003FC64(0x212);
        if (particle != 0) {
            F(particle, s16, 0x4A) = 8;
            F(particle, void *, 0x10) = spawn_data;
            func_8004491C(particle, D_80045340);
            sprite = F(particle, void *, 0xC);
            F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 0xC);
            position = F(particle, void *, 8);
            if ((func_80069EF8() & 1) == 0) {
                F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 1);
            }
            F(position, u16, 2) = F(effect_base, u16, 0xC);
            F(position, u16, 6) = F(effect_base, u16, 0xE);
            F(position, u16, 0xA) = F(effect_base, u16, 0x10);
            F(position, u16, 2) = (u16)(F(position, u16, 2) + F(world_offset, u16, 2));
            F(position, u16, 6) = (u16)(F(position, u16, 6) + F(world_offset, u16, 6));
            F(position, u16, 0xA) = (u16)(F(position, u16, 0xA) + F(world_offset, u16, 0xA));
            if (particle_index != 0) {
                bits = (u32)func_80069EF8() & 0x1F;
                component = F(position, u16, 2);
                component -= 0x10;
                component += bits;
                F(position, u16, 2) = (u16)component;
                bits = (u32)func_80069EF8() & 0x1F;
                component = F(position, u16, 6);
                component -= 0x10;
                component += bits;
                F(position, u16, 6) = (u16)component;
                bits = (u32)func_80069EF8() & 0x1F;
                component = F(position, u16, 0xA);
                component -= 0x10;
                component += bits;
                F(position, u16, 0xA) = (u16)component;
            }
            sprite = F(particle, void *, 0xC);
            {
                register void *anim_sprite ASM_REG("$4") = sprite;
                if (particle_index != 0) {
                    register void *animation ASM_REG("$5") = D_800DED28;
                    register void *anim_context ASM_REG("$6") = 0;
                    ASM_USE2(animation, anim_context);
                    bits = 0x20;
                    F(sprite, u16, 0x10) = (u16)bits;
                    F(sprite, u16, 0x1E) = 0x1000;
                    F(sprite, u16, 0x1C) = 0x1000;
                    return func_80024FC4(anim_sprite, animation, anim_context);
                } else {
                    register void *animation ASM_REG("$5") = D_800DEB28;
                    register void *anim_context ASM_REG("$6") = 0;
                    ASM_USE2(animation, anim_context);
                    F(sprite, u16, 0x1E) = 0x2000;
                    F(sprite, u16, 0x1C) = 0x2000;
                    ASM_SCHED_BARRIER();
                    bits = 0x20;
                    F(sprite, u16, 0x10) = (u16)bits;
                    ASM_SCHED_BARRIER();
                    func_8003DB94(anim_sprite, animation, anim_context);
                }
            }
            F(sprite, u8, 0xE) = (u8)effect_context;
            F(sprite, u8, 0xD) = (u8)effect_context;
            F(sprite, u8, 0xC) = (u8)effect_context;
        }
        particle_index++;
    } while (particle_index < 4);
    if (F(effect_base, s16, 0x20) < 6) {
        F(effect_base, s16, 0x18) =
            (F(effect_base, s16, 0xC) + F(effect_base, s16, 0x12)) / 2;
        F(effect_base, s16, 0x1A) =
            (F(effect_base, s16, 0xE) + F(effect_base, s16, 0x14)) / 2;
        F(effect_base, s16, 0x1C) =
            (F(effect_base, s16, 0x10) + F(effect_base, s16, 0x16)) / 2;
        particle_index = 0;
        do {
            bits = (u32)func_80069EF8();
            particle_color = 0x200000;
            ASM_KEEP_NV(particle_color);
            bits &= 0x7F;
            particle_alpha = (s32)(bits | 0x60);
            particle_level = F(effect_base, s16, 0x26);
            particle_x = F(effect_base, s16, 0x18);
            particle_color |= 0x20F0;
            func_80024798((u8 *)D_800814A8[0] - 0x20,
                          particle_level, particle_color,
                          particle_alpha,
                          particle_x, F(effect_base, s16, 0x1A),
                          F(effect_base, s16, 0x1C));
            particle_index++;
        } while (particle_index < 4);
        particle_index = 0;
        spawn_data = D_8002492C;
        world_offset = D_80083780;
        effect_context = 0x80;
        do {
            particle = func_8003FC64(0x212);
            if (particle != 0) {
                F(particle, s16, 0x4A) = 8;
                F(particle, void *, 0x10) = spawn_data;
                func_8004491C(particle, D_80045340);
                sprite = F(particle, void *, 0xC);
                F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 0xC);
                position = F(particle, void *, 8);
                if ((func_80069EF8() & 1) == 0) {
                    F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 1);
                }
                F(position, u16, 2) = F(effect_base, u16, 0x18);
                F(position, u16, 6) = F(effect_base, u16, 0x1A);
                F(position, u16, 0xA) = F(effect_base, u16, 0x1C);
                F(position, u16, 2) = (u16)(F(position, u16, 2) + F(world_offset, u16, 2));
                F(position, u16, 6) = (u16)(F(position, u16, 6) + F(world_offset, u16, 6));
                F(position, u16, 0xA) = (u16)(F(position, u16, 0xA) + F(world_offset, u16, 0xA));
                if (particle_index != 0) {
                    bits = (u32)func_80069EF8() & 0xF;
                    component = F(position, u16, 2);
                    component -= 8;
                    component += bits;
                    F(position, u16, 2) = (u16)component;
                    bits = (u32)func_80069EF8() & 0xF;
                    component = F(position, u16, 6);
                    component -= 8;
                    component += bits;
                    F(position, u16, 6) = (u16)component;
                    bits = (u32)func_80069EF8() & 0x1F;
                    component = F(position, u16, 0xA);
                    component -= 0x10;
                    component += bits;
                    F(position, u16, 0xA) = (u16)component;
                }
                sprite = F(particle, void *, 0xC);
                ASM_KEEP_NV(sprite);
                {
                    register void *anim_sprite ASM_REG("$4") = sprite;
                    if (particle_index != 0) {
                        register void *animation ASM_REG("$5") = D_800DED28;
                        register void *anim_context ASM_REG("$6") = 0;
                        ASM_USE2(animation, anim_context);
                        bits = 0x20;
                        F(anim_sprite, u16, 0x10) = (u16)bits;
                        F(anim_sprite, u16, 0x1E) = 0x1000;
                        F(anim_sprite, u16, 0x1C) = 0x1000;
                        return func_80025228(anim_sprite, animation, anim_context);
                    } else {
                        register void *animation ASM_REG("$5") = D_800DEB28;
                        register void *anim_context ASM_REG("$6") = 0;
                        ASM_USE2(animation, anim_context);
                        F(anim_sprite, u16, 0x1E) = 0x2000;
                        F(anim_sprite, u16, 0x1C) = 0x2000;
                        ASM_SCHED_BARRIER();
                        bits = 0x20;
                        F(anim_sprite, u16, 0x10) = (u16)bits;
                        F(anim_sprite, u8, 0xE) = (u8)effect_context;
                        F(anim_sprite, u8, 0xD) = (u8)effect_context;
                        F(anim_sprite, u8, 0xC) = (u8)effect_context;
                        func_8003DB94(anim_sprite, animation, anim_context);
                    }
                }
            }
            particle_index++;
        } while (particle_index < 4);
    }
    {
        bits = F(effect_base, u16, 0xC);
        component = F(effect_base, u16, 0xE);
        effect = F(effect_base, u16, 0x10);
        F(effect_base, u16, 0x12) = (u16)bits;
        F(effect_base, u16, 0x14) = (u16)component;
        F(effect_base, u16, 0x16) = (u16)effect;
    }
emit_flash:
    if (F(effect_base, s16, 0x20) != 11) {
        return;
    }
    particle = func_8003FC64(0x212);
    if (particle == 0) {
        return;
    }
    init_object = particle;
    init_data = D_80045340;
    ASM_KEEP_NV(init_data);
    F(particle, s16, 0x4A) = 6;
    ASM_SCHED_BARRIER();
    bits = (u32)&D_800248B8;
    F(particle, void *, 0x10) = (void *)bits;
    func_8004491C(init_object, init_data);
    bits = 0x20;
    sprite = F(particle, void *, 0xC);
    {
        void *actor_position;
        F(sprite, u16, 0x10) = (u16)bits;
        F(sprite, u16, 6) = 8;
        actor_position = D_800814A8[0];
        F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 0xC);
        position = F(particle, void *, 8);
        actor_position = F(actor_position, void *, -24);
        F(position, u32, 0) = F(actor_position, u32, 0);
        F(position, u32, 4) = F(actor_position, u32, 4);
        F(position, u32, 8) = F(actor_position, u32, 8);
    }
    {
        u8 *dungeon = D_80082E80;
        if (func_8003DF74(F(dungeon, void *, 8), dungeon,
                          (u8 *)effect_base + 0xC, 0) != 0) {
            F(position, u32, 0) += (u32)(F(effect_base, s16, 0xC) << 16);
            F(position, u32, 4) += (u32)(F(effect_base, s16, 0xE) << 16);
            F(position, u32, 8) += (u32)(F(effect_base, s16, 0x10) << 16);
        }
    }
    sprite = F(particle, void *, 0xC);
    F(sprite, u16, 0x1E) = 0x80;
    F(sprite, u16, 0x1C) = 0x80;
    F(sprite, u8, 0xE) = 0x80;
    F(sprite, u8, 0xD) = 0x80;
    F(sprite, u8, 0xC) = 0x80;
    *(Packed12 *)((u8 *)particle + 146) = *(Packed12 *)D_800256EC;
    F(sprite, void *, 8) = (u8 *)particle + 146;
    func_800256AC();

emit_burst:
    if (F(effect_base, s16, 0x20) < 13) {
        goto fade_model;
    }
    particle_index = 0;
    particle_script = D_8002492C;
    spawn_data = D_80082E80;
    world_offset = D_80083780;
    effect_context = 0x80;
    do {
        particle = func_8003FC64(0x212);
        if (particle != 0) {
            init_object = particle;
            init_data = D_80045340;
            ASM_KEEP_NV(init_data);
            effect_context = (u8 *)particle + 0x20;
            F(effect_context, s16, 0x2A) = 12;
            F(particle, void *, 0x10) = particle_script;
            func_8004491C(init_object, init_data);
            sprite = F(particle, void *, 0xC);
            F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 0xC);
            F(sprite, u16, 0x10) = 0x60;
            if ((func_80069EF8() & 1) == 0) {
                F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 1);
            }
            position = F(particle, void *, 8);
            if (func_8003DF74(F(spawn_data, void *, 8), spawn_data, (u8 *)effect_base + 0xC, 0) != 0) {
                F(effect_base, u16, 0xC) = (u16)(F(effect_base, u16, 0xC) + F(world_offset, u16, 2));
                F(effect_base, u16, 0xE) = (u16)(F(effect_base, u16, 0xE) + F(world_offset, u16, 6));
                F(effect_base, u16, 0x10) = (u16)(F(effect_base, u16, 0x10) + F(world_offset, u16, 0xA));
                if (particle_index != 0) {
                    F(effect_context, s16, 0x2A) = 8;
                    F(sprite, u16, 0x10) = 0x20;
                    bits = (u32)func_80069EF8() & 0x3F;
                    component = F(effect_base, u16, 0xC);
                    component -= 0x20;
                    component += bits;
                    F(effect_base, u16, 0xC) = (u16)component;
                    bits = (u32)func_80069EF8() & 0x3F;
                    component = F(effect_base, u16, 0xE);
                    component -= 0x20;
                    component += bits;
                    F(effect_base, u16, 0xE) = (u16)component;
                    bits = (u32)func_80069EF8() & 0x3F;
                    component = F(effect_base, u16, 0x10);
                    component -= 0x20;
                    component += bits;
                    F(effect_base, u16, 0x10) = (u16)component;
                }
            }
            F(position, u16, 2) = F(effect_base, u16, 0xC);
            F(position, u16, 6) = F(effect_base, u16, 0xE);
            F(position, u16, 0xA) = F(effect_base, u16, 0x10);
            sprite = F(particle, void *, 0xC);
            F(sprite, u16, 0x1E) = 0x1000;
            F(sprite, u16, 0x1C) = 0x1000;
            F(sprite, u8, 0xE) = 0x80;
            F(sprite, u8, 0xD) = 0x80;
            F(sprite, u8, 0xC) = 0x80;
            if (particle_index != 0) {
                register void *anim_sprite ASM_REG("$4") = sprite;
                void *animation = D_800DEB28;
                ASM_TAILSLOT_PIN(animation);
                return func_8002555C(anim_sprite, animation);
            } else {
                func_8003DB94(sprite, D_800DE870, 0);
            }
        }
        particle_index++;
    } while (particle_index < 4);

fade_model:
    {
        register void *actor_model ASM_REG("$5") = F(D_800814A8[0], void *, 0x60);
        s32 fade;
        if (actor_model != 0) {
            F(actor_model, u32, 0x1C) |= 0x10000000;
            {
                register void *model_color ASM_REG("$6") = F(actor_model, void *, -20);
                fade = F(effect_base, s16, 0x20) * 0x7F;
                if (fade < 0) {
                    fade += 15;
                }
                F(model_color, s8, 0xC) = (s8)((fade >> 4) - 0x80);
                fade = (16 - F(effect_base, s16, 0x20)) << 3;
                F(model_color, s8, 0xE) = (s8)fade;
                F(model_color, s8, 0xD) = (s8)fade;
            }
        }
    }
    if ((F(D_80082E80, u16, 0x14) & 0x8000) == 0) {
        F(effect_base, u16, 0x20) = (u16)(F(effect_base, u16, 0x20) - 1);
        if (F(effect_base, s16, 0x20) >= 0) {
            return;
        }
    }
    F(effect_base, u16, 0xA) = 4;
    func_800256AC();

finish:
    if (F(D_8002571C, s16, 0) == 0) {
        void *actor_model =
            F(D_800814A8[0], void *, 0x60);
        register s32 neutral_color ASM_REG("$4");
        if (actor_model != 0) {
            bits = (u32)0xEFFFFFFF;
            neutral_color = 0x00808080;
            component = (s32)F(actor_model, u32, 0x1C);
            particle_color = (s32)F(actor_model, void *, -20);
            component &= (s32)bits;
            F(actor_model, u32, 0x1C) = (u32)component;
            F((void *)particle_color, u32, 0xC) = (u32)neutral_color;
        }
        {
            D_80083460_t *dungeon_state = &D_80083460;
            bits = dungeon_state->fieldA;
            F(dungeon_state, u32, 0xC) = 0;
            F(D_80082E80, u16, 6) = 0;
            dungeon_state->fieldA = (u16)(bits - 1);
        }
        F(effect_base, u16, -2) = (u16)(F(effect_base, u16, -2) | 0x8000);
        D_800814A0[0] |= 0x8000;
        func_800256AC();
    }
    F(D_8002571C, s16, 0) = 0;
}
