#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) UnalignedWord;

typedef struct {
    u8 pad[0x50];
    s32 (*callback)(UnalignedWord *);
} CallbackOwner;

typedef struct {
    s32 kind;
    s32 mode;
} OverlayWork;

extern UnalignedWord D_A0700140;
extern u8 *D_A0700F40;
extern CallbackOwner *D_A0700F58;
extern OverlayWork D_000012F0;

// Set the overlay work kind from the callback result using a copy of the stored word.
void func_808B34B0(void)
{
    UnalignedWord callback_input;
    unsigned long work_offset;
    u8 *overlay_base;
    OverlayWork *overlay_work;

    callback_input = D_A0700140;
    work_offset = (unsigned long)&D_000012F0;
    overlay_base = D_A0700F40;
    overlay_work = (OverlayWork *)(overlay_base + work_offset);
    overlay_work->kind = D_A0700F58->callback(&callback_input);
}
