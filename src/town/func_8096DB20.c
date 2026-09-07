#include "common.h"

typedef struct S_80125FB8_0 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80125FB8_0;   /* arg0 in func_80125FB8 */

typedef struct S_80125FB8_1 {
    s32 unk_00;
} S_80125FB8_1;   /* destination in func_80125FB8 */

typedef struct S_80125FB8_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80125FB8_2;   /* *objects in func_80125FB8 */

typedef struct S_80125FB8_3 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80125FB8_3;   /* object_data in func_80125FB8 */



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

void func_80125FB8(S_80125FB8_0 *arg0)
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
    s32 counter;
    s32 offset;
    s8 *source_base;
    s32 *source;
    void **object_base;
    register void **objects ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    S_80125FB8_1 *destination;
    S_80125FB8_3 *object_data;
    s32 value;
    u16 half;

    selector = (s16)(arg0->unk_04 - 8);
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
    do {
        source = (s32 *)((u32)offset + (u32)source_base);
        offset += 8;
        destination = objects[0];
        ASM_KEEP(destination);   /* MATCH pin: retail schedule: same instructions, different order without it */
        value = *source;
        ASM_KEEP(value);   /* MATCH pin: retail delay-slot fill depends on it */
        counter += 1;
        destination->unk_00 = value;
        objects += 1;
    } while (counter < 0x1E);

case_123:
    counter = 0x1C;
    object_base = D_80129728;
    objects = &object_base[0x1C];
    do {
        object_data = ((S_80125FB8_2 *)(*objects))->unk_08;
        half = object_data->unk_02;
        ASM_KEEP(half);   /* MATCH pin: retail schedule: same instructions, different order without it */
        counter += 1;
        object_data->unk_02 = (u16)(half - 0x100);
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
    do {
        object_data = ((S_80125FB8_2 *)(*objects))->unk_08;
        half = object_data->unk_02;
        ASM_KEEP(half);   /* MATCH pin: retail schedule: same instructions, different order without it */
        counter += 1;
        object_data->unk_02 = (u16)(half - 0x100);
        objects += 1;
    } while (counter < 0x62);

done:
    return;
}

/* MECHANISM: The true-space 0x801260D4 target is a local epilogue edge; a 13-way
   external-table dispatch preserves the 0x18 frame and sole s0 hold. Named bases,
   runtime a0/a1 pins, load-boundary keeps, and integer index-first addition close it. */
