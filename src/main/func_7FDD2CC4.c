/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80089C24_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
} S_80089C24_0;   /* temp_v0 in func_80089C24 */

typedef struct S_80089C24_1 {
    u8 pad_00[0x12];
    s16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80089C24_1;   /* var_s4 in func_80089C24 */

typedef struct S_80089C24_2 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80089C24_2;   /* ((S_80089C24_0 *)temp_v0)->unk_08 in func_80089C24 */


typedef struct Sol9Copy8 {
    u8 bytes[8];
} Sol9Copy8;

static inline void sol9_copy8(void *dst, const void *src, s32 ignored_size) {
    *(Sol9Copy8 *)dst = *(const Sol9Copy8 *)src;
    (void)ignored_size;
}

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80053428();                      /* extern */
M2C_UNK func_80053DA8(); /* extern */
M2C_UNK func_80067014();                     /* extern */
M2C_UNK func_800672D8();        /* extern */
M2C_UNK func_8006733C();        /* extern */
M2C_UNK func_8008A98C(); /* extern */
M2C_UNK func_8008ABD4();   /* extern */
M2C_UNK func_8008AE60();            /* extern */
extern u8 D_80013180;
extern u8 D_80013181;
extern u8 D_80013182;
extern u8 D_80013184;
extern u8 D_80013186;
extern M2C_UNK D_800786E8;
extern M2C_UNK D_80078AF0;
extern s8 D_80080A84;
extern s32 D_80080A94;
extern s32 D_80080A98;
extern s32 D_80080A9C;
extern u8 D_800888AC;
extern M2C_UNK D_8008A288;
extern M2C_UNK D_8008A794;
extern M2C_UNK D_8008AA40;
extern M2C_UNK D_8008AA84;
extern M2C_UNK D_8008AAE4;
extern M2C_UNK D_8008AB44;
extern M2C_UNK D_8008AC70;
extern M2C_UNK D_8008ACB4;
extern M2C_UNK D_8008AD58;
extern M2C_UNK D_8008AEEC;
extern M2C_UNK D_8008B030;
extern s32 D_8008B2B0;
extern s32 D_8008B2B4;
extern s32 D_8008B2BC;
extern M2C_UNK D_8008B2C4;
extern M2C_UNK D_8008B2D4;
extern s32 D_8008B2DC;
extern M2C_UNK D_8008B2E4;
extern M2C_UNK D_8008B2F0;
extern M2C_UNK D_8008B2FC;

/* Initializes the settings screen palette, labels, panels, and sliders. */
void func_80089C24(void) {
    u8 frame[0x278];
    s32 heading_x;
    s32 heading_y;
    s32 panel_x_fixed;
    s32 panel_y_fixed;
    s32 next_slider;
    s32 footer_text;
    s32 top_text;
    s32 choice_text;
    s32 middle_text;
    s32 choice_heading;
    s32 bottom_text;
    s32 channel_text;
    s32 next_channel;
    s32 second_level;
    s32 first_level;
    s32 palette_mask;
    s32 *levels;
    s32 descriptor_color;
    register s32 index;
    s32 item_index;
    s32 third_level;
    register void *screen_object;
    void *settings;
#define panel_flags (*(s16 *)(frame + 0x18 + 0))
#define panel_owner (*(void **)(frame + 0x18 + 4))
#define panel_color (*(s32 *)(frame + 0x18 + 8))
#define panel_x (*(s16 *)(frame + 0x18 + 12))
#define panel_y (*(s16 *)(frame + 0x18 + 14))
#define panel_width (*(s16 *)(frame + 0x18 + 16))
#define panel_height (*(s16 *)(frame + 0x18 + 18))
#define panel_style (*(s16 *)(frame + 0x18 + 20))
#define panel_shading (*(s16 *)(frame + 0x18 + 22))
#define slider_index (*(s32 *)(frame + 0x18 + 24))
#define label_flags (((s16 *)(frame + 0x40))[0])
#define label_order (((s16 *)(frame + 0x40))[1])
#define label_text (((s32 *)(frame + 0x40))[1])
#define label_owner (*(void **)(frame + 0x40 + 12))
#define label_color (((s32 *)(frame + 0x40))[4])
#define label_x (((s16 *)(frame + 0x40))[10])
#define label_y (((u16 *)(frame + 0x40))[11])
#define label_style (((s16 *)(frame + 0x40))[12])
#define label_font (((s16 *)(frame + 0x40))[13])
#define label_extra (((s16 *)(frame + 0x40))[14])
#define label_value (((s32 *)(frame + 0x40))[8])
#define label_index (((s32 *)(frame + 0x40))[9])

    settings = NULL;
    sol9_copy8(frame + 0x270, &D_800888AC, 8);
    first_level = 0x100;
    D_80080A84 = 1;
    levels = (s32 *)&D_8008B2F0;
    if (D_80080A98 != 0x7FFF) {
        first_level = (s32) D_80080A98 >> 7;
    }
    second_level = 0x100;
    levels[0] = first_level;
    if (D_80080A9C != 0x7FFF) {
        second_level = (s32) D_80080A9C >> 7;
    }
    third_level = 0x100;
    levels[1] = second_level;
    if (D_80080A94 != 0x7FFF) {
        third_level = (s32) D_80080A94 >> 7;
    }
    levels[2] = third_level;
    func_80053DA8(0x200);
    func_8006733C(frame + 0x270, frame + 0x70);
    func_80067014(0);
    index = 0xFF;
    palette_mask = ~0x7FFF;
    do {
        *(u16 *)(frame + index * 2 + 0x70) = *(u16 *)(frame + index * 2 + 0x70) | palette_mask;
        index -= 1;
    } while (index >= 0);
    func_800672D8(frame + 0x270, frame + 0x70);
    screen_object = func_8003FC64(0x11);
    if (screen_object != NULL) {
        ((S_80089C24_0 *)screen_object)->unk_10 = &D_8008A288;
        func_8004491C(screen_object, &D_8008A794);
        settings = screen_object + 0x20;
        ((S_80089C24_2 *)(((S_80089C24_0 *)screen_object)->unk_08))->unk_06 = 0xF0;
        (*(s16 *)((u8 *)settings + 4)) = 0x20;
        (*(s16 *)((u8 *)settings + 0x14)) = (s16) ((u8) D_80013184 >> 5);
        index = 2;
        (*(s16 *)((u8 *)settings + 0xE)) = (s16) D_80013180;
        (*(s16 *)((u8 *)settings + 0x10)) = (s16) D_80013181;
        ((S_80089C24_1 *)settings)->unk_12 = (s16) D_80013182;
        do {
            if (*(s16 *)((u8 *)settings + index * 2 + 14) >= 0xFF) {
                *(s16 *)((u8 *)settings + index * 2 + 14) = 0x100;
            }
            index -= 1;
        } while (index >= 0);
        if ((D_80013186 & 1) == 0) {
            ((S_80089C24_1 *)settings)->unk_16 = (u16) (((S_80089C24_1 *)settings)->unk_16 | 2);
        } else {
            ((S_80089C24_1 *)settings)->unk_16 = (u16) (((S_80089C24_1 *)settings)->unk_16 & 0xFFFD);
        }
    }
    func_80053428(settings);
    panel_x_fixed = 0x400000;
    panel_y_fixed = 0xA00000;
    *(s32 *)(frame + 0x0) = panel_x_fixed;
    *(s32 *)(frame + 0x4) = panel_y_fixed;
    func_8008A98C(frame, &D_8008AC70, &D_80078AF0, settings);
    heading_x = 0x94;
    heading_y = 0x44;
    *(s16 *)(frame + 0x2) = heading_x;
    *(s16 *)(frame + 0x6) = heading_y;
    func_8008A98C(frame, &D_8008ACB4, &D_800786E8, settings);
    label_y = 0xD0;
    label_style = 1;
    label_extra = 0;
    label_font = 0x7C80;
    label_color = 0x808080;
    index = 0x1A;
    label_owner = settings;
    label_flags = 0;
    do {
        label_x = index * 8 + 48;
        footer_text = ((s32 *)&D_8008B2FC)[index];
        label_order = index * 2 + 30;
        label_text = footer_text;
        func_8008AE60((u8 *)&D_8008AEEC, &label_flags);
        index -= 1;
    } while (index >= 0);
    label_x = 0x74;
    label_y = 0xC;
    label_text = D_8008B2B0;
    func_8008AE60((u8 *)&D_8008B030, &label_flags);
    index = 0;
    label_x = 0x20;
    do {
        label_y = index * 0xC + 0x20;
        top_text = ((s32 *)&D_8008B2B4)[index];
        label_text = top_text;
        func_8008AE60((u8 *)&D_8008B030, &label_flags);
        index += 1;
    } while (index < 2);
    item_index = 0;
    label_y -= 6;
    do {
        label_value = 0;
        label_index = item_index;
        label_x = item_index * 0x40 + 0xBE;
        choice_text = ((s32 *)&D_8008B2BC)[item_index];
        label_text = choice_text;
        func_8008AE60((u8 *)&D_8008AD58, &label_flags);
        item_index += 1;
    } while (item_index < 2);
    label_x = 0x20;
    item_index = 3;
    do {
        label_y = item_index * 0xC + 0x40;
        middle_text = ((s32 *)&D_8008B2C4)[item_index];
        label_text = middle_text;
        func_8008AE60((u8 *)&D_8008B030, &label_flags);
        item_index -= 1;
    } while (item_index >= 0);
    item_index = 1;
    do {
        label_x = item_index * 0x40 + 0xBE;
        choice_heading = ((s32 *)&D_8008B2D4)[item_index];
        label_text = choice_heading;
        func_8008AE60((u8 *)&D_8008B030, &label_flags);
        item_index -= 1;
    } while (item_index >= 0);
    label_x = 0x20;
    item_index = 0;
    do {
        label_y = item_index * 0xC + 0x78;
        bottom_text = ((s32 *)&D_8008B2DC)[item_index];
        label_text = bottom_text;
        func_8008AE60((u8 *)&D_8008B030, &label_flags);
        item_index += 1;
    } while (item_index < 2);
    label_x = 0xB2;
    item_index = 2;
    do {
        label_y = item_index * 0xC + 0x7E;
        channel_text = ((s32 *)&D_8008B2E4)[item_index];
        label_text = channel_text;
        func_8008AE60((u8 *)&D_8008B030, &label_flags);
        item_index -= 1;
    } while (item_index >= 0);
    panel_x = 0x1C;
    panel_width = 0x100;
    panel_style = 2;
    panel_shading = 1;
    descriptor_color = 0x202020;
    panel_color = descriptor_color;
    panel_flags = 0;
    panel_owner = settings;
    panel_height = 0x1C;
    panel_y = 0x1C;
    func_8008ABD4(&D_8008AA40, &panel_flags);
    panel_height = 0x34;
    panel_y = 0x3C;
    func_8008ABD4(&D_8008AA40, &panel_flags);
    panel_height = 0x2E;
    panel_y = 0x74;
    func_8008ABD4(&D_8008AA40, &panel_flags);
    panel_x = 0x20;
    panel_y = 0xA6;
    panel_width = 0x40;
    panel_height = 0x18;
    func_8008ABD4(&D_8008AB44, &panel_flags);
    panel_x = 0xCA;
    panel_height = 8;
    panel_width = 0x40;
    panel_shading = 0;
    slider_index = 2;
    do {
        panel_color = 0xFF << (slider_index * 8);
        panel_y = (slider_index * 0xC) + 0x7E;
        func_8008ABD4(&D_8008AA84, &panel_flags);
        next_channel = slider_index - 1;
        slider_index = next_channel;
    } while (next_channel >= 0);
    panel_height = 8;
    panel_color = 0xFFFFFF;
    panel_style = 0;
    panel_shading = 0;
    slider_index = 2;
    do {
        panel_y = ((slider_index + 1) * 0xC) + 0x40;
        func_8008ABD4(&D_8008AAE4, &panel_flags);
        next_slider = slider_index - 1;
        slider_index = next_slider;
    } while (next_slider >= 0);
}
