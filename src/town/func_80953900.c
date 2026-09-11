#include "common.h"

typedef struct {
    s16 state;
    s16 timer;
    u16 flags;
    s16 selection;
    s16 quantity;
} TownEntity;

typedef struct {
    s16 active;
    s16 pad02;
    void *data;
    u8 pad08[4];
    void *owner;
    u32 color;
    s16 x;
    s16 y;
    s16 mode;
    s16 value;
    s16 enabled;
    s16 pad1E;
    u8 tail[0x10];
} TownRecord30;

typedef struct {
    s16 active;
    s16 pad02;
    void *owner;
    u32 color;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 mode;
    s16 enabled;
    u8 tail[0x10];
} TownRecord28;

typedef struct {
    s32 word[6];
} WordTable18;

typedef struct {
    u16 value[6];
} __attribute__((packed)) HalfTable0C;

typedef struct {
    s16 first;
    u16 second;
} __attribute__((packed)) Pair04;

typedef struct {
    Pair04 pair[6];
} __attribute__((packed)) PairTable18;

extern WordTable18 D_80020088;
extern HalfTable0C D_800200A0;
extern PairTable18 D_800200AC;
extern u8 D_80020000[];
extern u8 D_800200C4[];
extern u8 D_800200D0[];
extern u8 D_800203D8[];
extern u8 D_800204AC[];
extern u8 D_80021028[];
extern s32 D_80012D5C;
extern s32 D_80024300[];
extern s16 D_80024308[];
extern s32 D_800814A0;
extern u8 D_80083160[];
extern u16 D_80113158;
extern s32 D_8011315C;

extern void func_800201C8(void *, void *);
extern void func_8002025C(void *, void *);
extern s32 func_80033B9C(s32);
extern s32 func_80033BC0();
extern void func_80043FB8(void *, s32);
extern void SD_Call(s32);
extern s32 func_800B1BEC(s32, s32, s32);
extern void func_800B1DBC(s32);

