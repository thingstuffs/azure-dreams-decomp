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

void func_808B34B0(void)
{
    UnalignedWord local;
    unsigned long work_offset;
    u8 *base;
    OverlayWork *work;

    local = D_A0700140;
    work_offset = (unsigned long)&D_000012F0;
    base = D_A0700F40;
    work = (OverlayWork *)(base + work_offset);
    work->kind = D_A0700F58->callback(&local);
}
