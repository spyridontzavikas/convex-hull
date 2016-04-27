
def options(opt):
	opt.load('g++')

def configure(conf):
	conf.load('g++')
	conf.env.INCLUDES_TEST = ['C:\\boost_1_59_0']
	conf.env.DEFINES_TEST  = ['TEST']
	conf.env.CFLAGS_TEST   = ['-std=c++11', '-std=c++1y', '-O0']
	conf.env.LIB_TEST       = ['boost_system-mgw51-mt-d-1_59']
	conf.env.LIBPATH_TEST   = ['C:\\boost_1_59_0\\stage\\lib']
	conf.env.LINKFLAGS_TEST = ['-g']

def build(bld):
	bld.program(source='src/cpp_tests.cpp', 
				target='test',
				cxxflags = ['-std=c++11', '-std=c++1y', '-O0', '-Wno-deprecated-declarations'],
				use = 'TEST')