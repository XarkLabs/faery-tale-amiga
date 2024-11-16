#include "ftale.h"        // Xark: Added to verify headers in sync

extern UWORD openflags;

// static BOOL hdrive = FALSE;
static FILE * filep;

/* 9 diskreqs: 5 landscape, 2 Terrain, 1 map, 1 sector, 1 monster */

// struct MsgPort * diskport;
// struct IOExtTD * diskreq1, diskreqs[10], *lastreq;

int AllocDiskIO()
{
    // int16_t i;
    // BPTR    lock;
    //     if ((lock = Lock("image", ACCESS_READ)))
    //     {
    //         hdrive = TRUE;
    //         UnLock(lock);
    //
    //         if ((file = Open("image", MODE_OLDFILE)) == 0)
    //             return 30;        // Xark: NULL -> 0 (since BPTR)
    //     }
    //     else
    //     {
    //         if ((diskport = CreatePort(0, 0)) == 0)
    //             return 30;
    //         SETFN(AL_PORT);
    //         if ((diskreq1 = (struct IOExtTD *)CreateExtIO(diskport, sizeof(struct IOExtTD))) ==
    //         0)
    //             return 31;
    //         SETFN(AL_IOREQ);
    //         if (OpenDevice(TD_NAME, 0, (struct IORequest *)diskreq1, 0))
    //             return 32;
    //         SETFN(AL_TDISK);
    //         for (i = 0; i < 9; i++)
    //         {
    //             diskreqs[i] = *diskreq1;
    //         }
    //     }

    // Xark:    hdrive = TRUE;

    if ((filep = fopen("game/image", "r")) == NULL)
    {
        printf("\nCan't open game data: \"game/image\"\n\n");
        return 30;
    }

    return 0;
}

void FreeDiskIO()
{
    if (filep)
    {
        fclose(filep);
        filep = NULL;
    }

    // if (TSTFN(AL_TDISK))
    //     CloseDevice((struct IORequest *)diskreq1);
    // if (TSTFN(AL_IOREQ))
    //     DeleteExtIO((struct IORequest *)diskreq1);
    // if (TSTFN(AL_PORT))
    //     DeletePort(diskport);
}

void WaitDiskIO(int num)
{
    (void)num;
    // if (hdrive == FALSE)
    //     WaitIO((struct IORequest *)&diskreqs[num]);
}

void InvalidDiskIO(int num)
{
    (void)num;
    // if (hdrive == FALSE)
    //     diskreqs[num].iotd_Req.io_Command = CMD_INVALID;
}

int CheckDiskIO(int num)
{
    (void)num;
    // if (hdrive == FALSE)
    //     return (CheckIO((struct IORequest *)&diskreqs[num]) == NULL)
    //                ? FALSE
    //                : TRUE;        // Xark: Converting ptr to int, test added

    return TRUE;
}

int IsReadDiskIO(int num)
{
    (void)num;
    // if (hdrive == FALSE)
    //     return (diskreqs[num].iotd_Req.io_Command == CMD_READ);

    return FALSE;
}

void WaitLastDiskIO()
{
    // if (hdrive == FALSE)
    //     WaitIO((struct IORequest *)lastreq);
}

void InvalidLastDiskIO()
{
    // if (hdrive == FALSE)
    //     lastreq->iotd_Req.io_Command = CMD_INVALID;
}

int CheckLastDiskIO()
{
    // if (hdrive == FALSE)
    //     return (CheckIO((struct IORequest *)lastreq) == NULL) ? FALSE : TRUE;

    return TRUE;
}

int IsReadLastDiskIO()
{
    // if (hdrive == FALSE)
    //     return (lastreq->iotd_Req.io_Command == CMD_READ);

    return FALSE;
}

void load_track_range(int16_t f_block, int16_t b_count, APTR buffer, int16_t dr)
{
    // Xark: unused:    int16_t error;
    (void)dr;

    // if (hdrive == FALSE)
    // {
    //     lastreq = &(diskreqs[dr]);
    //     if (lastreq->iotd_Req.io_Command == CMD_READ)
    //         WaitIO((struct IORequest *)lastreq);
    //     *lastreq                     = *diskreq1;
    //     lastreq->iotd_Req.io_Length  = b_count * 512;
    //     lastreq->iotd_Req.io_Data    = buffer;
    //     lastreq->iotd_Req.io_Command = CMD_READ;
    //     lastreq->iotd_Req.io_Offset  = f_block * 512;
    //     SendIO((struct IORequest *)lastreq);
    // }
    // else
    {
        CHECK(0 == fseek(filep, f_block * 512, SEEK_SET));
        CHECK(1 == fread(buffer, b_count * 512, 1, filep));
    }
}

void motor_off(void)
{
    // if (hdrive == FALSE)
    // {
    //     diskreqs[9]                     = *diskreq1;
    //     diskreqs[9].iotd_Req.io_Length  = 0;
    //     diskreqs[9].iotd_Req.io_Command = TD_MOTOR;
    //     DoIO((struct IORequest *)&diskreqs[9]);
    // }
}

// BOOL IsHardDrive(void)
// {
//     return hdrive;
// }
