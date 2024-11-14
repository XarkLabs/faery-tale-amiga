// Xark - Pretend like we are amiga39.pre "pre-includes" used by Aztec Manx C on Amiga

#if !defined(AMIGA39_H)
#define AMIGA39_H

#include <stdint.h>

#define timeval amigaOS_timeval // Xark: Avoid conflicting with native OS

#include "exec/types.h"
#include "exec/memory.h"
#include "devices/audio.h"
#include "graphics/view.h"
#include "graphics/scale.h"
#include "hardware/blit.h"
#include "hardware/custom.h"
#include "dos/exall.h"
#include "graphics/gfxmacros.h"
#include "graphics/copper.h"
#include "graphics/display.h"
#include "graphics/text.h"
#include "graphics/gfxbase.h"
#include "graphics/sprite.h"
#include "exec/devices.h"
#include "libraries/diskfont.h"
#include "libraries/dosextens.h"
#include "devices/input.h"
#include "devices/inputevent.h"
#include "devices/trackdisk.h"

#include "clib/alib_protos.h"
#include "clib/cia_protos.h"
#include "clib/colorwheel_protos.h"
#include "clib/commodities_protos.h"
#include "clib/console_protos.h"
#include "clib/disk_protos.h"
#include "clib/diskfont_protos.h"
#include "clib/dos_protos.h"
#include "clib/dtclass_protos.h"
#include "clib/exec_protos.h"
#include "clib/graphics_protos.h"
#include "clib/icon_protos.h"
#include "clib/iffparse_protos.h"
#include "clib/input_protos.h"
#include "clib/intuition_protos.h"
#include "clib/keymap_protos.h"
#include "clib/layers_protos.h"
#include "clib/lowlevel_protos.h"
#include "clib/misc_protos.h"
#include "clib/utility_protos.h"
#include "clib/wb_protos.h"

#undef timeval

#define TRUE 1
#define FALSE 0

#endif