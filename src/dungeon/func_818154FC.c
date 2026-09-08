#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_818154FC_0_pre {
    u16 unk_00;
} S_818154FC_0_pre;   /* the 0x2 bytes before arg0 in func_818154FC, addressed as arg0[-1] */

typedef struct S_818154FC_0 {
    void * unk_00;
    u16 * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x72];
    union { s16 s; u16 u; } unk_7E;   /* accessed as both */
    u8 pad_80[0x2];
    u16 unk_82;
    union { u16 s; s16 u; } unk_84;   /* accessed as both */
    s16 unk_86;
    s16 unk_88;
    u8 pad_8A[0x6];
    u8 * unk_90;
    union { void * s; u8 * u; } unk_94;   /* accessed as both */
    u8 pad_98[0x10];
    u8 unk_A8;
    u8 unk_A9;
    u8 pad_AA[0x6];
    s32 unk_B0;
    s32 unk_B4;
    s32 unk_B8;
} S_818154FC_0;   /* arg0 in func_818154FC */

typedef struct S_818154FC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_818154FC_1;   /* temp_s2 in func_818154FC */


typedef struct S_818154FC_3_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_818154FC_3_pre;   /* the 0x14 bytes before temp_s1 in func_818154FC, addressed as temp_s1[-1] */

typedef struct S_818154FC_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    union { s32 s; void * u; u8 * p; } unk_60;   /* accessed as both */
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
} S_818154FC_3;   /* temp_s1 in func_818154FC */

typedef struct S_818154FC_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_818154FC_4;   /* temp_a1 in func_818154FC */

typedef struct S_818154FC_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_818154FC_5;   /* arg1 in func_818154FC */

typedef struct S_818154FC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818154FC_6;   /* temp_s4 in func_818154FC */

typedef struct S_818154FC_7 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x4];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x9];
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x14];
    void * unk_2C;
    s32 unk_30;
    u8 pad_34[0x24];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_818154FC_7;   /* work in func_818154FC */

typedef struct S_818154FC_8 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_818154FC_8;   /* map in func_818154FC */

typedef struct S_818154FC_9 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_818154FC_9;   /* motion in func_818154FC */

typedef struct S_818154FC_10 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_818154FC_10;   /* node in func_818154FC */

typedef struct S_818154FC_11 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818154FC_11;   /* temp_a0_5 in func_818154FC */

typedef struct S_818154FC_12 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_818154FC_12;   /* temp_v1_3 in func_818154FC */

typedef struct S_818154FC_13 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818154FC_13;   /* saved in func_818154FC */

typedef struct S_818154FC_14 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818154FC_14;   /* ((S_818154FC_1 *)temp_s2)->unk_0C in func_818154FC */

typedef struct S_818154FC_15_pre {
    u8 * unk_00;
    u8 pad_04[0x14];
} S_818154FC_15_pre;   /* the 0x18 bytes before ((S_818154FC_3 *)temp_s1)->unk_60.p in func_818154FC, addressed as ((S_818154FC_3 *)temp_s1)->unk_60.p[-1] */


typedef struct {
    u8 bytes[0x20];
} LocalPoints;

typedef struct {
    s16 x;
    u16 y;
} LocalPoint;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Offset;

/* cfail-repair: tf7-phase1-cache-v3 */
extern LocalPoints D_80024004;
extern u8 D_800DEC00[];
extern s16 D_80025338[5];
extern s32 D_8008346C[];
extern s32 D_800814A0[3];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
void func_80024F14() __attribute__((noreturn));     /* extern */
void func_8002512C(void) __attribute__((noreturn));     /* extern */
void func_8002515C(void) __attribute__((noreturn));     /* extern */
void func_80025228(void) __attribute__((noreturn));     /* extern */
void func_800252A8(void) __attribute__((noreturn));     /* extern */
void func_8002530C() __attribute__((noreturn));     /* extern */
s32 func_8003DF74(s32, void *, Offset *, s32);     /* extern */
u8 *func_8003FC64();   /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_800246DC;

