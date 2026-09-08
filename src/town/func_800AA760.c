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

/* Updates the linked position, or clears the object flag and sets cleanup bits. */
void func_800A7EC0(void *object, void *out_position)
{
    s32 x_offset;
    s32 y_offset;
    s8 *object_flag;
    u8 link_id;
    u8 link_index;
    void *linked_record;
    void *linked_entity;
    void *linked_position;

    link_id = FIELD(object, u8 *, 0x60);
    link_index = link_id & 0xFF;
    if (func_8009CFE0(object, out_position) != 0) {
        object_flag = FIELD(object, s8 **, 0x98);
        if (object_flag != 0) {
            *object_flag = 0;
        }
        func_80033D08(object);
        FIELD(object, u16 *, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    if (link_index != 0) {
        linked_record = D_80082660[link_index].record;
        linked_entity = (u8 *)linked_record + 0x20;
        if (linked_record != 0) {
            linked_position = FIELD(linked_record, void **, 8);
            x_offset = func_800644B8(FIELD(linked_entity, s16 *, 0x72));
            if (x_offset < 0) {
                x_offset += 0xFF;
            }
            FIELD(out_position, s16 *, 2) =
                FIELD(linked_position, u16 *, 2) + (x_offset >> 8);

            y_offset = func_80064584(FIELD(linked_entity, s16 *, 0x72));
            if (y_offset < 0) {
                y_offset += 0xFF;
            }
            FIELD(out_position, s16 *, 6) =
                FIELD(linked_position, u16 *, 6) + (y_offset >> 8);
            FIELD(out_position, s16 *, 0xA) = FIELD(linked_position, u16 *, 0xA) - 0x20;
        }
    }
}
