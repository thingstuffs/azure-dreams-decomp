#include "common.h"

typedef struct {
    s32 value0;
    s32 value4;
    s32 value8;
} PayloadObject;

typedef struct {
    u8 pad0[6];
    s16 field6;
    void *ptr8;
    u8 fieldc;
    u8 fieldd;
    u8 fielde;
    u8 padf;
    s16 field10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    s16 field1c;
    s16 field1e;
} ChildObject;

typedef struct {
    u8 pad0[0x1a];
    u16 angle_copy;
    s16 angle_index;
    u8 pad1e[0xa];
    void *arg28;
    s32 field2c;
    void *field30;
    u8 pad34[0x18];
    s8 field4c;
    s8 field4d;
} BlockObject;

typedef struct {
    u8 pad0[8];
    PayloadObject *payload;
    ChildObject *child;
    u8 *resource10;
    u8 pad14[0x40];
    u32 copy54[3];
} AllocationObject;

typedef struct {
    u8 pad0[0x2a];
    u16 angle;
} Arg0Object;

typedef struct {
    u8 pad0[0xa];
    u16 height;
} Arg1Object;

typedef struct {
    u8 pad0[0x24];
    u8 x24;
    u8 y25;
} Arg2Object;

typedef struct {
    u8 bytes[12];
} Copy12;

typedef struct {
    u8 pad0[0xc];
    void *child;
} SecondaryObject;

typedef struct {
    u8 pad0[0x24];
    u8 x24;
    u8 y25;
} SecondaryChild;

typedef struct {
    u8 pad0[0x14];
    u32 flags14;
    u8 pad18[4];
    u32 flags1c;
} SecondaryBlock;

extern u8 D_80174AA4[];
extern u8 D_80045340[];
extern u8 D_8017610C[];
extern u8 D_8017612C[];

extern AllocationObject *func_8003FC64(s32 arg0);
extern void func_8004491C(AllocationObject *arg0, void *arg1);
extern void func_8009A3D0(u8 arg0, u8 arg1, s32 arg2, s32 arg3);
extern s32 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);
extern void func_800C77D0(AllocationObject *arg0, PayloadObject *arg1, s32 arg2, s32 arg3);
extern void *func_801748FC(void *arg0, u32 arg1, u32 arg2, s16 arg3);

/* Creates an object offset from the origin in the owner's facing direction and links its secondary object. */
void func_80175494(Arg0Object *owner, Arg1Object *height_source, Arg2Object *origin) {
    AllocationObject *allocated;
    BlockObject *block;
    PayloadObject *payload;
    ChildObject *child;
    s32 mode;
    u8 secondary_x;
    u8 secondary_y;
    SecondaryChild *secondary_child;
    SecondaryBlock *secondary_block;
    void *secondary;

    allocated = func_8003FC64(0x212);
    if (allocated != 0) {
        block = (BlockObject *)((u8 *)allocated + 0x20);
        block->arg28 = owner;
        block->field30 = 0;
        block->field2c = 0;
        allocated->resource10 = D_80174AA4;
        func_8004491C(allocated, D_80045340);
        child = allocated->child;
        child->field10 = 0x20;
        child->flags14 |= 0xc;
        block->field4c = (s8)(origin->x24 + D_8017610C[(owner->angle >> 7) & 0x1c]);
        {
            u8 origin_y = origin->y25;
            u16 angle = owner->angle;
            u8 *direction_offset = D_8017610C + ((angle >> 7) & 0x1c);
            block->field4d = (s8)(origin_y + direction_offset[2]);
        }
        child->field6 = 6;
        payload = allocated->payload;
        payload->value0 = (((block->field4c << 6) + 0x20) << 0x10);
        payload->value4 = (((block->field4d << 6) + 0x20) << 0x10);
        payload->value8 = func_800BCB04(*(u16 *)((u8 *)payload + 2), *(u16 *)((u8 *)payload + 6), (s16)(height_source->height - 0x20)) << 0x10;
        block->angle_copy = owner->angle;
        block->angle_index = (owner->angle >> 9) & 7;
        child = allocated->child;
        child->field1c = 0x2400;
        child->field1e = 0x1c00;
        child->fielde = 0;
        child->fieldd = 0;
        child->fieldc = 0;
        *(Copy12 *)((u8 *)allocated + 0x54) = *(Copy12 *)D_8017612C;
        child->ptr8 = (u8 *)allocated + 0x54;
        secondary = func_801748FC(owner, (u16)(s8)block->field4c, (u16)(s8)block->field4d, *(s16 *)((u8 *)payload + 0xa));
        block->field30 = secondary;
        if (secondary != 0) {
            secondary_block = (SecondaryBlock *)((u8 *)secondary + 0x20);
            secondary_child = ((SecondaryObject *)secondary)->child;
            secondary_block->flags14 |= 0x100000;
            secondary_x = secondary_child->x24;
            secondary_y = secondary_child->y25;
            if (secondary_block->flags1c & 0x2000) {
                mode = 0x300;
            } else {
                mode = 0x3000;
            }
            func_8009A3D0(secondary_x, secondary_y, mode, mode);
        }
        func_800C77D0(allocated, payload, 8, 0x300);
    }
}
