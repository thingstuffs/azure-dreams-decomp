# The Azure Dreams production compiler: it existed, and no one holds it

Status: evidence case, 2026-09-24 (round 77, fidelity plan). Owner direction: "I'm starting to lean towards it existed but no
one has it. So build the evidence and cite it ... if we need a patched compiler for this one epilogue fix then we move with that,
but it needs to be rock solid and I'd like to exhaust any avenues we can."

## Claim
The 2.8-era code in Azure Dreams (US SLUS-00614) was compiled by a gcc2 build dated after 1997-07-27 that still left the
function-return delay slot for the assembler (gcc 2.7.2's behaviour, deleted from FSF gcc on 1997-07-11). No FSF, Cygnus or SN
compiler we hold or can find publicly has both properties. It was most likely an SN or Cygnus internal build distributed to
licensed developers through SN's account-only BBS.

## Evidence chain
1. **What retail looks like.** 601 rows at the 2.8-era cells (2.8.0/2.8.1/2.91.66/2.95.2) are retail-exact only through two maspsx
   rules (`_maybe_unfill_return_delay`, `_unfill_via_load_delay`). Rewriting only the cc1 epilogue into gcc 2.7.2's text form
   (`function_epilogue` + `mips_epilogue_delay_slots`) lets GENUINE ASPSX 2.79 alone reproduce 580/601, including 84/84 controls;
   retail's return-form statistics match 2.7.2's rule (469 multi-register returns all unfilled). - fidelity_step1_aspsx_diff.md,
   fidelity_step1b_epilogue.md (tools/fidelity/epilogue_model.py).
2. **When that behaviour ended.** gcc 2.8.0 ChangeLog: "Fri Jul 11 09:49:15 1997 Jeffrey A Law ... (mips_epilogue_delay_slots):
   Likewise [delete]" (verified in the 2.8.0 tarball); gcc-mirror 1f2d8f51 = SVN r14412 (07-11), parent 7a49a4fd = r14410 (07-10).
   - fidelity_step1b_epilogue.md, fidelity_websearch_1997_compiler.md.
3. **Every compiler we hold was tested; none has both properties.** 21 historical/rebuilt compilers + 13 patched research builds
   (genuine PsyQ 4.0/4.1/4.3/4.3-JP 2.8.0 SN32 4.0.0007/4.4/4.5/4.6, SN egcs-2.91.66 PSX, DOS SN16, pre-4.0 and legacy cc1s,
   970802/970821/971023 trunk rebuilds). All post-07-11 builds fill the return slot (470/470); all pre-07-11 builds lack 2.8-era
   codegen. - fidelity_step1c_compiler_inventory.md.
4. **The public record has no window compiler.** Web search: no genuine SN/Cygnus binary between 970404 and 2.8.0 is public; SN's
   interim builds lived on an account-only BBS ("latest versions ... if they have not yet filtered through to SCE", SN pages, May
   1997; "PSX and N64 versions of the Cygnus Experimental compiler", May 1998). - fidelity_websearch_1997_compiler.md.
5. **SN's released MIPS builds stayed on 970404 through Nov 1997.** SN N64 build 0006 = `cygnus-2.7.2-970404 SN32.3.7.0006`
   (linked 1997-11-26), asm identical to PSX 0004 on 1,403 rows; the June-1997 US disc carries 0002. A second SN Cygnus line
   existed: Saturn `2.7-97r1a SOA-971029 SN32.3.8.0006` (1997-11-25), no MIPS build known. - fidelity_lostcc_A_sn_binaries.md.
6. **Retail needs codegen from after the epilogue was deleted.** FSF trunk built and bisected 1997-04..08 (39 cc1s): April trunk
   equals the Cygnus tree (593/593 bodies, 440/440 cdk-exact rows); no in-window snapshot reproduces any pin-free target row;
   retail needs r14536 (Kenner, 07-27, expr.c ARRAY_REF: +36 rows, 22 pin-free) and r14479 (07-18) - both AFTER r14412 (07-11).
   No FSF state has 07-27 codegen AND the text epilogue. - fidelity_lostcc_B_trunk_bisect.md.

## Conclusion and route
- The compiler is recorded as: **"a post-July-1997 gcc2 snapshot with an unfilled return slot, not held (SN/Cygnus internal)".**
- A literal revert of r14412 is NOT rock solid: on 2.8.0/2.8.1 it loses 11 rows (6 pin-free) and breaks 6/13 controls (reorg
  decisions near the function end; retail keeps 2.8's RTL-epilogue decisions everywhere except the return slot). A two-condition
  patch (no return delay insn in frames saving more than $31, plus 2.7.2's $31-only rule) reaches 172/174 in an experiment - not
  exact. So no patched compiler is adopted now.
- **Model of record:** the two maspsx rules, relabelled as a model of this compiler's epilogue decision followed by ASPSX's own
  reorder-mode fill (their docstrings wrongly said "replicate ASPSX"). Rows that depend on them carry the L5 `maspsx_dependent`
  marker (tools/levels.py) - a toolchain-model residue, not a fault of the C.
- Rows that the genuine 970404 compiler reproduces were moved to 2.7.2-cdk (380 rows on 2026-09-24, all retail-exact under genuine
  ASPSX). Remaining: the pinned 2.8-era rows (natural C first), and the 17 egcs-cell rows (a separate proxy question).
- Reopen if: an SN/Cygnus MIPS build dated 1997-07..1998-01 surfaces (the 97r1a line or SN's "Cygnus Experimental" PSX compiler).
