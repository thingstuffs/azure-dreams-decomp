#ifndef FRONTEND_LIBCARD_DIALOG_PACKET_SETUP_G00380_H
#define FRONTEND_LIBCARD_DIALOG_PACKET_SETUP_G00380_H
/* Dialog packet setup; G00380; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_8000F90C, CL:main/func_8000F934, CL:main/func_8000FA30. */

#include "common.h"
#include "m2c_compat.h"

typedef struct { u8 bytes[4]; } Bytes4;

typedef struct {
    u32 address;
    u8 pad_04[2];
    u8 x;
    u8 y;
    u8 next_value;
    u8 next_kind;
    u8 pad_0A[2];
} Fields;

extern u8 D_800200A0[];
void card_boot_center_message_dialog_display(void *);

/* Functions defined in this translation unit. */
void *card_boot_build_paired_dialog_packets(void *buffer, s32 unused);
void card_boot_initialize_dialog_packets_and_display(s32 record);

#endif
