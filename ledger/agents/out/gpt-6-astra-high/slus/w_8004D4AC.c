#include "common.h"

#include "common.h"

#include "common.h"

typedef struct
{
  s16 m[3][3];
  s32 t[3];
} MATRIX;

typedef struct
{
  s16 vx;
  s16 vy;
  s16 vz;
  s16 pad;
} SVECTOR;

typedef struct
{
  s32 vx;
  s32 vy;
  s32 vz;
} VECTOR;

/* D_80083178 is declared canonically (include/globals.h -> include/game.h). The
 * game.h struct doesn't expose the SVECTOR sub-fields this function needs, so use
 * the same local-cast reconcile the landed twin func_8004D294 uses
 * (src/w_8004D294.c:25): a private S_80083178_local layout cast over &D_80083178. */
typedef struct
{
  char pad0[0x94];
  SVECTOR field_94;
  SVECTOR field_9C;
  short f_A4;
  short f_A6;
  short f_A8;
  char pad_aa[0xAC - 0xAA];
  SVECTOR field_AC;
  void (*callback)(void);
  void *field_B8;
  char pad_bc[(0xD8 - 0xB8) - 4];
  void *ptr;
  char pad_dc[0x1C4 - 0xDC];
} S_80083178_local;

extern void RotMatrix(SVECTOR *r, MATRIX *m);
extern void SetRotMatrix(MATRIX *m);
extern void SetTransMatrix(MATRIX *m);
extern void TransMatrix(MATRIX *m, VECTOR *v);
extern void RotTrans(SVECTOR *v0, VECTOR *v1, s32 *flg);
extern void CompMatrix(MATRIX *m0, MATRIX *m1, MATRIX *m2);
extern void func_80041900(MATRIX *m);

/* Build and install the combined rotation and translation from global transform state. */
void func_8004D4AC(void)
{
  S_80083178_local *transform = (S_80083178_local *)&D_80083178;
  VECTOR rotated_pos;
  MATRIX base_mat;
  MATRIX combined_mat;
  MATRIX offset_mat;
  MATRIX *offset_mat_ptr;
  SVECTOR neg_offset;
  s32 gte_flags;
  offset_mat.t[2] = 0;
  offset_mat.t[1] = 0;
  offset_mat.t[0] = 0;
  base_mat.t[2] = 0;
  offset_mat_ptr = &offset_mat;
  base_mat.t[1] = 0;
  base_mat.t[0] = 0;
  RotMatrix(&transform->field_AC, &offset_mat);
  SetRotMatrix(offset_mat_ptr);
  SetTransMatrix(&offset_mat);
  neg_offset.vx = -transform->f_A4;
  neg_offset.vy = -transform->f_A6;
  neg_offset.vz = -transform->f_A8;
  RotTrans(&neg_offset, &rotated_pos, &gte_flags);
  TransMatrix(&offset_mat, &rotated_pos);
  RotMatrix(&transform->field_9C, &base_mat);
  SetRotMatrix(&base_mat);
  SetTransMatrix(&base_mat);
  RotTrans(&transform->field_94, &rotated_pos, &gte_flags);
  TransMatrix(&base_mat, &rotated_pos);
  func_80041900(&base_mat);
  CompMatrix(&base_mat, &offset_mat, &combined_mat);
  SetTransMatrix(&combined_mat);
  SetRotMatrix(&combined_mat);
}
