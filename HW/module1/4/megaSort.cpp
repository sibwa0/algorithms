#include <iostream>
#include <vector>

struct Point {
	int X = 0;
	int Y = 0;

	Point() = default;
	Point( int x, int y ) : X( x ), Y( y ) {}
};

// 1
bool operator < ( const Point& l, const Point& r )
{
	return l.X == r.X ? l.Y < r.Y : l.X < r.X;
}

// 2
bool isLessByX( const Point& l, const Point& r ) {
	return l.X < r.X;
}

bool isLessByY( const Point& l, const Point& r ) {
	return l.Y < r.Y;
}

// 3
template<class T>
bool IsLessDefault( const T& l, const T& r ) {
	return l < r;
}

// 4
class IsLessByPoint {
public:
	IsLessByPoint( const Point& _reper ) : reper( _reper ) {}

	bool operator()(const Point& l, const Point& r)
	{
		return abs( l.X - reper.X ) < abs( r.X - reper.X );
	}

private:
	Point reper;
};

// 5
template<class T>
class IsLess {
public:
	bool operator()( const T& l, const T& r ) { return l < r; }
};


template<class T, class Compare = IsLess<T> >
void MegaSort( T* arr, int l, int r, Compare cmp = IsLess<T>() )// bool (*isLess)( const T&, const T& ) = IsLessDefault )
{
	for( int i = l; i < r; ++i ) {
		for( int j = l; j < r; ++j ) {
			if( cmp( arr[j + 1], arr[j] ) ) {
				std::swap( arr[j], arr[j + 1] );
			}
		}
	}
}

int main()
{
	std::vector<char> charArr = { 2, 1, 4, 0, 5 };
	std::vector<int> intArr = { 2, 1, 4, 0, 5 };
	MegaSort( &intArr[0], 0, 4 );
	std::cout << "IntArr: \n";
	for( int i = 0; i < intArr.size(); ++i ) {
		std::cout << intArr[i] << ", ";
	}
	std::cout << std::endl;

	std::vector<Point> pointArr = { { 2, 1 }, { 4, 0 }, { 5, 0 }, { -5, 3 }, { 2, 2 } };
	MegaSort( &pointArr[0], 0, 4 );
	std::cout << "PointArr: \n";
	for( int i = 0; i < pointArr.size(); ++i ) {
		std::cout << "( " << pointArr[i].X << ", " << pointArr[i].Y << "), ";
	}
	std::cout << std::endl;

	MegaSort( &pointArr[0], 0, 4, isLessByY );
	std::cout << "PointArr by isLessByY: \n";
	for( int i = 0; i < pointArr.size(); ++i ) {
		std::cout << "( " << pointArr[i].X << ", " << pointArr[i].Y << "), ";
	}
	std::cout << std::endl;

	IsLessByPoint isLessBy( { 3, 3 } );
	MegaSort( &pointArr[0], 0, 4, isLessBy );
	std::cout << "PointArr by isLessBy: \n";
	for( int i = 0; i < pointArr.size(); ++i ) {
		std::cout << "( " << pointArr[i].X << ", " << pointArr[i].Y << "), ";
	}
	std::cout << std::endl;

	MegaSort( &pointArr[0], 0, 4, []( const Point& l, const Point& r ) { return l.Y < r.Y; } );
	std::cout << "PointArr by lambda: \n";
	for( int i = 0; i < pointArr.size(); ++i ) {
		std::cout << "( " << pointArr[i].X << ", " << pointArr[i].Y << "), ";
	}

	return 0;
}
/*
template<class T, class Compare>
class Heap {
public:
	Heap( Compare cmp );
	Heap( T* arr, int size, Compare cmp );

	T ExtractMin();
	const T& PeekMin() const;
	void ReplaceMin( const T& el );	
	void Insert( const T& el );	
	int Size() const;

private:
	T* buffer;
	int size;
	int bufferSize;
	Compare cmp;
};

1 4 5          4 5 6 53            3 35  53 55          6 6  54 343 345     6 6 54 325 
vector<vector>

struct Element {
	int Value;
	int ValueIndex;
	int ArrayIndex;
};

Heap<Element, ElementCmp> h;


2  4  6  4  1  8  3  4  6  1  9  5
struct User {
	int Id;
	int Count;
};

Heap<User, UserCmp> h;
   6
 8    6
9

struct Process {
	int P;
	int t;
	int T;
};

Heap<Process, ProcessCmp> h;
P * (t + 1)
*/