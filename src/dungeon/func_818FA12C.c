#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
extern int abs(int);


typedef struct {
    s16 x;
    u16 y;
} Copy4;

typedef struct {
    Copy4 entries[8];
} __attribute__((packed)) Copy24;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Copy12;

typedef struct {
    s32 a;
    s32 b;
} Pair;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    Pair pair;
} OutPair;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Triple;

extern Copy24 D_80024014;
extern Copy12 D_80026668;
extern Copy12 D_80026674;
extern Copy12 D_80026680;
extern Copy12 D_80026698;
extern Copy12 D_800266A4;
extern s16 D_800266BC[5];
extern u8 D_80025348[12];
extern u8 D_80025398[12];
extern u8 D_8002558C[12];
extern u8 D_80025648[12];
extern u8 D_800E3D68[256];

extern void func_800B835C(void *, void *, s32, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);
extern s32 func_8002512C(void);
extern void func_80025228(void *, s32, s32, s32, s32, s32, s32);
extern s32 func_800A4778(u16, u16, s16, void *);
extern void func_800A56E0(s32);
extern void *func_8003FC64(s32);
extern s32 func_8009D218(void *, s32, void *);
extern s32 func_800A6D30(void);
extern void func_800C8A3C(void *, s32, s32);

typedef struct BaseView {
    u8 pad_00[0x8];
    s16 * unk_08;
    u8 * unk_0C;
} BaseView;

typedef struct PacketView {
    u8 pad_00[0x8];
    u32 unk_08;
    union {
        struct { u32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 v; } at00p;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x1]; u8 v; } at01u;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x2]; u8 v; } at02u;
    } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    union { u16 v; u16 n; } unk_1C;   /* accessed as both */
    union { u16 v; u16 n; } unk_1E;   /* accessed as both */
} PacketView;

typedef struct ParentHead {
    u8 * unk_00;
    u8 pad_04[0x10];
} ParentHead;

typedef struct ParentView {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    union { u8 * p; void * p2; } unk_60;   /* accessed as both */
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} ParentView;

typedef struct ColorsView {
    u8 pad_00[0x10];
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x1];
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
} ColorsView;

typedef struct OutView {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} OutView;

typedef struct TableEntryView {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} TableEntryView;

typedef struct ObjHeadView {
    u8 * unk_00;
} ObjHeadView;

typedef struct SrcView {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} SrcView;

typedef struct ObjDataView {
    u8 pad_00[0x6];
    u16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} ObjDataView;

typedef struct Obj2DataView {
    u8 pad_00[0x6];
    u16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} Obj2DataView;

typedef struct CursorView {
    u8 pad_00[0x38];
    u8 unk_38;
} CursorView;

typedef struct TmpSrcView {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} TmpSrcView;

typedef struct BaseChildView {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} BaseChildView;

typedef struct SelfChildView {
    u16 unk_00;
} SelfChildView;

typedef struct ParentLinkMinus18 {
    u8 * unk_00;
} ParentLinkMinus18;

typedef struct ParentLink {
    u8 pad_00[0x13];
    u8 unk_13;
} ParentLink;

typedef struct ParentLinkMinus14 {
    u8 * unk_00;
} ParentLinkMinus14;

typedef struct EffectObject {
    u8 pad_00[0x8];
    s32 *position;
    u8 *render;
    u32 callback;
    u8 pad_14[0xE];
    u16 unk_22;
    u8 pad_24[0x16];
    Copy12 anim;
} EffectObject;

typedef struct ParticleState {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x4];
    u16 unk_0A;
    u8 pad_0C[0xE];
    Copy12 anim;
    u8 pad_26[0x2];
    void *parent;
    void *target;
    void *source;
    void *flash_state;
    u8 pad_38[0x62];
    u16 unk_9A;
} ParticleState;

typedef struct ProjectileSelf {
    u8 *parent;
    void *owner_data;
    u8 pad_08[0x1];
    u8 unk_09;
    union { u16 u; s16 s; } state;
    u8 pad_0C[0x6C];
    union { u16 u; s16 s; } target_y;
    u8 flags;
    u8 frames_left;
    u8 pad_7C[0x2];
    union { u16 u; s16 s; } direction;
    u8 pad_80[0x2];
    u16 timer;
    u8 pad_84[0x4];
    s16 frames_copy;
    s16 frames_squared;
    u8 pad_8C[0x4];
    union { u16 u; s16 s; } shrinking;
    union { u16 u; s16 s; } pulse_ticks;
    union { u16 u; s16 s; } pulse_period;
    u16 pulse_step;
    u8 pad_98[0x4];
    union { u16 u; s16 s; } unk_9C;
    u8 pad_9E[0x4];
    Copy12 copy12;
    u8 pad_AE[0xC];
    u8 tile_x;
    u8 tile_y;
} ProjectileSelf;

