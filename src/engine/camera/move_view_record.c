#include "common.h"
#include "engine/camera.h"

typedef struct S_8004D75C_sub {
    s32 w[16];
} S_8004D75C_sub;

typedef struct S_8004D75C {
    s32 unk0;
    S_8004D75C_sub sub;
} S_8004D75C;

/* Copies the 0x44-byte source struct to the destination and clears the source first word. */
void move_view_record(S_8004D75C *dst, S_8004D75C *src) {
    dst->unk0 = src->unk0;
    dst->sub = src->sub;
    src->unk0 = 0;
}
