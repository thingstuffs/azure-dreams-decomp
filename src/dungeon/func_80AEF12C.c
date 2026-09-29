#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad[0x8D0];
    u8 *field_8D0;
} Context;

typedef struct {
    u8 pad[8];
    u32 field_8;
} Input0;

typedef struct {
    u8 pad0[2];
    u16 field_2;
    u8 pad4[2];
    u16 field_6;
    u8 pad8[2];
    u16 field_A;
} Input1;

typedef struct {
    u8 pad0[4];
    u16 x;
    u16 y;
    u16 z;
    u8 pad0A[0x12];
    u8 *volatile next;
    u8 pad20[4];
    u32 *ot;
    u8 pad28[0xA8];
    u8 padD0[0x30];
    u32 index;
} Scratch;

extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);

/* Projects a point and queues a semitransparent pixel and its drawing mode. */
s32 func_80AEF12C(Input0 *object_data, Input1 *position_data) {
    u8 *object_bytes = (u8 *)object_data;
    u8 *position_bytes = (u8 *)position_data;

    {
        GameWork *context_addr = &gameWork;
        u32 address_mask = 0x00FFFFFF;
        Context *context = gameWork.unk_000;
        u32 length_mask = 0xFF000000;
        Scratch *scratch = (Scratch *)0x1F800000;
        u8 *prim;
        union { void *pointer; u32 value; } state_prim;
        u32 prim_addr;
        u8 *packet_start;
        void *linked_object;

        packet_start = context->field_8D0;
        scratch->ot = (u32 *)((u8 *)context + 0xB0);
        scratch->next = packet_start;
    next_object:
        scratch->x = *(u16 *)(position_bytes + 2);
        prim = scratch->next;
        scratch->y = *(u16 *)(position_bytes + 6);
        scratch->z = *(u16 *)(position_bytes + 0xA);
        scratch->next = prim + 0xC;
        {
            void *position = &scratch->x;
            scratch->index = func_80065420(position, prim + 8,
                                           (u8 *)scratch + 0xD0,
                                           (u8 *)scratch + 0xD4);
        }

        if (scratch->index < 0x1E0U) {
            *(s32 *)(prim + 4) = *(u32 *)(object_bytes + 8);
            *(s8 *)(prim + 3) = 2;
            {
                register u8 red ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                register u8 green ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                register u8 blue ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                red = *(volatile u8 *)(prim + 4);
                green = *(volatile u8 *)(prim + 5);
                blue = *(volatile u8 *)(prim + 6);
            }
            *(s8 *)(prim + 7) = 0x6A;
            *(u32 *)prim = (*(u32 *)prim & length_mask) |
                (scratch->ot[scratch->index] & address_mask);
            {
                u32 *ot_entry;
                ot_entry = (u32 *)((scratch->index << 2) + (u32)scratch->ot);
                {
                    state_prim.value = *ot_entry;
                    prim_addr = (u32)prim & address_mask;
                    state_prim.value &= length_mask;
                    state_prim.value |= prim_addr;
                    *ot_entry = state_prim.value;
                }
            }
            state_prim.pointer = scratch->next;
            *(u8 **)((u8 *)scratch + 0x1C) = (u8 *)state_prim.pointer + 0xC;
            prim_addr = func_80066460(0, 1, 0, 0);
            func_80067F20(state_prim.pointer, 0, 0, prim_addr & 0xFFFF, 0);
            *(u32 *)state_prim.pointer = (*(u32 *)state_prim.pointer & length_mask) |
                (scratch->ot[scratch->index] & address_mask);
            scratch->ot[scratch->index] =
                (scratch->ot[scratch->index] & length_mask) | ((u32)state_prim.pointer & address_mask);
        }

        linked_object = *(void **)(object_bytes - 8);
        if (linked_object != 0) {
            object_bytes = (u8 *)linked_object + 0x20;
            position_bytes = *(u8 **)((u8 *)linked_object + 8);
            ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): this second, opaque definition keeps combine from rewriting scratch+4/+0xD0/+0xD4 as ori; the source shape that makes it unnecessary has not been found */
            {
                u32 scratch_addr;
#ifdef NON_MATCHING
                scratch_addr = (u32)scratch;
#endif
            }
            goto next_object;
        }
        (((Context *)context_addr->unk_000))->field_8D0 = scratch->next;
        {
            s32 return_zero = 0;
#ifdef NON_MATCHING
            return_zero = 0;
#endif
            return return_zero;
        }
    }
}
