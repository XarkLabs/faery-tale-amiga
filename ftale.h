/* include file for faery tale adventures - by Talin */

// Xark new additions
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "amigaos.h"        // Xark: most AmigaOS includes (like "amiga39.pre")

// FTA defines and sizes

/* playing map is 6 * 19 = 114 */        // Xark: Or 120?

#define PAGE_DEPTH 5
#define TEXT_DEPTH 4

#define SCREEN_WIDTH 288
#define PHANTA_WIDTH 320 /* two words added for horizontal scrolling */

#define PAGE_HEIGHT 143
#define RAST_HEIGHT 200
#define TEXT_HEIGHT 57

#define TERRA_BLOCK 149
#define NO_REGION   10

#define MAXCOORD (16 * 16 * 128)
#define MAXMASK  MAXCOORD - 1

#define QPLAN_SZ   4096           /* 1 plane of 64 chars */
#define IPLAN_SZ   16384          /* 1 plane of 256 chars */
#define IMAGE_SZ   (IPLAN_SZ * 5) /* 5 planes of 256 chars - 81K */
#define SHAPE_SZ   (78000)
#define SHADOW_SZ  8192 + 4096          /* background masks */
#define SECTOR_SZ  ((128 * 256) + 4096) /* 256 sectors - 32K+4K region map */
#define SECTOR_OFF (128 * 256)          /* 256 sectors - 32K */
#define SAMPLE_SZ  (5632)               /* 5K for samples */

#define S_WAVBUF (128 * 8)
#define S_VOLBUF (10 * 256)
#define VOICE_SZ (S_WAVBUF + S_VOLBUF)
#define SCORE_SZ 5900

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
    char     index;
    char     visible; /* image index and on-screen flag */
    char     weapon;  /* type of weapon carried */
    char     environ; /* environment variable */
    char     goal;
    char     tactic; /* current goal mode and means to carry it out */
    char     state;
    char     facing;              /* current movement state and facing */
    int16_t  vitality;            /* also original object number */
    char     vel_x, vel_y;        /* velocity for slippery areas */
    /* APTR     source_struct; */ /* address of generating structure */
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
    int16_t          witchx, witchy;
    int16_t          witchdir;
    int16_t          wflag; /* for erasure */
};

struct seq_info
{
    int16_t   width, height, count; /* this part loaded in */
    uint8_t * location;
    uint8_t * maskloc;
    int16_t   bytes; /* this part calculated */
    int16_t   current_file;
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
    char * debug_name;
};

#define KEYBUFFER_SIZE 0x80        // NOTE: probably excessive (must be POT)

