#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800A75E4_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800A75E4_0;   /* entry in fukidasi_set */

typedef struct S_800A75E4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800A75E4_1;   /* object in fukidasi_set */

typedef struct S_800A75E4_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A75E4_2;   /* part_data in fukidasi_set */

typedef struct S_800A75E4_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800A75E4_3;   /* part in fukidasi_set */

typedef struct S_800A75E4_4 {
    u8 pad_00[0x50];
    s32 unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
    u8 pad_92[0x3];
    s8 unk_95;
    s8 unk_96;
} S_800A75E4_4;   /* body in fukidasi_set */



typedef struct {
    s32 unk0;
    void *value;
} EntryRecord;

extern void func_80033CD8();
extern void *func_8009C390();
extern s32 D_80045340;
extern EntryRecord D_80082660[];
extern u8 D_800A76F0;
extern s32 D_800D0E24[];
extern s32 D_800D0E3C[];

/* fukidasi_set: create a speech bubble object and initialize its part and body from indexed data. */
void fukidasi_set(s32 entry_index, s32 part_index, s32 body_index, s32 body_value) {
    s32 saved_part_index;
    s32 saved_body_index;
    s32 saved_body_value;
    void *entry_or_body;
    void *entry_data;
    void *object_template;
    S_800A75E4_0 *entry;
    void *object;
    u8 *body;
    S_800A75E4_3 *part;
    s32 *value_slot;
    S_800A75E4_2 *part_data;

    saved_part_index = part_index;
    saved_body_index = body_index;
    saved_body_value = body_value;
    entry_or_body = NULL;
    entry_data = entry_or_body;
    if (entry_index != 0) {
        entry = D_80082660[entry_index].value;
        if (entry != NULL) {
            entry_or_body = entry;
            entry_data = entry->unk_08;
        }
    }
    object_template = &D_800A76F0;

    object = func_8009C390(entry_or_body, entry_data, object_template, 0);
    body = (u8 *)object + 0x20;
    if (object != NULL) {
        S_800A75E4_0 *entry;
        entry_or_body = body;
        ASM_KEEP(entry_or_body);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        entry = D_800D0E24;
        value_slot = (s32 *)(((u32)saved_part_index << 2) + (u32)entry);
        ASM_KEEP(value_slot);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        part = ((S_800A75E4_1 *)object)->unk_08;
        part_data = ((S_800A75E4_1 *)object)->unk_0C;
        part_data->unk_08 = *value_slot;
        func_80033CD8(entry_or_body, &D_80045340, part_data);
        part->unk_0A = part->unk_0A - 0x62;
        ((S_800A75E4_4 *)body)->unk_90 = 0xA;
        ((S_800A75E4_4 *)body)->unk_6C = saved_body_value;
        ((S_800A75E4_4 *)body)->unk_95 = saved_part_index;
        ((S_800A75E4_4 *)body)->unk_96 = saved_body_index;
        ((S_800A75E4_4 *)body)->unk_50 = D_800D0E3C[saved_body_index];
    }
    ASM_KEEP(saved_part_index);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_body_index);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_body_value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(part);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
}
