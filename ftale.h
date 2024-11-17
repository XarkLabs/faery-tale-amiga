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
#define BPTR_OFFSET_ADDR(bptr, byteoff, ptype) (ptype *)((intptr_t)(bptr << 2) + byteoff)

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

// "wizard" = 0
// "priest" = 1
// "guard" = 2
// "guard" = 3 (back)
// "princess" = 4
// "king" = 5
// "noble" = 6
// "sorceress" = 7
// "bartender" = 8
// "witch" = 9
// "spectre" = 10
// "ghost" = 11
// "ranger" = 12
// "begger" = 13
#define NUM_SETFIG_ENTRIES 14

// Xark: moved here
struct setfig
{
    BYTE cfile_entry, image_base, can_talk;
};

// Xark: moved here
#define SETFN(n) openflags |= n
#define TSTFN(n) openflags & n

/* allocation definitions */
#define AL_BMAP   0x0001
#define AL_GBASE  0x0002
#define AL_HANDLE 0x0004
#define AL_MUSIC  0x0008
#define AL_IMAGE  0x0010
#define AL_SECTOR 0x0020
#define AL_MASK   0x0040
#define AL_SHAPE  0x0080
#define AL_SHADOW 0x0100
#define AL_FONT   0x0200
#define AL_SAMPLE 0x0400
#define AL_PORT   0x0800
#define AL_IOREQ  0x1000
#define AL_TDISK  0x2000
#define AL_TERR   0x4000

// sst position code
#define XY          0x80  // then x/2 then y

// current RastPort
extern struct RastPort * rp;

// compass image data
extern UBYTE hinor[];
extern UBYTE hivar[];

extern char event_msg[];
extern char speeches[];

extern char endload[2];

extern struct in_work   handler_data;
extern struct TextFont *tfont, *afont;

// Xark includes after structs
#include "fmain.h"
#include "fmain2.h"
#include "iffsubs.h"
#include "sdlsubs.h"

// Xark: Functions below are from assembly files
// TODO: Clean these up

void    map_draw(void);
void    scrollmap(int32_t dir);
int32_t px_to_im(USHORT x, USHORT y);
int32_t newx(int32_t x, int32_t dir, int32_t speed);
int32_t newy(int32_t y, int32_t dir, int32_t speed);
UBYTE * mapxy(int32_t x, int32_t y);
void    map_adjust(int32_t x, int32_t y);
void    bigdraw(int32_t x, int32_t y);
void    genmini(int32_t x, int32_t y);
void    move(int32_t x, int32_t y);
void    rest_blit(UBYTE *);
void    clear_blit(UBYTE *, LONG size);
void    save_blit(UBYTE *);
void    mask_blit(void);
void    shape_blit(void);
void    strip_draw(int32_t s);
void    row_draw(int32_t y);
void    maskit(int32_t x, int32_t y, int32_t mod, int32_t cnum);
void    make_mask(UBYTE * s, UBYTE * d, int32_t words, int32_t lines, int32_t len);
void    prdec(int32_t val, int32_t len);
void    dohit(int32_t i, int32_t j, int32_t fc, int16_t wt);
int32_t page_det(int32_t x);

int32_t AllocDiskIO(void);
void    FreeDiskIO(void);
void    WaitDiskIO(int32_t num);
void    InvalidDiskIO(int32_t num);
int32_t CheckDiskIO(int32_t num);
int32_t IsReadDiskIO(int32_t num);
int32_t CheckLastDiskIO(void);
int32_t IsReadLastDiskIO(void);

void do_error(int32_t e);
void init_music(SHORT * new_wave, UBYTE * wav_mem, UBYTE * vol_mem);
void wrap_music(void);
void setscore(UBYTE * t1, UBYTE * t2, UBYTE * t3, UBYTE * t4);
void stopscore(void);
void playscore(UBYTE * t1, UBYTE * t2, UBYTE * t3, UBYTE * t4);
void playsample(UBYTE * ptr, LONG length, LONG rate);

int32_t stuff_flag(int32_t f);

void    text(char *, int32_t len);
void    ssp(UBYTE *);
void    placard(void);
void    placard_text(int32_t n);
void    prq(int32_t n);
int32_t getkey(void);
int32_t rnd(int32_t m);
void    decode_mouse(void);
void    msg(char *, int32_t n);
void    speak(int32_t p);
void    event(int32_t e);
void    set_course(int32_t object, int32_t target_x, int32_t target_y, int32_t mode);
void    question(int32_t q);
void    cursor(int32_t len, int32_t color);

int32_t bitrand(int32_t m);
int32_t ft_rand(void);        // Xark: rand->ft_rand
int32_t rand2(void);
int32_t rand4(void);
int32_t rand8(void);
int32_t rand64(void);
int32_t rand256(void);
int16_t wrap(int16_t v);

int32_t prox(int32_t x, int32_t y);

// fsubs
int32_t HandlerInterface(struct InputEvent * a0, struct in_work * a1);

// makebitmap
BOOL MakeBitMap(struct BitMap * b, int32_t depth, int32_t width, int32_t height);
void UnMakeBitMap(struct BitMap * b);

// EOF
