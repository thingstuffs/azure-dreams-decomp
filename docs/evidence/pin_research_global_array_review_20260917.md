# Independent review: `D_8002992E` array extent

## Verdict

`D_8002992E` is confidently a 16-bit object at the named address. The current
sources do **not** establish that it is a five-element array. `s16[5]` is more
likely inherited code-generation scaffolding chosen to advertise a 10-byte
extern, just over the historical `-G8` small-data threshold, than recovered
data-layout evidence.

An unsized `extern s16 D_8002992E[]` with `[0]` accesses is therefore a
defensible unknown-extent view for further diagnosis: it preserves the proven
base address and halfword width without claiming five elements. Its improved
333/334-word, 9-edit result remains nonexact and demonstrates a compiler-shape
effect, not a recovered array layout or a promotable repair.

## What the current sources prove

Every current reference in `src/dungeon` is a halfword access at exactly
`D_8002992E + 0`. There is no indexed access to elements 1 through 4, no
address arithmetic from this symbol, and no neighboring symbol record that
supplies an upper bound. The available SLUS and dungeon symbol files do not
declare this symbol or a nearby endpoint.

The five named siblings all spell the access as `D_8002992E[0]`:

| Synthetic row | True row | Declaration | Recipe |
|---|---|---|---|
| `func_819BEB98` | `func_80024398` | `extern s16 D_8002992E[5]` | `2.8.1-G0` |
| `func_819BEEB0` | `func_800246B0` | `extern s16 D_8002992E[5]` | `2.7.2-cdk-G0` |
| `func_819BF888` | `func_80025088` | `extern s16 D_8002992E[5]` | `2.7.2-cdk` |
| `func_819C0000` | `func_80025800` | `extern s16 D_8002992E[5]` | `2.8.1-G0` |
| `func_819C095C` | `func_8002615C` | `extern s16 D_8002992E[5]` | `2.7.2-cdk-G0` |

There is contrary same-bank declaration evidence. `func_819BEFC0` (true
`func_800247C0`) declares `extern s16 D_8002992E` and stores one halfword.
The reviewed target `func_819C0C18` (true `func_80026418`) also declares it as
scalar, stores 0/1, and reads one signed halfword. Thus same-bank sources agree
on address and width but split five array declarations versus two scalar
declarations; none accesses a nonzero element.

## Bank certainty

The sibling relationship is strong. The six rows from `func_819BEB98` through
`func_819C095C` are all covered by proven rowbase record
`img_19deb98_80024398`; `func_819C0C18` is covered by proven record
`jtbl_19E0C18`. Both records use the identical delta `0x7E645800`, yielding the
true names in the table and target above. This is one coherent bank, rather
than coincidental reuse of the low address in another dungeon image.

That bank identity validates comparison of the declarations. It does not turn
five copied `[5]` declarations into five independent layout observations.

## Why `[5]` looks like historical `-G8` scaffolding

- Five `s16` elements have size 10, the smallest even-sized declaration above
  the assembler's `-G8` cutoff. Repository maspsx tests explicitly document
  that an extern size at most 8 selects `$gp` small-data treatment while a size
  above 8 selects `%hi/%lo`; their halfword regression fixture uses an extern
  size of 10 for exactly this boundary.
- The repository contains an explicit analogous source pattern in
  `func_8009499C.c`: padding a global's declared type beyond eight bytes solely
  because retail uses `%hi/%lo` addressing.
- Four of the five `[5]` siblings are currently attributed `-G0`; only
  `func_819BF888` retains the ordinary `2.7.2-cdk` recipe where the `-G8`
  threshold directly matters. This distribution is consistent with a
  historical declaration copied across related sources, not five independent
  extent recoveries.
- Git history provides no semantic origin for five elements. The `[5]`
  declarations and `[0]` accesses arrived together in the initial complete-tree
  import (`061b85f8`) and remained unchanged through `e993cfe4` and
  `a31aee0f`. The scalar declarations were present in those same revisions.
  No commit message, source comment, later edit, or use of another element
  explains the extent.

This is strong evidence about the declaration's likely code-generation role,
but it is not proof of the original linker's symbol size. A real array whose
other elements are unused in the recovered C remains possible. Layout
confidence is therefore: **high** for `s16` at offset zero, **low** for extent
five, and **medium-high** that `[5]` was selected as size scaffolding.

## Hypothesis boundary

The `array/f.c` versus `free/f.c` diagnostic changes only the declaration from
scalar to unsized array and the three accesses to `[0]`. It changes first-pass
scheduling around the store and improves the broader free-switch candidate
from 332 words/23 edits to 333 words/9 edits, but remains one word short with
six substitutions and three indels. That result justifies continued mechanism
research. It does not justify changing the landed scalar declaration, asserting
an array bound, or promoting the broader switch rewrite.

## Bound evidence

- `v1_global_array.c`: `6b5af390e1ee0fec997eccb4a749e399be076d34ccaf6f45c60154e5415eb3ab`
- `v1_global_array.summary.json`: `80ddc6b9d6347526fd52536a996852bc0346f68710f9ba416e5a1bbbe2765bf9`
- `config/overlays/dungeon.rowbase.jsonl`: `d54e8b55cacf46a4ffec3cfb637334bfe47c2d486a1fe61f9cf7254973590dc8`
- `src/dungeon/INDEX.md`: `55f4c9c09a8fdd80008af1335b889bbabacd9673855aca310fe191b7207b8252`
- `tools/maspsx/tests/test_store_delay.py`: `dd20617006908cd15ec7ac1f7d9a515881437e23136ac0ca5e1b02b44c641679`

| Source | SHA-256 |
|---|---|
| `func_819BEB98.c` | `e0c78b27767a091ba67462ee0b93c3754156a692bb55d40fd6934aa7f7f5efd2` |
| `func_819BEEB0.c` | `acca74b187c6908c053c423f456be2cb2178ec7a013e20ac3a1fd8ddb6c78fe9` |
| `func_819BEFC0.c` | `5ad2f00de4a1bbe7ae6f4e30b3ca2c3bc7f5861aa01b465f711bc0855d82e6a7` |
| `func_819BF888.c` | `26817d40b81539698fb0244a1c030eb907ebe7daa9b44e0cc94fd1fe2e0b9996` |
| `func_819C0000.c` | `24fe10483994f2a6d2efae72cb66923dd4af581e8250809d6347bd87f45284d7` |
| `func_819C095C.c` | `0f07cc0119d987376daffcb6210075d39d5078ba2880e50ee4840f12bc1de2cf` |
| `func_819C0C18.c` | `4a9303d048c233784e11880122d5697a75917ec03189d46aad90b2d234ae5e0f` |