/* input handler data */
struct in_work
{
    int16_t               xsprite, ysprite;
    int16_t               qualifier; /* input qualifier */
    UBYTE                 laydown, pickup;
    char                  newdisk, lastmenu;
    struct GfxBase *      gbase;
    struct SimpleSprite * pbase;
    struct ViewPort *     vbase;
    uint8_t               keybuf[KEYBUFFER_SIZE];
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

struct setfig
{
    BYTE cfile_entry, image_base, can_talk;
};

struct extent
{
    UWORD x1, y1, x2, y2;
    UBYTE etype, v1, v2, v3;
};

extern struct extent extent_list[];

struct encounter
{
    char hitpoints, agressive, arms, cleverness, treasure, file_id;
};

extern struct encounter encounter_chart[];

extern char treasure_probs[];
extern char weapon_probs[];

extern char bow_x[];
extern char bow_y[];
extern char bowshotx[];
extern char bowshoty[];
extern char gunshoty[];

extern UBYTE place_tbl[];
extern UBYTE inside_tbl[];
extern char  place_msg[];
extern char  inside_msg[];

extern char    turtle_eggs;
extern UBYTE   fallstates[];
extern int16_t cheat1;
extern int16_t cheat2;
extern char    quitflag;

extern uint16_t encounter_type;
extern uint8_t  encounter_number;
extern char     actors_loading;
extern int16_t  wt;

extern struct object ob_listg[];
extern struct object ob_list8[];

extern int16_t minimap[120];

extern BYTE svflag;

extern UBYTE itrans[];
extern char  jtrans[];

extern int16_t s1, s2;

extern int16_t secret_timer, light_timer, freeze_timer;
extern UWORD   region_num, new_region;

extern struct shape anim_list[20];
extern int16_t      anix, anix2;

extern USHORT hero_x, hero_y, map_x, map_y;

extern USHORT pagecolors[];

extern char skipp;

extern UBYTE titletext[];

extern struct View     v;
extern struct ViewPort vp_page;
extern struct ViewPort vp_text;

extern struct RastPort rp_map;
extern struct RastPort rp_text;
extern struct BitMap * bm_draw;
extern struct fpage *  fp_drawing;
extern struct fpage *  fp_viewing;

extern char viewstatus;

#define FTMOUSE_MIN_X 5
#define FTMOUSE_MAX_X 315
#define FTMOUSE_MIN_Y 147
#define FTMOUSE_MAX_Y 195

#define FTMOUSE_MENU_MIN_X  215        // X >= for menu
#define FTMOUSE_MENU_MID_X  240        // X > for 2nd menu column
#define FTMOUSE_MENU_MAX_X  265        // X <= for menu
#define FTMOUSE_MENU_MIN_Y  144        // Y >= for menu
#define FTMOUSE_MENU_HEIGHT 9          // height of menu item

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
#define XY 0x80        // followed by x/2 then y

// current RastPort
extern struct RastPort * rp;

// compass image data
extern UBYTE           nhinor[];
extern UBYTE           nhivar[];
extern struct BitMap * bm1_source;
extern struct BitMap * bm2_source;

extern int16_t oldir;
extern int16_t keydir;

extern char event_msg[];
extern char speeches[];

extern char endload[2];

extern struct in_work   handler_data;
extern struct TextFont *tfont, *afont;

// Xark includes after structs
#include "fmain.h"
#include "fmain2.h"

// Xark: Functions below are from assembly files
// TODO: Clean these up

const char * c_string(const char * s, int maxlen);
void         map_draw(void);
void         scrollmap(int32_t dir);
int32_t      px_to_im(USHORT x, USHORT y);
int16_t      newx(int16_t x, int16_t dir, int16_t speed);
int16_t      newy(int16_t y, int16_t dir, int16_t speed);
UBYTE *      mapxy(int32_t x, int32_t y);
void         map_adjust(int16_t x, int16_t y);
void         bigdraw(int32_t x, int32_t y);
void         genmini(int32_t x, int32_t y);
void         move(int32_t x, int32_t y);
void         rest_blit(UBYTE *);
void         clear_blit(UBYTE *, LONG size);
void         save_blit(UBYTE *);
void         mask_blit(void);
void         shape_blit(void);
void         strip_draw(int32_t s);
void         row_draw(int32_t y);
void         maskit(int32_t x, int32_t y, int32_t mod, int32_t cnum);
void         make_mask(UBYTE * s, UBYTE * d, int32_t words, int32_t lines, int32_t len);
void         prdec(int32_t val, int32_t len);
void         dohit(int32_t i, int32_t j, int32_t fc, int16_t wt);
int32_t      page_det(int32_t x);

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

// makebitmap
BOOL MakeBitMap(struct BitMap * b, int32_t depth, int32_t width, int32_t height, const char * name);
void UnMakeBitMap(struct BitMap * b);

// sdlsubs.c
extern BOOL  big_endian;
extern char  raw_asset_fname[128];
extern float sdl_window_scale;
extern BOOL  sdl_quit;
extern BOOL  sdl_screenshot;

extern struct BitMap * bm_text;


uint32_t  swap_endian(uint32_t v);
uint16_t  swap_endian16(uint16_t v);
SDL_Color amiga_color(UWORD color);
void      print_surface_info(char * msg, SDL_Surface * s);
void      save_raw_asset(const char * fname, void * ptr, int32_t len, int appendflag);
int       sdl_init(void);
void      sdl_exit(int retval) __attribute__((noreturn));
void      sdl_update_cursor(struct ViewPort * vp);
void      sdl_save_screenshot(char * name);
void      sdl_drawframe(void);
void      sdl_endframe(void);
void      add_to_keybuf(int key);
int16_t   get_from_keybuf();
void      ft_mouse_button(int16_t qual);
void      ft_mouse_pos(int16_t x, int16_t y);
void      sdl_blitsurface8(SDL_Surface * src, SDL_Rect * sr, SDL_Surface * dest, SDL_Rect * dr);
void      sdl_blitsurface8_transmask(SDL_Surface * src,
                                     SDL_Rect *    sr,
                                     SDL_Surface * dest,
                                     SDL_Rect *    dr,
                                     UBYTE         maskbyte);
void      sdl_blitsurface8_or_bitplane(SDL_Surface * src,
                                       SDL_Rect *    sr,
                                       SDL_Surface * dest,
                                       SDL_Rect *    dr,
                                       UBYTE         planebyte);
void      sdl_extract_bitplane(SDL_Surface * dest, UBYTE * planedata, UBYTE planemask);


void sdl_pump(void);
BOOL unpack_png(char * filename, struct BitMap * bitmap, int16_t wx, int16_t y);

// EOF
