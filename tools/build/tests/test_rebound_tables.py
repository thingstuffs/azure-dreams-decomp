"""Compiler-local tables must be discovered under the rebound definition name."""
import contextlib,json,sys,tempfile,types,unittest
from pathlib import Path
from unittest.mock import Mock,patch
ROOT=Path(__file__).resolve().parents[3]
sys.path.insert(0,str(ROOT))
from tools.build import mkbuild as M

class StopAtDiscovery(Exception):pass

class ReboundTableTests(unittest.TestCase):
    def exercise(self,function,stem,renames,symbol,rebinding=True,defined=True,expected=None):
        parent=ROOT/'tmp';parent.mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(dir=parent) as temp:
            root=Path(temp);state=root/'build/.state'
            (state/'recipes').mkdir(parents=True);(root/'build/obj').mkdir(parents=True)
            (root/'build/obj/home.o').write_bytes(b'synthetic object')
            (root/'retail.bin').write_bytes(bytes(16))
            (state/'recipes/home.json').write_text(json.dumps(dict(output='build/obj/home.o',source='src/home.c')))
            unit=dict(recipe='home',func=function,source_stem=stem,kind='c',off=0,size=16,vma=0x80164000)
            if rebinding:unit['rebind']=dict(bindings={})
            spec=dict(tag='fixture',container='retail.bin',image='dungeon/fixture',units=[unit])
            path=state/'image.json';path.write_text(json.dumps(spec))
            gate=types.SimpleNamespace(ROOT=root,cfg_path=lambda p:root/p,
                MatchEntry=lambda *a,**k:None,Segment=lambda *a,**k:None,rodata_owner=lambda *a:None)
            discover=Mock(side_effect=StopAtDiscovery)
            links=types.SimpleNamespace(rebind_object=Mock(return_value=renames))
            matcher=types.SimpleNamespace(_local_section_placements=discover)
            metadata=dict(symbols=[(symbol,'.text.'+symbol if defined else None,0)],sections=[('.text.'+symbol,16),('.rodata',4)])
            modules={'linklist':links,'match':matcher,'linklist_data':types.SimpleNamespace()}
            with patch.dict(sys.modules,modules),patch.object(M,'ROOT',root),patch.object(M,'STATE',state),\
                 patch.object(M,'load_gate',return_value=gate),patch.object(M,'frozen_lists',lambda *a:contextlib.nullcontext()),\
                 patch.object(M,'object_metadata',return_value=metadata):
                with self.assertRaises(StopAtDiscovery):M._image_one(path)
            self.assertEqual(discover.call_args.args[1],expected or symbol)
            if rebinding:links.rebind_object.assert_called_once()
            else:links.rebind_object.assert_not_called()

    def test_renamed_definition_reaches_local_table_discovery(self):
        self.exercise('func_80170000','func_80F00000',{'func_80170000':'func_80164000'},'func_80164000')

    def test_rebound_source_stem_remains_a_valid_fallback(self):
        self.exercise('old_declaration','func_80170000',{'func_80170000':'func_80164000'},'func_80164000')

    def test_ordinary_definition_keeps_its_existing_name(self):
        self.exercise('func_80170000','func_80F00000',{},'func_80170000',rebinding=False)

    def test_synthetic_inventory_id_uses_the_actual_rebound_entry(self):
        self.exercise('func_80F00000','func_80F00000',{'func_80170000':'func_80164000'},'func_80164000')

    def test_undefined_address_is_not_an_entry_definition(self):
        self.exercise('inventory','hint',{'func_80170000':'func_80164000'},'func_80164000',defined=False,expected='hint')

if __name__=='__main__':unittest.main()

