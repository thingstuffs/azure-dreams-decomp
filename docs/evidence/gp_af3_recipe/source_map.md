# `func_8004437C` retail source map

This is read-only preparation for a C reconstruction. [retail_100.dis](retail_100.dis) contains all 100 words at `0x8004437C` through `0x80044508` from the retail-exact SLUS ELF; the extraction also checked those 400 bytes against the retail image. [default_cdk_object.dis](default_cdk_object.dis) is the registered CDK object, which links to retail. [dialect_compiler.s](dialect_compiler.s) and [dialect_cdk_mmips_as_object.dis](dialect_cdk_mmips_as_object.dis) are the existing unchanged-C `-mmips-as` trial. The source-map preparation only extracted and scanned these existing bytes; it compiled nothing.

## Frame and register roles

The function allocates `0x28` bytes. It saves `$s0` at `0x10(sp)`, `$s1` at `0x14`, `$s2` at `0x18`, `$s3` at `0x1C`, and `$ra` at `0x20`; the first `0x10` bytes are the outgoing argument area. The epilogue at `0x800444EC` through `0x80044508` restores those registers, adds `0x28` to `$sp`, and returns. The fast path from the first comparison jumps to that epilogue with `$v0=1` in the jump slot; the other path sets `$v0=0` before restoration.

| Register | Retail role and lifetime |
| --- | --- |
| `$s0` | Address of the selected `D_8006E704[entry_index]` pointer **slot**, computed at `0x800443A8`; reused for slot loads through `0x80044440` across the first calls. Recomputed from saved index at `0x8004447C`–`0x80044490`, then used through the `Control_CD` call and at `0x800444AC`. |
| `$s1` | Original `mode` from `$a1`; compared with `D_80080AF3` after `func_800542BC`. |
| `$s2` | Original `entry_index` from `$a0`; survives the early calls so the `D_8006E704` slot can be recomputed later. |
| `$s3` | Copy of `mode`, made in the first conditional branch's delay slot at `0x800443D4`; survives the update calls and supplies `func_8004450C`'s argument. |
| `$a1` (`$5`) | Holds the first absolute `D_80080AF4` base from `0x800443B0`–`0x800443B4` through **both** initial indexed loads. It is caller-clobbered and is not live across the `func_800542BC` call. Later `$a1` carries an entry pointer and a call argument. |
| `$a0` (`$4`) | Holds a **fresh** absolute `D_80080AF4` base at `0x800444A0`–`0x800444A4`, after `Control_CD`; used for the final indexed store. No AF4 pointer must live across that call. |

## Data access forms in retail

| Symbol | Retail accesses | Shape |
| --- | --- | --- |
| `D_80080AF3` (`0x80080AF3`) | `lb $v1,0x15F($gp)` at `0x8004440C` | One GP-relative signed byte read after `func_800542BC`; compared with saved `mode`. No write here. |
| `D_80080AFC` (`0x80080AFC`) | `lh` at `0x800443AC`, `lhu` at `0x800443CC`, `sh` at `0x800443F8`; later `lh` at `0x80044444`, `0x800444A8`, and `0x800444CC` | GP-relative halfword at `0x168($gp)`. The first value indexes AF4; the unsigned read is toggled and stored; later fresh reads select packed marker, final AF4 slot, and `SD_Call` code. |
| `D_80080AF4` (`0x80080AF4`) | Base in `$a1` at `0x800443B0`–`0x800443B4`; indexed loads at `0x800443C4`–`0x800443C8` and `0x800443EC`–`0x800443F4`. Fresh base in `$a0` at `0x800444A0`–`0x800444A4`; indexed store at `0x800444B4`–`0x800444BC`. | The first two loads use the **same held base** and an index shifted by two. The final store uses a newly materialized base after `Control_CD`; `sw $v1,0($v0)` occupies the `func_8003F320` call delay slot. Retail uses no `$at` for these three accesses. |
| `D_8006E704` (`0x8006E704`) | Absolute base at `0x80044398`–`0x8004439C`, plus `entry_index * 4` into `$s0`; repeated base materialization at `0x80044484`–`0x80044488` for the same slot. | An array of pointers. Loads from `0($s0)` at `0x800443BC`, `0x800443F0`, `0x80044428`, `0x80044440`, `0x80044494`, and `0x800444AC` fetch the selected pointer; separate loads/stores through that pointer touch its word field. `$s0` holds the array **slot address**, not the pointed-to object's address. |

