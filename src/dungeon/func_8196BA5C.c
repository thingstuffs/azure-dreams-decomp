#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"

   /* work in func_8196BA5C */

   /* obj in func_8196BA5C */

   /* the 0x18 bytes before D_800814A8 in func_8196BA5C, addressed as D_800814A8[-1] */















extern void func_800B8FC8(void *, Rect16 *, void *, s32, s32);

/* Creates an object in the first free rectangle slot and marks completion when the timer expires. */
void func_8002525C(void *owner) {
    s16 center[2];
    RectTable slot_rects;
    u8 *copy_src;
    u8 *copy_dst;
    u8 *copy_end;
    s16 slot;
    s32 rect_offset;
    Rect16 *rect;
    void *child;
    u8 *child_work;
    Display *display;
    void *source_vector;
    void *child_vector;
    u16 ticks_left;

    copy_dst = (u8 *)&slot_rects;
    copy_src = (u8 *)&D_80024024;
    if ((u32)copy_src & 3) {
        copy_end = copy_src + sizeof(RectTable);
        do {
            *(PackedBlock *)copy_dst = *(PackedBlock *)copy_src;
            copy_src += sizeof(PackedBlock);
            copy_dst += sizeof(PackedBlock);
        } while (copy_src != copy_end);
    } else {
        copy_end = copy_src + sizeof(RectTable);
        do {
            *(AlignedBlock *)copy_dst = *(AlignedBlock *)copy_src;
            copy_src += sizeof(AlignedBlock);
            copy_dst += sizeof(AlignedBlock);
        } while (copy_src != copy_end);
    }

    D_800269B4 = 1;

    slot = 0;
    while (slot < 8 && (*(s16 *)((u8 *)owner + 0x64 + (((s32)slot << 16) >> 15))) != 0) {
        slot++;
    }

    if (slot != 8) {
        (*(s16 *)((u8 *)owner + 0x64 + slot * 2)) = 1;
        rect_offset = (s32)slot << 3;
        rect = (Rect16 *)((u8 *)&slot_rects + rect_offset);
        center[0] = rect->x + ((s16)rect->w >> 1);
        center[1] = rect->y + 0x30;
        func_800B8FC8(D_800814A8, rect, center, 1, 1);

        child = func_8003FC64(0x212);
        if (child != 0) {
            child_work = (u8 *)child + 0x20;
            ((S_8196BA5C_0 *)child_work)->unk_2C = 7;
            ((S_8196BA5C_0 *)child_work)->unk_2E = 7;
            ((S_8196BA5C_0 *)child_work)->unk_50 = slot;
            ((S_8196BA5C_0 *)child_work)->unk_7C = owner;
            ((S_8196BA5C_1 *)child)->unk_10 = func_8002407C;
            func_8004491C(child, (s32)func_80045340);

            display = ((S_8196BA5C_1 *)child)->unk_0C;
            display->field6 = 4;
            display->flags &= 0xFFF3;

            source_vector = ((S_8196BA5C_2_pre *)D_800814A8)[-1].unk_00;
            child_vector = ((S_8196BA5C_1 *)child)->unk_08;
            ((s32 *)child_vector)[0] = ((s32 *)source_vector)[0];
            ((s32 *)child_vector)[1] = ((s32 *)source_vector)[1];
            ((s32 *)child_vector)[2] = ((s32 *)source_vector)[2];

            display = ((S_8196BA5C_1 *)child)->unk_0C;
            display->scaleX = 0x1000;
            display->scaleY = 0x1000;
            display->blue = 0x80;
            display->green = 0x80;
            display->red = 0x80;

            *(PackedVec3 *)((u8 *)child + 0x58) = D_80026978;
            display->vector = (u8 *)child + 0x58;
            ((S_8196BA5C_0 *)child_work)->unk_40 = (u8)rect->x - 0x40;
            ((S_8196BA5C_0 *)child_work)->unk_41 = (u8)rect->y;
        }
    }

    ticks_left = (*(u16 *)((u8 *)owner + 0x2C)) - 1;
    (*(u16 *)((u8 *)owner + 0x2C)) = ticks_left;
    if ((s16)ticks_left <= 0) {
        (*(u16 *)((u8 *)owner + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

/* MECHANISM: The 0x80-byte frame, sibling table/center locals, packed copies,
   held object roles, and noreturn tail shape preserve the seed's 184-word body.
   A block-local $v1 page pin lets LEAD27 sink lui 0x8002 into the tail-j slot. */
