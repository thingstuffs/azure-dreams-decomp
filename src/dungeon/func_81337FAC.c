#include "common.h"

typedef struct {
    u8 pad[0x3714];
    u16 flags;        /* 0x3714 */
    s16 f3716;
    s16 f3718;
    s16 f371A;
    void *handler;    /* 0x371C */
} SysWork;

typedef struct {
    u8 pad[0xA];
    u16 counter;      /* 0x0A */
} DungeonCounters;

extern void func_8009A028(void *);
extern u16 func_800A0818(u8, u8, u8, u8, s32 *);
extern void func_80164BA4(void *);
extern void func_8017394C(void);

extern u16 D_80013714;
extern s16 D_80013716;
extern s16 D_80013718;
extern s16 D_8001371A;
extern void *D_8001371C;
extern u8 D_80082E80[];
extern DungeonCounters D_80083460;
extern u16 D_800834E2;
extern s32 D_800E296C;
extern u8 D_80173C8C[];
extern u8 D_80173D74[];
extern u8 *D_80175D50;
extern s32 D_80175DC4;
extern s16 D_80175DC8;

/* Set up the active object's handler and direction, then update its two linked entries. */
void func_8016EFAC(void)
{
    s32 unused_result;
    s32 slot;
    u16 direction;
    u8 *work_page;
    SysWork *sys_work;
    u8 *active_object;
    u8 *object_state;
    u8 *position_data;
    u8 *entry;
    DungeonCounters *counters;
    u32 handler_index;
    u8 *handler_table;
    u32 high_bit;

    slot = 0;
    work_page = (u8 *)0x800E0000;
    sys_work = (SysWork *)0x80010000;
    high_bit = 0x80000000;
    D_80175D50[0xCF] = 1;
    sys_work->f371A = 0;
    sys_work->f3718 = 0;
    sys_work->f3716 = 0;
    counters = &D_80083460;
    counters->counter -= 1;
    active_object = D_80175D50;
    sys_work->flags = (sys_work->flags | 9) & 0xFFEF;
    handler_index = D_800834E2 >> 7;
    handler_table = D_80173C8C;
    sys_work->handler = *(void **)(handler_table + (handler_index & 0x1C));
    position_data = *(u8 **)(active_object + 0xC);
    D_800E296C |= 0x200000;
    object_state = active_object + 0x20;
    direction = func_800A0818(position_data[0x24], position_data[0x25],
                           D_80082E80[0x24], D_80082E80[0x25], &unused_result);
    *(u16 *)(object_state + 0x2A) = direction;
    direction >>= 7;
    D_80175DC8 = 0;
    {
        u8 *direction_table;

        direction_table = D_80173D74;
        direction &= 0x1C;
        D_80175DC4 = *(s32 *)(direction_table + direction);
    }

    do {
        entry = *(u8 **)(*(u8 **)(work_page + 0x3D7C) + slot * 4 + 0xAC);
        if (entry != 0) {
            u8 *entry_header;
            func_80164BA4(entry);
            func_8009A028(*(void **)(*(u8 **)(work_page + 0x3D7C) + slot * 4 + 0xAC));
            entry_header = *(u8 **)(*(u8 **)(work_page + 0x3D7C) + slot * 4 + 0xAC) - 0x20;
            *(u32 *)(entry_header + 0x10) |= high_bit;
        }
        slot++;
    } while (slot < 2);
    func_8017394C();
}

/* MECHANISM (stock 2.7.2-cdk -O2 -G0, no bridge):
   - D_80175D50 is a plain pointer variable (non-struct MEM) while every page
     store goes through a struct pointer (in-struct MEM): gcc 2.x's
     true/anti_dependence struct-vs-scalar rule then frees the second load
     of D_80175D50 from all page stores and sched2 floats it to retail's slot.
   - The table pointer is parked in `handler_table` between the `>> 7` and the `& 0x1C`
     so its lui/addiu pair is scheduled inside the index chain; that lengthens
     the pair's qty (QTY_CMP_PRI 1.33 < 1.5) so the index chain is coloured
     first and takes $v0, the pair $v1 (retail's roles).
   - The 0x800e page is held across the loop while the high-bit literal stays
     live across calls; a five-argument call owns the 0x18 stack local. */
