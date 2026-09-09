#include "common.h"

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

extern s32 func_8009CFE0(void *, void *);
extern void func_80033D08(void *arg0);
extern s32 func_800644B8(s32 angle);
extern s32 func_80064584(s32 angle);

typedef struct {
    s32 unused;
    void *record;
} D_80082660_entry;

extern s32 D_800814A0[3];
extern D_80082660_entry D_80082660[];

typedef struct S_func_800AA760_0 {
    u8 pad_00[0x60];
    u8 unk_60;
    u8 pad_61[0x37];
    s8 *unk_98;
} S_func_800AA760_0;

typedef struct S_func_800AA760_1 {
    u8 pad_00[2];
    s16 unk_02;
    u8 pad_04[2];
    s16 unk_06;
    u8 pad_08[2];
    s16 unk_0A;
} S_func_800AA760_1;

typedef struct S_func_800AA760_2 {
    u8 pad_00[8];
    void *unk_08;
} S_func_800AA760_2;

typedef struct S_func_800AA760_3 {
    u8 pad_00[0x72];
    s16 unk_72;
} S_func_800AA760_3;

typedef struct S_func_800AA760_4 {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[2];
    u16 unk_06;
    u8 pad_08[2];
    u16 unk_0A;
} S_func_800AA760_4;

typedef struct S_func_800AA760_5 {
    u16 unk_00;
} S_func_800AA760_5;

/* Updates the linked position, or clears the object flag and sets cleanup bits. */
void func_800A7EC0(S_func_800AA760_0 *object, S_func_800AA760_1 *out_position)
{
    s32 x_offset;
    s32 y_offset;
    s8 *object_flag;
    u8 link_id;
    u8 link_index;
    S_func_800AA760_2 *linked_record;
    S_func_800AA760_3 *linked_entity;
    S_func_800AA760_4 *linked_position;

    link_id = object->unk_60;
    link_index = link_id & 0xFF;
    if (func_8009CFE0(object, out_position) != 0) {
        object_flag = object->unk_98;
        if (object_flag != 0) {
            *object_flag = 0;
        }
        func_80033D08(object);
        ((S_func_800AA760_5 *)((u8 *)object - 2))->unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    if (link_index != 0) {
        linked_record = D_80082660[link_index].record;
        linked_entity = (S_func_800AA760_3 *)((u8 *)linked_record + 0x20);
        if (linked_record != 0) {
            linked_position = linked_record->unk_08;
            x_offset = func_800644B8(linked_entity->unk_72);
            if (x_offset < 0) {
                x_offset += 0xFF;
            }
            out_position->unk_02 =
                linked_position->unk_02 + (x_offset >> 8);

            y_offset = func_80064584(linked_entity->unk_72);
            if (y_offset < 0) {
                y_offset += 0xFF;
            }
            out_position->unk_06 =
                linked_position->unk_06 + (y_offset >> 8);
            out_position->unk_0A = linked_position->unk_0A - 0x20;
        }
    }
}
