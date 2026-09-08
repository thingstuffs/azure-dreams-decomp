#include "common.h"


typedef void (*TownCall3)(void *, void *, s32);
typedef void (*TownCall1)(s32);

typedef struct S_80018F20_0 {
    u8 pad_00[0x6000];
    u8 * unk_6000;
} S_80018F20_0;   /* initial_page in func_80018F20 */

typedef struct S_80018F20_1 {
    u8 pad_00[0x38];
    u8 * unk_38;
} S_80018F20_1;   /* initial_root in func_80018F20 */

typedef struct S_80018F20_2 {
    u8 pad_00[0x6000];
    union { u8 * p; void * p2; } unk_6000;   /* accessed as both */
} S_80018F20_2;   /* page in func_80018F20 */

typedef struct S_80018F20_3 {
    u8 pad_00[0x20];
    u8 * unk_20;
} S_80018F20_3;   /* root in func_80018F20 */

typedef struct S_80018F20_4 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80018F20_4;   /* ((S_80018F20_2 *)page)->unk_6000.p2 in func_80018F20 */


extern void func_800193F4(void *, s32);
extern s8 D_80016000[];
extern u8 D_80016034[16];
extern u8 D_8001605C[];

/* Returns the first unused slot address, reporting duplicate entries or a full slot table. */
s32 func_80018F20(s32 *slot_list)
{
    u8 used_slots[0x100];
    volatile s32 *slot_cursor;
    s32 slot_base;
    s32 slot_addr;
    s32 free_slot;
    u32 next_slot_addr;
    u8 *used_map;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *used_flag;
    u8 *initial_page;
    u8 *initial_root;
    u8 *loaded_base;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    slot_cursor = slot_list;
    initial_page = (u8 *)0x80010000;
    initial_root = ((S_80018F20_0 *)initial_page)->unk_6000;
    ASM_KEEP(initial_root);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    loaded_base = ((S_80018F20_1 *)initial_root)->unk_38;
    slot_base = (s32)loaded_base + 0x248;
    ASM_KEEP(slot_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    func_800193F4(used_slots, 0x14);
    used_map = used_slots;
    if (*slot_cursor != 0) {
        u8 *page;
        u8 *message_page;

        page = (u8 *)0x80010000;
        next_slot_addr = *slot_cursor;
        do {
            message_page = (u8 *)0x80010000;
            if (used_map[(u32)(next_slot_addr - slot_base) >> 2] != 0) {
                u8 *root;
                u8 *call_table;
                TownCall3 report_error;
                register u8 *name_page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                root = ((S_80018F20_2 *)page)->unk_6000.p;
                call_table = ((S_80018F20_3 *)root)->unk_20;
                ASM_KEEP(call_table);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                name_page = (u8 *)0x80010000;
                ASM_KEEP(name_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                report_error = (*(TownCall3 *)((u8 *)call_table + 0x168));
                ASM_KEEP(message_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                report_error(name_page + 0x6034, message_page + 0x605C, 0x71);
                (*(TownCall1 *)((u8 *)(((S_80018F20_4 *)(((S_80018F20_2 *)page)->unk_6000.p2))->unk_20) + 0x174))(1);
            }
            slot_addr = *slot_cursor;
            used_flag = used_map + ((u32)(slot_addr - slot_base) >> 2);
            ASM_KEEP(used_flag);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            *used_flag = 1;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            slot_cursor++;
            next_slot_addr = *slot_cursor;
        } while (next_slot_addr != 0);
    }

    free_slot = 0;
    if (used_slots[0] != 0) {
        register u8 *scan_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

        scan_base = used_slots;
        do {
            free_slot++;
        } while (scan_base[free_slot] != 0);
    }

    if (free_slot >= 0x14) {
        u8 *page;
        u8 *root;
        u8 *call_table;
        TownCall3 report_error;

        page = (u8 *)0x80010000;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        root = ((S_80018F20_2 *)page)->unk_6000.p;
        call_table = ((S_80018F20_3 *)root)->unk_20;
        report_error = (*(TownCall3 *)((u8 *)call_table + 0x168));
        ASM_KEEP(report_error);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        report_error(D_80016034, D_8001605C, 0x76);
        (*(TownCall1 *)((u8 *)(((S_80018F20_4 *)(((S_80018F20_2 *)page)->unk_6000.p2))->unk_20) + 0x174))(1);
    }
    return slot_base + free_slot * 4;
}

/* MECHANISM: A 256-byte byte-map at sp+0x10 supplies the retail 0x128 frame.
   Cursor/object/map roles span calls, while separate block-local 0x80010000
   page bases reproduce the s3 loop hold and final s0 rematerialization. */
