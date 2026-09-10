#include "common.h"

typedef struct {
    u8 pad_00[0x38];
    s32 *field_38;
    u8 field_3C[1];
} ObjectHeader;

extern void *func_8003FC64(s32);
extern s32 func_8004B404(s32);
extern void func_8004491C(void *, void *);
extern void func_800DC988(void *);
extern s32 func_800DCBE4(void *, s32);
extern void func_800DCCF4(void *, s32);
extern s32 D_800133A0[];
extern u8 D_8004CAA0[];
extern s32 D_800814A0;
extern u8 D_800DC8F8[];
extern void *D_800E5910[];

/* Allocate and initialize an object, marking allocation failure in the status flags. */
void *func_800DCD38(void) {
    s32 allocation;
    register ObjectHeader *header ASM_REG("$18");
    s32 *status_page;
    s32 *source_table;
    u8 *data;
    u8 *object;

    object = func_8003FC64(0);
    if (object != 0) {
        D_800E5910[0] = object;
        allocation = func_8004B404(0x100);
        if (allocation != 0) {
            do {
                header = (ObjectHeader *)(object + 0x20);
            } while (0);
            data = object + 0x5C;
            func_800DCCF4(data, allocation);
            source_table = (s32 *)0x800133A0;
            header->field_38 = source_table;
            *(s32 *)(object + 0xC) = func_800DCBE4(data, source_table[0]);
            func_800DC988(object);
            *(u8 **)(object + 0x10) = D_800DC8F8;
            func_8004491C(object, D_8004CAA0);
            return object;
        }
        *(u16 *)(object + 0x1E) |= 0x8000;
        status_page = (s32 *)0x80080000;
        object = 0;
        status_page[0x528] |= 0x8000;
    }
    return object;
}

