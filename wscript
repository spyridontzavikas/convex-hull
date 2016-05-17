
def options(opt):
	opt.load('g++')

def configure(conf):
	conf.load('g++')
	conf.env.append_value('INCLUDES', ['C:\\mercurial_repo\\cpp_tests'])
	conf.env.INCLUDES_TEST = ['C:\\boost_1_59_0']
	conf.env.DEFINES_TEST  = ['TEST', '_GLIBCXX_DEBUG']
	conf.env.CFLAGS_TEST   = ['-std=c++11', '-std=c++1y', '-O0', '-g']
	conf.env.LIB_TEST       = ['boost_system-mgw51-mt-d-1_59']
	conf.env.LIBPATH_TEST   = ['C:\\boost_1_59_0\\stage\\lib']
	conf.env.LINKFLAGS_TEST = ['-g']

def build(bld):
	bld.program(source='src/main.cpp', 
				target='test',
				cxxflags = ['-std=c++11', '-std=c++1y', '-O0', '-g', '-Wno-deprecated-declarations'],
				use = 'TEST')