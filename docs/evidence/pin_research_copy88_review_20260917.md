Working paths in this snapshot refer to `work/native_lane/r41_copy88/`.

# Independent semantic review: `town/func_8080E838` / runtime `func_80529438`

## Verdict

`natural_v3.c` is a faithful reconstruction of the retail operations on the PS1 32-bit ABI. Its two aggregate copies have the correct extents, the later field accesses use the copied objects consistently, the definite same-image callers provide enough storage, and the null path and two-argument callee ABI are unchanged. An independent fixed-cell verifier run records `MATCH`, 87/87 words, at stock `2.7.2-G0` in `semantic_independent_v3_verify.txt`; the parent's standard receipt is `natural_v3_2.7.2-G0_verify.json`. `natural_v3.c` SHA-256 is `5052beecc2889d28ed98574d29336f4878157ef6c7ba872f133c7d1fe70e57dc`; it has zero pin sites and `pin_census.landing_refusal == None`.

Two declarations in v3 should be corrected before treating the C types as reviewed rather than merely byte-exact:

1. Same-image source declares `D_80530130` as an array of 32-bit values and assigns its elements to scalar actor/resource fields. V3 declares it `void *[]` and makes `RenderPart.image` a pointer. That happens to be one word on PS1, but it gives the wrong element stride and moves following fields on a wider-pointer host.
2. Address `0x80529594` is the three-argument handler defined by `func_80529594(State *, Motion *, Actor *)`. V3 declares the address as `u8[]` and stores it through `void *callback`, losing the function-pointer contract.

`semantic_typefix_v3.c` is a review-only corrected form. It uses `s32 image`, `extern s32 D_80530130[3]`, a three-argument `ObjectCallback`, and a function declaration for `D_80529594`. It remains independently exact at 87/87, has zero pins, and passes `landing_refusal`; its SHA-256 is `eb3a961d716358b4f85cee668d60a67410b7314a65f9e8123dbbd3ccbbc38324`. The receipt is `semantic_typefix_v3_verify.txt`. This proves the type corrections are codegen-neutral at the accepted cell. The address-coded handler name can later be replaced by the canonical `func_80529594` spelling when the overlay symbol mapping is used consistently.

## Layout and retail mapping

All offsets below are target ABI offsets and agree with the complete 87-word retail map in `SITE_MAP.md` and `../r40_copy_transfer/return_probe/maps/func_8080E838.retail.dis`.

| Type/region | Size or fields | Retail use |
|---|---|---|
| `Payload88` | 22 words = `0x58` bytes | Source `+0x00..+0x57` copied to allocated object `+0x20..+0x77`; five 16-byte iterations plus the final 8 bytes. |
| `Initial24` | 6 words = `0x18` bytes | `initial_data + 0x00..0x17` copied to the object-owned record reached through object offset `+0x08`. |
| `Object` | child record at `+0x08`, render record at `+0x0C`, handler at `+0x10` | Retail loads/stores exactly these three offsets. |
| `RenderPart` | `x/y` at `+4/+5`, image/resource word at `+8`, color at `+0x0C`, flags at `+0x14`, scales at `+0x1C/+0x1E` | Every v3 field maps to the corresponding retail byte, word, halfword, or word access. |

The payload copy includes source offsets `+0x50` and `+0x54`. The later store intentionally overwrites payload `+0x50` with `D_8052643C`; the copied `+0x54` halfword remains the resource-table index. This matches retail and explains why the record is 88 bytes rather than an 80-byte body followed by unrelated data.

`allocated = func_800373DC(0x136); table = D_8052643C; object = allocated;` is semantically real staging. GCC eliminates the temporary copy while retaining the retail order: it materializes the table before moving the allocator result into the held object register. It adds no runtime operation or fake dependency.

## Definite caller and bounds review

The only definite same-image caller found is `src/town/func_8080F4A4.c`, which invokes runtime name `func_80529438` in two loops.

