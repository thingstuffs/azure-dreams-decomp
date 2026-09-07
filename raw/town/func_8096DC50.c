#include "common.h"

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))

typedef struct TownInitialPosition {
    void *data;
    volatile u16 x;
    volatile u16 y;
} TownInitialPosition;

extern void func_801235EC(void);
extern void func_80123700(void);
extern void func_801237E8(void *);
extern void func_80123898(void *);
extern void func_801238E4(void *);
extern void func_80124728(void *);
extern void func_801247F8(void *);
extern void *D_8011AD90[];
extern TownInitialPosition D_80126AF8[5];
extern void *D_80129728[];

void func_801260E8(void *arg0)
{
    static void *const switch_labels[] = {
        &&case_0,
        &&done,
        &&done,
        &&done,
        &&done,
        &&done,
        &&done,
        &&case_7,
        &&case_8_10,
        &&case_8_10,
        &&case_8_10,
        &&case_11,
        &&case_12_14,
        &&case_12_14,
        &&case_12_14,
        &&done,
        &&case_16,
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
    register void **objects_a1 ASM_REG("$5");
    void *destination;
    void *object_data;
    s32 value;
    u16 half;

    selector = (s16)(FIELD(arg0, u16, 4) - 1);
    if ((u32)selector >= 20) {
        goto done;
    }
    (void)switch_labels;
    goto *D_8011AD90[selector];

case_0:
    {
        void *clear_target;

        clear_target = FIELD(arg0, void *, 0x58);
        clear_target = FIELD(clear_target, void *, 0x70);
        FIELD(clear_target, s32, 0) = 0;
    }
    func_80123700();
    func_80124728(arg0);
    func_801235EC();
    func_801247F8(arg0);
    func_801237E8(arg0);
    func_80123898(arg0);
    {
        s32 clear_count;
        u8 *clear_base;
        s32 **clear_cursor;
        s32 *clear_entry;

        clear_count = 14;
        clear_base = (u8 *)D_80129728;
        clear_cursor = (s32 **)(clear_base + 0x38);
        do {
            clear_entry = *clear_cursor;
            ASM_KEEP(clear_entry);
            clear_count += 1;
            *clear_entry = 0;
            clear_cursor = (s32 **)((u8 *)clear_cursor + 4);
        } while (clear_count < 16);
    }
    goto done;

case_7:
    counter = 14;
    source_base = (s8 *)D_80126AF8;
    offset = 0;
    object_base = D_80129728;
    objects_a1 = &object_base[14];
    ASM_KEEP_NV(counter);
    ASM_KEEP_NV(objects_a1);
    do {
        source = (s32 *)((u32)offset + (u32)source_base);
        offset += 8;
        destination = *objects_a1;
        ASM_KEEP(destination);
        value = *source;
        ASM_KEEP(value);
        counter += 1;
        FIELD(destination, s32, 0) = value;
        objects_a1 += 1;
    } while (counter < 16);

case_8_10:
    counter = 14;
    object_base = D_80129728;
    objects_a1 = &object_base[14];
    ASM_KEEP_NV(counter);
    ASM_KEEP_NV(objects_a1);
    do {
        object_data = FIELD(*objects_a1, void *, 8);
        ASM_KEEP(object_data);
        half = FIELD(object_data, u16, 2);
        ASM_KEEP(half);
        counter += 1;
        FIELD(object_data, u16, 2) = (u16)(half - 0x100);
        objects_a1 += 1;
    } while (counter < 28);
    goto done;

case_11:
    func_801238E4(arg0);

case_12_14:
    counter = 14;
    object_base = D_80129728;
    objects_a1 = &object_base[14];
    ASM_KEEP_NV(counter);
    ASM_KEEP_NV(objects_a1);
    do {
        object_data = FIELD(*objects_a1, void *, 8);
        ASM_KEEP(object_data);
        half = FIELD(object_data, u16, 2);
        ASM_KEEP(half);
        counter += 1;
        FIELD(object_data, u16, 2) = (u16)(half - 0x100);
        objects_a1 += 1;
    } while (counter < 28);
    goto done;

case_16:
    func_801237E8(arg0);
    {
        s32 clear_count;
        u8 *clear_base;
        s32 **clear_cursor;
        s32 *clear_entry;

        clear_count = 14;
        clear_base = (u8 *)D_80129728;
        clear_cursor = (s32 **)(clear_base + 0x38);
        do {
            clear_entry = *clear_cursor;
            ASM_KEEP(clear_entry);
            clear_count += 1;
            *clear_entry = 0;
            clear_cursor = (s32 **)((u8 *)clear_cursor + 4);
        } while (clear_count < 28);
    }

done:
    return;
}

/* MECHANISM: The one-argument ABI plus external 20-way table/local epilogue edges yields the
   retail 0x18 frame and CFG. Scoped clear-loop locals recover v1/v0 coloring and the cursor
   delay slot; a0/a1 loop roles plus load-boundary keeps preserve the remaining schedules. */
