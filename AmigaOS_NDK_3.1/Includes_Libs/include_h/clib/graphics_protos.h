#ifndef  CLIB_GRAPHICS_PROTOS_H
#define  CLIB_GRAPHICS_PROTOS_H

/*
**	$VER: graphics_protos.h 39.31 (29.4.93)
**	Includes Release 40.15
**
**	C prototypes. For use with 32 bit integers only.
**
**	(C) Copyright 1990-1993 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef  GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif
#ifndef  GRAPHICS_DISPLAYINFO_H
#include <graphics/displayinfo.h>
#endif
#ifndef  GRAPHICS_GELS_H
#include <graphics/gels.h>
#endif
#ifndef  GRAPHICS_RASTPORT_H
#include <graphics/rastport.h>
#endif
#ifndef  GRAPHICS_VIEW_H
#include <graphics/view.h>
#endif
#ifndef  GRAPHICS_COPPER_H
#include <graphics/copper.h>
#endif
#ifndef  GRAPHICS_CLIP_H
#include <graphics/clip.h>
#endif
#ifndef  GRAPHICS_REGIONS_H
#include <graphics/regions.h>
#endif
#ifndef  GRAPHICS_SPRITE_H
#include <graphics/sprite.h>
#endif
#ifndef  GRAPHICS_TEXT_H
#include <graphics/text.h>
#endif
#ifndef  HARDWARE_BLIT_H
#include <hardware/blit.h>
#endif
/*------ BitMap primitives ------*/
LONG BltBitMap( struct BitMap *srcBitMap, int32_t xSrc, int32_t ySrc,
	struct BitMap *destBitMap, int32_t xDest, int32_t yDest, int32_t xSize,
	int32_t ySize, uint32_t minterm, uint32_t mask,
	PLANEPTR tempA );
void BltTemplate( PLANEPTR source, int32_t xSrc, int32_t srcMod,
	struct RastPort *destRP, int32_t xDest, int32_t yDest, int32_t xSize,
	int32_t ySize );
/*------ Text routines ------*/
void ClearEOL( struct RastPort *rp );
void ClearScreen( struct RastPort *rp );
WORD TextLength( struct RastPort *rp, STRPTR string, uint32_t count );
LONG Text( struct RastPort *rp, STRPTR string, uint32_t count );
LONG SetFont( struct RastPort *rp, struct TextFont *textFont );
struct TextFont *OpenFont( struct TextAttr *textAttr );
void CloseFont( struct TextFont *textFont );
ULONG AskSoftStyle( struct RastPort *rp );
ULONG SetSoftStyle( struct RastPort *rp, uint32_t style,
	uint32_t enable );
/*------	Gels routines ------*/
void AddBob( struct Bob *bob, struct RastPort *rp );
void AddVSprite( struct VSprite *vSprite, struct RastPort *rp );
void DoCollision( struct RastPort *rp );
void DrawGList( struct RastPort *rp, struct ViewPort *vp );
void InitGels( struct VSprite *head, struct VSprite *tail,
	struct GelsInfo *gelsInfo );
void InitMasks( struct VSprite *vSprite );
void RemIBob( struct Bob *bob, struct RastPort *rp, struct ViewPort *vp );
void RemVSprite( struct VSprite *vSprite );
void SetCollision( uint32_t num,
	void (*routine)(struct VSprite *vSprite, APTR),
	struct GelsInfo *gelsInfo );
void SortGList( struct RastPort *rp );
void AddAnimOb( struct AnimOb *anOb, struct AnimOb **anKey,
	struct RastPort *rp );
void Animate( struct AnimOb **anKey, struct RastPort *rp );
BOOL GetGBuffers( struct AnimOb *anOb, struct RastPort *rp, int32_t flag );
void InitGMasks( struct AnimOb *anOb );
/*------	General graphics routines ------*/
void DrawEllipse( struct RastPort *rp, int32_t xCenter, int32_t yCenter, int32_t a,
	int32_t b );
LONG AreaEllipse( struct RastPort *rp, int32_t xCenter, int32_t yCenter, int32_t a,
	int32_t b );
