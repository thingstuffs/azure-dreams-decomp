#include "common.h"
#include "shared/object_flags.h"

extern void func_800478B8(void *arg0);

/* Advance and fade the effect, marking it finished when faded out or flagged. */
void func_8186898C(void *effect, void *position, void *render_data)
{
    u8 *effect_state = *(u8 **)effect;
    u16 coordinate;
    u8 intensity;

    *(u16 *)(effect_state + 0x14) = *(u16 *)(effect_state + 0x14) + 1;
    coordinate = *(u16 *)((u8 *)render_data + 0x1E);
    intensity = *(u8 *)((u8 *)render_data + 0xE);
    coordinate += 0x400;
    intensity -= 4;
    *(u16 *)((u8 *)render_data + 0x1E) = coordinate;
    *(u16 *)((u8 *)render_data + 0x1C) = coordinate;
    *(u8 *)((u8 *)render_data + 0xE) = intensity;
    *(u8 *)((u8 *)render_data + 0xD) = intensity;
    *(u8 *)((u8 *)render_data + 0xC) = intensity;
    if (intensity == 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
    *(u16 *)((u8 *)position + 0xA) -= 8;
    func_800478B8(render_data);
    if (*(u16 *)((u8 *)render_data + 0x14) & 0x6000) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
