
# The presence of this file turns this directory into a Python package

# ----------------------------------------------------------------
# Temporary workaround for ticket:181 (swig+python problem)
import sys
_RTLD_GLOBAL = 0
try:
    from dl import RTLD_GLOBAL as _RTLD_GLOBAL
except ImportError:
    try:
	from DLFCN import RTLD_GLOBAL as _RTLD_GLOBAL
    except ImportError:
	pass
    
if _RTLD_GLOBAL != 0:
    _dlopenflags = sys.getdlopenflags()
    sys.setdlopenflags(_dlopenflags|_RTLD_GLOBAL)
# ----------------------------------------------------------------


# import swig generated symbols into the howto namespace
from dip_swig import *

# import any pure python here
#

# ----------------------------------------------------------------
# Tail of workaround
if _RTLD_GLOBAL != 0:
    sys.setdlopenflags(_dlopenflags)      # Restore original flags
# ----------------------------------------------------------------
