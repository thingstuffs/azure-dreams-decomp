#include "common.h"
#include "records/Rec_func_80027018_arg0.h"


typedef struct S_800270E0_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800270E0_1;   /* ((Rec_func_80027018_arg0 *)arg0)->unk_FC.as_pv in card_boot_initialize_save_heading_layout */

typedef struct S_800270E0_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800270E0_2;   /* ((Rec_func_80027018_arg0 *)arg0)->unk_F0.as_pv in card_boot_initialize_save_heading_layout */

typedef struct S_800270E0_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800270E0_3;   /* ((Rec_func_80027018_arg0 *)arg0)->unk_F4.as_pv in card_boot_initialize_save_heading_layout */

typedef struct S_800270E0_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800270E0_4;   /* ((Rec_func_80027018_arg0 *)arg0)->unk_F8.as_pv in card_boot_initialize_save_heading_layout */

typedef struct S_800270E0_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800270E0_5;   /* ((S_800270E0_1 *)(((Rec_func_80027018_arg0 *)arg0)->unk_FC.as_pv))->unk_04 in card_boot_initialize_save_heading_layout */

typedef struct S_800270E0_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800270E0_6;   /* ((S_800270E0_2 *)(((Rec_func_80027018_arg0 *)arg0)->unk_F0.as_pv))->unk_04 in card_boot_initialize_save_heading_layout */

typedef struct S_800270E0_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800270E0_7;   /* ((S_800270E0_3 *)(((Rec_func_80027018_arg0 *)arg0)->unk_F4.as_pv))->unk_04 in card_boot_initialize_save_heading_layout */

typedef struct S_800270E0_8 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800270E0_8;   /* ((S_800270E0_4 *)(((Rec_func_80027018_arg0 *)arg0)->unk_F8.as_pv))->unk_04 in card_boot_initialize_save_heading_layout */


#include "frontend/libcard/interfaces.h"
void format_save_heading_text(void *);                            /* extern */
void func_80027080(void *, s32, s32);       /* extern */


/* Initializes the object and positions its four components. */
void card_boot_initialize_save_heading_layout(void *object) {
    format_save_heading_text(object);
    func_80027080(object + 4, 0x36, 0x10);
    card_boot_bind_save_heading_display_data(object);
    ((S_800270E0_5 *)(((S_800270E0_1 *)(((Rec_func_80027018_arg0 *)object)->unk_FC.as_pv))->unk_04))->unk_08 = 0x8E;
    ((S_800270E0_5 *)(((S_800270E0_1 *)(((Rec_func_80027018_arg0 *)object)->unk_FC.as_pv))->unk_04))->unk_0A = 0x82;
    ((S_800270E0_6 *)(((S_800270E0_2 *)(((Rec_func_80027018_arg0 *)object)->unk_F0.as_pv))->unk_04))->unk_08 = 9;
    ((S_800270E0_6 *)(((S_800270E0_2 *)(((Rec_func_80027018_arg0 *)object)->unk_F0.as_pv))->unk_04))->unk_0A = 0xA;
    ((S_800270E0_7 *)(((S_800270E0_3 *)(((Rec_func_80027018_arg0 *)object)->unk_F4.as_pv))->unk_04))->unk_08 = 0x42;
    ((S_800270E0_7 *)(((S_800270E0_3 *)(((Rec_func_80027018_arg0 *)object)->unk_F4.as_pv))->unk_04))->unk_0A = 0xA;
    ((S_800270E0_8 *)(((S_800270E0_4 *)(((Rec_func_80027018_arg0 *)object)->unk_F8.as_pv))->unk_04))->unk_08 = 0x24;
    ((S_800270E0_8 *)(((S_800270E0_4 *)(((Rec_func_80027018_arg0 *)object)->unk_F8.as_pv))->unk_04))->unk_0A = 0xA;
}
