#include "Viewer.h"
#include "DxLib.h"

const int WALL_HEIGHT = 8;

Viewer::Viewer( ) {
	GetWindowSize( &_screen_width, &_screen_height );
	_count = GetNowCount( );
}

Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
}

void Viewer::finalize( ) {

}

void Viewer::update( ) {
	while ( 1 ) {
		int now = GetNowCount( );
		if ( now - _count > 1000 / 30 ) {
			_count = now;
			break;
		}
	}

	flip( );
}

void Viewer::flip( ) {
	ScreenFlip( );
	ClearDrawScreen( );
}

Vector Viewer::convScreenPosToWorldPos( int x, int y, int z ) {
	VECTOR vp = VGet( ( float )x, ( float )y, ( float )z );
	vp = ConvScreenPosToWorldPos( vp );
	Vector pos = Vector( vp.x, vp.y, vp.z ); 
	return pos;
}

void Viewer::line( Vector p1, Vector p2, int r, int g, int b ) {
	DrawLine3D( 
		VGet( ( float )p1.x, ( float )p1.y, ( float )p1.z ),
		VGet( ( float )p2.x, ( float )p2.y, ( float )p2.z ),
		GetColor( r, g, b ) );
}

int Viewer::getScreenWidth( ) const {
	return _screen_width;
}

int Viewer::getScreenHeight( ) const {
	return _screen_height;
}


void Viewer::setZBuffer( bool on ) {
	if ( on ) {
		SetUseZBuffer3D( TRUE );
		SetWriteZBuffer3D( TRUE );
	} else {
		SetUseZBuffer3D( FALSE );
		SetWriteZBuffer3D( FALSE );
	}
}

int Viewer::loadGraph( const char *file_name ) const {
	return LoadGraph( file_name );
}

int Viewer::loadModel( const char *file_name ) const {
	return MV1LoadModel( file_name );
}

int Viewer::duplicateModel( int model_handle ) const {
	return MV1DuplicateModel( model_handle );
}

void Viewer::deleatModel( int model_handle ) const {
	MV1DeleteModel( model_handle );
}

void Viewer::drawModel( const int model_handle ) const {
	MV1DrawModel( model_handle );
}

int Viewer::attachAnim( const int model_handle, int anim_index, const int model_anim_handle ) const {
	return MV1AttachAnim( model_handle, anim_index, model_anim_handle, FALSE );
}

void Viewer::dettachAnim( const int model_handle, int anim_index ) const {
	MV1DetachAnim( model_handle, anim_index );
}

float Viewer::animTotalTime( const int model_handle, int anim_index ) const {
	return MV1GetAttachAnimTotalTime( model_handle, anim_index );
}

void Viewer::setAttachAnimTime( const int model_handle, int anim_index, float time ) const {
	MV1SetAttachAnimTime( model_handle, anim_index, time );
}

void Viewer::modelSetPos( const int model_handle, const Vector pos ) {
	MV1SetPosition( model_handle, VGet( ( float )pos.x + 5.0f, ( float )pos.y, ( float )pos.z + 5.0f ) );
}

void Viewer::modelSetRotation( const int model_handle, float angle_x, float angle_y, float angle_z ) {
	MV1SetRotationXYZ( model_handle, VGet( angle_x * DX_PI_F / 180.0f, angle_y * DX_PI_F / 180.0f, angle_z * DX_PI_F / 180.0f ) );
}

void Viewer::modelSetScale(  const int model_handle, float x, float y, float z ) {
	MV1SetScale( model_handle, VGet( x, y, z ) );
}


void Viewer::drawGraph( const int x, const int y, const int id ) const {
	DrawGraph( x, y, id, TRUE );
}

void Viewer::drawRectGraph( const int x, const int y, const int src_x, const int src_y, const int width, const int height, const int id ) const {
	DrawRectGraph( x, y, src_x, src_y, width, height, id, TRUE, FALSE );
}

void Viewer::setNormalBlend( ) {
	int pal = 0;
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, pal );
}

void Viewer::setAlpha( int pal ) {
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, pal );
}

void Viewer::drawExtendGraph( const int x1, const int y1, const int x2, const int y2, const int id ) const {
	DrawExtendGraph( x1, y1, x2, y2, id, TRUE );
}

void Viewer::drawBillboard( const Vector& pos, int id, double size ) const {
	VECTOR vp = VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z );
	DrawBillboard3D( vp, 1.0f, 1.0f, ( float )size, 0, id, TRUE );
}

