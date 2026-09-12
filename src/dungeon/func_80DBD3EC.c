#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80174BEC_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174BEC_0_pre;   /* the 0x14 bytes before arg0 in func_80174BEC, addressed as arg0[-1] */

typedef struct S_80174BEC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174BEC_0;   /* arg0 in func_80174BEC */



typedef struct S_80174BEC_3 {
    u8 pad_00[0x24];
    s16 unk_24;
    u8 pad_26[0x3A];
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    u8 pad_6C[0x8];
    s32 unk_74;
    u8 pad_78[0x1E];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
} S_80174BEC_3;   /* motion in func_80174BEC */

typedef struct S_80174BEC_4 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_80174BEC_4;   /* object in func_80174BEC */

typedef struct S_80174BEC_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80174BEC_5;   /* render in func_80174BEC */

typedef struct S_80174BEC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174BEC_6;   /* position in func_80174BEC */

typedef struct S_80174BEC_7 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174BEC_7;   /* map in func_80174BEC */

typedef struct S_80174BEC_8 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    void * unk_60;
} S_80174BEC_8;   /* arg3 in func_80174BEC */



typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u;

typedef struct {
    s16 x;
    u16 y;
} TableEntry;

typedef struct {
    u32 words[4];
} Copy16;

typedef struct {
    u32 words[8];
} __attribute__((packed)) PackedTable;

extern void func_8003DB94(void *, void *, s32);
extern s32 func_8003DE58(void *, void *, Vec3u *, s32);
extern s32 func_8003DF74(void *, void *, Vec3u *, s32);
extern void *func_8003FC64(s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
extern s32 func_80069EF8(void);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_800C857C(void *, void *);

extern s32 D_80045340;
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern s32 D_800DE870;
extern u8 D_80170854[];
extern u8 D_80171040[];
extern u8 D_8017142C[];
extern u8 D_80171E20[];
extern u8 D_801753BC[];
extern u8 D_8017541C[];

/* Spawns directional particles, advances the actor animation, and resets its state after a delay. */
void func_80174BEC(void *state, void *source_pos, void *source_render, void *actor)
{
    Vec3u map_offset;
    PackedTable velocity_table;
    s16 frame;
    s32 coord;

    velocity_table = *(PackedTable *)D_80170854;

    switch (((S_80174BEC_0 *)state)->unk_9B) {
    case 0:
        goto initialize;
    case 1:
        goto spawn_particles;
    case 2:
        goto wait_for_animation;
    case 3:
        goto finish_delay;
    default:
        goto done;
    }

initialize:
    ((Rec_D_800E3D7C *)source_pos)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)source_pos)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)source_pos)->unk_0C.as_s32 = 0;
    ((S_80174BEC_0 *)state)->unk_96.s = 0;
    ((S_80174BEC_0 *)state)->unk_9B++;
    ((Rec_D_80082E80 *)source_render)->unk_14.at00_u16.v &= 0x9FFF;