void LoadRGB4( struct ViewPort *vp, UWORD *colors, int32_t count );
void InitRastPort( struct RastPort *rp );
void InitVPort( struct ViewPort *vp );
ULONG MrgCop( struct View *view );
ULONG MakeVPort( struct View *view, struct ViewPort *vp );
void LoadView( struct View *view );
void WaitBlit( void );
void SetRast( struct RastPort *rp, uint32_t pen );
void Move( struct RastPort *rp, int32_t x, int32_t y );
void Draw( struct RastPort *rp, int32_t x, int32_t y );
LONG AreaMove( struct RastPort *rp, int32_t x, int32_t y );
LONG AreaDraw( struct RastPort *rp, int32_t x, int32_t y );
LONG AreaEnd( struct RastPort *rp );
void WaitTOF( void );
void QBlit( struct bltnode *blit );
void InitArea( struct AreaInfo *areaInfo, APTR vectorBuffer,
	int32_t maxVectors );
void SetRGB4( struct ViewPort *vp, int32_t index, uint32_t red,
	uint32_t green, uint32_t blue );
void QBSBlit( struct bltnode *blit );
void BltClear( PLANEPTR memBlock, uint32_t byteCount,
	uint32_t flags );
void RectFill( struct RastPort *rp, int32_t xMin, int32_t yMin, int32_t xMax,
	int32_t yMax );
void BltPattern( struct RastPort *rp, PLANEPTR mask, int32_t xMin, int32_t yMin,
	int32_t xMax, int32_t yMax, uint32_t maskBPR );
ULONG ReadPixel( struct RastPort *rp, int32_t x, int32_t y );
LONG WritePixel( struct RastPort *rp, int32_t x, int32_t y );
BOOL Flood( struct RastPort *rp, uint32_t mode, int32_t x, int32_t y );
void PolyDraw( struct RastPort *rp, int32_t count, WORD *polyTable );
void SetAPen( struct RastPort *rp, uint32_t pen );
void SetBPen( struct RastPort *rp, uint32_t pen );
void SetDrMd( struct RastPort *rp, uint32_t drawMode );
void InitView( struct View *view );
void CBump( struct UCopList *copList );
void CMove( struct UCopList *copList, APTR destination, int32_t data );
void CWait( struct UCopList *copList, int32_t v, int32_t h );
LONG VBeamPos( void );
void InitBitMap( struct BitMap *bitMap, int32_t depth, int32_t width, int32_t height );
void ScrollRaster( struct RastPort *rp, int32_t dx, int32_t dy, int32_t xMin, int32_t yMin,
	int32_t xMax, int32_t yMax );
void WaitBOVP( struct ViewPort *vp );
WORD GetSprite( struct SimpleSprite *sprite, int32_t num );
void FreeSprite( int32_t num );
void ChangeSprite( struct ViewPort *vp, struct SimpleSprite *sprite,
	PLANEPTR newData );
void MoveSprite( struct ViewPort *vp, struct SimpleSprite *sprite, int32_t x,
	int32_t y );
void LockLayerRom( struct Layer *layer );
void UnlockLayerRom( struct Layer *layer );
void SyncSBitMap( struct Layer *layer );
void CopySBitMap( struct Layer *layer );
void OwnBlitter( void );
void DisownBlitter( void );
struct TmpRas *InitTmpRas( struct TmpRas *tmpRas, PLANEPTR buffer,
	int32_t size );
void AskFont( struct RastPort *rp, struct TextAttr *textAttr );
void AddFont( struct TextFont *textFont );
void RemFont( struct TextFont *textFont );
PLANEPTR AllocRaster( uint32_t width, uint32_t height );
void FreeRaster( PLANEPTR p, uint32_t width, uint32_t height );
void AndRectRegion( struct Region *region, struct Rectangle *rectangle );
BOOL OrRectRegion( struct Region *region, struct Rectangle *rectangle );
struct Region *NewRegion( void );
BOOL ClearRectRegion( struct Region *region, struct Rectangle *rectangle );
void ClearRegion( struct Region *region );
void DisposeRegion( struct Region *region );
void FreeVPortCopLists( struct ViewPort *vp );
void FreeCopList( struct CopList *copList );
void ClipBlit( struct RastPort *srcRP, int32_t xSrc, int32_t ySrc,
	struct RastPort *destRP, int32_t xDest, int32_t yDest, int32_t xSize,
	int32_t ySize, uint32_t minterm );
