
struct S_80083178
{
  char pad0[2];
  unsigned short unk2;
  char pad4[6];
  unsigned short unkA;
  char padC[0x94];
  short f_A0;
  char pad_a2[2];
  short f_A4;
  short f_A6;
  short f_A8;
  char pad_aa[0xB4 - 0xAA];
  void (*callback)(void);
  void *field_B8;
  char pad_bc[(0xD8 - 0xB8) - 4];
  void *ptr;
  char pad_dc[0x1C4 - 0xDC];
};
typedef struct 
{
  unsigned char data[24];
} MonsterInitialStats;
typedef struct 
{
  unsigned char data[12];
} Trap;
typedef struct 
{
  unsigned char data[8];
} StatGrowth;
extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
extern short D_80084808[8];
extern struct S_80083178 D_80083178;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern void func_80016DDC(void *, void *, s32);
/* Copies records through the end marker, patches control fields, and returns the destination end. */
u8 *func_806D2C3C(u8 *dst, u8 *src, s32 control_bits, u32 byte_value)
{
  u8 *field_cursor;
  u32 high_bits;
  u8 *field_ptr;
  u32 byte_bits;
  field_cursor = dst + 12;
  do
  {
    func_80016DDC(dst, src, 5);
    field_ptr = field_cursor;
    dst += 20;
    if (control_bits != 0)
    {
      *((u32 *) (field_ptr - 4)) = (control_bits & 0x3FFF0000) | 0xC0000010;
    }
    do { } while (0);
    src += 20;
    {
      u32 packed_word;
      u32 combined_bits;
      high_bits = ((control_bits >> 8) & 0x3F) << 24;
      byte_bits = (byte_value & 0xFF) << 16;
      packed_word = 0xC0000000;
      packed_word |= byte_bits;
      combined_bits = high_bits;
      combined_bits |= packed_word;
      packed_word = combined_bits;
      packed_word |= *((u16 *) field_ptr);
      *((u32 *) field_ptr) = packed_word;
    }
    field_cursor += 20;
  }
  while (src[-19] != 0x80);
  return dst;
}