- The first argument is `&spawn_mode`, byte zero of `u8 spawn_data[0x80]`. Reading `0x58` bytes is within that object.
- The second argument is `&spawn_x`, `spawn_data + 0x58`. The six contiguous words are `spawn_x`, `spawn_y`, `spawn_z`, `velocity_x`, `velocity_y`, and `velocity_z`, occupying `0x58..0x6F`; the 24-byte copy is within the same `0x80`-byte object.
- These two source ranges are adjacent and do not overlap: the payload source ends at `spawn_data + 0x58`, where the initial-record source begins. Both destination records belong to the newly allocated object and do not alias the caller's stack buffer.
- In the column loop, the index at source `+0x54` is `coin_kind` and the calls occur with values 2, 1, and 0. In the payout loop it is assigned `func_80071494() % 3`; same-image declarations also describe that RNG as returning `u32`, supporting the intended range 0..2. Declaring `D_80530130[3]` therefore covers every observed call. If the RNG can return negative values despite that unsigned contract, retail itself would index before the table; the reconstruction does not add that risk.
- The stack buffer is declared as bytes, although the caller and callee both access word fields through casts. Runtime alignment is established by the retail `lw/sw` implementation and the aligned stack. Strict-aliasing/alignment debt exists in the reconstructed caller already; the aggregate spelling does not introduce a new hardware alignment requirement.
- Some payload words can be indeterminate because the caller does not initialize every byte of `spawn_data` before copying it. Retail and the current manual C copy all 88 bytes too. This is existing source-model debt, not a behavioral difference in v3.

## ABI and external declarations

- V3's restored `extern void *func_800373DC(s32)` agrees with the current source and the dominant typed declarations in adjacent town rows. Assigning that result to `Object *` is the correct local cast/conversion boundary and avoids inventing a cross-TU typed return.
- `func_8003BC18(void *, void *)` agrees with the dominant two-argument declarations and the existing row. The second argument is an address/table-like object in several callers, so strengthening it to a particular callback signature is not justified here.
- `func_8023FA58(void *, void *, void *)` preserves the current row's declaration and agrees with another close object initializer. Other rows call the same address with a fourth argument or use an unprototyped/variadic declaration. Its true global prototype remains repository debt; v3 neither creates nor resolves it. Retail at this site passes three meaningful arguments, and exact code proves those registers and their order.
- The candidate's public definition remains `void func_8080E838(void *source_data, void *initial_data)`. The definite caller declares the runtime alias as `void func_80529438(void *, ...)`; one call supplies an unused third `column_offset`, while another supplies two arguments. MIPS o32 safely ignores the extra caller argument, which is also what retail does. The declarations are not strictly compatible C types. The caller should eventually use the two-argument prototype and have removal of the extra argument byte-verified in its own row; this is caller-side prototype debt, not a reason to add a variadic parameter to the reconstructed callee.
- `D_805300F4` is only passed by address and its `u8[]` declaration agrees with the adjacent handler TU. `D_8003C558` and `D_8052643C` are likewise used only as addresses here.

## Guest-pointer model

The exact target assumes 32-bit pointers. V3's `Object` embeds two data pointers and one callback address; its original `RenderPart` also embedded a pointer. On an LP64 host, ordinary C pointers make `Object` offsets become `+8/+16/+24`, and v3's pointer-typed image field also moves the fields after `+8`. The reviewed type fix removes the unnecessary image/table-width problem, but the object child pointers and callback still require the project's normal guest-pointer policy: compile this layout under a 32-bit ABI, or represent stored guest addresses with an explicit 32-bit guest-address type and translate them before host dereference. Native LP64 code must not map this target-memory structure with unqualified host pointers.

This constraint is broader than this function and already appears throughout the reconstructed object model. It should be stated in the landing record because byte identity on PS1 cannot validate native-host structure layout.

## Provenance boundary

The zero-pin whole reconstruction is reproducibly exact at stock `2.7.2-G0`. Its aggregate-copy register allocation and indexed global load are consistent with the recovered 2.7-era family. The current 19-pin source is exact at its recorded `2.95.2-G0 -mno-split-addresses` recipe and fails at the older cell; conversely, this is a substantial source reconstruction rather than a same-source recipe correction.

These facts establish a valid stock build endpoint, not the historical compiler release. The source and recipe must move as one hash-bound reviewed transition, as described in `RECIPE_REVIEW.md`. A live-row verify and the complete affected overlay window gate remain the publication authority.

## Landing form

Parent accepted the scalar-table and callback corrections, retained the original
allocator void-pointer declaration, and replaced the address-coded handler
name with canonical `func_80529594`. This matches the `State`, `Motion`, and
`Actor` tags in `src/town/func_8080E994.c`. The resulting `final.c` independently
verifies 87/87; no source ABI or runtime operations changed during this cleanup.
