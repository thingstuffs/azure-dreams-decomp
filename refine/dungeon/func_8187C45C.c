#include "common.h"

typedef struct {
    s16 x;
    u16 y;
} Point __attribute__((packed));

typedef struct {
    Point p[8];
} PointTable __attribute__((packed));

typedef struct {
    u32 w[3];
} Copy12 __attribute__((packed));

typedef struct {
    u8 pad[0x98];
    Copy12 copy;
} PackedArg0 __attribute__((packed));

typedef struct {
    u8 pad[0x64];
    Copy12 copy;
} PackedSpawn __attribute__((packed));

extern PointTable D_80024074;
extern Copy12 D_80026934;
extern Copy12 D_80026940;
extern s16 D_8002694C[5];
extern u8 D_8007CCD8[];
extern u8 D_8007CCE8[];
extern s32 D_800814A0[3];
extern s32 D_8008346C[3];
extern u8 D_800DDC40[];
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern void *func_8003FC64(s32);
extern s32 func_80069EF8(void);
extern void func_800250B0(void *, s32, u32, u32, s32, s32, s32);
extern void func_800251E8(s32, u32, s32, s32, s32, s32);
extern s32 func_800A4778(u16, u16, s16, void *);
extern void func_800240B8(void *, u8, void *);
extern void func_800A56E0(s32);
extern void *memcpy(void *, const void *, unsigned int);

extern void func_80045340(void);
extern void func_8002569C(void);
extern void func_800257E0(void);
extern void *D_80024098[];

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