spawn_particles:
    frame = ((S_80174BEC_0 *)state)->unk_96.u;
    if (frame == 0 || frame == 7) {
        s16 particle_index;

        if (!(((Rec_D_80082E80 *)source_render)->unk_14.at00_u16.v & 0x8000)) {
            func_800A56E0(0x80D);
        }

        particle_index = 0;
        {
            TableEntry *directions;

            directions = (TableEntry *)&velocity_table;
            do {
                void *particle;

                particle = func_8003FD64(0x112, D_80083498);
                if (particle == 0) goto next_particle_1;
                ASM_KEEP_NV(particle);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                {
                    s32 offset_y;
                    s32 velocity_y;
                    register s32 offset_x ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    s32 velocity_x;
                    s32 offset_z;
                    s32 position_y;
                    u8 *position;
                    u8 *render;
                    u8 *motion;
                    u8 *copy_src;
                    u8 *copy_dst;
                    u8 *copy_end;
                    u8 animation;
                    void *map;
                    u32 direction_offset;

                    motion = (u8 *)particle + 0x20;
                    ((S_80174BEC_3 *)motion)->unk_96 = 0x28 - ((S_80174BEC_0 *)state)->unk_96.s;
                    ((S_80174BEC_3 *)motion)->unk_9B = 0;
                    render = ((S_80174BEC_4 *)particle)->unk_0C;
                    ((S_80174BEC_4 *)particle)->unk_10 = D_80171040;

                    copy_src = source_render;
                    copy_dst = render;
                    copy_end = (u8 *)source_render + 0x30;
                    do {
                        *(Copy16 *)copy_dst = *(Copy16 *)copy_src;
                        copy_src += 0x10;
                        copy_dst += 0x10;
                    } while (copy_src != copy_end);

                    ((S_80174BEC_5 *)render)->unk_14 &= 0xFFFC;
                    func_8004491C(particle, &D_80045340);
                    animation = D_8017541C[0];
                    ((S_80174BEC_5 *)render)->unk_2C = D_8017541C;
                    func_80047784(render, animation, 0);

                    position = ((S_80174BEC_4 *)particle)->unk_08;
                    ((S_80174BEC_6 *)position)->unk_02 = ((Rec_D_800E3D7C *)source_pos)->unk_00.at02_u16.v;
                    ((S_80174BEC_6 *)position)->unk_06 = ((Rec_D_800E3D7C *)source_pos)->unk_04.at02_u16.v;
                    ((S_80174BEC_6 *)position)->unk_0A = ((Rec_D_800E3D7C *)source_pos)->unk_08.at02_u16.v;

                    map = ((S_80174BEC_0_pre *)state)[-1].unk_00;
                    if (func_8003DF74(((S_80174BEC_7 *)map)->unk_08, map, &map_offset, 1)) {
                        ((S_80174BEC_6 *)position)->unk_02 += map_offset.x;
                        ((S_80174BEC_6 *)position)->unk_06 += map_offset.y;
                        ((S_80174BEC_6 *)position)->unk_0A += map_offset.z;
                    }

                    offset_x = func_80069EF8() & 0x1F;
                    offset_x -= 0x10;
                    offset_y = func_80069EF8() & 0x1F;
                    offset_y -= 0x10;
                    coord = ((S_80174BEC_6 *)position)->unk_02;
                    coord += offset_x;
                    position_y = ((S_80174BEC_6 *)position)->unk_06 + offset_y;
                    ((S_80174BEC_6 *)position)->unk_02 = coord;
                       /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    ((S_80174BEC_6 *)position)->unk_06 = position_y;
                    offset_z = func_80069EF8() & 0x1F;
                    velocity_x = (s32)(offset_x << 16) >> 4;
                    velocity_y = (s32)(offset_y << 16) >> 4;
                    coord = ((S_80174BEC_6 *)position)->unk_0A;
                    coord -= 0x14;
                    coord += offset_z;
                    ((S_80174BEC_6 *)position)->unk_0A = coord;
                    ((S_80174BEC_3 *)motion)->unk_A4 = velocity_x;
                    ((S_80174BEC_3 *)motion)->unk_A8 = velocity_y;

                    direction_offset = (((S_80174BEC_8 *)actor)->unk_2A.s >> 7) & 0x1C;
                    ((S_80174BEC_3 *)motion)->unk_A4 += (s32)((TableEntry *)((u8 *)directions + direction_offset))->x << 19;
                    direction_offset = (((S_80174BEC_8 *)actor)->unk_2A.s >> 7) & 0x1C;
                    ((S_80174BEC_3 *)motion)->unk_A8 += (u32)((TableEntry *)((u8 *)directions + direction_offset))->y << 19;
                    ((S_80174BEC_3 *)motion)->unk_AC = -((func_80069EF8() & 0x7FFF) * 2);
                    ((S_80174BEC_3 *)motion)->unk_B0 = 0x1000;
                    ((S_80174BEC_5 *)render)->unk_1E = 0x1000;
                    ((S_80174BEC_5 *)render)->unk_1C = 0x1000;
                    ((S_80174BEC_5 *)render)->unk_0E = 0x80;
                    ((S_80174BEC_5 *)render)->unk_0D = 0x80;
                    ((S_80174BEC_5 *)render)->unk_0C = 0x80;
                }
next_particle_1:
                particle_index++;
            } while (particle_index < 5);
        }

        particle_index = 0;
        {
            TableEntry *directions;

            directions = (TableEntry *)&velocity_table;
            do {
                void *particle;

                particle = func_8003FC64(0x212);
                if (particle == 0) goto next_particle_2;
                ASM_KEEP_NV(particle);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                {
                    s32 offset_y;
                    s32 velocity_y;
                    register s32 offset_x ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    s32 velocity_x;
                    s32 offset_z;
                    s32 position_z;
                    s32 position_y;
                    u8 *position;
                    u8 *motion;
                    u8 *render;
                    void *map;
                    u32 direction_offset;

                    motion = (u8 *)particle + 0x20;
                    ((S_80174BEC_3 *)motion)->unk_24 = 0x19 - ((S_80174BEC_0 *)state)->unk_96.s;
                    ((S_80174BEC_4 *)particle)->unk_20 = 0;
                    ((S_80174BEC_4 *)particle)->unk_10 = D_8017142C;
                    func_8004491C(particle, &D_80045340);

                    render = ((S_80174BEC_4 *)particle)->unk_0C;
                    ((S_80174BEC_5 *)render)->unk_14 |= 0x0C;
                    ((S_80174BEC_5 *)render)->unk_10 = 0x60;
                    ((S_80174BEC_5 *)render)->unk_14 |= 2;

                    position = ((S_80174BEC_4 *)particle)->unk_08;
                    ((S_80174BEC_6 *)position)->unk_02 = ((Rec_D_800E3D7C *)source_pos)->unk_00.at02_u16.v;
                    ((S_80174BEC_6 *)position)->unk_06 = ((Rec_D_800E3D7C *)source_pos)->unk_04.at02_u16.v;
                    ((S_80174BEC_6 *)position)->unk_0A = ((Rec_D_800E3D7C *)source_pos)->unk_08.at02_u16.v;

                    map = ((S_80174BEC_0_pre *)state)[-1].unk_00;
                    if (func_8003DE58(((S_80174BEC_7 *)map)->unk_08, map, &map_offset, 1)) {
                        ((S_80174BEC_6 *)position)->unk_02 += map_offset.x;
                        ((S_80174BEC_6 *)position)->unk_06 += map_offset.y;
                        ((S_80174BEC_6 *)position)->unk_0A += map_offset.z;
                    }

                    offset_x = func_80069EF8() & 0x1F;
                    offset_x -= 0x10;
                    offset_y = func_80069EF8() & 0x1F;
                    offset_y -= 0x10;
                    coord = ((S_80174BEC_6 *)position)->unk_02;
                    coord += offset_x;
                    position_y = ((S_80174BEC_6 *)position)->unk_06 + offset_y;
                    ((S_80174BEC_6 *)position)->unk_02 = coord;
                    ((S_80174BEC_6 *)position)->unk_06 = position_y;
                    offset_z = func_80069EF8() & 0x1F;
                    velocity_x = (s32)(offset_x << 16) >> 4;
                    velocity_y = (s32)(offset_y << 16) >> 4;
                    position_z = ((S_80174BEC_6 *)position)->unk_0A;
                    position_z -= 0x14;
                    position_z += offset_z;
                    ((S_80174BEC_6 *)position)->unk_0A = position_z;
                    ((S_80174BEC_3 *)motion)->unk_60 = velocity_x;
                    ((S_80174BEC_3 *)motion)->unk_64 = velocity_y;

                    direction_offset = (((S_80174BEC_8 *)actor)->unk_2A.s >> 7) & 0x1C;
                    ((S_80174BEC_3 *)motion)->unk_60 += (s32)((TableEntry *)((u8 *)directions + direction_offset))->x << 19;
                    direction_offset = (((S_80174BEC_8 *)actor)->unk_2A.s >> 7) & 0x1C;
                    ((S_80174BEC_3 *)motion)->unk_64 += (u32)((TableEntry *)((u8 *)directions + direction_offset))->y << 19;
                    ((S_80174BEC_3 *)motion)->unk_68 = -((func_80069EF8() & 0x7FFF) * 2);
                    ((S_80174BEC_3 *)motion)->unk_74 = 0x400;
                    ((S_80174BEC_5 *)render)->unk_1C = 0x800;
                    ((S_80174BEC_5 *)render)->unk_1E = 0x800;
                    ((S_80174BEC_5 *)render)->unk_0D = 0x80;
                    ((S_80174BEC_5 *)render)->unk_0C = 0x80;
                    ((S_80174BEC_5 *)render)->unk_0E = 0;
                    ((S_80174BEC_5 *)render)->unk_12 = 0x7DCF;
                    ((S_80174BEC_5 *)render)->unk_14 |= 0x100;
                    func_8003DB94(render, &D_800DE870, 0);
                }
next_particle_2:
                particle_index++;
            } while (particle_index < 4);
        }
    }

    ((S_80174BEC_0 *)state)->unk_96.s++;
    if (((Rec_D_80082E80 *)source_render)->unk_14.at00_u16.v & 0xE000) {
        void *active_object;

        ((S_80174BEC_0 *)state)->unk_9B++;
        active_object = ((S_80174BEC_8 *)actor)->unk_60;
        if (active_object != 0) {
            func_800C857C(actor, active_object);
        }
    }
    goto done;

