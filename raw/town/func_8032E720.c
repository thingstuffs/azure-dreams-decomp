#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*TownCall3)(void *, void *, s32);
typedef void (*TownCall1)(s32);

extern void func_800193F4(void *, s32);
extern s8 D_80016000[];
extern u8 D_80016034[16];
extern u8 D_8001605C[];

s32 func_80018F20(s32 *arg0)
{
    u8 seen[0x100];
    volatile s32 *cursor;
    register s32 object_base ASM_REG("$18");
    s32 current;
    s32 count;
    register u32 index ASM_REG("$2");
    register u8 *map_base ASM_REG("$17");
    register u8 *mark ASM_REG("$2");
    register u8 *initial_page ASM_REG("$2");
    register u8 *initial_root ASM_REG("$2");
    register u8 *loaded_base ASM_REG("$2");

    ASM_SCHED_BARRIER();
    cursor = arg0;
    initial_page = (u8 *)0x80010000;
    ASM_KEEP(initial_page);
    initial_root = FIELD(initial_page, u8 *, 0x6000);
    ASM_KEEP(initial_root);
    loaded_base = FIELD(initial_root, u8 *, 0x38);
    ASM_KEEP(loaded_base);
    object_base = (s32)loaded_base + 0x248;
    ASM_KEEP(object_base);
    func_800193F4(seen, 0x14);
    map_base = seen;
    if (*cursor != 0) {
        register u8 *page ASM_REG("$19");
        register u8 *message ASM_REG("$5");

        page = (u8 *)0x80010000;
        ASM_KEEP(page);
        index = *cursor;
        do {
            message = (u8 *)0x80010000;
            if (map_base[(u32)(index - object_base) >> 2] != 0) {
                register u8 *root ASM_REG("$2");
                register u8 *call_table ASM_REG("$2");
                register TownCall3 call3 ASM_REG("$2");
                register u8 *name_page ASM_REG("$4");

                root = FIELD(page, u8 *, 0x6000);
                ASM_KEEP(root);
                call_table = FIELD(root, u8 *, 0x20);
                ASM_KEEP(call_table);
                name_page = (u8 *)0x80010000;
                ASM_KEEP(name_page);
                call3 = FIELD(call_table, TownCall3, 0x168);
                ASM_KEEP(message);
                call3(name_page + 0x6034, message + 0x605C, 0x71);
                FIELD(FIELD(FIELD(page, void *, 0x6000), void *, 0x20),
                      TownCall1, 0x174)(1);
            }
            current = *cursor;
            ASM_KEEP(current);
            mark = map_base + ((u32)(current - object_base) >> 2);
            ASM_KEEP(mark);
            *mark = 1;
            ASM_SCHED_BARRIER();
            cursor++;
            index = *cursor;
        } while (index != 0);
    }

    count = 0;
    if (seen[0] != 0) {
        register u8 *scan_base ASM_REG("$3");

        scan_base = seen;
        do {
            count++;
        } while (scan_base[count] != 0);
    }

    if (count >= 0x14) {
        u8 *page;
        register u8 *root ASM_REG("$2");
        register u8 *call_table ASM_REG("$2");
        register TownCall3 call3 ASM_REG("$2");

        page = (u8 *)0x80010000;
        ASM_KEEP(page);
        root = FIELD(page, u8 *, 0x6000);
        ASM_KEEP(root);
        call_table = FIELD(root, u8 *, 0x20);
        ASM_KEEP(call_table);
        call3 = FIELD(call_table, TownCall3, 0x168);
        ASM_KEEP(call3);
        call3(D_80016034, D_8001605C, 0x76);
        FIELD(FIELD(FIELD(page, void *, 0x6000), void *, 0x20),
              TownCall1, 0x174)(1);
    }
    return object_base + count * 4;
}

/* MECHANISM: A 256-byte byte-map at sp+0x10 supplies the retail 0x128 frame.
   Cursor/object/map roles span calls, while separate block-local 0x80010000
   page bases reproduce the s3 loop hold and final s0 rematerialization. */
