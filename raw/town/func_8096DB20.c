#include "common.h"

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))

typedef struct TownInitialPosition {
    void *data;
    volatile u16 x;
    volatile u16 y;
} TownInitialPosition;

extern void func_801232DC(void);
extern void func_80124188(void *);
extern void *D_8011AD58[];
extern TownInitialPosition D_80126AF8[5];
extern void *D_80129728[];

void func_80125FB8(void *arg0)
{
    static void *const switch_labels[] = {
        &&case_0,
        &&case_123,
        &&case_123,
        &&case_123,
        &&case_4,
        &&case_567,
        &&case_567,
        &&case_567,
        &&done,
        &&done,
        &&done,
        &&done,
        &&done
    };
    s32 selector;
    register s32 counter ASM_REG("$4");
    s32 offset;
    s8 *source_base;
    s32 *source;
    void **object_base;
    register void **objects ASM_REG("$5");
    void *destination;
    void *object_data;
    s32 value;
    u16 half;

    selector = (s16)(FIELD(arg0, u16, 4) - 8);
    if ((u32)selector >= 13) {
        goto done;
    }
    (void)switch_labels;
    goto *D_8011AD58[selector];

case_0:
    counter = 0x1C;
    source_base = (s8 *)D_80126AF8;
    offset = 0;
    object_base = D_80129728;
    objects = &object_base[0x1C];
    ASM_KEEP_NV(counter);
    ASM_KEEP_NV(objects);
    do {
        source = (s32 *)((u32)offset + (u32)source_base);
        offset += 8;
        destination = objects[0];
        ASM_KEEP(destination);
        value = *source;
        ASM_KEEP(value);
        counter += 1;
        FIELD(destination, s32, 0) = value;
        objects += 1;
    } while (counter < 0x1E);

case_123:
    counter = 0x1C;
    object_base = D_80129728;
    objects = &object_base[0x1C];
    ASM_KEEP_NV(counter);
    ASM_KEEP_NV(objects);
    do {
        object_data = FIELD(*objects, void *, 8);
        ASM_KEEP(object_data);
        half = FIELD(object_data, u16, 2);
        ASM_KEEP(half);
        counter += 1;
        FIELD(object_data, u16, 2) = (u16)(half - 0x100);
        objects += 1;
    } while (counter < 0x62);
    goto done;

case_4:
    func_801232DC();
    func_80124188(arg0);

case_567:
    counter = 0x1C;
    object_base = D_80129728;
    objects = &object_base[0x1C];
    ASM_KEEP_NV(counter);
    ASM_KEEP_NV(objects);
    do {
        object_data = FIELD(*objects, void *, 8);
        ASM_KEEP(object_data);
        half = FIELD(object_data, u16, 2);
        ASM_KEEP(half);
        counter += 1;
        FIELD(object_data, u16, 2) = (u16)(half - 0x100);
        objects += 1;
    } while (counter < 0x62);

done:
    return;
}

/* MECHANISM: The true-space 0x801260D4 target is a local epilogue edge; a 13-way
   external-table dispatch preserves the 0x18 frame and sole s0 hold. Named bases,
   runtime a0/a1 pins, load-boundary keeps, and integer index-first addition close it. */
