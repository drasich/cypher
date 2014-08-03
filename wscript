#! /usr/bin/env python
# encoding: utf-8
import sys
#import Options

# the following two variables are used by the target "waf dist"
VERSION='0.0.1'
APPNAME='cypher'

# these variables are mandatory ('/' are converted automatically)
top = '.'
out = 'build'

def options(opt):
  opt.load('compiler_c')
  opt.add_option('--debug', action='store_true', dest='debug', default=False, help='Build with DEBUG')


def configure(conf):
  #conf.env["CC"] = ["clang"]
  conf.load('compiler_c')
  conf.check(header_name='stdio.h', features='c cprogram', mandatory=False)
  conf.check_cfg(package='eina', uselib_store='eina', atleast_version='0.0.1', args='--cflags --libs', mandatory=True)
  conf.check_cfg(package='eet', uselib_store='eet', atleast_version='0.0.1', args='--cflags --libs', mandatory=True)
  conf.check_cfg(package='evas', uselib_store='eet', atleast_version='0.0.1', args='--cflags --libs', mandatory=True)
  #conf.check_cfg(package='efl', uselib_store='efl', atleast_version='1.8.0', args='--cflags --libs', mandatory=True)
  conf.check_cfg(package='libpng', uselib_store='png', atleast_version='0.0.0', mandatory=1, args='--cflags --libs')

  #conf.define ('DEBUG', 0)
  #conf.env['CXXFLAGS']=['-O2']
    
  # set some debug relevant config values
  #if Options.options.debug:
  conf.define ('DEBUG', 1)
  conf.env['CXXFLAGS'] = ['-O0', '-g3', '-Werror']
  conf.env.CFLAGS = ['-g', '-Werror'] 

def post(ctx):
  pass

def build(bld):

  engine_lib_c_files = bld.path.ant_glob('src/*.c')
  engine_lib_c_files += bld.path.ant_glob('src/*/*.c')
  bld.shlib(
      source= engine_lib_c_files,
      target='cypher',
      use='eina eet evas',
      includes = 'src',
      defines = ['EVAS_GL']
      )


