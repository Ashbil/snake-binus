#include <conio.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 

#define MAX_LENGTH 100

int i, j, k;
char tempat[20][20];
int gameover, score; 
int x, y, xMakanan, yMakanan, flag; 
char penguasa = '^';
int ekorX[MAX_LENGTH], ekorY[MAX_LENGTH];
int ekorLength = 0;

// munculin makanan
void makanan() 
{ 
	x = 20 / 2; 
	y = 20 / 2; 
label1: 
	xMakanan = rand() % 20; 
	if (xMakanan == 0) 
		goto label1; 
label2: 
	yMakanan = rand() % 20; 
	if (yMakanan == 0) 
		goto label2; 
	score = 0; 
} 

//ngebikin tempat
void map() 
{ 
	system("color B");
	system("cls"); 

	for (i = 0; i < 20; i++) { 
		for (j = 0; j < 20; j++) { 
			if (i == 0 || i == 20 - 1 
				|| j == 0 
				|| j == 20 - 1) { 
				printf("#"); 
			}
			else 
			{
			//bikin pengikut
				int isEkor = 0;
				for (k = 0; k < ekorLength; k++) 
				{
					if (ekorX[k] == i && ekorY[k] == j) 
					{
						printf("o"); 
						isEkor = 1;
						break;
					}
				}
				if (!isEkor) {
					if (i == x && j == y) 
						printf("%c",penguasa);
					else if (i == xMakanan && j == yMakanan) 
						printf("0"); 
					else
						printf(" "); 
				}
			}
		}
		printf("\n"); 
	} 

	//score
	printf("score = %d", score); 
	printf("\n");
	printf("press X to quit the game"); 
} 

//gerakan
void input() 
{ 
	if (kbhit()) { 
		switch (getch()) { 
		case 'a': 
			penguasa = '<';
			flag = 1; 
			break; 
		case 's':
			penguasa = 'v';
			flag = 2; 
			break; 
		case 'd':
			penguasa = '>'; 
			flag = 3; 
			break; 
		case 'w':
			penguasa = '^';
			flag = 4; 
			break; 
		case 'x': 
			gameover = 1; 
			break; 
		} 
	} 
} 

void logic() 
{
	// Pergerakan ekor
	int prevX = ekorX[0];
	int prevY = ekorY[0];
	int prev2X, prev2Y;
	ekorX[0] = x;
	ekorY[0] = y;
	for (i = 1; i < ekorLength; i++) {
		prev2X = ekorX[i];
		prev2Y = ekorY[i];
		ekorX[i] = prevX;
		ekorY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	//pergerakan kepala
	switch (flag) { 
	case 1: 
		y--; //kekiri
		break; 
	case 2: 
		x++; //kebawah
		break; 
	case 3: 
		y++; //kekanan
		break; 
	case 4: 
		x--; //keatas
		break; 
	default: 
		break; 
	} 
	
	// nabrak wall mati
	if (x < 0 || x > 20 || y < 0 || y > 20) {
		gameover = 1;
	}

	// munculin makanan selanjutnya
	if (x == xMakanan && y == yMakanan) { 
	label3: 
		xMakanan = rand() % 20; 
		if (xMakanan == 0) 
			goto label3; 

	label4: 
		yMakanan = rand() % 20; 
		if (yMakanan == 0) 
			goto label4; 
		score += 10; 
		// nambahin ekor pas makan
		ekorLength++;
	}
}


void main() 
{ 
	makanan(); 
	while (!gameover) 
	{
		map(); 
		input(); 
		logic(); 
		sleep(0.01); 
	}
}
