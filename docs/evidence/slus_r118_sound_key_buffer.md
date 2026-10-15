# Buffered sound-register values and key state: shared access-view review

Reviewer: pending. These two complete functions use the established stock-2.7.2
sound lineage, with empty compiler/assembler flags. The present aggregator
includes func_8005E4C4 and func_8005E97C in retail order. Both select buffered or
direct register writes using D_80079950, maintain D_8007951C, and operate on
24-bit voice/register masks. This supports a bounded integration cluster;
no historical filename or original two-function TU boundary is asserted.

The shared base is the generic helper's existing plain u16 pointer. The key
helper casts to its existing observed register view: key-on halfwords at
0x188/0x18A retain their volatile qualifiers; key-off halfwords at 0x18C/0x18E
remain ordinary. The generic helper retains its explicit volatile read/cached
views and ordinary direct-write views. Every existing access width, qualifier,
mask, store and state update is preserved. The buffered array declarations
remain extent-free, and no allocated data, adjacent extent or new qualifier is
introduced. No other helper, collector contribution or data owner is included.

Their current sources differ from old frozen-raw object references, so no
candidate was accepted against those references. The unchanged production
verify.rebaseline_slus helper validated each current compiled object against
the object linked by the retail-gated pinned recipe, then wrote only a private
diagnostic cache. Exact current controls and exact whole-object identity trials
followed. The canonical cache/reference was not changed. This is input evidence,
not a substitute for the final production module gate.

Delivery requires a fresh full retail image and unchanged complete module
certification, including both physical/logical functions, direct genuine ASPSX
2.79 and zero masked retail relocations. The header is an explicit physical
dependency. No logical split row, rowbase, data allocation, compiler/assembler
exception, gate tool, window value or noreturn census is changed. Review and
real --write remain orchestrator actions under the landing lock after final
inputs. Existing source-quality residues remain visible and unpromoted.

Rebase receipt at 97f105e7f: this input uses the committed code/code2 parent recipes (both 2.7.2-cdk) and preserves the seven-function stock-2.7.2 sound_tu_code partition. Any earlier production proof is historical; this delivery requires fresh unchanged full-image, member/physical-owner genuine and relevant production-window checks at this HEAD. No old collector recipe, asm alias, compiler flag, pin-census implementation or parked-container setting is restored. Reviewer remains pending.
