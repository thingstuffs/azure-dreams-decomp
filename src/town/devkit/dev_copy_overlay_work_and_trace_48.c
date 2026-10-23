/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_pointees.h"

typedef struct S_808B3620_4 {
    u8 pad_00[0x64];
    union { M2C_UNK (*s)(u8 *, u8 *, s32, s8 *); M2C_UNK (*u)(u8 *, u8 *, s32); } unk_64;   /* printf-style trace hook */
} S_808B3620_4;   /* *(volatile void **)(D_A0700000 + 0xF58) in dev_copy_overlay_work_and_trace_48 */


   /* held_arg0 in dev_copy_overlay_work_and_trace_48 */

typedef struct S_808B3620_3 {
    u8 pad_00[0x6C];
    M2C_UNK (*unk_6C)(s32);
} S_808B3620_3;   /* *(volatile void **)(D_A0700000 + 0xF58) in dev_copy_overlay_work_and_trace_48 */

extern u8 devkit_overlay_page[];
extern u8 D_A0700150[];
extern u8 D_A0700158[];
extern u8 D_A0700168[];
extern u8 D_A070017C[];

/* The 0x34-byte overlay work block; gcc copies it with a 16-byte block-move loop plus one word. */
typedef struct OverlayWork {
    s32 words[13];
} OverlayWork;

/* Copies overlay state into ov_work, prints both kinds, and emits a source mark. */
void dev_copy_overlay_work_and_trace_48(s8 *overlay_state) {
    s8 *kind_format;
    s8 *p = overlay_state;

    *(OverlayWork *)(devkit_overlay_page + 0xF40) = *(OverlayWork *)p;
    kind_format = devkit_overlay_page + 0x144;
    ((S_808B3620_4 *)(*(void **)(devkit_overlay_page + 0xF58)))->unk_64.u(kind_format, D_A0700150, ((TownFormatKindView *)p)->unk_08);
    ((S_808B3620_4 *)(*(void **)(devkit_overlay_page + 0xF58)))->unk_64.u(kind_format, D_A0700158, *(s32 *)(devkit_overlay_page + 0xF48));
    ((S_808B3620_4 *)(*(void **)(devkit_overlay_page + 0xF58)))->unk_64.u(D_A0700168, D_A070017C, 0x30);
    ((S_808B3620_3 *)(*(void **)(devkit_overlay_page + 0xF58)))->unk_6C(0);
}
