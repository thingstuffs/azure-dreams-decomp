"""Normal-Ninja emitted coverage must reject invisible and local extra functions."""
import json, os, shutil, subprocess, sys, tempfile, unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
sys.path[:0]=[str(ROOT/'tools/build')]
import slus_partitions as P

A,B,C,D=['func_8003'+x for x in ('0000','0010','0020','0030')]
RECIPE={'ccver':'2.7.2','ccflags':'','asflags':''}

@unittest.skipUnless(shutil.which('mipsel-linux-gnu-as') and shutil.which('mipsel-linux-gnu-readelf'), 'MIPS binutils unavailable')
class EmittedBuildTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup);self.root=Path(self.temp.name)
        (self.root/'build/src').mkdir(parents=True);(self.root/'config').mkdir()
        self.plan=[{'id':'slus/code','source':'src/code.c','raw_sha256':'0'*64,'recipe':RECIPE,
                    'functions':[A,B],'parts':[{'module':'owner','functions':[A]}]}]
        self.modules=[{'name':'owner','source':'src/owner.c','recipe':RECIPE,'headers':[],'data':[],
                       'evidence':'docs/evidence/owner.md','members':[{'id':'slus/member','source':'src/member.c','functions':[C]}]}]
        for file,content in [('slus_partitions.json',{'version':1,'parents':self.plan}),('slus_modules.json',{'version':1,'modules':self.modules})]:
            (self.root/'config'/file).write_text(json.dumps(content))
        (self.root/'config/names.tsv').write_text('')
        self.assemble('code',[(B,False)])
        self.assemble('owner',[(A,False),(C,True)])
    def assemble(self,stem,functions):
        text='\n'.join(('.text\n'+('' if local else '.globl '+name+'\n')+f'.type {name}, @function\n{name}:\n.word 0\n.size {name}, .-{name}\n') for name,local in functions)
        subprocess.run(['mipsel-linux-gnu-as','-EL','-march=r3000','-o',str(self.root/'build/src'/f'{stem}.o')],input=text,text=True,check=True,capture_output=True)
    def cli(self,stamp='build/partition_sources/coverage.ok'):
        return subprocess.run([sys.executable,P.__file__,'check-emitted','--plan','config/slus_partitions.json','--manifest','config/slus_modules.json','--names','config/names.tsv','--stamp',stamp],cwd=self.root,env=dict(os.environ,PYTHONPATH=str(ROOT/'tools/build')),text=True,capture_output=True)
    def test_actual_objects_and_local_symbols_are_checked_before_stamp(self):
        self.assertEqual({k:set(v) for k,v in P.check_emitted_objects(self.plan,self.modules,self.root).items()}, {'src/code.c':{B},'src/owner.c':{A,C}})
        result=self.cli();self.assertEqual(result.returncode,0,result.stderr)
        stamp=self.root/'build/partition_sources/coverage.ok'
        self.assertEqual(set(json.loads(stamp.read_text())['src/owner.c']),{A,C})
        self.assemble('owner',[(A,False),(C,True),(D,True)])
        result=self.cli();self.assertNotEqual(result.returncode,0)
        self.assertIn('emitted function coverage differs',result.stderr)
        self.assertFalse(stamp.exists())
    def test_missing_symbol_or_object_refuses_coverage(self):
        self.assemble('owner',[(A,False)])
        with self.assertRaisesRegex(P.PartitionError,'emitted function coverage differs'):
            P.check_emitted_objects(self.plan,self.modules,self.root)
        (self.root/'build/src/code.o').unlink()
        with self.assertRaisesRegex(P.PartitionError,'cannot read emitted functions'):
            P.check_emitted_objects(self.plan,self.modules,self.root)
    def test_stamp_cannot_overwrite_inputs_or_escape_by_symlink(self):
        original=(self.root/'config/slus_partitions.json').read_bytes()
        self.assertNotEqual(self.cli('config/slus_partitions.json').returncode,0)
        self.assertEqual((self.root/'config/slus_partitions.json').read_bytes(),original)
        folder=self.root/'build/partition_sources';folder.mkdir()
        (folder/'coverage.ok').symlink_to(self.root/'config/slus_partitions.json')
        result=self.cli();self.assertNotEqual(result.returncode,0)
        self.assertIn('coverage stamp escapes',result.stderr)
        self.assertEqual((self.root/'config/slus_partitions.json').read_bytes(),original)

if __name__=='__main__':unittest.main()
