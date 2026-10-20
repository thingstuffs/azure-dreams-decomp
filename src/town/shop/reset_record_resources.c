#include "common.h"

typedef struct S_800B34A8_0 {
    u8 pad_00[0xA8];
    void * unk_A8;
} S_800B34A8_0;   /* arg0 in reset_record_resources */

typedef struct S_800B34A8_1 {
    u8 pad_00[0x98];
    s32 unk_98;
    s32 unk_9C;
} S_800B34A8_1;   /* ((S_800B34A8_0 *)arg0)->unk_A8 in reset_record_resources */
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} Color800497F4;
typedef struct {
    s32 unk0;         /* flag/counter; function is a no-op when 0 */
    Color800497F4 *unk4; /* pointer to the object's color */
} Struct800497F4;
void fade_color_to_gray(Struct800497F4 *object, s32 stop_at_gray);                /* extern */
struct FrameState; s32 advance_timed_tagged_stream(struct FrameState *);                         /* extern */


/* Resets the object substate and its two referenced resources. */
void reset_record_resources(void *object) {
    advance_timed_tagged_stream(object + 0x1C);
    fade_color_to_gray(((S_800B34A8_1 *)(((S_800B34A8_0 *)object)->unk_A8))->unk_98, 0);
    fade_color_to_gray(((S_800B34A8_1 *)(((S_800B34A8_0 *)object)->unk_A8))->unk_9C, 0);
}