The precise AF4 fold boundary is visible by comparing the registered and dialect objects:

| Indexed AF4 site | Retail requirement | `-mmips-as` unchanged-C output |
| --- | --- | --- |
| First read, `0x800443C4`–`0x800443C8` | Index plus the already held `$a1` base, then `lw 0($v0)`. | **Folds** to `lw $2,D_80080AF4($2)` even though `la $5,D_80080AF4` was emitted earlier; the stock assembler expands through `$at`. |
| Second read, `0x800443EC` and `0x800443F4` | Reuse the same `$a1` base across the branch; an `E704` slot load intervenes. | **Does not fold**: retains `addu $2,$2,$5; lw $2,0($2)`. |
| Final write, `0x800444B4` and `0x800444BC` | Fresh `$a0` base created after `Control_CD`, plus shifted AFC index; `sw $v1,0($v0)` fills the following call's delay slot. | **Folds** to `sw $3,D_80080AF4($2)`; the stock object uses `$at` and GP-relative indexed addressing. |

The dialect trial's exact 16-word aligned residual is in `dialect.json`. These are observed emission differences, not an attribution of the original compiler family.

## Call boundaries and live values

| Call site | Delay slot | Values required after the call |
| --- | --- | --- |
| `0x80044404` `func_800542BC` | `nop` | `$s0` slot address, `$s1` mode for AF3 compare, `$s2` entry index for later recomputation, `$s3` mode copy. The early AF4 `$a1` base is dead. |
| `0x80044420` conditional `func_80044698` | `nop` | `$s0` slot address, `$s2` entry index, `$s3` mode copy. `$s1` has finished its comparison. |
| `0x80044498` `Control_CD` (`func_8003E4FC`) | `move $a2,$zero` | Recomputed `$s0` slot address for the post-call pointer load; `$s3` mode copy. AF4's final base is created **after** this call. |
| `0x800444B8` `func_8003F320` | `sw $v1,0($v0)` to indexed AF4 slot | `$s3` mode copy for the next call; the AF4 base and computed destination are consumed in the delay slot. |
| `0x800444C4` `func_8004450C` | sign-extend `$a0` from `$s3` | No saved input value is read again; AFC is loaded afresh to choose the final sound code. |
| `0x800444E0` `func_80053DA8` (`SD_Call`) | `nop` | Only the saved return context and zero return value remain. |

## Direct lineage fingerprint

[lineage.json](lineage.json) is a direct `lineage_fingerprint.scan`/`classify` of this raw SLUS 400-byte function slice, following the same method used for the earlier `gp_order_bytes` function. It finds one `slot_store` signature: the AF4 `sw` in the `func_8003F320` delay slot. It finds no `$at` macro store, split store, held-page, split-la, zero-copy, or return-copy signature. The classifier returns **insufficient store-emission evidence** with no family; its only note treats the filled call slot as family-neutral. No score-based or compiler-family attribution follows from this scan.

The constrained source-map handoff is therefore narrow: preserve the `$s0` slot-address lifetime and saved input roles; make the first two AF4 reads share the early base, then make a fresh AF4 base after `Control_CD` for the delayed store. The next step is to identify a compiler address-folding mechanism that can preserve these access forms. Another C candidate would still need stock, genuine-ASPSX, and full retail-image proof. This report makes no C edit or new recipe trial.
