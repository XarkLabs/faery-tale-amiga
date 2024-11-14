// amigaos_dos.c
#include "amiga39.h"

#include <stdlib.h>
#include <stdio.h>

// success = Close( file )
LONG Close(BPTR bfile)
{
    // TODO: Close
    RUNLOGF("1 <= dos.Close(0x%x) STUB", bfile);
    return TRUE;
}