BOOL XorRectRegion( struct Region *region, struct Rectangle *rectangle );
void FreeCprList( struct cprlist *cprList );
struct ColorMap *GetColorMap( int32_t entries );
void FreeColorMap( struct ColorMap *colorMap );
ULONG GetRGB4( struct ColorMap *colorMap, int32_t entry );
void ScrollVPort( struct ViewPort *vp );
struct CopList *UCopperListInit( struct UCopList *uCopList, int32_t n );
void FreeGBuffers( struct AnimOb *anOb, struct RastPort *rp, int32_t flag );
void BltBitMapRastPort( struct BitMap *srcBitMap, int32_t xSrc, int32_t ySrc,
	struct RastPort *destRP, int32_t xDest, int32_t yDest, int32_t xSize,
	int32_t ySize, uint32_t minterm );
BOOL OrRegionRegion( struct Region *srcRegion, struct Region *destRegion );
BOOL XorRegionRegion( struct Region *srcRegion, struct Region *destRegion );
BOOL AndRegionRegion( struct Region *srcRegion, struct Region *destRegion );
void SetRGB4CM( struct ColorMap *colorMap, int32_t index, uint32_t red,
	uint32_t green, uint32_t blue );
void BltMaskBitMapRastPort( struct BitMap *srcBitMap, int32_t xSrc, int32_t ySrc,
	struct RastPort *destRP, int32_t xDest, int32_t yDest, int32_t xSize,
	int32_t ySize, uint32_t minterm, PLANEPTR bltMask );
BOOL AttemptLockLayerRom( struct Layer *layer );
/*--- functions in V36 or higher (Release 2.0) ---*/
APTR GfxNew( uint32_t gfxNodeType );
void GfxFree( APTR gfxNodePtr );
void GfxAssociate( APTR associateNode, APTR gfxNodePtr );
void BitMapScale( struct BitScaleArgs *bitScaleArgs );
UWORD ScalerDiv( uint32_t factor, uint32_t numerator,
	uint32_t denominator );
WORD TextExtent( struct RastPort *rp, STRPTR string, int32_t count,
	struct TextExtent *textExtent );
ULONG TextFit( struct RastPort *rp, STRPTR string, uint32_t strLen,
	struct TextExtent *textExtent, struct TextExtent *constrainingExtent,
	int32_t strDirection, uint32_t constrainingBitWidth,
	uint32_t constrainingBitHeight );
APTR GfxLookUp( APTR associateNode );
BOOL VideoControl( struct ColorMap *colorMap, struct TagItem *tagarray );
BOOL VideoControlTags( struct ColorMap *colorMap, uint32_t tag1Type,
	... );
struct MonitorSpec *OpenMonitor( STRPTR monitorName,
	uint32_t displayID );
BOOL CloseMonitor( struct MonitorSpec *monitorSpec );
DisplayInfoHandle FindDisplayInfo( uint32_t displayID );
ULONG NextDisplayInfo( uint32_t displayID );
ULONG GetDisplayInfoData( DisplayInfoHandle handle, UBYTE *buf,
	uint32_t size, uint32_t tagID, uint32_t displayID );
void FontExtent( struct TextFont *font, struct TextExtent *fontExtent );
LONG ReadPixelLine8( struct RastPort *rp, uint32_t xstart,
	uint32_t ystart, uint32_t width, UBYTE *array,
	struct RastPort *tempRP );
LONG WritePixelLine8( struct RastPort *rp, uint32_t xstart,
	uint32_t ystart, uint32_t width, UBYTE *array,
	struct RastPort *tempRP );
LONG ReadPixelArray8( struct RastPort *rp, uint32_t xstart,
	uint32_t ystart, uint32_t xstop, uint32_t ystop,
	UBYTE *array, struct RastPort *temprp );
LONG WritePixelArray8( struct RastPort *rp, uint32_t xstart,
	uint32_t ystart, uint32_t xstop, uint32_t ystop,
	UBYTE *array, struct RastPort *temprp );
LONG GetVPModeID( struct ViewPort *vp );
LONG ModeNotAvailable( uint32_t modeID );
WORD WeighTAMatch( struct TextAttr *reqTextAttr,
	struct TextAttr *targetTextAttr, struct TagItem *targetTags );
WORD WeighTAMatchTags( struct TextAttr *reqTextAttr,
	struct TextAttr *targetTextAttr, uint32_t tag1Type, ... );
void EraseRect( struct RastPort *rp, int32_t xMin, int32_t yMin, int32_t xMax,
	int32_t yMax );