/* Update a projectile effect, its trail, and the target hit animation. */
void func_80025C5C(void *effect_data, void *motion_data, void *sprite_data) {
    static void *const dispatch_keepalive[] = {
        &&initialize, &&await_launch, &&move_projectile, &&spawn_impact,
        &&fade_projectile, &&brighten_target, &&animate_target, &&finish_effect
    };
    u16 origin_offset[4];
    PointTable direction_steps;
    void *effect = effect_data;
    void *motion = motion_data;
    void *sprite = sprite_data;
    register void *owner ASM_REG("$20");
    register void *object ASM_REG("$16");
    register void *object_data ASM_REG("$17");
    void *busy_base;
    void *effect_object;
    void *depth_value;
    void *owner_sprite;
    void *direction_offset;
    void *y_velocity;
    void *origin_sprite;
    void *target_data;
    void *z_step;
    register void *offset_value ASM_REG("$3");
    register void *spawn_sprite ASM_REG("$7");
    void *target;
    register void **table_value ASM_REG("$2");
    register PointTable *template_data ASM_REG("$6");
    register u16 next_state ASM_REG("$2");
    u16 render_flags;
    s32 trail_color;
    s32 state_index;
    s32 finish_tick;
    s32 particle_color;
    s32 effect_busy;
    s32 fade_out_tick;
    s32 target_tick;
    s32 blue_scaled;
    s32 green_scaled;
    s32 red_scaled;
    register s32 channel_value ASM_REG("$2");
    s32 owner_z;
    s32 effect_z;
    register s32 z_offset ASM_REG("$3");
    s32 tile_distance;

    table_value = (void **)0x80020000;
    ASM_KEEP(table_value);
    owner = PTR(effect, 0);
    ASM_KEEP(owner);
    template_data = (PointTable *)((u8 *)table_value + 0x4074);
    ASM_KEEP_NV(template_data);
    memcpy(&direction_steps, template_data, 12);
    memcpy((u8 *)&direction_steps + 12, (u8 *)template_data + 12, 12);
    memcpy((u8 *)&direction_steps + 24, (u8 *)template_data + 24, 8);
    ASM_USE_NV(table_value);
    state_index = S16(effect, 0xA);
    ASM_KEEP(state_index);
    object = (u8 *)owner - 0x20;
    object_data = PTR(object, 8);

    if ((u32)state_index >= 8) {
        goto end;
    }
    goto *D_80024098[state_index];

initialize:
    U32(sprite, 0xC) = 0x00808080;
    U16(sprite, 0x1E) = 0x1000;
    U16(sprite, 0x1C) = 0x1000;
    ASM_KEEP(sprite);
    table_value = (void **)0x80020000;
    ASM_KEEP(table_value);
    template_data = (PointTable *)((u8 *)table_value + 0x6934);
    ASM_KEEP_NV(template_data);
    memcpy((u8 *)effect + 0x98, template_data, 12);
    ASM_USE_NV(table_value);
    {
        void *sprite_copy = (u8 *)effect + 0x98;
        ASM_KEEP(sprite_copy);
        busy_base = (void *)0x80020000;
        PTR(sprite, 8) = sprite_copy;
    }
    table_value = (void **)(u32)U16(owner, 0x2A);
    ASM_KEEP_NV(table_value);
    offset_value = (void *)1;
    S16(busy_base, 0x694C) = (u32)offset_value;
    ASM_KEEP(busy_base);
    offset_value = (void *)(u32)U16(effect, 0xA);
    ASM_KEEP_NV(offset_value);
    table_value = (void **)(((u32)table_value >> 9) & 7);
    offset_value = (void *)((u32)offset_value + 1);
    U16(effect, 0x7E) = (u32)table_value;
    U16(effect, 0xA) = (u32)offset_value;

    origin_sprite = PTR(object, 0xC);
    if (func_8003DF74(PTR(origin_sprite, 8), origin_sprite, origin_offset, 0) == 0) {
        if (!(U16(PTR(object, 0xC), 0x14) & 0x8000)) {
            goto end;
        }
    }

    U16(motion, 2) = U16(object_data, 2);
    U16(motion, 6) = U16(object_data, 6);
    owner_z = U16(object_data, 0xA);
    U16(motion, 0xA) = owner_z;
    if (!(U16(PTR(object, 0xC), 0x14) & 0x8000)) {
        U16(motion, 2) = U16(motion, 2) + origin_offset[0];
        U16(motion, 6) = U16(motion, 6) + origin_offset[1];
        ASM_KEEP(motion);
        effect_z = U16(motion, 0xA);
        z_offset = origin_offset[2];
        effect_z += z_offset;
        goto store_z;
    }
    effect_z = owner_z - 0x40;
store_z:
    U16(motion, 0xA) = effect_z;

await_launch:
    if (!(U16(PTR(effect, 4), 0) & 0x80)) {
        goto end;
    }

    if (!(U8(effect, 0x7A) & 4)) {
        effect_object = (u8 *)effect - 0x20;
        func_8004491C(effect_object, func_80045340);
        depth_value = (void *)0x20;
        offset_value = (void *)(u32)U16(sprite, 0x14);
        table_value = (void **)0x80;
        U16(sprite, 0x10) = (u32)depth_value;
        U8(sprite, 0xD) = (u32)table_value;
        U8(sprite, 0xC) = (u32)table_value;
        U8(sprite, 0xE) = (u32)depth_value;
        offset_value = (void *)((u32)offset_value | 0xC);
        U16(sprite, 0x14) = (u32)offset_value;
        U8(effect, 0x7A) |= 4;
    }

    table_value = PTR(owner, 0x60);
    offset_value = (void *)0x10;
    if (table_value != 0) {
        object = PTR(table_value, -0x18);
        U16(effect, 0x74) = U16(object, 2);
        U16(effect, 0x76) = U16(object, 6);
        ASM_KEEP(effect);
        offset_value = PTR(owner, 0x60);
        ASM_KEEP_NV(offset_value);
        table_value = (void **)0x800E0000;
        ASM_KEEP_NV(table_value);
        offset_value = (void *)(u32)U8(offset_value, 0x13);
        table_value = (void **)((u8 *)table_value - 0x23C0);
        offset_value = (u8 *)offset_value + (u32)table_value;
        ASM_KEEP_DEP_NV(offset_value, table_value);
        table_value = (void **)(u32)U8(offset_value, 0);
        offset_value = (void *)(u32)U16(object, 0xA);
        table_value = (void **)((u32)table_value + 0x20);
        offset_value = (void *)((u32)offset_value - (u32)table_value);
        table_value = (void **)0x80070000;
        ASM_KEEP_NV(table_value);
        table_value = (void **)((u8 *)table_value - 0x3328);
        U16(effect, 0x78) = (u32)offset_value;
        offset_value = (void *)(s32)S16(effect, 0x7E);
        ASM_KEEP(offset_value);
        owner_sprite = PTR(owner, -0x14);
        ASM_KEEP(owner_sprite);
        offset_value = (void *)((s32)offset_value * 2);
        offset_value = (u8 *)offset_value + (u32)table_value;
        table_value = (void **)(u32)U8(owner_sprite, 0x24);
        offset_value = (void *)(u32)U8(offset_value, 0);
        table_value = (void **)((u32)table_value + (u32)offset_value);
        U8(effect, 0xA4) = (u32)table_value;

        table_value = (void **)0x80070000;
        ASM_KEEP_NV(table_value);
        offset_value = (void *)(s32)S16(effect, 0x7E);
        table_value = (void **)((u8 *)table_value - 0x3318);
        offset_value = (void *)((s32)offset_value * 2);
        offset_value = (u8 *)offset_value + (u32)table_value;
        table_value = (void **)(u32)U8(owner_sprite, 0x25);
        offset_value = (void *)(u32)U8(offset_value, 0);
        table_value = (void **)((u32)table_value + (u32)offset_value);
        U8(effect, 0xA5) = (u32)table_value;

        {
            s32 owner_axis = S8(owner, 0x72);
            register u32 sprite_axis ASM_REG("$3") = U8(owner_sprite, 0x24);

            if (owner_axis != sprite_axis) {
                tile_distance = owner_axis - sprite_axis;
            } else {
                owner_axis = S8(owner, 0x73);
                sprite_axis = U8(owner_sprite, 0x25);
                tile_distance = owner_axis - sprite_axis;
            }
        }
        if (tile_distance < 0) {
            tile_distance = -tile_distance;
        }
        U8(effect, 0x7B) = tile_distance * 2 - 1;
    } else {
        table_value = (void **)(s32)S16(effect, 0x7E);
        ASM_KEEP(effect);
        direction_offset = (void *)(s32)S16(effect, 0x7E);
        U8(effect, 0x7B) = (u32)offset_value;
        target_data = &direction_steps.p[0];
        ASM_KEEP4_NV(table_value, offset_value, direction_offset, target_data);
        table_value = (void **)((s32)table_value * 4);
        table_value = (void **)((u8 *)target_data + (u32)table_value);
        ASM_KEEP_DEP_NV(table_value, target_data);
        direction_offset = (void *)((s32)direction_offset * 4);
        target_data = (u8 *)target_data + (u32)direction_offset;
        offset_value = (void *)(u32)U16(table_value, 0);
        table_value = (void **)(u32)U16(motion, 2);
        offset_value = (void *)((u32)offset_value << 4);
        table_value = (void **)((u32)table_value + (u32)offset_value);
        U16(effect, 0x74) = (u32)table_value;
        table_value = (void **)(u32)U8(effect, 0x7B);
        offset_value = (void *)(u32)U16(target_data, 2);
        ASM_KEEP4_NV(table_value, offset_value, target_data, effect);
        table_value = (void **)((u32)table_value << 24);
        table_value = (void **)((s32)table_value >> 24);
        U16(effect, 0x76) = U16(motion, 6) +
            (u32)offset_value * (s32)table_value;
        U16(effect, 0x78) = U16(owner, 0x88) - 0x50;
    }

    S32(motion, 0xC) = direction_steps.p[S16(effect, 0x7E)].x << 16;
    S32(motion, 0x10) = direction_steps.p[S16(effect, 0x7E)].y << 16;
    S32(motion, 0x14) = ((S16(effect, 0x78) << 16) - S32(motion, 8)) / S8(effect, 0x7B);
    next_state = U16(effect, 0xA);
    U16(effect, 0x82) = 0;
    ASM_KEEP_NV(next_state);
    goto advance_state;

move_projectile:
    trail_color = 0x60;
trail_loop:
    object = func_8003FC64(0x12);
    object_data = (u8 *)object + 0x20;
    if (object != 0) {
        U16(object_data, 2) = 8;
        U16(object_data, 4) = 8;
        PTR(object, 0x10) = func_8002569C;
        func_8004491C(object, func_80045340);

        spawn_sprite = PTR(object, 0xC);

        offset_value = (void *)(u32)U16(spawn_sprite, 0x14);
        table_value = (void **)0x20;
        U16(spawn_sprite, 0x10) = (u32)table_value;
        offset_value = (void *)((u32)offset_value | 0xC);
        U16(spawn_sprite, 0x14) = (u32)offset_value;
        offset_value = PTR(object, 8);
        U16(offset_value, 2) = U16(motion, 2);
        U16(offset_value, 6) = U16(motion, 6);
        table_value = (void **)(u32)U16(motion, 0xA);
        U16(offset_value, 0xA) = (u32)table_value;
        spawn_sprite = PTR(object, 0xC);
        table_value = (void **)0x1000;
        U16(spawn_sprite, 0x1E) = (u32)table_value;
        U16(spawn_sprite, 0x1C) = (u32)table_value;
        table_value = (void **)0x10;
        U8(spawn_sprite, 0xD) = trail_color;
        U8(spawn_sprite, 0xC) = trail_color;
        U8(spawn_sprite, 0xE) = (u32)table_value;
        U8(object_data, 0x38) = (u32)table_value;
        U8(object_data, 0x37) = trail_color;
        U8(object_data, 0x36) = trail_color;
        table_value = (void **)0x80020000;
        ASM_KEEP(table_value);
        template_data = (PointTable *)((u8 *)table_value + 0x6934);
        ASM_KEEP_NV(template_data);
        memcpy((u8 *)object + 0x64, template_data, 12);
        ASM_USE_NV(table_value);
        PTR(spawn_sprite, 8) = (u8 *)object + 0x64;
        ASM_KEEP(object);
    }

    if ((s16)func_800A4778(U16(motion, 2), U16(motion, 6), S16(motion, 0xA),
                           PTR(owner, 0x60)) != 0) {
        goto collision_hit;
    }

    U8(effect, 0x7B) = U8(effect, 0x7B) - 1;
    if (S8(effect, 0x7B) <= 0) {
        if (PTR(owner, 0x60) != 0) {
            goto reach_target;
        }
        U16(effect, 0xA) = 7;
        U16(effect, 0x82) = 0;
        render_flags = U16(sprite, 0x14);
        U8(sprite, 0xE) = 0;
        U8(sprite, 0xD) = 0;
        U8(sprite, 0xC) = 0;
        goto set_render_flag;
    }

    S32(motion, 0xC) = ((S16(effect, 0x74) << 16) - S32(motion, 0)) / S8(effect, 0x7B);
    S32(motion, 0x10) = ((S16(effect, 0x76) << 16) - S32(motion, 4)) / S8(effect, 0x7B);
    table_value = (void **)(s32)S8(effect, 0x7B);
    offset_value = (void *)(u32)S32(motion, 8);
    depth_value = (void *)(u32)(S16(effect, 0x78) << 16);
    depth_value = (void *)((s32)depth_value - (s32)offset_value);
    depth_value = (void *)((s32)depth_value / (s32)table_value);
    table_value = (void **)(u32)S32(motion, 0);
    offset_value = (void *)(u32)S32(motion, 0xC);
    table_value = (void **)((s32)table_value + (s32)offset_value);
    S32(motion, 0) = (s32)table_value;
    table_value = (void **)(u32)S32(motion, 4);
    offset_value = (void *)(u32)S32(motion, 8);
    *(volatile s32 *)((u8 *)motion + 0x14) = (s32)depth_value;
    y_velocity = (void *)(u32)S32(motion, 0x10);
    z_step = (void *)(u32)S32(motion, 0x14);
    table_value = (void **)((s32)table_value + (s32)y_velocity);
    offset_value = (void *)((s32)offset_value + (s32)z_step);
    S32(motion, 4) = (s32)table_value;
    S32(motion, 8) = (s32)offset_value;
    goto trail_loop;

spawn_impact:
    if (S16(effect, 0x96) == 0) {
        U16(effect, 0x96) = 1;
        U8(effect, 0xA0) = U8(effect, 0xA0) + 0x18;
    } else {
        U16(effect, 0x96) = 0;
        U8(effect, 0xA0) = U8(effect, 0xA0) - 0x18;
    }

    object = func_8003FC64(0x12);
    object_data = (u8 *)object + 0x20;
    if (object != 0) {
        U16(object_data, 2) = 8;
        U16(object_data, 4) = 8;
        U16(object_data, 0xA) = 0x30;
        S16(object_data, 0xC) = -0xDE;
        PTR(object, 0x10) = func_800257E0;
        spawn_sprite = PTR(object, 0xC);
        U16(spawn_sprite, 0x10) = 0x20;
        U16(spawn_sprite, 0x14) |= 0xC;
        offset_value = PTR(object, 8);
        U16(offset_value, 2) = U16(motion, 2);
        U16(offset_value, 6) = U16(motion, 6);
        U16(offset_value, 0xA) = U16(motion, 0xA);
        ASM_SCHED_BARRIER();
        table_value = (void **)0x80020000;
        ASM_KEEP(table_value);
        template_data = (PointTable *)((u8 *)table_value + 0x6940);
        ASM_KEEP_NV(template_data);
        memcpy((u8 *)object + 0x64, template_data, 12);
        ASM_USE_NV(table_value);
        PTR(spawn_sprite, 8) = (u8 *)object + 0x64;
        ASM_KEEP(object);
    }
    U8(effect, 0x92) = 0;
    U8(effect, 0x91) = 0;
    U8(effect, 0x90) = 0;
    U16(effect, 0xA) = 4;
    U16(effect, 0x82) = 0;
    goto end;

fade_projectile:
    {
        u16 next_tick = U16(effect, 0x82) + 1;
        fade_out_tick = (s16)next_tick;
        U16(effect, 0x82) = next_tick;
    }
    if (fade_out_tick >= 0x14) {
        goto finish_fade;
    }

    U8(sprite, 0xC) = ((0x14 - fade_out_tick) * 0xE0) / 0x14;
    U8(sprite, 0xD) = ((0x14 - S16(effect, 0x82)) * 0xE0) / 0x14;
    U8(sprite, 0xE) = ((0x14 - S16(effect, 0x82)) * 0x20) / 0x14;
    if (S16(effect, 0x96) == 0) {
        U16(effect, 0x96) = 1;
        U8(effect, 0xA0) = U8(effect, 0xA0) + 0x18;
    } else {
        U16(effect, 0x96) = 0;
        U8(effect, 0xA0) = U8(effect, 0xA0) - 0x18;
    }

    object_data = 0;
    do {
        object_data = (u8 *)object_data + 1;
        particle_color = func_80069EF8();
        {
            void *task;
            s32 base_color;
            s32 brightness;
            task = (u8 *)effect - 0x20;
            ASM_KEEP(task);
            base_color = 0x0020E0E0;
            ASM_KEEP(base_color);
            particle_color &= 0xFF;
            brightness = particle_color | 0x80;
            ASM_KEEP(brightness);
            func_800250B0(task, S16(effect, 0x7E), base_color, brightness, 0, 0, 0);
        }
    } while ((s32)object_data < 4);
    goto end;

finish_fade:
    next_state = U16(effect, 0xA);
    U16(effect, 0x82) = 0;
    ASM_KEEP_NV(next_state);
    goto advance_state;

brighten_target:
    U16(effect, 0x82) = U16(effect, 0x82) + 1;
    object_data = 0;
    blue_scaled = S16(effect, 0x82) * 0x20;
    channel_value = blue_scaled / 0x28;
    U8(effect, 0x92) = channel_value;
    green_scaled = S16(effect, 0x82) * 8;
    green_scaled = (green_scaled - S16(effect, 0x82)) * 32;
    channel_value = green_scaled / 0x28;
    U8(effect, 0x91) = channel_value;
    red_scaled = S16(effect, 0x82) * 8;
    red_scaled = (red_scaled - S16(effect, 0x82)) * 32;
    channel_value = red_scaled / 0x28;
    U8(effect, 0x90) = channel_value;

    table_value = (void **)0x800E0000;
    ASM_KEEP(table_value);
    offset_value = PTR(owner, 0x60);
    motion = (u8 *)table_value - 0x23C0;
    object = PTR(offset_value, -0x18);
    do {
        template_data = (PointTable *)0x80;
        object_data = (u8 *)object_data + 1;
        ASM_KEEP(object_data);
        particle_color = (U8(effect, 0x92) << 16) + (U8(effect, 0x91) << 8) + U8(effect, 0x90);
        func_800251E8((*(u8 *)((u32)U8(PTR(owner, 0x60), 0x13) + (u32)motion) >> 1) + 4,
                      particle_color, (s32)template_data, S16(object, 2), S16(object, 6),
                      (s16)(U16(object, 0xA) -
                            (*(u8 *)((u32)U8(PTR(owner, 0x60), 0x13) + (u32)motion) >> 1)));
    } while ((s32)object_data < 2);
    if (S16(effect, 0x82) >= 0x28) {
        next_state = U16(effect, 0xA);
        U16(effect, 0x82) = 0;
        goto advance_state;
    }
    goto end;

animate_target:
    {
        u16 next_tick = U16(effect, 0x82) + 1;
        target_tick = (s16)next_tick;
        U16(effect, 0x82) = next_tick;
    }
    object_data = 0;
    if (target_tick >= 0x24) {
        U8(effect, 0x92) = ((0x46 - target_tick) * 0x20) / 0x23;
        U8(effect, 0x91) = ((0x46 - S16(effect, 0x82)) * 0xE0) / 0x23;
        U8(effect, 0x90) = ((0x46 - S16(effect, 0x82)) * 0xE0) / 0x23;
    }

    table_value = (void **)0x800E0000;
    ASM_KEEP(table_value);
    offset_value = PTR(owner, 0x60);
    motion = (u8 *)table_value - 0x23C0;
    object = PTR(offset_value, -0x18);
    do {
        template_data = (PointTable *)0x80;
        object_data = (u8 *)object_data + 1;
        ASM_KEEP(object_data);
        particle_color = (U8(effect, 0x92) << 16) + (U8(effect, 0x91) << 8) + U8(effect, 0x90);
        func_800251E8((*(u8 *)((u32)U8(PTR(owner, 0x60), 0x13) + (u32)motion) >> 1) + 4,
                      particle_color, (s32)template_data, S16(object, 2), S16(object, 6),
                      (s16)(U16(object, 0xA) -
                            (*(u8 *)((u32)U8(PTR(owner, 0x60), 0x13) + (u32)motion) >> 1)));
    } while ((s32)object_data < 2);

    target = PTR(owner, 0x60);
    table_value = (void **)(u32)U32(target, 0x1C);
    offset_value = (void *)0x10000000;
    table_value = (void **)((u32)table_value | (u32)offset_value);
    U32(target, 0x1C) = (u32)table_value;
    table_value = (void **)(s32)S16(effect, 0x82);
    target_data = PTR(target, -0x14);
    if ((s32)table_value >= 0x24) {
        U8(target_data, 0xC) -= 3;
        U8(target_data, 0xD) -= 3;
        U8(target_data, 0xE) += 2;
    } else {
        U8(target_data, 0xC) += 3;
        U8(target_data, 0xD) += 3;
        U8(target_data, 0xE) -= 2;
    }
    if (S16(effect, 0x82) < 0x46) {
        goto end;
    }

    offset_value = PTR(owner, 0x60);
    target_data = PTR(offset_value, -0x14);
    U32(offset_value, 0x1C) &= 0xEFFFFFFF;
    U8(target_data, 0xE) = 0x80;
    U8(target_data, 0xD) = 0x80;
    U8(target_data, 0xC) = 0x80;
    func_800240B8(PTR(owner, 0x60), U8(effect, 9), owner);
    next_state = U16(effect, 0xA);
    U16(effect, 0x82) = 0x14;

advance_state:
    U16(effect, 0xA) = next_state + 1;
    goto end;

finish_effect:
    finish_tick = U16(effect, 0x82);
    U16(effect, 0x82) = finish_tick + 1;
    if ((s16)finish_tick < 0x15) {
        goto end;
    }
    busy_base = (void *)0x80020000;
    ASM_KEEP_NV(busy_base);
    effect_busy = S16(busy_base, 0x694C);
    U16(effect, 0x82) = finish_tick;
    if (effect_busy == 0) {
        table_value = (void **)0x80080000;
        ASM_KEEP_NV(table_value);
        S32(table_value, 0x346C) = 0;
        U16(effect, -2) |= 0x8000;
        offset_value = (void *)0x80080000;
        U32(offset_value, 0x14A0) |= 0x8000;
        goto end;
    }
    goto clear_busy;
collision_hit:
    U16(effect, 0xA) = 7;
    U16(effect, 0x82) = 0;
    render_flags = U16(sprite, 0x14);
set_render_flag:
    render_flags |= 0x80;
    U16(sprite, 0x14) = render_flags;
    goto end;

reach_target:
    ASM_SCHED_BARRIER();
    U16(effect, 0xA) = 3;
    U16(effect, 0x82) = 0;
    table_value = PTR(owner, 0x60);
    object = PTR(table_value, -0x18);
    U16(motion, 2) = U16(object, 2);
    U16(motion, 6) = U16(object, 6);
    U16(motion, 0xA) = U16(effect, 0x78);
    func_800A56E0(0x300);
    goto end;

clear_busy:
    S16(busy_base, 0x694C) = 0;

end:
    return;
}
