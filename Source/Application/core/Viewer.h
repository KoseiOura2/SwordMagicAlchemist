#pragma once

#include "Task.h"
#include "mathematics.h"
#include <string>

PTR( Viewer );

const int TILE_SIZE        = 10;								// ‚Pƒ^ƒCƒ‹‚Ì‘å‚«‚³

class Viewer : public Task {
public:
	Viewer( );
	virtual ~Viewer( );
	virtual void initialize( );
	virtual void finalize( );
	void update( );
	Vector convScreenPosToWorldPos( int x, int y, int z );
	void line( Vector p1, Vector p2, int r, int g, int b );
	int getScreenWidth( ) const;
	int getScreenHeight( ) const;
	void setZBuffer( bool on );
	int loadGraph( const char *file_name ) const;
	void deleteGraph( const int handle ) const;
	int loadModel( const char *file_name ) const;
	int duplicateModel( int model_handle ) const;
	void deleatModel( int model_handle ) const;
	void drawModel( const int model_handle ) const;
	int attachAnim( const int model_handle, int anim_index, const int model_anim_handle ) const;
	void dettachAnim( const int model_handle, int anim_index ) const;
	float animTotalTime( const int model_handle, int anim_index ) const;
	void setAttachAnimTime( const int model_handle, int anim_index, float time ) const;
	void drawBillboard( const Vector& pos, int id, double size ) const;
	void drawPolygonFloor( const Vector& pos, int id ) const;
	void drawPolygonWall( const Vector& pos, int id, int id_2 ) const;
	void drawBox( const int width, const int height, Vector2& pos, int r, int g, int b, bool fill ) const;
	void modelSetPos( const int model_handle, const Vector pos );
	void modelSetRotation( const int model_handle, float angle_x, float angle_y, float angle_z );
	void modelSetScale( const int model_handle, float x, float y, float z );
	void flip( );
	void drawGraph( const int x, const int y, const int id ) const;
	void drawRectGraph( const int x, const int y, const int src_x, const int src_y, const int width, const int height, const int id ) const;
	void setNormalBlend( );
	void setAlpha( int pal );
	void drawExtendGraph( const int x1, const int y1, const int x2, const int y2, const int id ) const;
private:
	int _screen_width;
	int _screen_height;
	int _count;
};

