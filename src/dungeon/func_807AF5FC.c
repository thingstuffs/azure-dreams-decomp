typedef unsigned char u8;
typedef int s32;
void *func_800F6DFC(void *arg0)
{
  void *base;
  void *original;
  void *new_var;
  new_var = *((void **) (((u8 *) arg0) + 0x5C));
  original = arg0;
  arg0 = (u8 *) new_var + 0x20;
  if (arg0 != original)
  {
    s32 key = 0x15;
    loop:
    base = (u8 *) arg0 - 0x20;
    if ((*((u8 *) (((u8 *) arg0) - -0x13))) == key)
    {
      return base;
    }
    arg0 = (*((void **) (((u8 *) arg0) + 0x5C))) + 0x20;
    if (arg0 == original)
    {
      return 0;
    }
    goto loop;
  }
  return 0;
}
