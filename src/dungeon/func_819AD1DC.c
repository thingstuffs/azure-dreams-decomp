#include "common.h"



typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_FIELD_V(expr, type_ptr, offset) (*(volatile type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_800245A0;
extern M2C_UNK D_80027460;
extern M2C_UNK D_800CEEFC;

typedef struct S_819AD1DC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_819AD1DC_0;   /* obj in func_819AD1DC */

typedef struct S_819AD1DC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_819AD1DC_1;   /* src in func_819AD1DC */

typedef struct S_819AD1DC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_819AD1DC_2;   /* coords in func_819AD1DC */

typedef struct S_819AD1DC_3 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0xE];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
} S_819AD1DC_3;   /* part in func_819AD1DC */

typedef struct S_819AD1DC_4 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x1];
    s8 unk_0D;
    u8 pad_0E[0xE];
    u16 unk_1C;
    u16 unk_1E;
} S_819AD1DC_4;   /* render in func_819AD1DC */

/* Spawn the nine trail sprites at the source position, the last one larger and all fading with distance. */
void *func_819AD1DC(void *src)
{
    s32 i;
    M2C_UNK *handler;
    M2C_UNK *sub_handler;
    register s32 last_index;
    void *obj;
    s32 shade;
    u16 scale;
    u16 x;
    u16 y;
    u16 z;
    S_819AD1DC_4 *render;
    S_819AD1DC_3 *part;
    S_819AD1DC_2 *coords;

    i = 0;
    handler = &D_800245A0;
    sub_handler = &D_80027460;
    last_index = 8;
spawn_next:
    obj = func_8003FC64(18);
    if (obj != NULL) {
        ((S_819AD1DC_0 *)obj)->unk_10 = handler;
        func_8004491C(obj, &D_800CEEFC);
        coords = ((S_819AD1DC_0 *)obj)->unk_08;
        x = ((S_819AD1DC_1 *)src)->unk_02;
        part = obj + 0x20;
        coords->unk_02 = x;
        coords->unk_0E = x;
        part->unk_1C = x;
        y = ((S_819AD1DC_1 *)src)->unk_06;
        coords->unk_06 = y;
        coords->unk_12 = y;
        part->unk_1E = y;
        z = ((S_819AD1DC_1 *)src)->unk_0A;
        coords->unk_0A = z;
        coords->unk_16 = z;
        part->unk_20 = z;
        render = ((S_819AD1DC_0 *)obj)->unk_0C;
        render->unk_08 = sub_handler;
        if (i != last_index) {
            render->unk_1E = 0x200U;
        } else {
            render->unk_1E = 0x800U;
        }
        shade = -0x80 - ((s32)((last_index - i) * 4));
        scale = M2C_FIELD_V(render, u16 *, 0x1E);
        render->unk_0D = (u8)shade;
        render->unk_1C = scale;
        part->unk_38 = i;
        if (i == last_index) {
            part->unk_38 = 7;
        }
        part->unk_30 = last_index;
    }
    i += 1;
    if (i < 9) {
        goto spawn_next;
    }
    return obj;
}
