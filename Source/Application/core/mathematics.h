#pragma once

#include <math.h>

const double PI  = 3.1415926535897932384626433832795;
const double PI2 = PI * 2;

const unsigned int RATIO = 1 << 16;
const unsigned int MARGIN = 1 << 15;

inline double round( const double in_value ) {
	int in = ( int )( in_value * RATIO );
	return ( double )in / RATIO;
}

struct Vector {
	double x;
	double y;
	double z;

	Vector( )
		: x( 0 )
		, y( 0 )
		, z( 0 ) {
	}

	Vector( const double inX, const double inY, const double inZ = 0 )
		: x( round ( inX ) )
		, y( round ( inY ) )
		, z( round ( inZ ) ) {
	}

	virtual ~Vector( ) {

	}

	inline Vector add(const Vector& inVector) const {
		return Vector(
			x + inVector.x,	
			y + inVector.y,
			z + inVector.z);
	}
	inline Vector operator+(const Vector& inVector) const {
		return add(inVector);
	}
	inline Vector operator+=(const Vector& inVector) {
		*this = *this + inVector;
		return *this;
	}

	inline Vector sub(const Vector& inVector) const {
		return Vector(
			x - inVector.x,	
			y - inVector.y,
			z - inVector.z);
	}
	inline Vector operator-(const Vector& inVector) const {
		return sub(inVector);
	}
	inline Vector operator-=(const Vector& inVector) {
		*this = *this - inVector;
		return *this;
	}
		// Š|‚¯Z
	inline Vector multiply( const double inValue ) const {
		return Vector(
			x * inValue,	
			y * inValue,
			z * inValue);
	}
	inline Vector operator*( const double inValue ) const {
		return multiply( inValue );
	}

	inline bool operator==( const Vector& inVector ) {
		if ( x == inVector.x && y == inVector.y && z == inVector.z ) {
			return true;
		}
		return false;
	}
	inline bool operator!=( const Vector& inVector ) {
		if ( x != inVector.x || y != inVector.y || z != inVector.z ) {
			return true;
		}
		return false;
	}
	// ‹——£
	inline double getLength( ) const {
		double s[ 3 ] = {abs( x ), abs( y ), abs( z ) };
		double n = s[ 0 ];
		for ( int i = 1; i < 3; i++ ) {
			if ( n < s[ i ] ) n = s[ i ];
		}
		if ( n == 0.0 ) {
			return 0;
		}
		double x = this-> x / n;
		double y = this-> y / n;
		double z = this-> z / n;
		return sqrt( x * x + y * y + z * z ) * n;
	}

	// ³‹K‰»	
	inline Vector normalize( ) const {
		double norm = getLength( );
		if ( norm == 0 ) {
			norm = 1; // ‘å‚«‚³‚ª‚È‚¢‚Ì‚ÅA‚P‚Å‘Î‰
		}
		return Vector(
			x / norm,
			y / norm,
			z / norm );
	}
};

struct Vector2 {
	double x;
	double y;

	Vector2( )
		: x( 0 )
		, y( 0 ) {
	}

	Vector2( const double inX, const double inY )
		: x( round ( inX ) )
		, y( round ( inY ) ) {
	}

	virtual ~Vector2( ) {

	}

	inline Vector2 add(const Vector2& inVector2) const {
		return Vector2(
			x + inVector2.x,	
			y + inVector2.y );
	}
	inline Vector2 operator+(const Vector2& inVector2) const {
		return add(inVector2);
	}
	inline Vector2 operator+=(const Vector2& inVector2) {
		*this = *this + inVector2;
		return *this;
	}

	inline Vector2 sub(const Vector2& inVector2) const {
		return Vector2(
			x - inVector2.x,	
			y - inVector2.y );
	}
	inline Vector2 operator-(const Vector2& inVector2) const {
		return sub(inVector2);
	}
	inline Vector2 operator-=(const Vector2& inVector2) {
		*this = *this - inVector2;
		return *this;
	}
	inline bool operator==(const Vector2& inVector2) {
		if( x == inVector2.x && y == inVector2.y ) {
			return true;
		}
		return false;
	}
	inline bool operator!=( const Vector2& inVector ) {
		if ( x != inVector.x || y != inVector.y ) {
			return true;
		}
		return false;
	}
};

struct Matrix {
	double data[ 4 ] [ 4 ];

	Matrix( ) {
		// Matrix‚ªì‚ç‚ê‚½‚çA’PˆÊs—ñ‚ğì¬‚·‚é
		for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ ) {
			data[ i ][ j ] = 0;
		}
		for ( int i = 0; i < 4; i++ ) {
			data[ i ][ i ] = 1;
		}
	}

	virtual ~Matrix( ) {
	}

	inline static Matrix makeTransformRotation( const Vector& inAxis, const int inDegree ) {
		// “x”–@‚©‚çŒÊ“x–@‚É•ÏŠ·
		double radian = inDegree * PI / 180.0;

		// ”CˆÓ²‰ñ“]‚Ì•ÏŠ·s—ñ‚ğì‚é
		Matrix mat;
		Vector v = inAxis.normalize( );
		double c = ( 1 - cos( radian ) );

		mat.data[ 0 ] [ 0 ] = v.x * v.x * c + cos( radian );
		mat.data[ 0 ] [ 1 ] = v.x * v.y * c - v.z * sin( radian );
		mat.data[ 0 ] [ 2 ] = v.z * v.x * c + v.y * sin( radian );

		mat.data[ 1 ] [ 0 ] = v.x * v.y * c + v.z * sin( radian );
		mat.data[ 1 ] [ 1 ] = v.y * v.y * c + cos( radian );
		mat.data[ 1 ] [ 2 ] = v.y * v.z * c - v.x * sin( radian );

		mat.data[ 2 ] [ 0 ] = v.z * v.x * c - v.y * sin( radian );
		mat.data[ 2 ] [ 1 ] = v.y * v.z * c + v.x * sin( radian );
		mat.data[ 2 ] [ 2 ] = v.z * v.z * c + cos( radian );

		return mat;
	}

	inline Vector multiply( const Vector& inVector ) const {
		return Vector(
			data[ 0 ] [ 0 ] * inVector.x + data[ 1 ] [ 0 ] * inVector.y + data[ 2 ] [ 0 ] * inVector.z + data[ 3 ] [ 0 ] * 1,
			data[ 0 ] [ 1 ] * inVector.x + data[ 1 ] [ 1 ] * inVector.y + data[ 2 ] [ 1 ] * inVector.z + data[ 3 ] [ 1 ] * 1,
			data[ 0 ] [ 2 ] * inVector.x + data[ 1 ] [ 2 ] * inVector.y + data[ 2 ] [ 2 ] * inVector.z + data[ 3 ] [ 2 ] * 1 );
	}
};