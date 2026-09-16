"""T70: retype both a scalar parameter and its pinned local copy.

APPEARS   A direct parameter-to-local copy, either initialized in its declaration
          or assigned later. Both ends are integers; a pin names the local.
RESOLVES  The original narrow value was widened independently in both declarations.
          Retyping only one end leaves a conversion or a different allocation.
EVIDENCE  Round 37: 164 unique rows / 1,612 screens, 15 exact rows. Composing on
          those winners removes 27 pins. 80D65810's parameter-only repair scores 1,
          local-only 14, both s16 exact. Inspect value uses when accepting widths;
          the byte verifier proves the target, not cross-TU type consistency.

Same-file prototypes track the parameter. Unscored arms must remain identical.
Signature-changing candidates require a batch caller review before apply_candidates:
80287768 was scorer-exact but its real caller could not adopt the narrow prototype
exactly, so that one removal was withdrawn. The automatic sweep path refuses such
candidates; candidates() exposes them for reviewed multi-TU batches.
No compiler/flag changes or new scaffolding. This deliberately handles direct
copies only, not arithmetic, casts, pointer copies or local-to-local pairs.
"""
import re
from .t29_addrsym import mask_comments
from .t36_paramwidth import functions, build
from .t37_localwidth import pinned_locals, decl_re, INT_TYPES
from pin_census import sites_of, unscored_text


def pairs(text):
    masked = mask_comments(text)
    pinned = {v for v, ty, _ in pinned_locals(text) if ty in INT_TYPES}
    out = []
    for fname, params, b0, b1 in functions(text):
        scalar = {p for p, ty, _, _ in params if ty in INT_TYPES}
        for local in sorted(pinned):
            ds = list(decl_re(local).finditer(masked))
            if len(ds) != 1 or not b0 < ds[0].start() < b1 or '[' in ds[0].group(0):
                continue
            sources = set(re.findall(r'(?<![\w.>])\b' + re.escape(local) +
                                     r'\s*=\s*(\w+)\s*;', masked[b0:b1]))
            sources.update(re.findall(r'=\s*(\w+)\s*;', ds[0].group(0)))
            for param in sorted(sources & scalar):
                out.append((fname, local, param))
    return out


def candidates(text):
    out, seen = [], set()
    for fname, local, param in pairs(text):
        for ty in INT_TYPES:
            candidate = build(text, fname, {param: ty}, {local})
            if candidate is None:
                continue
            ds = list(decl_re(local).finditer(mask_comments(candidate)))
            if len(ds) != 1:
                continue
            a, b = ds[0].span('ty')
            candidate = candidate[:a] + ty + candidate[b:]
            if (candidate in seen or unscored_text(candidate) != unscored_text(text)
                    or len(sites_of(candidate)) >= len(sites_of(text))):
                continue
            seen.add(candidate)
            out.append(('copywidth:%s:%s=%s:%s' % (fname, local, param, ty), candidate))
    return out


class T:
    name = 't70_copywidth'
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if pairs(text) else 'no pinned scalar parameter copy'

    @staticmethod
    def apply_verified(text, row, census, vf):
        signature = lambda t: [(f, tuple(ty for p, ty, a, b in params))
                               for f, params, b0, b1 in functions(t)]
        original_signature = signature(text)
        needs_review = 0
        for label, candidate in candidates(text):
            if signature(candidate) != original_signature:
                needs_review += 1
                continue
            if vf(candidate).get('exact'):
                return candidate, {'label': label}
        return None, {'refused': ['no signature-preserving pair exact; review callers for a signature change'],
                      'requires_caller_review': needs_review}
