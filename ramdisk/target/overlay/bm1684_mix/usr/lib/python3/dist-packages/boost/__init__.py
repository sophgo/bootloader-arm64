import sys
if sys.platform == 'linux2':
    import DLFCN as dl
    flags = sys.getdlopenflags()
    sys.setdlopenflags(dl.RTLD_NOW|dl.RTLD_GLOBAL)
    import mpi
    sys.setdlopenflags(flags)
if sys.platform == 'linux':
    from . import mpi
else:
    import mpi

