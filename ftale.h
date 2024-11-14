/* include file for faery tale adventures - by Talin */

// Xark new additions
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "amiga39.h"        // Xark: most AmigaOS includes (like "amiga39.pre")

#define free_chip(new, old, size)                                                                  \
    if (new != old)                                                                                \
        FreeMem(new, size);

        // TODO: used based pointer
#define BPTR_ADDR(bptr, ptype) (ptype *)((intptr_t)bptr << 2)
// TODO: used based pointer
#define BPTR_OFFSET_ADDR(bptr, byteoff, ptype)                                                     \
    (ptype *)((intptr_t)(bptr << 2) + byteoff)        

/* motion states */
#define WALKING  12
#define STILL    13
#define FIGHTING 0
#define DYING    14
#define DEAD     15
#define SINK     16
#define OSCIL    17 /* and 18 */
#define TALKING  19
#define FROZEN   20
#define FLYING   21
#define FALL     22
#define SLEEP    23
#define SHOOT1   24 /* bow up - aiming */
#define SHOOT3   25 /* bow fired, arrow given velocity */

/* goal modes */

#define USER     0  /* character is user-controlled */
#define ATTACK1  1  /* attack character (stupidly) */
#define ATTACK2  2  /* attack character (cleverly) */
#define ARCHER1  3  /* archery attack style 1 */
#define ARCHER2  4  /* archery attack style 2 */
#define FLEE     5  /* run directly away */
#define STAND    6  /* don't move but face character */
#define DEATH    7  /* a dead character */
#define WAIT     8  /* wait to speak to character */
#define FOLLOWER 9  /* follow another character */
#define CONFUSED 10 /* run around randomly */

/* tactical modes (sub-goals) */
/* choices 2-5 can be selected randomly for getting around obstacles */

#define FRUST       0  /* all tactics frustrated - try sonething else */
#define PURSUE      1  /* go in the direction of the character */
#define FOLLOW      2  /* go toward another character */
#define BUMBLE_SEEK 3  /* bumble around looking for him */
#define RANDOM      4  /* move randomly */
#define BACKUP      5  /* opposite direction we were going */
#define EVADE       6  /* move 90 degrees from character */
#define HIDE        7  /* seek a hiding place */
#define SHOOT       8  /* shoot an arrow */
#define SHOOTFRUST  9  /* arrows not getting through */
#define EGG_SEEK    10 /* snakes going for the eggs */
#define DOOR_SEEK   11 /* dknight blocking door */
#define DOOR_LET    12 /* dknight letting pass */

struct shape
{
    uint16_t abs_x, abs_y, rel_x, rel_y;
    char     type;
    UBYTE    race;
    char     index, visible,       /* image index and on-screen flag */
        weapon,                    /* type of weapon carried */
        environ,                   /* environment variable */
        goal, tactic,              /* current goal mode and means to carry it out */
        state, facing;             /* current movement state and facing */
    int16_t vitality;              /* also original object number */
    char    vel_x, vel_y;          /* velocity for slippery areas */
    /*	APTR	source_struct;	*/ /* address of generating structure */
};

struct fpage
{
    struct RasInfo * ri_page;
    struct cprlist * savecop;
    int32_t          isv_x, isv_y;
    int16_t          obcount;
    struct sshape *  shape_queue;
    uint8_t *        backsave;
    int32_t          saveused;
    int16_t          witchx, witchy, witchdir, wflag; /* for erasure */
};

struct seq_info
{
    int16_t  width, height, count; /* this part loaded in */
    uint8_t *location, *maskloc;
    int16_t  bytes; /* this part calculated */
    int16_t  current_file;
};

enum sequences
{
    PHIL,
    OBJECTS,
    ENEMY,
    RAFT,
    SETFIG,
    CARRIER,
    DRAGON
};

struct object
{ /* 250 objects, for a start */
    uint16_t xc, yc;
    char     ob_id, ob_stat;
};

struct inv_item
{
    UBYTE  image_number;        /* what image number to use */
    UBYTE  xoff, yoff;          /* x and y offset on image screen */
    UBYTE  ydelta;              /* y increment value */
    UBYTE  img_off, img_height; /* what part of the image to draw */
    UBYTE  maxshown;            /* maximum number that can be shown */
    char * name;
};

struct need
{
    USHORT image[4], terra1, terra2, sector, region, setchar;
};

struct in_work
{ /* input handler data area */
    int16_t               xsprite, ysprite;
    int16_t               qualifier; /* input qualifier */
    UBYTE                 laydown, pickup;
    char                  newdisk, lastmenu;
    struct GfxBase *      gbase;
    struct SimpleSprite * pbase;
    struct ViewPort *     vbase;
    uint8_t               keybuf[128];
    int16_t               ticker;
};

// Xark includes after structs
#include "fmain.h"
#include "fmain2.h"
#include "iffsubs.h"

// Xark: Functions below are from assembly files
// TODO: Clean these up

int  MakeBitMap(struct BitMap * b, int depth, int width, int height);
void UnMakeBitMap(struct BitMap * b);

void    map_draw(void);
void    scrollmap(int dir);
int     px_to_im(USHORT x, USHORT y);
int     newx(int x, int dir, int speed);
int     newy(int y, int dir, int speed);
UBYTE * mapxy(int x, int y);
void    map_adjust(int safe_x, int safe_y);
void    bigdraw(int x, int y);
void    genmini(int x, int y);
void    move(int x, int y);
void    rest_blit(UBYTE *);
void    clear_blit(UBYTE *, LONG size);
void    save_blit(UBYTE *);
void    mask_blit(void);
void    shape_blit(void);
void    strip_draw(int s);
void    row_draw(int r);
void    maskit(int x, int y, int mod, char c);
void    make_mask(UBYTE * s, UBYTE * d, int words, int lines, int len);
void    prdec(int val, int len);
void    dohit(int32_t i, int32_t j, int32_t fc, int16_t wt);
int     page_det(int d);

int  AllocDiskIO(void);
void FreeDiskIO(void);
void WaitDiskIO(int num);
void InvalidDiskIO(int num);
int  CheckDiskIO(int num);
int  IsReadDiskIO(int num);
int  CheckLastDiskIO();
int  IsReadLastDiskIO();

void do_error(int e);
void init_music(SHORT * new_wave, UBYTE * wav_mem, UBYTE * vol_mem);
void wrap_music(void);
void setscore(UBYTE * v1, UBYTE * v2, UBYTE * v3, UBYTE * v4);
void stopscore(void);
void playscore(UBYTE * t1, UBYTE * t2, UBYTE * t3, UBYTE * t4);
void playsample(UBYTE * ptr, LONG length, LONG rate);

int stuff_flag(int f);

void text(char *, int len);
void ssp(char *);
void placard(void);
void placard_text(int msg);
void prq(int p);
int  getkey(void);
int  rnd(int x);
void decode_mouse(void);
void msg(char *, int len);
void speak(int p);
void event(int e);
void set_course(int object, int target_x, int target_y, int mode);
void question(int q);
void cursor(int len, int color);

int bitrand(int m);
int rand(void);
int rand2(void);
int rand4(void);
int rand8(void);
int rand64(void);
int rand256(void);
int wrap(int v);

int prox(int x, int y);