/* Updates the selection menu, quantity, payment, and closing state. */
void func_80020900(TownEntity *menu)
{
    TownEntity *entity = menu;
    TownRecord30 text_record;
    TownRecord28 panel_record;
    WordTable18 option_labels = D_80020088;
    HalfTable0C option_ids = D_800200A0;
    PairTable18 factor_pairs = D_800200AC;
    s32 option_index;
    s32 row_y;
    s32 total_factor;
    s32 scaled_quantity;
    s32 second_factor;
    s16 first_factor;
    s16 *prices;
    s32 quantity;
    s32 state;
    u8 *input;
    u8 *data_page;
    u8 *label_page;
    register TownRecord30 *label_record ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 *label_cursor;
    register void *text_pool ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register TownRecord30 *text_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 text_color;

    input = D_80083160;

    if (func_80033BC0(0x590) != 0) {
        entity->state = 0x100;
    }
    func_80043FB8(D_800200C4, entity->state);

    state = entity->state;
    if (state == 3) goto state_3;
    if (state >= 4) goto state_high;
    if (state == 1) goto state_1;
    if (state >= 2) goto state_2;
    if (state == 0) goto state_0;
    goto exit;

state_high:
    if (state == 0x101) goto state_101;
    if (state >= 0x102) goto state_200_check;
    if (state == 0x100) goto state_100;
    goto exit;
state_200_check:
    if (state == 0x200) goto state_200;
    goto exit;

state_0:
    if (func_80033BC0(0x592) != 0) goto exit;
    panel_record.x = 0xC8;
    panel_record.y = 0x10;
    panel_record.width = 0x38;
    panel_record.height = 0x58;
    panel_record.mode = 2;
    panel_record.enabled = 1;
    panel_record.color = 0x606060;
    panel_record.active = 0;
    panel_record.owner = entity;
    func_8002025C(D_800203D8, &panel_record);

    panel_record.x = 0xCA;
    panel_record.y = 0x1E;
    panel_record.width = 0x34;
    panel_record.height = 0x0C;
    panel_record.mode = 0;
    panel_record.enabled = 1;
    panel_record.color = 0xB0B0B0;
    panel_record.active = 0;
    panel_record.owner = entity;
    func_8002025C(D_80021028, &panel_record);

    text_color = 0x808080;
#ifdef NON_MATCHING
    data_page = D_80020000;
#else
    data_page = (u8 *)0x80020000;
#endif
    ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    text_pool = data_page + 0x4AC;
    text_arg = &text_record;
    text_record.x = 0xCC;
    text_record.y = 0x14;
    text_record.value = 0x7C80;
    text_record.mode = 3;
    text_record.enabled = 0;
    text_record.color = text_color;
    text_record.data = D_800200D0;
    text_record.active = 0;
    text_record.owner = entity;
    func_800201C8(text_pool, text_arg);

    option_index = 5;
    label_record = &text_record;
    label_page = data_page;
    label_cursor = &text_record.x;
    row_y = 0x5C;
    text_record.x = 0xDC;
    do {
        text_pool = label_page + 0x4AC;
        text_arg = label_record;
        text_record.y = row_y;
        text_record.data = (void *)*(s32 *)((u8 *)label_cursor + 0x58);
        label_cursor -= 2;
        row_y -= 0x0C;
        option_index--;
        func_800201C8(text_pool, text_arg);
    } while (option_index >= 0);
    entity->state = (u16)entity->state + 1;
    entity->timer = 0;
    goto exit;

state_1:
    if ((*(s32 *)(input + 0x10) & 0x1000) &&
        (entity->selection > 0)) {
        SD_Call(0x502);
        entity->selection = (u16)entity->selection - 1;
    } else if ((*(s32 *)(input + 0x10) & 0x4000) &&
               (entity->selection < 5)) {
        SD_Call(0x502);
        entity->selection = (u16)entity->selection + 1;
    }
    if (*(s32 *)(input + 0x10) & 0x20) {
        SD_Call(0x515);
        func_80033B9C(0x592);
        func_80033B9C(0x593);
        entity->state = 0x100;
        goto exit;
    }
    if (*(s32 *)(input + 0x10) & 0x40) {
        volatile s32 *money = &D_80012D5C;

        SD_Call(0x503);
        entity->quantity = 1;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        *money -= 100;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        D_80113158 = option_ids.value[entity->selection];
        func_80033B9C(0x592);
        D_80024300[0] = func_800B1BEC(0, -0x48, -0x28);
        entity->timer = -1;
        entity->state = (u16)entity->state + 1;
        goto exit;
    }
    goto exit;

state_2:
    if (entity->timer > 0) {
        entity->timer = (u16)entity->timer - 1;
    }
    if (func_80033BC0(0x592) != 0) goto exit;
    if (entity->timer > 0) goto exit;
    if (entity->timer < 0) {
        entity->timer = 0x10;
    }
    entity->state = (u16)entity->state + 1;
    goto exit;

state_3:
    if (entity->timer > 0) {
        entity->timer = (u16)entity->timer - 1;
        goto exit;
    }
    if ((*(s32 *)(input + 8) & 0x2000) &&
        (entity->quantity < 10) &&
        ((u32)D_80012D5C >= 100U)) {
        SD_Call(0x502);
        func_80033B9C(0x592);
        func_80033B9C(0x594);
        entity->quantity = (u16)entity->quantity + 1;
        do {
        } while (0);
        D_80012D5C -= 100;
        entity->timer = 0x10;
        entity->state = (u16)entity->state - 1;
        goto exit;
    }
    if ((*(s32 *)(input + 8) & 0x8000) &&
        (entity->quantity >= 2)) {
        s32 *money = &D_80012D5C;

        SD_Call(0x502);
        func_80033B9C(0x592);
        func_80033B9C(0x595);
        entity->quantity = (u16)entity->quantity - 1;
        do {
        } while (0);
        *money += 100;
        entity->timer = 0x10;
        entity->state = (u16)entity->state - 1;
        goto exit;
    }
    if (*(s32 *)(input + 0x10) & 0x40) {
        Pair04 *selected_pair;

        do {
            SD_Call(0x503);
            selected_pair = factor_pairs.pair;
        } while (0);
        prices = D_80024308;
        selected_pair += entity->selection;
        first_factor = prices[*(s16 *)(void *)selected_pair];
        quantity = entity->quantity;
        scaled_quantity = quantity * first_factor;
        second_factor = prices[(s16)*(u16 *)((u8 *)selected_pair + 2)];
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        D_80113158 = option_ids.value[entity->selection];
        total_factor = scaled_quantity * second_factor;
        D_8011315C = total_factor * 100;
        func_80033B9C(0x592);
        func_800B1DBC(D_80024300[0]);
        entity->state = 0x100;
    }
    if (*(s32 *)(input + 0x10) & 0x20) {
        SD_Call(0x515);
        D_80012D5C += entity->quantity * 100;
        func_800B1DBC(D_80024300[0]);
        func_80033B9C(0x592);
        func_80033B9C(0x593);
        entity->state = 0x200;
        goto exit;
    }
    goto exit;

state_100:
    entity->flags |= 0x8000;
    func_80033B9C(0x590);
    entity->state = (u16)entity->state + 1;
    goto exit;

state_101:
    {
        s32 *global_flags = &D_800814A0;

        ((u16 *)entity)[-1] |= 0x8000;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        *global_flags |= 0x8000;
    }
    goto exit;

state_200:
    if (func_80033BC0(0x592) == 0) {
        entity->state = 1;
        goto exit;
    }
    goto exit;

exit:
    return;
}
