#include "common.h"
#include "shared/sprite_frame_state.h"

/* Default packed GPU color shared by the primitive builders. */
extern SpriteColor shared_primitive_color;

typedef struct {
    s32 unk0;         /* flag/counter; function is a no-op when 0 */
    SpriteColor *unk4; /* pointer to the object's color */
} Struct800497F4;

/* Fades color toward gray, restoring the template on arrival or optionally stopping if already gray. */
void fade_color_to_gray(Struct800497F4 *object, s32 stop_at_gray)
{
    SpriteColor *color;

    if (object->unk0 == 0) {
        return;
    }

    color = object->unk4;
    if ((color->unsigned_word << 8) != 0x80808000) {
        object->unk4->c.r -= 0x10;
        object->unk4->c.g -= 0x10;
        object->unk4->c.b -= 0x10;

        if ((object->unk4->unsigned_word << 8) == 0x80808000) {
            object->unk4->unsigned_word = shared_primitive_color.word;
        }
        return;
    }

    if (stop_at_gray != 0) {
        object->unk0 = 0;
    }
}