wait_for_animation:
    if (((Rec_D_80082E80 *)source_render)->unk_14.at00_u16.v & 0xE000) {
        s32 direction_index;

        ((Rec_D_800E3D7C *)source_pos)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)source_pos)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)source_pos)->unk_0C.as_s32 = 0;
        func_800A2B04(source_pos, ((Rec_D_80082E80 *)source_render)->unk_24, ((Rec_D_80082E80 *)source_render)->unk_25);
        if (((Rec_D_80082E80 *)source_render)->unk_2C.as_pu8 != D_801753BC) {
            ((Rec_D_80082E80 *)source_render)->unk_2C.as_pu8 = D_801753BC;
            ((Rec_D_80082E80 *)source_render)->unk_14.at00_u16.v &= 0xF7FF;
            direction_index = (D_80083228 + ((S_80174BEC_8 *)actor)->unk_2A.u + 0x100) >> 9;
            func_80047784(source_render, ((Rec_D_80082E80 *)source_render)->unk_2C.as_pu8[direction_index & 7], 0);
            ((S_80174BEC_0 *)state)->unk_96.s = 0x14;
            ((S_80174BEC_0 *)state)->unk_9B++;
        }
    }
    goto done;

finish_delay:
    {
        u16 timer;

        timer = ((S_80174BEC_0 *)state)->unk_96.s;
        ((S_80174BEC_0 *)state)->unk_96.s = timer - 1;
        if ((s16)timer <= 0 || (((Rec_D_80082E80 *)source_render)->unk_14.at00_u16.v & 0xE000)) {
            func_800AD594(actor, 0x1000);
            ((S_80174BEC_0 *)state)->unk_8C = D_80171E20;
            D_8008346C = 0;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        }
    }

done:
    return;
}