ULONG ExtendFont( struct TextFont *font, struct TagItem *fontTags );
ULONG ExtendFontTags( struct TextFont *font, uint32_t tag1Type, ... );
void StripFont( struct TextFont *font );
/*--- functions in V39 or higher (Release 3) ---*/
UWORD CalcIVG( struct View *v, struct ViewPort *vp );
LONG AttachPalExtra( struct ColorMap *cm, struct ViewPort *vp );
LONG ObtainBestPenA( struct ColorMap *cm, uint32_t r, uint32_t g,
	uint32_t b, struct TagItem *tags );
LONG ObtainBestPen( struct ColorMap *cm, uint32_t r, uint32_t g,
	uint32_t b, uint32_t tag1Type, ... );
void SetRGB32( struct ViewPort *vp, uint32_t n, uint32_t r,
	uint32_t g, uint32_t b );
ULONG GetAPen( struct RastPort *rp );
ULONG GetBPen( struct RastPort *rp );
ULONG GetDrMd( struct RastPort *rp );
ULONG GetOutlinePen( struct RastPort *rp );
void LoadRGB32( struct ViewPort *vp, ULONG *table );
ULONG SetChipRev( uint32_t want );
void SetABPenDrMd( struct RastPort *rp, uint32_t apen, uint32_t bpen,
	uint32_t drawmode );
void GetRGB32( struct ColorMap *cm, uint32_t firstcolor,
	uint32_t ncolors, ULONG *table );
struct BitMap *AllocBitMap( uint32_t sizex, uint32_t sizey,
	uint32_t depth, uint32_t flags,
	struct BitMap *friend_bitmap );
void FreeBitMap( struct BitMap *bm );
LONG GetExtSpriteA( struct ExtSprite *ss, struct TagItem *tags );
LONG GetExtSprite( struct ExtSprite *ss, uint32_t tag1Type, ... );
ULONG CoerceMode( struct ViewPort *vp, uint32_t monitorid,
	uint32_t flags );
void ChangeVPBitMap( struct ViewPort *vp, struct BitMap *bm,
	struct DBufInfo *db );
void ReleasePen( struct ColorMap *cm, uint32_t n );
ULONG ObtainPen( struct ColorMap *cm, uint32_t n, uint32_t r,
	uint32_t g, uint32_t b, int32_t f );
ULONG GetBitMapAttr( struct BitMap *bm, uint32_t attrnum );
struct DBufInfo *AllocDBufInfo( struct ViewPort *vp );
void FreeDBufInfo( struct DBufInfo *dbi );
ULONG SetOutlinePen( struct RastPort *rp, uint32_t pen );
ULONG SetWriteMask( struct RastPort *rp, uint32_t msk );
void SetMaxPen( struct RastPort *rp, uint32_t maxpen );
void SetRGB32CM( struct ColorMap *cm, uint32_t n, uint32_t r,
	uint32_t g, uint32_t b );
void ScrollRasterBF( struct RastPort *rp, int32_t dx, int32_t dy, int32_t xMin,
	int32_t yMin, int32_t xMax, int32_t yMax );
LONG FindColor( struct ColorMap *cm, uint32_t r, uint32_t g,
	uint32_t b, int32_t maxcolor );
struct ExtSprite *AllocSpriteDataA( struct BitMap *bm, struct TagItem *tags );
struct ExtSprite *AllocSpriteData( struct BitMap *bm, uint32_t tag1Type,
	... );
LONG ChangeExtSpriteA( struct ViewPort *vp, struct ExtSprite *oldsprite,
	struct ExtSprite *newsprite, struct TagItem *tags );
LONG ChangeExtSprite( struct ViewPort *vp, struct ExtSprite *oldsprite,
	struct ExtSprite *newsprite, uint32_t tag1Type, ... );
void FreeSpriteData( struct ExtSprite *sp );
void SetRPAttrsA( struct RastPort *rp, struct TagItem *tags );
void SetRPAttrs( struct RastPort *rp, uint32_t tag1Type, ... );
void GetRPAttrsA( struct RastPort *rp, struct TagItem *tags );
void GetRPAttrs( struct RastPort *rp, uint32_t tag1Type, ... );
ULONG BestModeIDA( struct TagItem *tags );
ULONG BestModeID( uint32_t tag1Type, ... );
/*--- functions in V40 or higher (Release 3.1) ---*/
void WriteChunkyPixels( struct RastPort *rp, uint32_t xstart,
	uint32_t ystart, uint32_t xstop, uint32_t ystop,
	UBYTE *array, int32_t bytesperrow );
#endif	 /* CLIB_GRAPHICS_PROTOS_H */
