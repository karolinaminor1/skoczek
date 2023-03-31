
#include <stdio.h>
#include <iostream>


#define CHESSBOARD_SIZE 6
#define HORSE_MOVES 8

typedef struct {
	int x;
	int y;
}Point;


typedef enum { FIRST,SECOND,THIRD,FOURTH, FIFTH, SIXTH, SEVENTH, EIGHT } ruchy;


void FreeChessboard( int*** pTab );
int** createChessboard( int nDim );
void PrintChessboard( int** pTab, int nDim );
int move( int** pChessBoard, int nDim, int Move, int x, int y, int* px, int* py, Point* pHorseMoves );
int root( int** pChessBoard, int nDim, int Move, int x, int y, Point* pHorseMoves );



int main(int argc, char* argv[]) {

	if (argc != 3) {
		printf("Usage %s <x_coord> <y_coord>\n", argv[0]);
		return -1;
	}

	int nDim = CHESSBOARD_SIZE;

	if( (( atoi( argv[1] ) < 0 )  ||  ( atoi( argv[1]) >= nDim )) ){
		printf( "X coordinate does not match the CHESSBOARD_SIZE\n" );
		return -2;
	}

	if( (( atoi( argv[2] ) < 0 )  ||  ( atoi( argv[2]) >= nDim )) ){
		printf( "Y coordinate does not match the CHESSBBOARD_SIZE\n" );
		return -2;
	}
	int** pChessBoard = createChessboard( nDim );

	if( pChessBoard  ==  NULL ){
		printf( "ERROR: createChessboard\n" );
		return -3;
	}

	

	printf( "Pusta szachownica:\n" );
	PrintChessboard( pChessBoard, nDim );

	Point HorseMove[ HORSE_MOVES ] = { {-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1} };
	Point* pHorseMoves = HorseMove;

	int x = atoi( argv[1] );
	int y = atoi( argv[2] );

	

	if( root( pChessBoard, nDim, 1, x, y, pHorseMoves ) == 0 ){
		printf("** Nie ma mozliwosci odwiedzic jednokrotnie ka¿dego pola!!\n\n");
	}
	else {
		printf("Szachownica z numerami kolejnych krokow skoczka: \n");
		PrintChessboard( pChessBoard, nDim );
	}

	FreeChessboard( &pChessBoard );

//	if( pChessBoard != NULL ) {
	//	printf("ERROR: FreeChessboard\n");
		//return -4;
	//}

	return 0;
}



int move( int** pChessBoard, int nDim, int Move, int x, int y, int* px, int* py, Point* pHorseMoves ){
	
	*px = x + pHorseMoves[Move].x;
	*py = y + pHorseMoves[Move].y;

	if( *py < 0 || *py >= nDim || *px < 0 || *px >= nDim ) return 0;         //skok poza szachownice
	if( pChessBoard[*px][*py] > 0 ) return 0;								   //skoczek juz tam byl

	return 1;
}
 



int root( int** pChessBoard, int nDim, int Move, int x, int y, Point* pHorseMoves ){

	
	pChessBoard[ x ][ y ] = Move;

	if( Move  ==  nDim * nDim ) return 1;

		int px = x;
		int py = y;

		for( int i = FIRST; i <= EIGHT; i++ ){

			if( move(pChessBoard, nDim, i, x, y, &px, &py, pHorseMoves ) == 1 ){
				if( root(pChessBoard, nDim, Move+1, px, py,  pHorseMoves) == 1 )    return 1;
			}
		}
	

	pChessBoard[ x ][ y]  = 0;
	
	return 0;
}



int** createChessboard( int nDim ){
	

	int** pTab = ( int** )calloc( nDim, sizeof(int*) );
	if (!pTab) return NULL;

	*pTab = ( int* )calloc( nDim*nDim, sizeof(int) );
	if( !*pTab )return NULL;


	int** v = pTab+1;
	int* p = *pTab+nDim;
	for (int i = 1; i < nDim; i++){
		*v++ = p;
		p += nDim;
	}
	return pTab;
}



void PrintChessboard( int** pTab, int nDim ){
	for( int i = 0; i < nDim; i++ ){
		int* v = *pTab++;

		for ( int j = 0; j < nDim; j++ ){
			printf( "%d ", *v++ );
		}
		printf("\n");
	}
}



void FreeChessboard( int*** pTab ){			
	free( **pTab );
	free( *pTab );
	*pTab = NULL;
}
	