/* Updates an effect through attachment, spawning, tracking, and cleanup. */
void func_818154FC(void *effect, S_818154FC_5 *position, Rec_D_80082E80 *sprite) {
    Offset offset;
    LocalPoints points;
    LocalPoint *point_base;
    s32 state;
    register s32 tracking_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 spawn_tick;
    u16 angle;
    u8 *point_table;
    S_818154FC_11 *spawn_position;
    S_818154FC_4 *parent_sprite;
    void *parent;
    S_818154FC_1 *parent_node;
    S_818154FC_6 *parent_position;
    S_818154FC_12 *spawn_sprite;

    parent = ((S_818154FC_0 *)effect)->unk_00;
    point_table = (u8 *)&D_80024004;
    points = *(LocalPoints *)point_table;
    point_base = (LocalPoint *)&points;
    state = ((S_818154FC_0 *)effect)->unk_0A.s;
    parent_node = parent - 0x20;
    parent_position = parent_node->unk_08;
    ((S_818154FC_0 *)effect)->unk_82 = (u16) (((S_818154FC_0 *)effect)->unk_82 + 1);
    if (state == 1) {
        goto update_position;
    }
    if (state < 2) {
        if (state == 0)
            goto initialize;
        func_8002530C();
        return;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    if (state == 2)
        goto spawn_effects;
    if (state == 3) {
        tracking_state = 0x63;
        goto wait_effects;
    }
    func_8002530C();
    return;

initialize:
    sprite->unk_0C.at00_s32.v = 0x00808080;
    sprite->unk_1C.at02_s16.v = 0x1000;
    sprite->unk_1C.at00_s16.v = 0x1000;
    func_8003DB94(sprite, D_800DEC00, 0, sprite);
    angle = ((S_818154FC_3 *)parent)->unk_2A;
    D_80025338[0] = 1;
    ((S_818154FC_0 *)effect)->unk_7E.s = (s16) ((angle >> 9) & 7);
    ((S_818154FC_0 *)effect)->unk_0A.s = (s16) ((u16) ((S_818154FC_0 *)effect)->unk_0A.s + 1);

update_position:
  {
    u16 position_z;
    register u16 final_z ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u16 delta_z ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    parent_sprite = parent_node->unk_0C;
    if ((func_8003DF74(parent_sprite->unk_08, parent_sprite, &offset, 0) != 0) || (((S_818154FC_14 *)(parent_node->unk_0C))->unk_14 & 0x8000)) {
        position->unk_00.at02.v = (u16) parent_position->unk_02;
        position->unk_04.at02.v = (u16) parent_position->unk_06;
        position_z = parent_position->unk_0A;
        position->unk_08.at02.v = position_z;
        if (!(((S_818154FC_14 *)(parent_node->unk_0C))->unk_14 & 0x8000)) {
            position->unk_00.at02.v = (u16) (position->unk_00.at02.v + offset.x);
            position->unk_04.at02.v = (u16) (position->unk_04.at02.v + offset.y);
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            final_z = position->unk_08.at02.v;
            delta_z = offset.z;
            final_z += delta_z;
            ASM_TAILSLOT_PIN(final_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80024F14();
            return;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        final_z = position_z - 0x40;
        position->unk_08.at02.v = final_z;
        {
            register s32 coord ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            coord = position->unk_00.at00.v;
            ((S_818154FC_0 *)effect)->unk_B0 = coord;
            coord = position->unk_04.at00.v;
            ((S_818154FC_0 *)effect)->unk_B4 = coord;
            coord = position->unk_08.at00.v;
            ((S_818154FC_0 *)effect)->unk_B8 = coord;
        }
        if (*((S_818154FC_0 *)effect)->unk_04 & 0x80) {
            ((S_818154FC_0 *)effect)->unk_84.s = 0U;
            ((S_818154FC_0 *)effect)->unk_0A.s = (s16) ((u16) ((S_818154FC_0 *)effect)->unk_0A.s + 1);
            func_800A56E0(0x300);
            func_8002530C();
        }
    }
    goto done;
  }

spawn_effects:
    spawn_tick = ((S_818154FC_0 *)effect)->unk_84.s + 1;
    ((S_818154FC_0 *)effect)->unk_84.s = spawn_tick;
    if (spawn_tick & 1) {
        u8 *node;

        node = func_8003FC64(0x12);
        if (node != NULL) {
            u8 *work;
            u8 *map;
            s32 index;

            work = node + 0x20;
            {
                s16 *entry;

                index = ((S_818154FC_0 *)effect)->unk_7E.s;
                entry = (s16 *)((u8 *)point_base + index * 4);
                ((S_818154FC_7 *)work)->unk_58 = (s32)entry[0] << 16;
            }
            {
                u16 *entry;

                index = ((S_818154FC_0 *)effect)->unk_7E.s;
                entry = (u16 *)((u8 *)point_base + index * 4);
                ((S_818154FC_7 *)work)->unk_5C = (s32)entry[1] << 16;
            }
            ((S_818154FC_7 *)work)->unk_2C = parent;
            ((S_818154FC_7 *)work)->unk_30 = ((S_818154FC_3 *)parent)->unk_60.s;
            ((S_818154FC_7 *)work)->unk_0A =
                (((S_818154FC_0 *)effect)->unk_84.u - 1) / 2;
            ((S_818154FC_7 *)work)->unk_15 = ((S_818154FC_0 *)effect)->unk_09;
            ((S_818154FC_7 *)work)->unk_16 = ((S_818154FC_0 *)effect)->unk_7E.u;

            {
                u8 *table_base = (u8 *)D_8006CCD8;

                index = ((S_818154FC_0 *)effect)->unk_7E.s * 2;
                map = ((S_818154FC_3_pre *)parent)[-1].unk_00;
                ((S_818154FC_0 *)effect)->unk_A8 =
                    ((S_818154FC_8 *)map)->unk_24 + table_base[index];
            }
            {
                u8 *table_base = (u8 *)D_8006CCE8;

                index = ((S_818154FC_0 *)effect)->unk_7E.s * 2;
                ((S_818154FC_0 *)effect)->unk_A9 =
                    ((S_818154FC_8 *)map)->unk_25 + table_base[index];
            }

            if (((S_818154FC_3 *)parent)->unk_60.u != NULL) {
                register s32 tile_distance ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                s32 compare_one;
                u8 *motion;
                register s32 z_step ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                s32 other_z;

                ((S_818154FC_7 *)work)->unk_08 = 1;
                if (((S_818154FC_3 *)parent)->unk_72 !=
                    ((S_818154FC_8 *)map)->unk_24) {
                    tile_distance = ((S_818154FC_3 *)parent)->unk_72 -
                                 ((S_818154FC_8 *)map)->unk_24;
                } else {
                    tile_distance = ((S_818154FC_3 *)parent)->unk_73;
                    tile_distance -= ((S_818154FC_8 *)map)->unk_25;
                }
                if (tile_distance < 0)
                    tile_distance = -tile_distance;
                ((S_818154FC_7 *)work)->unk_02.s = tile_distance * 2;
                ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

                compare_one = 1;
                ASM_KEEP(compare_one);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                motion = ((S_818154FC_15_pre *)(((S_818154FC_3 *)parent)->unk_60.p))[-1].unk_00;
                if (((S_818154FC_0 *)effect)->unk_84.u == compare_one) {
                    s32 duration;

                    duration = ((S_818154FC_7 *)work)->unk_02.s;
                    if (duration != 0) {
                        z_step = ((S_818154FC_9 *)motion)->unk_08;
                        other_z = position->unk_08.at00.v;
                        z_step -= other_z;
                        z_step -= 0x200000;
                        other_z = duration - 1;
                        z_step /= other_z;
                        ((S_818154FC_7 *)work)->unk_60 = z_step;
                        position->unk_14 = z_step;
                        func_8002512C();
                    }
                    goto configure_effect;
                }
                z_step = position->unk_14;
                ((S_818154FC_7 *)work)->unk_60 = z_step;
                func_8002512C();
            } else {
                ((S_818154FC_7 *)work)->unk_02.s = 8;
                ((S_818154FC_7 *)work)->unk_08 = 0;
            }
configure_effect:
            if (((S_818154FC_0 *)effect)->unk_84.u == 9) {
                if (((S_818154FC_3 *)parent)->unk_60.u != NULL) {
                    u16 end_time;

                    end_time = ((S_818154FC_7 *)work)->unk_02.u;
                    end_time += 0x28;
                    ASM_TAILSLOT_PIN(end_time);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    func_8002515C();
                }
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                ((S_818154FC_0 *)effect)->unk_86 = 0x1E;
            }
            spawn_position = ((S_818154FC_10 *)node)->unk_08;
            ((S_818154FC_10 *)node)->unk_10 = &D_800246DC;
            spawn_position->unk_00 = ((S_818154FC_0 *)effect)->unk_B0;
            spawn_position->unk_04 = ((S_818154FC_0 *)effect)->unk_B4;
            spawn_position->unk_08 = ((S_818154FC_0 *)effect)->unk_B8;
            spawn_sprite = ((S_818154FC_10 *)node)->unk_0C;
            spawn_sprite->unk_0E = 0x80;
            spawn_sprite->unk_0D = 0x80;
            spawn_sprite->unk_0C = 0x80;
            spawn_sprite->unk_1E = 0x1000;
            spawn_sprite->unk_1C = 0x1000;
            if ((s16) ((S_818154FC_0 *)effect)->unk_84.s == 1) {
                ((S_818154FC_0 *)effect)->unk_90 = node;
                ((S_818154FC_0 *)effect)->unk_94.s = spawn_position;
                ((S_818154FC_0 *)effect)->unk_88 = 0x63;
            }
            goto follow_effect;
        }
    }
follow_effect:
    if (((S_818154FC_0 *)effect)->unk_88 == 0x63) {
        register u8 *node ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u8 *tracked_position ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        node = ((S_818154FC_0 *)effect)->unk_90;
        tracked_position = ((S_818154FC_0 *)effect)->unk_94.u;
        if (((S_818154FC_10 *)node)->unk_1E & 0x8000) {
            ((S_818154FC_0 *)effect)->unk_88 = 0;
            func_80025228();
        }
        position->unk_00.at00.v = ((S_818154FC_13 *)tracked_position)->unk_00;
        position->unk_04.at00.v = ((S_818154FC_13 *)tracked_position)->unk_04;
        position->unk_08.at00.v = ((S_818154FC_13 *)tracked_position)->unk_08;
        goto finish_spawning;
    }
finish_spawning:
    if ((s16) ((S_818154FC_0 *)effect)->unk_84.s >= 0xB) {
        u16 old_state;

        old_state = ((S_818154FC_0 *)effect)->unk_0A.u;
        ((S_818154FC_0 *)effect)->unk_84.s = 0;
        old_state++;
        ((S_818154FC_0 *)effect)->unk_0A.u = old_state;
        func_8002530C();
    }
    goto done;

wait_effects:
    if (((S_818154FC_0 *)effect)->unk_88 == tracking_state) {
        register u8 *node ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u8 *tracked_position ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        node = ((S_818154FC_0 *)effect)->unk_90;
        tracked_position = ((S_818154FC_0 *)effect)->unk_94.u;
        if (((S_818154FC_10 *)node)->unk_1E & 0x8000) {
            ((S_818154FC_0 *)effect)->unk_88 = 0;
            func_800252A8();
        }
        position->unk_00.at00.v = ((S_818154FC_13 *)tracked_position)->unk_00;
        position->unk_04.at00.v = ((S_818154FC_13 *)tracked_position)->unk_04;
        position->unk_08.at00.v = ((S_818154FC_13 *)tracked_position)->unk_08;
        goto check_timeout;
    }
check_timeout:
  {
    u16 old_counter = ((S_818154FC_0 *)effect)->unk_84.s;
    s16 new_counter = old_counter + 1;

    ((S_818154FC_0 *)effect)->unk_84.s = new_counter;
    if (((S_818154FC_0 *)effect)->unk_86 < new_counter) {
        s32 global_state = D_80025338[0];

        ((S_818154FC_0 *)effect)->unk_84.s = old_counter;
        if (global_state == 0) {
            D_8008346C[0] = 0;
            ((S_818154FC_0_pre *)effect)[-1].unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
            func_8002530C();
        } else {
            D_80025338[0] = 0;
        }
    }
  }

done:
    return;
}
