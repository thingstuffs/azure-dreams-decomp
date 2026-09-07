#include "common.h"

extern s16 func_800374F4(s32 arg0);
extern u8 D_8009EE9C[];
/* Initialize entity flags, transform, and type-dependent variant. */
void func_8009F148(void *entity, void *state, void *transform)
{
  register s32 variant_id ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
  u8 *entity_bytes = entity;
  *(((s8 *) state) + 0x14) = 1;
  *(((s8 *) state) + 0x15) = 1;
  *((s32 *) (((u8 *) transform) + 0xC)) = 0;
  *((s32 *) (((u8 *) transform) + 0x10)) = 0;
  *((s32 *) (((u8 *) transform) + 0x14)) = 0;
  *((s32 *) (entity_bytes + 0xA0)) = 0xFFE00000;
  *((s32 *) (((u8 *) transform) + 8)) = 0xFFE00000;
  *((u8 **) (entity_bytes + 0x50)) = D_8009EE9C;
  *((s16 *) (entity_bytes + 0x6C)) = func_800374F4(0x1000);
  variant_id = 0x12;
  if ((*((u8 *) (entity_bytes + 0x4D))) != variant_id)
  {
    variant_id = 0x59;
  }
  else
  {
    variant_id = 0x58;
  }
  *((s32 *) (entity + 0x60)) = variant_id;
}
