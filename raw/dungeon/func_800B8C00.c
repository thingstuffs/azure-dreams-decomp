#include "common.h"

extern void func_8008D344(void *arg0, void *arg1, void *arg2, void *arg3);
extern s32 func_80098864(void *arg0, s32 arg1);
extern s32 func_80098B38(void *arg0);
extern s32 func_800997FC(void *arg0, s32 arg1, s32 arg2);
extern s32 func_800A5F38(void *arg0, void *arg1);
extern s32 func_800A6480(void *arg0, void *arg1, s32 arg2);
extern s32 func_800AD6FC(void *arg0, s32 arg1, void *arg2);

typedef struct {
    s16 flags;
    u8 pad2[18];
} DungeonItem;

typedef struct {
    u8 pad0[12];
    DungeonItem *entries;
    u8 pad10[4];
} DungeonGroup;

extern DungeonGroup D_80073414[];
extern u8 D_80082E80[];
extern u8 D_80083460[];
extern s32 D_80083780[];
extern u16 D_800DDE84[];
extern s32 D_800E3D7C[];

s32 func_800BE360(void *arg0, void *arg1, s16 arg2, s32 arg3) {
    s32 idx0;
    s32 idx1;
    DungeonItem *ptr;
    u16 *table_base;
    u8 *counter_base;
    u8 *far_page;
    register u8 *direct_page ASM_REG("$2");
    s32 direct_index;
    s32 selector;
    s16 val;
    u16 val2;

    if (arg2 == 0xD) {
        return func_80098864(arg1, arg3);
    }
    if ((s32) arg0 == D_800E3D7C[0]) {
        *(void **)((u8 *)arg0 + 0x110) = arg1;
        func_8008D344(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }
    if ((u32)arg0 <= 0x9FFFFFFFU) {
        func_800A6480(arg0, arg1, arg2);
        idx1 = *((u8 *)arg1 + 1);
        idx0 = *((u8 *)arg1 + 0);
        ptr = D_80073414[idx1].entries;
        val = ptr[idx0].flags;
        if (!(val & 0x8000)) {
            direct_page = (u8 *)0x800E0000;
            ASM_KEEP(direct_page);
            direct_index = *((u8 *)arg0 + 0x13);
            ASM_SCHED_BARRIER();
            direct_page -= 0x217C;
            ASM_KEEP(direct_page);
            val2 = ((u16 *)direct_page)[direct_index];
            selector = val2 & 3;
        } else {
            table_base = D_800DDE84;
            val2 = table_base[*((u8 *)arg0 + 0x13)];
            selector = (val2 >> 4) & 3;
        }
        if (func_800AD6FC(arg0, selector, arg1) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
        func_80098B38(arg1);
    } else {
        far_page = (u8 *)0x800E0000;
        ASM_KEEP(far_page);
        func_800997FC(far_page + 0x101C, arg3, arg2);
    }
    counter_base = D_80083460;
    ASM_KEEP(counter_base);
    *(u16 *)(counter_base + 0xA) = *(u16 *)(counter_base + 0xA) - 1;
    return 1;
}

/* MECHANISM: The true-base CFG uses local selector, decrement, and epilogue joins
   under a 0x20 frame holding s0/s1; DungeonGroup typing preserves base-plus-0xC.
   Split page live ranges plus a v0 pin and scheduling seam emit lui/lbu/addiu.
   Held far/counter bases preserve signed offsets and predecessor delay-slot hoists. */
