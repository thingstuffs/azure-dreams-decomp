/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016FC4C_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8016FC4C_0;   /* var_a0 in func_8016FC4C */

typedef struct S_8016FC4C_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016FC4C_1_pre;   /* the 0x14 bytes before temp_v0 in func_8016FC4C, addressed as temp_v0[-1] */

typedef struct S_8016FC4C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016FC4C_2;   /* temp_v1 in func_8016FC4C */

typedef struct S_8016FC4C_3 {
    u8 pad_00[0x94];
    s16 unk_94;
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_8016FC4C_3;   /* arg0 in func_8016FC4C */

typedef struct S_8016FC4C_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8016FC4C_4;   /* temp_s5 in func_8016FC4C */

typedef struct S_8016FC4C_5 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    union { u16 s; volatile u16 u; } unk_1E;   /* accessed as both */
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8016FC4C_5;   /* object in func_8016FC4C */

typedef struct S_8016FC4C_6 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_8016FC4C_6;   /* entity in func_8016FC4C */

typedef struct S_8016FC4C_7 {
    s16 unk_00;
    s16 unk_02;
} S_8016FC4C_7;   /* (u8 *)table_ptr in func_8016FC4C */

typedef struct S_8016FC4C_8 {
    u8 pad_00[0x3228];
    s16 unk_3228;
    u8 pad_322A[0x2B26];
    void * unk_5D50;
} S_8016FC4C_8;   /* (u8 *)common_page in func_8016FC4C */


void func_80047738();
void func_800478B8();
s32 func_80069EF8();
u16 func_800A0818(u8, u8, u8, u8, s32 *);
M2C_UNK func_800A56E0();
M2C_UNK func_80164ED0();
M2C_UNK func_801655EC(void *, s16, s16, s16);
extern u8 D_80082E80[64];
extern s16 D_80083228[8];
extern u8 *D_800E3D7C[3];
extern s16 D_80173AFC[16];
extern void *D_80175D50[3];

/* Updates the effect phases, particle bursts, movement, and directional sprite. */
void func_8016FC4C(void *effect, void *entity_data, void *object_data) {
    M2C_UNK distance;
    s32 burst_y;
    s16 sustain_y;
    s32 direction;
    s16 burst_x;
    s16 sustain_x;
    s32 random_bits;
    s32 count;
    s32 phase_active;
    s32 rounded_step;
    u16 height;
    u16 burst_ticks;
    u16 width;
    u16 sustain_ticks;
    u16 turn_ticks;
    u16 move_ticks;
    s16 turned_angle;
    register u16 angle ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 phase;
    S_8016FC4C_4 *heading;
    S_8016FC4C_6 *entity;
    register S_8016FC4C_5 *object ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *linked_entity;
    S_8016FC4C_2 *linked_object;
    void *link_slot;
    void *shrink_source;
    void *burst_source;
    register u32 common_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u32 table_page;
    u16 table_angle;
    u32 table_ptr;
    u8 turn_phase;

    entity = entity_data;
    object = object_data;
    count = 1;
    heading = D_80175D50[0] + 0x20;
    link_slot = D_800E3D7C[0] + 4;
    do {
        linked_entity = ((S_8016FC4C_0 *)link_slot)->unk_AC;
        if (linked_entity != NULL) {
            linked_object = ((S_8016FC4C_1_pre *)linked_entity)[-1].unk_00;
            linked_object->unk_14 = (u16)(linked_object->unk_14 & 0xFFBF);
        }
        count -= 1;
        link_slot -= 4;
    } while (count >= 0);
    phase = ((S_8016FC4C_3 *)effect)->unk_9A;
    switch (phase) {
    case 0: {
        s32 shrink_step;
        s32 scaled_step;
        heading->unk_2A = func_800A0818(
            object->unk_24, object->unk_25,
            D_80082E80[0x24], D_80082E80[0x25], &distance);
        ((S_8016FC4C_3 *)effect)->unk_96 = (u16)(((S_8016FC4C_3 *)effect)->unk_96 + 1);
        height = object->unk_1E.s;
        height = (u16)(height - 0x14);
        object->unk_1E.s = height;
        width = object->unk_1C;
        scaled_step = object->unk_1E.u;
        width = (u16)(width - 0x14);
        scaled_step <<= 6;
        scaled_step = 0 - scaled_step;
        object->unk_1C = width;
        if (scaled_step < 0) scaled_step += 0xFFF;
        rounded_step = scaled_step;
        count = 0;
        shrink_step = rounded_step >> 0xC;
        shrink_source = effect - 0x20;
        do {
            func_80164ED0(shrink_source, 0xFFFFFF, 0xE, 0, 0, shrink_step);
            count += 1;
            shrink_source = effect - 0x20;
        } while (count < 6);
        if ((s16)((S_8016FC4C_3 *)effect)->unk_96 == 1) func_800A56E0(0xB1);
        phase_active = ((s16)((S_8016FC4C_3 *)effect)->unk_96 < 120);
        goto advance_phase;
    }
    case 1: {
        s32 burst_step;
        s32 scaled_step;
        heading->unk_2A = func_800A0818(
            object->unk_24, object->unk_25,
            D_80082E80[0x24], D_80082E80[0x25], &distance);
        ASM_CLOBBER("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        scaled_step = 0 - (object->unk_1E.s << 6);
        count = 0;
        if (scaled_step < 0) scaled_step += 0xFFF;
        burst_step = scaled_step >> 0xC;
        burst_source = effect - 0x20;
        do {
            func_80164ED0(burst_source, 0xFFFFFF, 0xE, 0, 0, burst_step);
            count += 1;
            burst_source = effect - 0x20;
        } while (count < 6);
        burst_ticks = ((S_8016FC4C_3 *)effect)->unk_96 + 1;
        ((S_8016FC4C_3 *)effect)->unk_96 = burst_ticks;
        if (!(burst_ticks & 1)) {
            burst_x = (func_80069EF8(burst_source) & 0x1F) - 0xF;
            burst_x = (s16)(((s32)burst_x << 16) >> 16);
            burst_y = (s16)((func_80069EF8() & 0x1F) - 0xF);
            func_801655EC(entity, burst_x, burst_y, (s16)((0 - (func_80069EF8() & 0x1F)) - 0xA));
        }
        if (!(((S_8016FC4C_3 *)effect)->unk_96 & 7)) func_800A56E0(0x817);
        phase_active = ((s16)((S_8016FC4C_3 *)effect)->unk_96 < 20);
        goto advance_phase;
    }
    case 2:
        sustain_ticks = ((S_8016FC4C_3 *)effect)->unk_96 + 1;
        ((S_8016FC4C_3 *)effect)->unk_96 = sustain_ticks;
        if (!(sustain_ticks & 7)) func_800A56E0(0x817);
        if (!(((S_8016FC4C_3 *)effect)->unk_96 & 1)) {
            random_bits = func_80069EF8();
            sustain_x = (random_bits & 0x1F) - 0xF;
            sustain_x = (s16)(((s32)sustain_x << 16) >> 16);
            sustain_y = (func_80069EF8() & 0x1F) - 0xF;
            sustain_y = (s16)(((s32)sustain_y << 16) >> 16);
            func_801655EC(entity, sustain_x, sustain_y, (s16)((0 - (func_80069EF8() & 0x1F)) - 0xA));
            goto update_sprite;
        }
        goto update_sprite;
    case 4:
        turn_ticks = ((S_8016FC4C_3 *)effect)->unk_96 + 1;
        ((S_8016FC4C_3 *)effect)->unk_96 = turn_ticks;
        if (((s16)turn_ticks == 3) || ((s16)turn_ticks == 6) || ((s16)turn_ticks == 9) || ((s16)turn_ticks == 0xC)) {
            angle = heading->unk_2A;
            turned_angle = angle - 0x200;
            ASM_KEEP(angle);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
            if (turned_angle < 0) angle = turned_angle + 0x1000;
            else angle = turned_angle;
            heading->unk_2A = angle;
        }
        if ((s16)((S_8016FC4C_3 *)effect)->unk_96 < 0xE) goto update_sprite;
        turn_phase = ((S_8016FC4C_3 *)effect)->unk_9A;
        ASM_KEEP(turn_phase);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        table_page = 0x80170000U;
        ASM_KEEP(table_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ((S_8016FC4C_3 *)effect)->unk_96 = 0U;
        ASM_KEEP(turn_phase);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        turn_phase = (u8)(turn_phase + 1);
        ((S_8016FC4C_3 *)effect)->unk_9A = turn_phase;
        table_angle = heading->unk_2A;
        table_page += 0x3AFC;
        table_ptr = ((table_angle >> 7) & 0x1C);
        table_ptr += table_page;
        entity->unk_0C = (s32)(((S_8016FC4C_7 *)((u8 *)table_ptr))->unk_00 * 0x30000);
        table_ptr = (((u16)heading->unk_2A >> 7) & 0x1C);
        table_ptr += table_page;
        entity->unk_10 = (s32)(((S_8016FC4C_7 *)((u8 *)table_ptr))->unk_02 * 0x30000);
        goto update_sprite;
    case 5:
        entity->unk_00.at00.v = (s32)(entity->unk_00.at00.v + entity->unk_0C);
        entity->unk_04.at00.v = (s32)(entity->unk_04.at00.v + entity->unk_10);
        move_ticks = ((S_8016FC4C_3 *)effect)->unk_96 + 1;
        ((S_8016FC4C_3 *)effect)->unk_96 = move_ticks;
        if ((s16)move_ticks < 6) goto update_sprite;
        ((S_8016FC4C_3 *)effect)->unk_96 = 0U;
        ((S_8016FC4C_3 *)effect)->unk_9A = (u8)(((S_8016FC4C_3 *)effect)->unk_9A + 1);
        goto update_sprite;
    advance_phase:
        if (phase_active != 0) goto update_sprite;
        ((S_8016FC4C_3 *)effect)->unk_9A = (u8)(((S_8016FC4C_3 *)effect)->unk_9A + 1);
        ((S_8016FC4C_3 *)effect)->unk_96 = 0U;
        goto update_sprite;
    case 7:
        object->unk_14 = (u16)(object->unk_14 | 0x80);
        entity->unk_04.at02.v = 1;
        entity->unk_00.at02.v = 1;
        goto update_sprite;
    default:
        goto update_sprite;
    }
update_sprite:
    common_page = 0x80170000;
    ASM_KEEP(common_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (((S_8016FC4C_8 *)((u8 *)common_page))->unk_5D50 != 0) {
        s16 sprite_direction;
        s32 old_direction;
        common_page = 0x80080000U;
        ASM_KEEP(common_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        common_page = (u32)(s32)((S_8016FC4C_8 *)((u8 *)common_page))->unk_3228;
        direction = (((s32)common_page + (s16)heading->unk_2A + 0x100) >> 9) & 7;
        old_direction = ((S_8016FC4C_3 *)effect)->unk_94;
        sprite_direction = direction;
        if (old_direction != sprite_direction) {
            func_80047738(object, *(object->unk_2C + sprite_direction), object->unk_04);
            ((S_8016FC4C_3 *)effect)->unk_94 = direction;
        }
        func_800478B8(object);
    }
}
