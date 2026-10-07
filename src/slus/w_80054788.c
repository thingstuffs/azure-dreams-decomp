#include "shared/sound_state.h"
#include "common.h"

/* Canonical status-block struct (established in w_800540A8.c / w_80054C58.c /
   w_800559B4.c / w_8005440C.c / w_80054E00.c). This function only reads
   flags1 (offset 0x0). */

/* Canonical task/timer object struct (established in w_800559B4.c /
   w_800540A8.c / w_80054C58.c / w_80054E00.c). Only its address is taken by
   this function, no fields accessed here. */

/* Canonical task/event object struct (established in w_8005440C.c). Only its
   address is taken by this function, no fields accessed here. */


extern void func_8005497C(u16 a0);
extern void func_800549FC(u16 a0);
extern void func_800553D4(u8 a0);
extern void func_80054104(void);
extern void func_80054E00(s32 a0);
extern void func_80054A7C(u8 a0);
extern void func_80054F9C(u32 a0, void *a1);

/* Dispatches packed events by status nibble and enabled event flags. */
void func_80054788(s32 event) {
    s32 event_bits = event;
    register s16 packed_event = event_bits;

    switch (event_bits & 0xF0) {
    case 0x10:
        func_8005497C((u16)packed_event);
        break;
    case 0x20:
        func_800549FC((u16)packed_event);
        break;
    case 0x70:
        if (event_bits & 1) {
            func_800553D4(0x71);
        }
        if (event_bits & 2) {
            func_80054104();
        }
        if (event_bits & 4) {
            func_80054E00(0x74);
        }
        break;
    case 0xE0:
        if (event_bits & 1) {
            func_800553D4(0xE1);
        }
        if (event_bits & 4) {
            func_80054E00(0xE4);
        }
        break;
    case 0xF0:
        if (event_bits & 1) {
            func_800553D4(0xF1);
        }
        if (event_bits & 4) {
            func_80054E00(0xF4);
        }
        break;
    case 0xB0:
    case 0xC0:
    case 0xD0:
        if (packed_event & 1) {
            if (D_800847D0.flags00 & 0x100) {
                if (!(D_800847D0.flags00 & 0x1000)) {
                    func_80054F9C(packed_event & 0xFFF1, &D_800848F8);
                }
            }
        }
        if (packed_event & 4) {
            if (D_800847D0.flags00 & 0x400) {
                if (!(D_800847D0.flags00 & 0x4000)) {
                    func_80054F9C(packed_event & 0xFFF4, &D_80084858);
                }
            }
        }
        break;
    default:
        func_80054A7C(packed_event & 0xFF);
        break;
    }
}
