#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Packed12;

extern u8 D_8002492C[16];
extern u8 D_80025704[16];
extern u8 D_80025710[16];
extern u16 D_8002571C[8];
extern u8 D_800256EC[16];
extern u8 D_800DED28[];
extern u8 D_800DEB28[];
extern u8 D_800DE870[];

extern s32 func_800249F0(void *, void *, void *, void *, s32, s32, s32, s32);
extern s32 func_800243D8(void *, void *, void *);
extern s32 func_800B8FC8(void *, void *, void *, s32, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern s32 func_80069EF8(void);
extern s32 func_80024798(void *, s32, s32, s32, s16, s16, s16);
extern void *func_8003FC64(s32);
extern s32 func_8004491C(void *, void *);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern void func_8003DB94(void *, void *, void *);
extern u8 D_800248B8;

static __inline__ u8 particle_alpha_from_random(s32 random_bits)
{
    return (random_bits & 0x7F) | 0x60;
}

static __inline__ void *prepare_burst(void *p, void *script, void *animation) {
    void *tail = (u8 *)p + 0x20;
    F(tail, s16, 0x2A) = 12;
    F(p, void *, 0x10) = script;
    func_8004491C(p, animation);
    return tail;
}

/* Updates a dungeon effect, spawning particles and fading the actor model through its states. */
void func_81941338(void *effect, void *effect_pos, void *effect_data)
{
    void *position = effect_pos;
    register void *effect_context ASM_REG("$18") = effect_data;
    u32 neutral_color;
    void *model_color;
    void *animation_m;
    s32 enabled;
    void *sprite;
    void *particle;
    EntityRec *world_offset;
    u8 *spawn_data;
    u8 *particle_script;
    s32 particle_index;
    s32 initial_color;
    s32 particle_color;
    s32 particle_alpha;
    void *init_object;
    s32 state;
    s16 timer;
    u16 old_state;
    s32 particle_level;
    s32 particle_x;
    s16 texture_rect[6];
    s32 component;
    u32 bits;
    u32 bits_2;
    u32 mode_a = 0;
    u32 mode_b = 0;
    u32 mode_c = 0;

    F(effect, u16, 0x2A) = (u16)(F(effect, u16, 0x2A) + 1);
    state = F(effect, s16, 0xA);
    effect_context = effect_data;
    switch (state) {
    case 0:
        enabled = 1;
        initial_color = 0x00808080;
        F(D_800814A8, s32, 0xF4) = 0;
        F(((u8 *)(&D_80082E80)), u16, 6) = 6;
        F(effect, void *, 0x64) = func_800249F0(effect, position, effect_context, D_80025704,
                                                     enabled, 0x1000, 0x1000, initial_color);
        F(effect, void *, 0x68) = func_800249F0(effect, position, effect_context, D_80025710,
                                                     2, 0xE00, 0xE00, 0x00E0E0E0);
        old_state = F(effect, u16, 0xA);
        F(D_8002571C, u16, 0) = (u16)enabled;
        F(effect, u16, 0xA) = (u16)(old_state + 1);

    case 1:
        if ((F(F(effect, void *, 4), u16, 0) & 0x80) == 0) {
            return;
        }
        init_object = effect;
        {
            void *actor = D_800814A8;
            F(effect, u16, 0x20) = (u16)((u32)(0x14));
            F(actor, u16, 0xA6) = (u16)(F(actor, u16, 0xA6) - 1);
            F(actor, u8, 0xA8) = F(effect, u8, 8);
        }
        component = F(D_800814A8, u16, 0x2A);
        F(effect, u16, 0xA) = (u16)(F(effect, u16, 0xA) + 1);
        F(effect, u16, 0x26) = (u16)component;
        func_800243D8(init_object, position, effect_context);
        if (F(effect, void *, 0x68) != 0) {
            texture_rect[0] = 0x340;
            texture_rect[1] = 0x100;
            texture_rect[2] = 0x40;
            texture_rect[3] = 0x40;
            texture_rect[4] = 0x360;
            texture_rect[5] = 0x120;
            func_800B8FC8(F(effect, void *, 0x68), texture_rect, &texture_rect[4], 0, 1);
        }
        if (F(effect, void *, 0x64) == 0) {
            return;
        }
        {
            texture_rect[0] = 0x340;
            texture_rect[1] = 0x100;
            texture_rect[2] = 0x40;
            texture_rect[3] = 0x40;
            texture_rect[4] = 0x360;
            texture_rect[5] = 0x120;
            func_800B8FC8(F(effect, void *, 0x64), texture_rect, &texture_rect[4], 1, 1);
        }
        return;

    case 2:
        timer = (s16)((u16)F(effect, u16, 0x20) - 1);
        F(effect, u16, 0x20) = (u16)timer;
        if (timer <= 0) {
            F(effect, u16, 0x20) = 0x10;
            F(effect, u16, 0xA) = (u16)(F(effect, u16, 0xA) + 1);
        }
        if (F(effect, s16, 0x20) == 0x13) {
            if (func_80053EF0(4) != 2) {
                func_800A56E0(0x300);
            } else {
                func_800A56E0(0x4300);
            }
        }
        if (F(effect, s16, 0x20) < 11) {
            u8 *dungeon = ((u8 *)(&D_80082E80));
            if (func_8003DF74(F(dungeon, void *, 8), dungeon,
                              (u8 *)effect + 0xC, 0) != 0) {
                particle_index = 0;
                do
                {
                    bits = (u32)func_80069EF8();
                    particle_color = 0x200000;
                    particle_alpha = particle_alpha_from_random(bits);
                    particle_level = F(effect, s16, 0x26);
                    particle_x = F(effect, s16, 0xC);
                    particle_color |= 0x20F0;
                    func_80024798((u8 *)D_800814A8 - 0x20,
                                  particle_level, particle_color,
                                  particle_alpha,
                                  particle_x, F(effect, s16, 0xE),
                                  F(effect, s16, 0x10));
                    particle_index++;
                }
                while (particle_index < 4);
                particle_index = 0;
                spawn_data = D_8002492C;
                world_offset = &D_80083780;
                effect_context = 0x80;
                do {
                    particle = func_8003FC64(0x212);
                    if (particle != 0) {
                        F(particle, s16, 0x4A) = 8;
                        F(particle, void *, 0x10) = spawn_data;
                        func_8004491C(particle, func_80045340);
                        sprite = F(particle, void *, 0xC);
                        F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 0xC);
                        position = F(particle, void *, 8);
                        if ((func_80069EF8() & 1) == 0) {
                            F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 1);
                        }
                        F(position, u16, 2) = F(effect, u16, 0xC);
                        F(position, u16, 6) = F(effect, u16, 0xE);
                        F(position, u16, 0xA) = F(effect, u16, 0x10);
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
                            void *anim_sprite = sprite;
                            if (particle_index != 0) {
                                void *animation = D_800DED28;
                                void *anim_context = 0;
                                mode_c = 0x20;
                                F(sprite, u16, 0x10) = mode_c;
                                F(sprite, u16, 0x1E) = 0x1000;
                                F(sprite, u16, 0x1C) = 0x1000;
                                func_8003DB94(anim_sprite, animation, anim_context);
                            } else {
                                void *animation = D_800DEB28;
                                void *anim_context = 0;
                                F(sprite, u16, 0x1E) = 0x2000;
                                F(sprite, u16, 0x1C) = 0x2000;
                                F(sprite, u16, 0x10) = (u16)0x20;
                                func_8003DB94(anim_sprite, animation, anim_context);
                            }
                        }
                        F(sprite, u8, 0xE) = (u8)effect_context;
                        F(sprite, u8, 0xD) = (u8)effect_context;
                        F(sprite, u8, 0xC) = (u8)effect_context;
                    }
                    particle_index++;
                } while (particle_index < 4);
                if (F(effect, s16, 0x20) < 6) {
                    F(effect, s16, 0x18) =
                        (F(effect, s16, 0xC) + F(effect, s16, 0x12)) / 2;
                    F(effect, s16, 0x1A) =
                        (F(effect, s16, 0xE) + F(effect, s16, 0x14)) / 2;
                    F(effect, s16, 0x1C) =
                        (F(effect, s16, 0x10) + F(effect, s16, 0x16)) / 2;
                    particle_index = 0;
                    do {
                        bits = (u32)func_80069EF8();
                        particle_color = 0x200000;
                        particle_alpha = particle_alpha_from_random(bits);
                        particle_level = F(effect, s16, 0x26);
                        particle_x = F(effect, s16, 0x18);
                        particle_color |= 0x20F0;
                        func_80024798((u8 *)D_800814A8 - 0x20,
                                      particle_level, particle_color,
                                      particle_alpha,
                                      particle_x, F(effect, s16, 0x1A),
                                      F(effect, s16, 0x1C));
                        particle_index++;
                    } while (particle_index < 4);
                    particle_index = 0;
                    spawn_data = D_8002492C;
                    world_offset = &D_80083780;
                    effect_context = 0x80;
                    do
                    {
                        particle = func_8003FC64(0x212);
                        if (particle != 0) {
                            F(particle, s16, 0x4A) = 8;
                            F(particle, void *, 0x10) = spawn_data;
                            func_8004491C(particle, func_80045340);
                            sprite = F(particle, void *, 0xC);
                            F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 0xC);
                            position = F(particle, void *, 8);
                            if ((func_80069EF8() & 1) == 0) {
                                F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 1);
                            }
                            F(position, u16, 2) = F(effect, u16, 0x18);
                            F(position, u16, 6) = F(effect, u16, 0x1A);
                            F(position, u16, 0xA) = F(effect, u16, 0x1C);
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
                                sprite = F(particle, void *, 0xC);
                            } else {
                                sprite = F(particle, void *, 0xC);
                            }
                            {
                                neutral_color = (s32)(sprite);
                                if (particle_index != 0) {
                                    void *animation = D_800DED28;
                                    void *anim_context = 0;
                                    mode_a = 0x20;
                                    F((void *)neutral_color, u16, 0x10) = mode_a;
                                    F((void *)neutral_color, u16, 0x1E) = 0x1000;
                                    F((void *)neutral_color, u16, 0x1C) = 0x1000;
                                    F((void *)neutral_color, u8, 0xE) = (u8)effect_context;
                                    F((void *)neutral_color, u8, 0xD) = (u8)effect_context;
                                    F((void *)neutral_color, u8, 0xC) = (u8)effect_context;
                                    func_8003DB94((void *)neutral_color, animation, anim_context);
                                } else {
                                    void *animation = D_800DEB28;
                                    void *anim_context = 0;
                                    F((void *)neutral_color, u16, 0x1E) = 0x2000;
                                    F((void *)neutral_color, u16, 0x1C) = 0x2000;
                                    mode_b = 0x20;
                                    F((void *)neutral_color, u16, 0x10) = mode_b;
                                    F((void *)neutral_color, u8, 0xE) = (u8)effect_context;
                                    F((void *)neutral_color, u8, 0xD) = (u8)effect_context;
                                    F((void *)neutral_color, u8, 0xC) = (u8)effect_context;
                                    func_8003DB94((void *)neutral_color, animation, anim_context);
                                }
                            }
                        }
                        particle_index++;
                    }
                    while (particle_index < 4);
                }
                {
                    bits = F(effect, u16, 0xC);
                    component = F(effect, u16, 0xE);
                    neutral_color = F(effect, u16, 0x10);
                    F(effect, u16, 0x12) = (u16)bits;
                    F(effect, u16, 0x14) = (u16)component;
                    F(effect, u16, 0x16) = (u16)neutral_color;
                }
            }
        }

        if (F(effect, s16, 0x20) != 11) {
            return;
        }
        particle = func_8003FC64(0x212);
        if (particle == 0) {
            return;
        }
        init_object = particle;
        animation_m = func_80045340;
        F(particle, s16, 0x4A) = 6;
        F(particle, void *, 0x10) = (void *)((u32)&D_800248B8);
        func_8004491C(init_object, animation_m);
        bits = 0x20;
        sprite = F(particle, void *, 0xC);
        {
            void *actor_position;
            F(sprite, u16, 0x10) = (u16)bits;
            F(sprite, u16, 6) = 8;
            actor_position = D_800814A8;
            F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 0xC);
            position = F(particle, void *, 8);
            actor_position = F(actor_position, void *, -24);
            F(position, u32, 0) = F(actor_position, u32, 0);
            F(position, u32, 4) = F(actor_position, u32, 4);
            F(position, u32, 8) = F(actor_position, u32, 8);
        }
        {
            u8 *dungeon = ((u8 *)(&D_80082E80));
            if (func_8003DF74(F(dungeon, void *, 8), dungeon,
                              (u8 *)effect + 0xC, 0) != 0) {
                F(position, u32, 0) += (u32)(F(effect, s16, 0xC) << 16);
                F(position, u32, 4) += (u32)(F(effect, s16, 0xE) << 16);
                F(position, u32, 8) += (u32)(F(effect, s16, 0x10) << 16);
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
        return;

    case 3:
        if (F(effect, s16, 0x20) >= 13) {
            particle_index = 0;
            particle_script = D_8002492C;
            spawn_data = ((u8 *)(&D_80082E80));
            world_offset = &D_80083780;
            effect_context = 0x80;
            do {
                particle = func_8003FC64(0x212);
                if (particle != 0) {
                    effect_context = prepare_burst(particle, particle_script, func_80045340);
                    sprite = F(particle, void *, 0xC);
                    F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 0xC);
                    F(sprite, u16, 0x10) = 0x60;
                    if ((func_80069EF8() & 1) == 0) {
                        F(sprite, u16, 0x14) = (u16)(F(sprite, u16, 0x14) | 1);
                    }
                    position = F(particle, void *, 8);
                    if (func_8003DF74(F(spawn_data, void *, 8), spawn_data, (u8 *)effect + 0xC, 0) != 0) {
                        F(effect, u16, 0xC) = (u16)(F(effect, u16, 0xC) + F(world_offset, u16, 2));
                        F(effect, u16, 0xE) = (u16)(F(effect, u16, 0xE) + F(world_offset, u16, 6));
                        F(effect, u16, 0x10) = (u16)(F(effect, u16, 0x10) + F(world_offset, u16, 0xA));
                        if (particle_index != 0) {
                            F(effect_context, s16, 0x2A) = 8;
                            F(sprite, u16, 0x10) = 0x20;
                            bits = (u32)func_80069EF8() & 0x3F;
                            component = F(effect, u16, 0xC);
                            component -= 0x20;
                            component += bits;
                            F(effect, u16, 0xC) = (u16)component;
                            bits = (u32)func_80069EF8() & 0x3F;
                            component = F(effect, u16, 0xE);
                            component -= 0x20;
                            component += bits;
                            F(effect, u16, 0xE) = (u16)component;
                            bits = (u32)func_80069EF8() & 0x3F;
                            component = F(effect, u16, 0x10);
                            component -= 0x20;
                            component += bits;
                            F(effect, u16, 0x10) = (u16)component;
                        }
                    }
                    F(position, u16, 2) = F(effect, u16, 0xC);
                    F(position, u16, 6) = F(effect, u16, 0xE);
                    F(position, u16, 0xA) = F(effect, u16, 0x10);
                    sprite = F(particle, void *, 0xC);
                    F(sprite, u16, 0x1E) = 0x1000;
                    F(sprite, u16, 0x1C) = 0x1000;
                    F(sprite, u8, 0xE) = 0x80;
                    F(sprite, u8, 0xD) = 0x80;
                    F(sprite, u8, 0xC) = 0x80;
                    if (particle_index != 0) {
                        func_8003DB94(sprite, D_800DEB28, 0);
                    } else {
                        func_8003DB94(sprite, D_800DE870, 0);
                    }
                }
                particle_index++;
            } while (particle_index < 4);
        }
        {
            s32 fade;
            animation_m = F(D_800814A8, void *, 0x60);
            if (animation_m != 0) {
                F(animation_m, u32, 0x1C) |= 0x10000000;
                {
                    model_color = F(animation_m, void *, -20);
                    fade = F(effect, s16, 0x20) * 0x7F;
                    if (fade < 0) {
                        fade += 15;
                    }
                    F(model_color, s8, 0xC) = (s8)((fade >> 4) - 0x80);
                    fade = (16 - F(effect, s16, 0x20)) << 3;
                    F(model_color, s8, 0xE) = (s8)fade;
                    F(model_color, s8, 0xD) = (s8)fade;
                }
            }
        }
        if ((F(((u8 *)(&D_80082E80)), u16, 0x14) & 0x8000) == 0) {
            F(effect, u16, 0x20) = (u16)(F(effect, u16, 0x20) - 1);
            if (F(effect, s16, 0x20) >= 0) {
                return;
            }
        }
        F(effect, u16, 0xA) = 4;
        return;

    case 4:
        if (F(D_8002571C, s16, 0) == 0) {
            animation_m = F(D_800814A8, void *, 0x60);
            if (animation_m != 0) {
                bits = (u32)0xEFFFFFFF;
                neutral_color = 0x00808080;
                component = (s32)F(animation_m, u32, 0x1C);
                model_color = F(animation_m, void *, -20);
                component &= (s32)bits;
                F(animation_m, u32, 0x1C) = (u32)component;
                F(model_color, u32, 0xC) = (u32)neutral_color;
            }
            {
                DungeonGlobalStatus *dungeon_state = &dungeonStatus;
                bits_2 = ((u16)dungeon_state->unk_0A);
                F(dungeon_state, u32, 0xC) = 0;
                F(((u8 *)(&D_80082E80)), u16, 6) = 0;
                dungeon_state->unk_0A = (u16)(bits_2 - 1);
            }
            F(effect, u16, -2) = (u16)(F(effect, u16, -2) | 0x8000);
            objectFlagBlock.flags |= 0x8000;
            return;
        }
        F(D_8002571C, s16, 0) = 0;
    }
}