/* Update a projectile effect, spawn impact particles, and advance its cleanup state. */
void func_8002592C(ProjectileSelf *self, u8 *position, void *volatile render_data)
{
    u8 *parent;
    u8 *parent_base;
    u8 *target_pos;
    s16 *origin;
    OutPair out_pair;
    Copy24 velocities;
    s32 state;

    Copy24 *velocity_table;
    EffectObject *impact;
    velocity_table = &D_80024014;
    parent = self->parent;
    velocities = *velocity_table;
    self->state.s;
    parent_base = parent - 0x20;
    state = self->state.s;
    origin = ((BaseView *)parent_base)->unk_08;
    switch (state) {
        s32 index;
        u32 frames_squared;
        s32 *flash_pos;
        s32 flags;
        ParticleState *particle_state;
        s32 angle;

    case 0:
    {
        s32 packed_pos;
        s32 packed_size;
        s32 copy_flags;
        u8 *colors;
        s32 state;
        frames_squared = (s32)(render_data);
        ((PacketView *)(u8 *)frames_squared)->unk_0C.at00.v = 0x00808080;
        packed_pos = 0x1400340;
        copy_flags = 0;
        ASM_KEEP(copy_flags);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        self->copy12 = D_80026698;
        packed_size = 0x400040;
        colors = (u8 *)&D_800266A4;
        ((PacketView *)(u8 *)frames_squared)->unk_08 = (u32)((u8 *)self + 0xA2);
        self->direction.u = (((ParentView *)parent)->unk_2A >> 9) & 7;
        ((ColorsView *)colors)->unk_10 = 0x80;
        ((ColorsView *)colors)->unk_11 = 0x80;
        ((ColorsView *)colors)->unk_12 = 0x80;
        ((ColorsView *)colors)->unk_14 = 4;
        ((ColorsView *)colors)->unk_15 = 4;
        ((ColorsView *)colors)->unk_16 = 4;
        out_pair.pair.a = packed_pos;
        out_pair.pair.b = packed_size;
        func_800B835C(colors, &out_pair.pair, 1, copy_flags);
        state = self->state.u;
        D_800266BC[0] = 1;
        self->state.u = state + 1;
    }

    case 1:
    {
        u8 *target;
        u8 *parent_data;
        u32 step_result;
        s32 height;
        s32 origin_z;
        s8 frames;
        s16 frames_copy;
        u32 target_height;
        s32 tile_distance;
        s32 tile;

        step_result = func_8003DF74(((BaseChildView *)(((BaseView *)parent_base)->unk_0C))->unk_08,
            ((BaseView *)parent_base)->unk_0C, &out_pair, 0);
        if (step_result == 0 && !(((BaseChildView *)(((BaseView *)parent_base)->unk_0C))->unk_14 & 0x8000)) {
            return;
        }
        ((OutView *)position)->unk_00.at02.v = ((TableEntryView *)origin)->unk_02;
        ((OutView *)position)->unk_04.at02.v = ((TableEntryView *)origin)->unk_06;
        origin_z = ((TableEntryView *)origin)->unk_0A;
        ((OutView *)position)->unk_08.at02.v = origin_z;
        if (!(((BaseChildView *)(((BaseView *)parent_base)->unk_0C))->unk_14 & 0x8000)) {
            ((OutView *)position)->unk_00.at02.v += out_pair.x;
            ((OutView *)position)->unk_04.at02.v += out_pair.y;
            ((OutView *)position)->unk_08.at02.v += out_pair.z;
        } else {
            ((OutView *)position)->unk_08.at02.v = origin_z - 0x40;
        }
        if (!(((SelfChildView *)(self->owner_data))->unk_00 & 0x80)) {
            return;
        }
        if (!(self->flags & 4)) {
            func_8004491C((u8 *)self - 0x20, func_80045340);
            frames_squared = (s32)(render_data);
            ((PacketView *)(u8 *)frames_squared)->unk_10 = 0x20;
            ((PacketView *)(u8 *)frames_squared)->unk_0C.at02.v = 0x20;
            ((PacketView *)(u8 *)frames_squared)->unk_0C.at00u.v = 0x20;
            ((PacketView *)(u8 *)frames_squared)->unk_14 |= 0x0C;
            ((PacketView *)(u8 *)frames_squared)->unk_0C.at01.v = 0xE0;
            ((PacketView *)(u8 *)frames_squared)->unk_1E.v = 2000;
            ((PacketView *)(u8 *)frames_squared)->unk_1C.v = 2000;
            ((PacketView *)(u8 *)frames_squared)->unk_14 &= 0xFFFC;
            self->flags |= 4;
            target = ((ParentView *)parent)->unk_60.p;
        } else {
            target = ((ParentView *)parent)->unk_60.p;
        }
        if (target != 0) {
            target_pos = ((ObjHeadView *)(target - 0x18))->unk_00;
            target_height = D_800DDC40[(*(u8 *)((u8 *)target + 0x13))];
            self->target_y.u = ((SrcView *)target_pos)->unk_08.at02.v - (target_height >> 1);
            parent_data = ((ParentHead *)parent)[-1].unk_00;
            self->tile_x = ((ObjDataView *)parent_data)->unk_24
            + ((u8 *)dirStepX)[self->direction.s * 2];
            self->tile_y = ((ObjDataView *)parent_data)->unk_25
            + ((u8 *)dirStepY)[self->direction.s * 2];
            flags = (s8)((ParentView *)parent)->unk_72;
            tile = ((ObjDataView *)parent_data)->unk_24;
            if (flags != tile) {
                flags = flags - tile;
            } else {
                flags = (s8)((ParentView *)parent)->unk_73;
                tile = ((ObjDataView *)parent_data)->unk_25;
                flags = flags - tile;
            }
            tile_distance = abs(flags);
            self->frames_left = tile_distance * 2 - 1;
        } else {
            self->target_y.u = ((ParentView *)parent)->unk_88 - 0x50;
            self->frames_left = 0x20;
        }
        ((OutView *)position)->unk_0C = (s32)velocities.entries[self->direction.s].x << 16;
        ((OutView *)position)->unk_10 = (u32)velocities.entries[self->direction.s].y << 16;
        ((OutView *)position)->unk_14 = (((s32)self->target_y.s << 16)
            - ((OutView *)position)->unk_08.at00.v)
        / (s8)self->frames_left;
        self->timer = 0;
        self->shrinking.u = 0;
        self->pulse_ticks.u = 0;
        self->pulse_period.u = 5;
        self->pulse_step = 200;
        self->state.u++;
        self->frames_copy = (s8)self->frames_left;
        step_result = self->frames_left << 24;
        frames = step_result >> 24;
        frames_copy = frames;
        frames_squared = frames * frames_copy;
        self->frames_squared = frames_squared;
        return;
    }

    case 2:
    {
        s32 random_bits;
        s32 hit_result;
        s16 pulse_ticks;
        s32 shrinking;
        EffectObject *flash;
        u8 *flash_data;
        void *flash_state;
        void *animation;
        u8 *impact_data;
        u8 *clear_cursor;

        index = 0;
        do {
            u8 *emitter;
            s32 direction;
            s32 color;
            s32 intensity;
            random_bits = func_80069EF8();
            emitter = (u8 *)self - 0x20;
            color = 0x40E020;
            intensity = (random_bits & 0xFF) | 0x80;
            direction = self->direction.s;
            func_80025228(emitter, direction, color, intensity, 0, 0, 0);
            index++;
        } while (index < 8);
        hit_result = func_800A4778(((OutView *)position)->unk_00.at02.v, ((OutView *)position)->unk_04.at02.v,
            ((OutView *)position)->unk_08.at02u.v, ((ParentView *)parent)->unk_60.p2);
        if (hit_result << 16) {
            (*(u16 *)((u8 *)self + 0x0A)) = 8;
            (*(u16 *)((u8 *)self + 0x82)) = 0;
            frames_squared = (s32)(render_data);
            ((PacketView *)(u8 *)frames_squared)->unk_0C.at02u.v = 0;
            ((PacketView *)(u8 *)frames_squared)->unk_0C.at01u.v = 0;
            ((PacketView *)(u8 *)frames_squared)->unk_0C.at00p.v = 0;
            return;
        }
        {
            s32 scale_y;
            frames_squared = (s32)(render_data);
            angle = ((PacketView *)(u8 *)frames_squared)->unk_1A;
            angle += 0x400;
            if (angle >= 0x1001) {
                angle -= 0x1000;
            }
            ((PacketView *)(u8 *)frames_squared)->unk_1A = angle;
            shrinking = self->shrinking.s;
            if (shrinking == 0) {
                ((PacketView *)(u8 *)frames_squared)->unk_1C.n += self->pulse_step;
                ((PacketView *)(u8 *)frames_squared)->unk_1E.n += self->pulse_step;
            } else {
                frames_squared = (s32)(render_data);
                ((PacketView *)(u8 *)frames_squared)->unk_1C.n -= self->pulse_step;
                ((PacketView *)(u8 *)frames_squared)->unk_1E.n -= self->pulse_step;
            }
        }
        pulse_ticks = self->pulse_ticks.s + 1;
        self->pulse_ticks.s = pulse_ticks;
        if (pulse_ticks >= self->pulse_period.s) {
            self->pulse_ticks.s = 0;
            self->shrinking.s ^= 1;
        }
        self->frames_left--;
        if ((s8)self->frames_left <= 0) {
            if (((ParentView *)parent)->unk_60.p != 0) {
                self->state.u = 3;
                self->timer = 0;
                target_pos = ((ParentLinkMinus18 *)(((ParentView *)parent)->unk_60.p - 0x18))->unk_00;
                ((OutView *)position)->unk_00.at02.v = ((SrcView *)target_pos)->unk_00.at02.v;
                ((OutView *)position)->unk_04.at02.v = ((SrcView *)target_pos)->unk_04.at02.v;
                ((OutView *)position)->unk_08.at02.v = ((SrcView *)target_pos)->unk_08.at02.v
                - D_800DDC40[((ParentLink *)(((ParentView *)parent)->unk_60.p))->unk_13];
                func_800A56E0(0x300);
                flash = func_8003FC64(0x212);
                if (flash != 0) {
                    flash->unk_22 = 120;
                    flash->callback = (u32)D_80025348;
                    func_8004491C(flash, func_80045340);
                    flash_data = flash->render;
                    ((Obj2DataView *)flash_data)->unk_14 |= 0x0C;
                    ((Obj2DataView *)flash_data)->unk_10 = 0;
                    ((Obj2DataView *)flash_data)->unk_06 = 0;
                    ((Obj2DataView *)flash_data)->unk_14 |= 0x80;
                    target_pos = ((ParentLinkMinus18 *)(((ParentView *)parent)->unk_60.p - 0x18))->unk_00;
                    flash_pos = flash->position;
                    flash_pos[0] = ((SrcView *)target_pos)->unk_00.at00.v;
                    flash_pos[1] = ((SrcView *)target_pos)->unk_04.at00.v;
                    flash_pos[2] = ((SrcView *)target_pos)->unk_08.at00.v;
                    flash_data = flash->render;
                    ((Obj2DataView *)flash_data)->unk_1E = 0x1000;
                    ((Obj2DataView *)flash_data)->unk_1C = 0x1000;
                    ((Obj2DataView *)flash_data)->unk_0E = 0x80;
                    ((Obj2DataView *)flash_data)->unk_0D = 0x80;
                    ((Obj2DataView *)flash_data)->unk_0C = 0x80;
                    flash->anim = D_80026680;
                    ((Obj2DataView *)flash_data)->unk_08 = (u8 *)flash + 0x3A;
                }
                impact = func_8003FC64(0x212);
                if (impact != 0) {
                    particle_state = (ParticleState *)((u8 *)impact + 0x20);
                    index = 95;
                    clear_cursor = (u8 *)particle_state + 95;
                    particle_state->unk_02 = 0x50;
                    particle_state->unk_0A = 0x14;
                    particle_state->unk_04 = 0;
                    particle_state->parent = parent;
                    particle_state->target = ((ParentView *)parent)->unk_60.p2;
                    particle_state->source = self;
                    flash_state = (u8 *)flash + 0x20;
                    particle_state->flash_state = flash_state;
                    for (; index >= 0; index--) {
                        ((CursorView *)clear_cursor)->unk_38 = 0;
                        clear_cursor--;
                    }
                    index = 96;
                    particle_state->unk_9A = 0;
                    impact->callback = (u32)D_80025398;
                    func_8004491C(impact, func_80045340);
                    impact_data = impact->render;
                    ((ObjDataView *)impact_data)->unk_14 = 0x0C;
                    ((ObjDataView *)impact_data)->unk_10.s = index;
                    ((ObjDataView *)impact_data)->unk_06 = 6;
                    ((ObjDataView *)impact_data)->unk_14 |= 0x80;
                    flash_pos = impact->position;
                    flash_pos[0] = ((OutView *)position)->unk_00.at00.v;
                    flash_pos[1] = ((OutView *)position)->unk_04.at00.v;
                    flash_pos[2] = ((OutView *)position)->unk_08.at00.v + 0x400000;
                    impact_data = impact->render;
                    ((ObjDataView *)impact_data)->unk_1C = 0x2000;
                    ((ObjDataView *)impact_data)->unk_1E = 0x1800;
                    ((ObjDataView *)impact_data)->unk_0E = 0;
                    ((ObjDataView *)impact_data)->unk_0D = 0;
                    ((ObjDataView *)impact_data)->unk_0C = 0;
                    particle_state->anim = D_80026674;
                    animation = (u8 *)particle_state + 0x1A;
                    ((ObjDataView *)impact_data)->unk_08 = animation;
                }
            } else {
                self->state.u = 8;
                self->timer = 0;
            }
            frames_squared = (u32)render_data;
            ((PacketView *)((u8 *)frames_squared))->unk_0C.at02u.v = 0;
            ((PacketView *)((u8 *)frames_squared))->unk_0C.at01u.v = 0;
            ((PacketView *)((u8 *)frames_squared))->unk_0C.at00p.v = 0;
            ((PacketView *)((u8 *)frames_squared))->unk_1E.n = 0;
            ((PacketView *)((u8 *)frames_squared))->unk_1C.n = 0;
            return;
        }
        ((OutView *)position)->unk_00.at00.v += ((OutView *)position)->unk_0C;
        ((OutView *)position)->unk_04.at00.v += ((OutView *)position)->unk_10;
        ((OutView *)position)->unk_08.at00.v += ((OutView *)position)->unk_14;
        return;
    }

    case 3:
    {
        s16 ticks;
        u8 *flash_data;
        u8 *clear_cursor;
        s32 render_flags;

        ticks = self->timer + 1;
        self->timer = ticks;
        if ((s16)ticks != 4) {
            return;
        }
        impact = func_8003FC64(0x212);
        if (impact != 0) {
            particle_state = (ParticleState *)((u8 *)impact + 0x20);
            index = 95;
            particle_state->parent = parent;
            particle_state->target = ((ParentView *)parent)->unk_60.p2;
            particle_state->source = self;
            clear_cursor = (u8 *)particle_state + 95;
            for (; index >= 0; index--) {
                ((CursorView *)clear_cursor)->unk_38 = 0;
                clear_cursor--;
            }
            particle_state->unk_9A = 0;
            impact->callback = (u32)D_80025648;
            func_8004491C(impact, func_80045340);
            flash_data = impact->render;
            render_flags = ((ObjDataView *)flash_data)->unk_14 & 0xFFF3;
            ((ObjDataView *)flash_data)->unk_14 = render_flags;
            ((ObjDataView *)flash_data)->unk_10.u = 0x20;
            ((ObjDataView *)flash_data)->unk_14 = render_flags | 0x80;
            target_pos = ((ParentLinkMinus18 *)(((ParentView *)parent)->unk_60.p - 0x18))->unk_00;
            flash_pos = impact->position;
            flash_pos[0] = ((SrcView *)target_pos)->unk_00.at00.v;
            flash_pos[1] = ((SrcView *)target_pos)->unk_04.at00.v;
            flash_pos[2] = ((SrcView *)target_pos)->unk_08.at00.v;
            flash_data = impact->render;
            ((ObjDataView *)flash_data)->unk_1E = 0x1000;
            ((ObjDataView *)flash_data)->unk_1C = 0x1000;
            ((ObjDataView *)flash_data)->unk_0E = 0x80;
            ((ObjDataView *)flash_data)->unk_0D = 0x80;
            ((ObjDataView *)flash_data)->unk_0C = 0x80;
            particle_state->anim = D_80026668;
            ((ObjDataView *)flash_data)->unk_08 = (u8 *)particle_state + 0x1A;
        }
        if ((s16)self->timer != 4) {
            return;
        }
        self->state.u = 4;
        self->timer = 0;
        self->unk_9C.u = 0;
        return;
    }

    case 4:
    {
        s16 ticks;
        u8 *particle_data;
        u8 *target_data;
        s32 random_bonus;
        s32 amount;
        s32 offset_radius;
        s32 height_random;
        s32 offset_sign;
        s16 effect_kind;
        s32 power_bonus;

        ticks = self->timer + 1;
        self->timer = ticks;
        if (!((ticks & 3) != 0 || (s16)ticks >= 80)) {
            impact = func_8003FC64(0x212);
            if (impact != 0) {
                particle_state = (ParticleState *)((u8 *)impact + 0x20);
                particle_state->unk_02 = 20;
                particle_state->unk_0A = 10;
                particle_state->unk_04 = 0;
                impact->callback = (u32)D_8002558C;
                func_8004491C(impact, func_80045340);
                particle_data = impact->render;
                ((ObjDataView *)particle_data)->unk_10.u = 0x20;
                ((ObjDataView *)particle_data)->unk_14 |= 0x0C;
                target_pos = ((ParentLinkMinus18 *)(((ParentView *)parent)->unk_60.p - 0x18))->unk_00;
                flash_pos = impact->position;
                offset_radius = func_80069EF8();
                offset_sign = func_8002512C();
                offset_radius &= 0x1F;
                offset_radius += 16;
                frames_squared = (u32)((u8 *)(offset_radius * offset_sign));
                angle = (s32)((u8 *)frames_squared) << 16;
                flash_pos[0] = ((SrcView *)target_pos)->unk_00.at00.v + angle;
                offset_radius = func_80069EF8();
                offset_sign = func_8002512C();
                offset_radius &= 0x1F;
                offset_radius += 16;
                frames_squared = (u32)((u8 *)(offset_radius * offset_sign));
                angle = (s32)((u8 *)frames_squared) << 16;
                flash_pos[1] = ((SrcView *)target_pos)->unk_04.at00.v + angle;
                height_random = func_80069EF8();
                flash_pos[2] = ((SrcView *)target_pos)->unk_08.at00.v
                - (D_800DDC40[((ParentView *)parent)->unk_60.p[0x13]] << 15)
                - ((height_random & 0x1F) << 16);
                particle_data = impact->render;
                target_data = ((ParentLinkMinus14 *)(((ParentView *)parent)->unk_60.p - 0x14))->unk_00;
                ((ObjDataView *)particle_data)->unk_1C = ((TmpSrcView *)target_data)->unk_1C >> 1;
                ((ObjDataView *)particle_data)->unk_1E = ((TmpSrcView *)target_data)->unk_1E >> 1;
                ((ObjDataView *)particle_data)->unk_0E = 0;
                ((ObjDataView *)particle_data)->unk_0D = 0;
                ((ObjDataView *)particle_data)->unk_0C = 0;
                impact->anim = D_80026668;
                ((ObjDataView *)particle_data)->unk_08 = (u8 *)impact + 0x3A;
            }
        }
        if ((s16)self->timer == 80) {
            if (func_8009D218(((ParentView *)parent)->unk_60.p2, 4, parent) == 0) {
                random_bonus = func_800A6D30();
                power_bonus = self->unk_09 >> 2;
                random_bonus = (random_bonus & 3) + 4;
                amount = power_bonus + random_bonus;
                if (D_800E3D68[0] == 0xFF) {
                    effect_kind = 0xFF;
                } else {
                    effect_kind = 16;
                }
                func_800C8A3C(((ParentView *)parent)->unk_60.p2, effect_kind, amount);
            }
        }
        if ((s16)self->timer < 120) {
            return;
        }
        self->state.u++;
        self->timer = 0;
        return;
    }

    case 5:
    {
        if (self->unk_9C.s == 0) {
            return;
        }
    }

        self->state.u++;
        self->timer = 0;
        return;

    case 6:
    {
        s16 ticks;
        ticks = self->timer + 1;
        self->timer = ticks;
        if ((s16)ticks < 11) {
            return;
        }
        self->state.u = 8;
        self->timer = 30;
        return;
    }

    case 8:
    {
        s16 ticks;
        s32 effect_active;
        ticks = self->timer;
        self->timer = ticks + 1;
        if ((s16)(ticks + 1) < 31) {
            return;
        }
        effect_active = D_800266BC[0];
        self->timer = ticks;
        if (effect_active == 0) {
            dungeonStatus.unk_0C = 0;
            (*(u16 *)((u8 *)self + -2)) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
            return;
        }
        D_800266BC[0] = 0;
        return;
    }

    case 7:
    default:
        return;
    }

    return;
}