void Viewer::drawPolygonFloor( const Vector& pos, int id ) const {
	VECTOR local_pos[ 4 ];
	local_pos[ 0 ] = VGet( 0, 0, 0 );
	local_pos[ 1 ] = VGet( TILE_SIZE, 0, 0 );
	local_pos[ 2 ] = VGet( 0, 0, TILE_SIZE );
	local_pos[ 3 ] = VGet( TILE_SIZE, 0, TILE_SIZE );

	VERTEX3D vertex[ 6 ];
	vertex[ 0 ].pos  = VGet( ( float )pos.x + local_pos[ 0 ].x, ( float )pos.y + local_pos[ 0 ].y, ( float )pos.z + local_pos[ 0 ].z );
    vertex[ 0 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex[ 0 ].dif  = GetColorU8( 255, 255 ,255, 255 ) ;
    vertex[ 0 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex[ 0 ].u    = 1.0f ;
    vertex[ 0 ].v    = 0.0f ;
    vertex[ 0 ].su   = 0.0f ;
    vertex[ 0 ].sv   = 0.0f ;
	
    vertex[ 1 ].pos  = VGet( ( float )pos.x + local_pos[ 2 ].x, ( float )pos.y + local_pos[ 2 ].y, ( float )pos.z + local_pos[ 2 ].z );
    vertex[ 1 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex[ 1 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex[ 1 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex[ 1 ].u    = 1.0f ;
    vertex[ 1 ].v    = 1.0f ;
    vertex[ 1 ].su   = 0.0f ;
    vertex[ 1 ].sv   = 0.0f ;
	
    vertex[ 2 ].pos  = VGet( ( float )pos.x + local_pos[ 1 ].x, ( float )pos.y + local_pos[ 1 ].y, ( float )pos.z + local_pos[ 1 ].z );
    vertex[ 2 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex[ 2 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex[ 2 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex[ 2 ].u    = 0.0f ;
    vertex[ 2 ].v    = 0.0f ;
    vertex[ 2 ].su   = 0.0f ;
    vertex[ 2 ].sv   = 0.0f ;
	
	
    vertex[ 3 ].pos  = VGet( ( float )pos.x + local_pos[ 3 ].x, ( float )pos.y + local_pos[ 3 ].y, ( float )pos.z + local_pos[ 3 ].z );
    vertex[ 3 ].norm = VGet(   0.0f,   0.0f, -1.0f ) ;
    vertex[ 3 ].dif  = GetColorU8(   255,255,255,255 ) ;
    vertex[ 3 ].spc  = GetColorU8(   0,  0,  0,  0 ) ;
    vertex[ 3 ].u    = 0.0f ;
    vertex[ 3 ].v    = 1.0f ;
    vertex[ 3 ].su   = 0.0f ;
    vertex[ 3 ].sv   = 0.0f ;
	
    vertex[ 4 ].pos  = VGet( ( float )pos.x + local_pos[ 1 ].x, ( float )pos.y + local_pos[ 1 ].y, ( float )pos.z + local_pos[ 1 ].z );
    vertex[ 4 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex[ 4 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex[ 4 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex[ 4 ].u    = 0.0f ;
    vertex[ 4 ].v    = 0.0f ;
    vertex[ 4 ].su   = 0.0f ;
    vertex[ 4 ].sv   = 0.0f ;

    vertex[ 5 ].pos  = VGet( ( float )pos.x + local_pos[ 2 ].x, ( float )pos.y + local_pos[ 2 ].y, ( float )pos.z + local_pos[ 2 ].z );
    vertex[ 5 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex[ 5 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex[ 5 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex[ 5 ].u    = 1.0f ;
    vertex[ 5 ].v    = 1.0f ;
    vertex[ 5 ].su   = 0.0f ;
    vertex[ 5 ].sv   = 0.0f ;
	
	DrawPolygon3D( vertex, 2, id, FALSE );
}

void Viewer::drawPolygonWall( const Vector& pos, int id, int id_2 ) const {
	VECTOR local_pos[ 8 ];
	local_pos[ 0 ] = VGet( 0, WALL_HEIGHT, 0 );
	local_pos[ 1 ] = VGet( TILE_SIZE, WALL_HEIGHT, 0 );
	local_pos[ 2 ] = VGet( 0, WALL_HEIGHT, TILE_SIZE );
	local_pos[ 3 ] = VGet( TILE_SIZE, WALL_HEIGHT, TILE_SIZE );
	local_pos[ 4 ] = VGet( 0, 0, 0 );
	local_pos[ 5 ] = VGet( TILE_SIZE, 0, 0 );
	local_pos[ 6 ] = VGet( 0, 0, TILE_SIZE );
	local_pos[ 7 ] = VGet( TILE_SIZE, 0, TILE_SIZE );
	
	// 天井
	VERTEX3D vertex_1[ 6 ];
	vertex_1[ 0 ].pos  = VGet( ( float )pos.x + local_pos[ 0 ].x, ( float )pos.y + local_pos[ 0 ].y, ( float )pos.z + local_pos[ 0 ].z );
    vertex_1[ 0 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_1[ 0 ].dif  = GetColorU8( 255, 255 ,255, 255 ) ;
    vertex_1[ 0 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_1[ 0 ].u    = 1.0f ;
    vertex_1[ 0 ].v    = 0.0f ;
    vertex_1[ 0 ].su   = 0.0f ;
    vertex_1[ 0 ].sv   = 0.0f ;
		  
    vertex_1[ 1 ].pos  = VGet( ( float )pos.x + local_pos[ 2 ].x, ( float )pos.y + local_pos[ 2 ].y, ( float )pos.z + local_pos[ 2 ].z );
    vertex_1[ 1 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_1[ 1 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_1[ 1 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_1[ 1 ].u    = 1.0f ;
    vertex_1[ 1 ].v    = 1.0f ;
    vertex_1[ 1 ].su   = 0.0f ;
    vertex_1[ 1 ].sv   = 0.0f ;
		  
    vertex_1[ 2 ].pos  = VGet( ( float )pos.x + local_pos[ 1 ].x, ( float )pos.y + local_pos[ 1 ].y, ( float )pos.z + local_pos[ 1 ].z );
    vertex_1[ 2 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_1[ 2 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_1[ 2 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_1[ 2 ].u    = 0.0f ;
    vertex_1[ 2 ].v    = 0.0f ;
    vertex_1[ 2 ].su   = 0.0f ;
    vertex_1[ 2 ].sv   = 0.0f ;
	
	
    vertex_1[ 3 ].pos  = VGet( ( float )pos.x + local_pos[ 3 ].x, ( float )pos.y + local_pos[ 3 ].y, ( float )pos.z + local_pos[ 3 ].z );
    vertex_1[ 3 ].norm = VGet(   0.0f,   0.0f, -1.0f ) ;
    vertex_1[ 3 ].dif  = GetColorU8(   255,255,255,255 ) ;
    vertex_1[ 3 ].spc  = GetColorU8(   0,  0,  0,  0 ) ;
    vertex_1[ 3 ].u    = 0.0f ;
    vertex_1[ 3 ].v    = 1.0f ;
    vertex_1[ 3 ].su   = 0.0f ;
    vertex_1[ 3 ].sv   = 0.0f ;
		  
    vertex_1[ 4 ].pos  = VGet( ( float )pos.x + local_pos[ 1 ].x, ( float )pos.y + local_pos[ 1 ].y, ( float )pos.z + local_pos[ 1 ].z );
    vertex_1[ 4 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_1[ 4 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_1[ 4 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_1[ 4 ].u    = 0.0f ;
    vertex_1[ 4 ].v    = 0.0f ;
    vertex_1[ 4 ].su   = 0.0f ;
    vertex_1[ 4 ].sv   = 0.0f ;
		  
    vertex_1[ 5 ].pos  = VGet( ( float )pos.x + local_pos[ 2 ].x, ( float )pos.y + local_pos[ 2 ].y, ( float )pos.z + local_pos[ 2 ].z );
    vertex_1[ 5 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_1[ 5 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_1[ 5 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_1[ 5 ].u    = 1.0f ;
    vertex_1[ 5 ].v    = 1.0f ;
    vertex_1[ 5 ].su   = 0.0f ;
    vertex_1[ 5 ].sv   = 0.0f ;


	/*
	local_pos[ 0 ] = VGet( 0, 10, 0 );
	local_pos[ 1 ] = VGet( 10, 10, 0 );
	local_pos[ 2 ] = VGet( 0, 10, 10 );
	local_pos[ 3 ] = VGet( 10, 10, 10 );
	local_pos[ 4 ] = VGet( 0, 0, 0 );
	local_pos[ 5 ] = VGet( 10, 0, 0 );
	local_pos[ 6 ] = VGet( 0, 0, 10 );
	local_pos[ 7 ] = VGet( 10, 0, 10 );
	*/
	// 壁：手前
	VERTEX3D vertex_2[ 6 ];
	vertex_2[ 0 ].pos  = VGet( ( float )pos.x + local_pos[ 2 ].x, ( float )pos.y + local_pos[ 2 ].y, ( float )pos.z + local_pos[ 2 ].z );
    vertex_2[ 0 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_2[ 0 ].dif  = GetColorU8( 255, 255 ,255, 255 ) ;
    vertex_2[ 0 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_2[ 0 ].u    = 1.0f ;
    vertex_2[ 0 ].v    = 0.0f ;
    vertex_2[ 0 ].su   = 0.0f ;
    vertex_2[ 0 ].sv   = 0.0f ;
		  
    vertex_2[ 1 ].pos  = VGet( ( float )pos.x + local_pos[ 6 ].x, ( float )pos.y + local_pos[ 6 ].y, ( float )pos.z + local_pos[ 6 ].z );
    vertex_2[ 1 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_2[ 1 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_2[ 1 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_2[ 1 ].u    = 1.0f ;
    vertex_2[ 1 ].v    = 1.0f ;
    vertex_2[ 1 ].su   = 0.0f ;
    vertex_2[ 1 ].sv   = 0.0f ;
		  
    vertex_2[ 2 ].pos  = VGet( ( float )pos.x + local_pos[ 3 ].x, ( float )pos.y + local_pos[ 3 ].y, ( float )pos.z + local_pos[ 3 ].z );
    vertex_2[ 2 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_2[ 2 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_2[ 2 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_2[ 2 ].u    = 0.0f ;
    vertex_2[ 2 ].v    = 0.0f ;
    vertex_2[ 2 ].su   = 0.0f ;
    vertex_2[ 2 ].sv   = 0.0f ;
	
    vertex_2[ 3 ].pos  = VGet( ( float )pos.x + local_pos[ 7 ].x, ( float )pos.y + local_pos[ 7 ].y, ( float )pos.z + local_pos[ 7 ].z );
    vertex_2[ 3 ].norm = VGet( 0.0f, 0.0f, -1.0f ) ;
    vertex_2[ 3 ].dif  = GetColorU8( 255,255,255,255 ) ;
    vertex_2[ 3 ].spc  = GetColorU8( 0,  0,  0,  0 ) ;
    vertex_2[ 3 ].u    = 0.0f ;
    vertex_2[ 3 ].v    = 1.0f ;
    vertex_2[ 3 ].su   = 0.0f ;
    vertex_2[ 3 ].sv   = 0.0f ;
		  
    vertex_2[ 4 ].pos  = VGet( ( float )pos.x + local_pos[ 3 ].x, ( float )pos.y + local_pos[ 3 ].y, ( float )pos.z + local_pos[ 3 ].z );
    vertex_2[ 4 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_2[ 4 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_2[ 4 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_2[ 4 ].u    = 0.0f ;
    vertex_2[ 4 ].v    = 0.0f ;
    vertex_2[ 4 ].su   = 0.0f ;
    vertex_2[ 4 ].sv   = 0.0f ;
		  
    vertex_2[ 5 ].pos  = VGet( ( float )pos.x + local_pos[ 6 ].x, ( float )pos.y + local_pos[ 6 ].y, ( float )pos.z + local_pos[ 6 ].z );
    vertex_2[ 5 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_2[ 5 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_2[ 5 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_2[ 5 ].u    = 1.0f ;
    vertex_2[ 5 ].v    = 1.0f ;
    vertex_2[ 5 ].su   = 0.0f ;
    vertex_2[ 5 ].sv   = 0.0f ;

	/*
	local_pos[ 0 ] = VGet( 0, 10, 0 );
	local_pos[ 1 ] = VGet( 10, 10, 0 );
	local_pos[ 2 ] = VGet( 0, 10, 10 );
	local_pos[ 3 ] = VGet( 10, 10, 10 );
	local_pos[ 4 ] = VGet( 0, 0, 0 );
	local_pos[ 5 ] = VGet( 10, 0, 0 );
	local_pos[ 6 ] = VGet( 0, 0, 10 );
	local_pos[ 7 ] = VGet( 10, 0, 10 );
	*/
	// 壁：右
	VERTEX3D vertex_3[ 6 ];
	vertex_3[ 0 ].pos  = VGet( ( float )pos.x + local_pos[ 0 ].x, ( float )pos.y + local_pos[ 0 ].y, ( float )pos.z + local_pos[ 0 ].z );
    vertex_3[ 0 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_3[ 0 ].dif  = GetColorU8( 255, 255 ,255, 255 ) ;
    vertex_3[ 0 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_3[ 0 ].u    = 1.0f ;
    vertex_3[ 0 ].v    = 0.0f ;
    vertex_3[ 0 ].su   = 0.0f ;
    vertex_3[ 0 ].sv   = 0.0f ;
		  
    vertex_3[ 1 ].pos  = VGet( ( float )pos.x + local_pos[ 4 ].x, ( float )pos.y + local_pos[ 4 ].y, ( float )pos.z + local_pos[ 4 ].z );
    vertex_3[ 1 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_3[ 1 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_3[ 1 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_3[ 1 ].u    = 1.0f ;
    vertex_3[ 1 ].v    = 1.0f ;
    vertex_3[ 1 ].su   = 0.0f ;
    vertex_3[ 1 ].sv   = 0.0f ;
		  
    vertex_3[ 2 ].pos  = VGet( ( float )pos.x + local_pos[ 2 ].x, ( float )pos.y + local_pos[ 2 ].y, ( float )pos.z + local_pos[ 2 ].z );
    vertex_3[ 2 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_3[ 2 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_3[ 2 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_3[ 2 ].u    = 0.0f ;
    vertex_3[ 2 ].v    = 0.0f ;
    vertex_3[ 2 ].su   = 0.0f ;
    vertex_3[ 2 ].sv   = 0.0f ;
	
    vertex_3[ 3 ].pos  = VGet( ( float )pos.x + local_pos[ 6 ].x, ( float )pos.y + local_pos[ 6 ].y, ( float )pos.z + local_pos[ 6 ].z );
    vertex_3[ 3 ].norm = VGet( 0.0f, 0.0f, -1.0f ) ;
    vertex_3[ 3 ].dif  = GetColorU8( 255,255,255,255 ) ;
    vertex_3[ 3 ].spc  = GetColorU8( 0,  0,  0,  0 ) ;
    vertex_3[ 3 ].u    = 0.0f ;
    vertex_3[ 3 ].v    = 1.0f ;
    vertex_3[ 3 ].su   = 0.0f ;
    vertex_3[ 3 ].sv   = 0.0f ;
		  
    vertex_3[ 4 ].pos  = VGet( ( float )pos.x + local_pos[ 2 ].x, ( float )pos.y + local_pos[ 2 ].y, ( float )pos.z + local_pos[ 2 ].z );
    vertex_3[ 4 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_3[ 4 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_3[ 4 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_3[ 4 ].u    = 0.0f ;
    vertex_3[ 4 ].v    = 0.0f ;
    vertex_3[ 4 ].su   = 0.0f ;
    vertex_3[ 4 ].sv   = 0.0f ;
		  
    vertex_3[ 5 ].pos  = VGet( ( float )pos.x + local_pos[ 4 ].x, ( float )pos.y + local_pos[ 4 ].y, ( float )pos.z + local_pos[ 4 ].z );
    vertex_3[ 5 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_3[ 5 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_3[ 5 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_3[ 5 ].u    = 1.0f ;
    vertex_3[ 5 ].v    = 1.0f ;
    vertex_3[ 5 ].su   = 0.0f ;
    vertex_3[ 5 ].sv   = 0.0f ;

	/*
	local_pos[ 0 ] = VGet( 0, 10, 0 );
	local_pos[ 1 ] = VGet( 10, 10, 0 );
	local_pos[ 2 ] = VGet( 0, 10, 10 );
	local_pos[ 3 ] = VGet( 10, 10, 10 );
	local_pos[ 4 ] = VGet( 0, 0, 0 );
	local_pos[ 5 ] = VGet( 10, 0, 0 );
	local_pos[ 6 ] = VGet( 0, 0, 10 );
	local_pos[ 7 ] = VGet( 10, 0, 10 );
	*/
	// 壁：左
	VERTEX3D vertex_4[ 6 ];
	vertex_4[ 0 ].pos  = VGet( ( float )pos.x + local_pos[ 3 ].x, ( float )pos.y + local_pos[ 3 ].y, ( float )pos.z + local_pos[ 3 ].z );
    vertex_4[ 0 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_4[ 0 ].dif  = GetColorU8( 255, 255 ,255, 255 ) ;
    vertex_4[ 0 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_4[ 0 ].u    = 1.0f ;
    vertex_4[ 0 ].v    = 0.0f ;
    vertex_4[ 0 ].su   = 0.0f ;
    vertex_4[ 0 ].sv   = 0.0f ;
		  
    vertex_4[ 1 ].pos  = VGet( ( float )pos.x + local_pos[ 7 ].x, ( float )pos.y + local_pos[ 7 ].y, ( float )pos.z + local_pos[ 7 ].z );
    vertex_4[ 1 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_4[ 1 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_4[ 1 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_4[ 1 ].u    = 1.0f ;
    vertex_4[ 1 ].v    = 1.0f ;
    vertex_4[ 1 ].su   = 0.0f ;
    vertex_4[ 1 ].sv   = 0.0f ;
		  
    vertex_4[ 2 ].pos  = VGet( ( float )pos.x + local_pos[ 1 ].x, ( float )pos.y + local_pos[ 1 ].y, ( float )pos.z + local_pos[ 1 ].z );
    vertex_4[ 2 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_4[ 2 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_4[ 2 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_4[ 2 ].u    = 0.0f ;
    vertex_4[ 2 ].v    = 0.0f ;
    vertex_4[ 2 ].su   = 0.0f ;
    vertex_4[ 2 ].sv   = 0.0f ;
	
    vertex_4[ 3 ].pos  = VGet( ( float )pos.x + local_pos[ 5 ].x, ( float )pos.y + local_pos[ 5 ].y, ( float )pos.z + local_pos[ 5 ].z );
    vertex_4[ 3 ].norm = VGet( 0.0f, 0.0f, -1.0f ) ;
    vertex_4[ 3 ].dif  = GetColorU8( 255,255,255,255 ) ;
    vertex_4[ 3 ].spc  = GetColorU8( 0,  0,  0,  0 ) ;
    vertex_4[ 3 ].u    = 0.0f ;
    vertex_4[ 3 ].v    = 1.0f ;
    vertex_4[ 3 ].su   = 0.0f ;
    vertex_4[ 3 ].sv   = 0.0f ;
		  
    vertex_4[ 4 ].pos  = VGet( ( float )pos.x + local_pos[ 1 ].x, ( float )pos.y + local_pos[ 1 ].y, ( float )pos.z + local_pos[ 1 ].z );
    vertex_4[ 4 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_4[ 4 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_4[ 4 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_4[ 4 ].u    = 0.0f ;
    vertex_4[ 4 ].v    = 0.0f ;
    vertex_4[ 4 ].su   = 0.0f ;
    vertex_4[ 4 ].sv   = 0.0f ;
		  
    vertex_4[ 5 ].pos  = VGet( ( float )pos.x + local_pos[ 7 ].x, ( float )pos.y + local_pos[ 7 ].y, ( float )pos.z + local_pos[ 7 ].z );
    vertex_4[ 5 ].norm = VGet( 0.0f, 0.0f, 0.0f ) ;
    vertex_4[ 5 ].dif  = GetColorU8( 255, 255, 255, 255 ) ;
    vertex_4[ 5 ].spc  = GetColorU8( 0, 0, 0, 0 ) ;
    vertex_4[ 5 ].u    = 1.0f ;
    vertex_4[ 5 ].v    = 1.0f ;
    vertex_4[ 5 ].su   = 0.0f ;
    vertex_4[ 5 ].sv   = 0.0f ;

	
	// 天井
	DrawPolygon3D( vertex_1, 2, id, FALSE );
	// 壁：手前
	DrawPolygon3D( vertex_2, 2, id_2, FALSE );
	// 壁：右
	DrawPolygon3D( vertex_3, 2, id_2, FALSE );
	// 壁：左
	DrawPolygon3D( vertex_4, 2, id_2, FALSE );
}

void Viewer::drawBox( const int width, const int height, Vector2& pos, int r, int g, int b, bool fill ) const {
	if ( fill == true ) {
		DrawBox( ( int )pos.x, ( int )pos.y,
				 ( int )pos.x + width, ( int )pos.y + height,
				 GetColor( r, g, b ), TRUE );
	} else {
		DrawBox( ( int )pos.x, ( int )pos.y,
				 ( int )pos.x + width, ( int )pos.y + height,
				 GetColor( r, g, b ), FALSE );
	}
}

