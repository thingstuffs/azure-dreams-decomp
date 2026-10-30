#ifndef FRONTEND_LIBCARD_SLOT_DETAIL_REFRESH_G00388_H
#define FRONTEND_LIBCARD_SLOT_DETAIL_REFRESH_G00388_H
/* Slot detail refresh; G00388; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_800112D8, CL:main/func_80011390, CL:main/func_80011818, CL:main/func_800119B4, PD:main/image_25c800:800283EC. */

#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard.h"
#include "modules/main_server_ship_interfaces.h"
#include "m2c_compat.h"

typedef struct Node {
    void *field0;
    struct Node *field4;
    u16 field8;
    s16 fieldA;
} Node;

typedef struct S_80024818_0 {
    u8 pad_00[0x80];
    s32 unk_80;
} S_80024818_0;

/* root in card_boot_format_empty_slot_guidance */
typedef struct S_80024818_1 {
    u8 pad_00[0xB4C];
    Node * unk_B4C;
} S_80024818_1;

typedef struct S_800249B4_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800249B4_3;

typedef struct S_800249B4_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800249B4_4;

typedef struct S_800249B4_0 {
    u8 pad_00[0xB4C];
    void * unk_B4C;
} S_800249B4_0;

typedef struct S_800249B4_1 {
    s32 unk_00;
    void * unk_04;
} S_800249B4_1;

typedef struct S_800249B4_2 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800249B4_2;

extern void strcat(void *dest, void *src);
extern void strcpy(void *dest, void *src);
extern void *D_800283B8[];
extern u8 D_800283C4[];
extern void *D_800283F4[];
extern u8 D_800283FC[];

extern u8 *card_empty_slot_guidance_lines[];

/* Functions defined in this translation unit. */
void card_boot_format_empty_slot_guidance(void *context);
void build_a_trigonometric_table_processes_up_eight_height_offset_segments(void *context);

#endif
