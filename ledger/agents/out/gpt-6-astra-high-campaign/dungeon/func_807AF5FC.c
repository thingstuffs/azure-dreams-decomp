typedef unsigned char u8;
typedef int s32;
/* Return the base of the next type 0x15 entity in the ring, or null if absent. */
void *func_800F6DFC(void *entity)
{
  void *entity_base;
  void *first_entity;
  void *next_base;
  next_base = *((void **) (((u8 *) entity) + 0x5C));
  first_entity = entity;
  entity = (u8 *) next_base + 0x20;
  if (entity != first_entity)
  {
    s32 target_type = 0x15;
    loop:
    entity_base = (u8 *) entity - 0x20;
    if ((*((u8 *) (((u8 *) entity) - -0x13))) == target_type)
    {
      return entity_base;
    }
    entity = (*((void **) (((u8 *) entity) + 0x5C))) + 0x20;
    if (entity == first_entity)
    {
      return 0;
    }
    goto loop;
  }
  return 0;
}
