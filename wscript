top = '.'
out = 'build'

def options(opt):
	opt.load('g++')

def configure(conf):
	conf.load('g++')
	conf.env.INCLUDES_TEST = ['C:\\boost_1_59_0']
	conf.env.DEFINES_TEST  = ['TEST']
	conf.env.CFLAGS_TEST   = ['-std=c++11', '-std=c++1y', '-O0']
	conf.env.LIB_TEST       = ['boost_system-mgw51-mt-d-1_59', 'ws2_32', 'wsock32']
	conf.env.LIBPATH_TEST   = ['C:\\boost_1_59_0\\stage\\lib']
	conf.env.LINKFLAGS_TEST = ['-g']

def build(ctx):
    ctx.program(features='c cxx cxxprogram', source="src/cpp_tests.cpp", target="cpp_tests", cxxflags="-g -Wall -O0 -std=gnu++11 -std=c++1y")
    