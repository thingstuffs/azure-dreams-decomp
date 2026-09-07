#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 count;
    u8 pad4[0x18];
    void *data;
    u8 pad20[8];
    void *meta;
} FuncArg;

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} FuncData;

typedef struct {
    u8 pad0[0x13];
    u8 index;
} FuncMeta;

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[8];
    u16 fieldC;
    u16 fieldE;
    u8 pad10[2];
    s16 field12;
    u8 pad14[2];
    u16 field16;
    s16 field18;
    u8 pad1A[2];
    void *field1C;
} FuncSub;

typedef struct {
    u8 pad0[8];
    void *field8;
    u8 padC[4];
    s16 field10;
    u8 pad12[2];
    s16 field14;
} FuncBlock;

typedef struct {
    u8 pad0[8];
    FuncData *data_block;
    FuncBlock *block;
    void *field10;
} FuncItem;

typedef struct {
    u8 pad0[0xA];
    u16 fieldA;
} FuncTable;

extern u8 D_80045340[];
extern u8 D_800DDC40[];
extern u8 D_800C4640[];
extern u8 D_800DF564[];
extern s32 D_800814A0[3];
extern FuncTable D_80083460;

extern s32 rand(void);
extern void *func_8003FC64(s32);
extern s32 func_8004491C(void *, void *);

void func_800C4944(FuncArg *arg0) {
    register s32 counter ASM_REG("$18");
    FuncSub *sub;
    FuncItem *item;
    FuncBlock *block;
    FuncData *data_block;
    FuncData *data;
    FuncMeta *meta;
    u8 *effect;
    u8 *table;
    u8 *tile;
    u16 x;
    u16 y;
    s32 seeds[3];

    seeds[0] = rand();
    seeds[1] = rand();
    seeds[2] = rand();
    counter = 1;
    effect = D_800C4640;
    table = D_800DDC40;
    tile = D_800DF564;
    loop:
    item = func_8003FC64(0x202);
    if (item != 0) {
        item->field10 = effect;
        sub = (FuncSub *)((u8 *)item + 0x20);
        func_8004491C(item, D_80045340);
        sub->field12 = (seeds[0] & 0xF) + 0x10;
        sub->field16 = seeds[1];
        data = (FuncData *)arg0->data;
        data_block = item->data_block;
        x = data->x;
        data_block->x = x;
        sub->fieldC = x;
        y = ((FuncData *)arg0->data)->y;
        data_block->y = y;
        sub->fieldE = y;
        meta = (FuncMeta *)arg0->meta;
        data_block->z = ((FuncData *)arg0->data)->z - *(u8 *)(meta->index + (s32)table) - (seeds[2] & 0xF);
        sub->field1C = arg0->data;
        block = item->block;
        block->field14 = 0xC;
        block->field8 = tile;
        if (counter != 0) {
            block->field10 = 0x20;
        } else {
            block->field10 = 0x60;
        }
        sub->field2 = 8;
        sub->field18 = counter;
    }
    counter -= 1;
    if (counter >= 0) {
        goto loop;
    }
    {
        u16 new_count;
        new_count = arg0->count - 1;
        arg0->count = new_count;
        if ((new_count << 0x10) <= 0) {
            u16 *before_count;
            before_count = (u16 *)arg0 - 1;
            *before_count = *before_count | 0x8000;
            D_800814A0[0] = D_800814A0[0] | 0x8000;
            D_80083460.fieldA = D_80083460.fieldA - 1;
        }
    }
}

/* MECHANISM: rowbase TRUE-SPACE row (region xfer_dungeon_A3000, delta 0x7FFE5760,
   true base 0x800C4944).  Three residues, three separate levers:
   1. Retail reloads `arg0->data` a THIRD time for the z field (word 53, which is
      what fills that load-delay slot); the warm cdk idiom held the first pointer
      live from the x load all the way through z and emitted a nop instead.
      Spelling z as its own `((FuncData *)arg0->data)->z` deref restores it.
   2. That reload flips gcc's callee-save assignment (arg0 -> $s2, counter -> $s3);
      retail is arg0 -> $s3, counter -> $s2.  Pinning `counter` to $s2 restores
      both roles and every $s2/$s3-bearing word in the function.
   3. `table[meta->index]` is a POINTER-array ref, so gcc canonicalises the address
      add base-first (`addu v0,s5,v0`).  Retail has `addu v0,v0,s5` -- an integer
      addition that keeps source order.  Writing the index first against an
      integer-cast base reproduces it. */
