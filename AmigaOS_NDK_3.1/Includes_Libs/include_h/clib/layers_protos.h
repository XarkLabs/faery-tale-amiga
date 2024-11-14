#ifndef  CLIB_LAYERS_PROTOS_H
#define  CLIB_LAYERS_PROTOS_H

/*
**	$VER: layers_protos.h 38.7 (26.3.92)
**	Includes Release 40.15
**
**	C prototypes. For use with 32 bit integers only.
**
**	(C) Copyright 1990-1993 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef  EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef  GRAPHICS_LAYERS_H
#include <graphics/layers.h>
#endif
#ifndef  GRAPHICS_CLIP_H
#include <graphics/clip.h>
#endif
#ifndef  GRAPHICS_RASTPORT_H
#include <graphics/rastport.h>
#endif
#ifndef  GRAPHICS_REGIONS_H
#include <graphics/regions.h>
#endif
void InitLayers( struct Layer_Info *li );
struct Layer *CreateUpfrontLayer( struct Layer_Info *li, struct BitMap *bm,
	int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t flags, struct BitMap *bm2 );
struct Layer *CreateBehindLayer( struct Layer_Info *li, struct BitMap *bm,
	int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t flags, struct BitMap *bm2 );
LONG UpfrontLayer( int32_t dummy, struct Layer *layer );
LONG BehindLayer( int32_t dummy, struct Layer *layer );
LONG MoveLayer( int32_t dummy, struct Layer *layer, int32_t dx, int32_t dy );
LONG SizeLayer( int32_t dummy, struct Layer *layer, int32_t dx, int32_t dy );
void ScrollLayer( int32_t dummy, struct Layer *layer, int32_t dx, int32_t dy );
LONG BeginUpdate( struct Layer *l );
void EndUpdate( struct Layer *layer, uint32_t flag );
LONG DeleteLayer( int32_t dummy, struct Layer *layer );
void LockLayer( int32_t dummy, struct Layer *layer );
void UnlockLayer( struct Layer *layer );
void LockLayers( struct Layer_Info *li );
void UnlockLayers( struct Layer_Info *li );
void LockLayerInfo( struct Layer_Info *li );
void SwapBitsRastPortClipRect( struct RastPort *rp, struct ClipRect *cr );
struct Layer *WhichLayer( struct Layer_Info *li, int32_t x, int32_t y );
void UnlockLayerInfo( struct Layer_Info *li );
struct Layer_Info *NewLayerInfo( void );
void DisposeLayerInfo( struct Layer_Info *li );
LONG FattenLayerInfo( struct Layer_Info *li );
void ThinLayerInfo( struct Layer_Info *li );
LONG MoveLayerInFrontOf( struct Layer *layer_to_move,
	struct Layer *other_layer );
struct Region *InstallClipRegion( struct Layer *layer,
	struct Region *region );
LONG MoveSizeLayer( struct Layer *layer, int32_t dx, int32_t dy, int32_t dw, int32_t dh );
struct Layer *CreateUpfrontHookLayer( struct Layer_Info *li, struct BitMap *bm,
	int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t flags, struct Hook *hook,
	struct BitMap *bm2 );
struct Layer *CreateBehindHookLayer( struct Layer_Info *li, struct BitMap *bm,
	int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t flags, struct Hook *hook,
	struct BitMap *bm2 );
struct Hook *InstallLayerHook( struct Layer *layer, struct Hook *hook );
/*--- functions in V39 or higher (Release 3) ---*/
struct Hook *InstallLayerInfoHook( struct Layer_Info *li, struct Hook *hook );
void SortLayerCR( struct Layer *layer, int32_t dx, int32_t dy );
void DoHookClipRects( struct Hook *hook, struct RastPort *rport,
	struct Rectangle *rect );
#endif	 /* CLIB_LAYERS_PROTOS_H */
