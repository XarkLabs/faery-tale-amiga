extern uint8_t sdl_key;
extern char    raw_asset_fname[128];

uint32_t  swap_endian(uint32_t v);
uint16_t  swap_endian16(uint16_t v);
SDL_Color amiga_color(UWORD color);
void      print_surface_info(char * msg, SDL_Surface * s);
void      save_raw_asset(const char * fname, void * ptr, int32_t len, int appendflag);
int       sdl_init(void);
void      sdl_exit(int retval) __attribute__((noreturn));
void      sdl_update_cursor(struct ViewPort * vp);
void      sdl_endframe(void);
void      sdl_pump(void);
BOOL      unpack_png(char * filename, struct BitMap * bitmap, int16_t wx, int16_t y);
