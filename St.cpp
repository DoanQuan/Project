#include <iostream>
#include<ctime>
#include<windows.h>
#include<vector>
#include<conio.h>
using namespace std;
void gotoxy(int column, int line) {
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}
typedef struct {
	int x;
	int y;
	char status;
}man;
typedef struct {
	int x;
	int y;
	char status;
}bucket;
man boy; 
const int buckhigh = 3;
const int bucklength = 5;
int score;
const int starty = 4;
const int highesty = 24;
const int highestx = 70;
const int lowesty = 3;
const int lowestx = 21;
const int borderhigh = 19;
const int borderlength = 50;
const int highbuck = ((highesty - lowesty) + 1) / buckhigh;
const int lengthbuck = ((highestx - lowestx) + 1) / bucklength;
int amountofbucks = highbuck*lengthbuck;
bucket buck[highbuck][lengthbuck];
void background();
void border();
void figure(man);
void bucks(bucket);
void prscore(int );
void render();
void move(man &boy, bucket[][lengthbuck], int highbuck);
int checkboy(man boy, bucket buck[][lengthbuck], int);
void checkbucks(bucket [][lengthbuck],int ,int &);
void setbuck(bucket[][lengthbuck], int);
int newbucket();
int main()
{
	score = 0;
	int i ,temp ,t=0;
	srand(time(0));
	boy.x = lowestx + 2;
	boy.y = highesty-buckhigh+1;
	boy.status = 'c';
	setbuck(buck, highbuck);
	do {
		render();
		Sleep(10);
		i = checkboy(boy, buck, buckhigh);
		if (t % 50 == 0) {
			temp = newbucket();
			buck[0][temp].status = 'M';
		}
		checkbucks(buck, highbuck, score);
		move(boy, buck, highbuck);
		t++;
		if (t == 55) t = 1;
	} while (i != 0);
	
}
void background() {
	int i, j;
	system("color 1");
	for (i = lowestx - 1; i <= highestx + 1; i++) {
		for (j = (lowesty - 1); j <= (highesty + 1); j++) {
			gotoxy(i, j);
			cout << " ";
		}
	}
}
void figure(man boy) {
	if (boy.status == 'A' || boy.status == 'a') {
		gotoxy(boy.x, boy.y); cout << "o";
		gotoxy(boy.x, boy.y + 1); cout << "|";
		gotoxy(boy.x - 1, boy.y + 1); cout << "/";
		gotoxy(boy.x - 1, boy.y + 2); cout << "/";
		gotoxy(boy.x + 1, boy.y + 2); cout << "\\";
	}
	else if (boy.status == 'd' || boy.status == 'D') {
		gotoxy(boy.x, boy.y); cout << "o";
		gotoxy(boy.x, boy.y + 1); cout << "|";
		gotoxy(boy.x + 1, boy.y + 1); cout << "\\";
		gotoxy(boy.x - 1, boy.y + 2); cout << "/";
		gotoxy(boy.x + 1, boy.y + 2); cout << "\\";
	}
	else {
		gotoxy(boy.x, boy.y); cout << "o";
		gotoxy(boy.x, boy.y + 1); cout << "|";
		gotoxy(boy.x - 1, boy.y + 1); cout << "/";
		gotoxy(boy.x + 1, boy.y + 1); cout << "\\";
		gotoxy(boy.x - 1, boy.y + 2); cout << "/";
		gotoxy(boy.x + 1, boy.y + 2); cout << "\\";
	}
}
void setbuck(bucket buck[][lengthbuck], int highbuck) {
	int i, j;
	for (i = 0; i < highbuck; i++) {
		for (j = 0; j < lengthbuck; j++) {
			buck[i][j].x = (lowestx + bucklength / 2) + bucklength * j;
			buck[i][j].y = starty+buckhigh*i;
			buck[i][j].status = 'E';
		}
	}
}
void bucks(bucket buck) {
	if (buck.status != 'E') {
		gotoxy(buck.x - 1, buck.y); cout << "___";
		gotoxy(buck.x - 2, buck.y + 1); cout << "|   |";
		gotoxy(buck.x - 2, buck.y + 2); cout << "|___|";
	}
}
void prscore(int score) {
	gotoxy(lowestx, highesty + buckhigh);
	cout << "Score: " << score;
}
void render() {
	int i,j;
	system("cls");
	prscore(score);
	border();
	figure(boy);
	for (i = 0; i < highbuck; i++) {
		for (j = 0; j < lengthbuck; j++) {
			bucks(buck[i][j]);
		}
	}
}
static int timee;
void move(man &boy,bucket buck[][lengthbuck],int highbuck) {
	int i, j, coorx, coory, temp;
	coory = (boy.y - starty) / buckhigh;
	coorx = (boy.x - (lowestx + bucklength / 2)) / bucklength;
	if (timee % 4 == 0) {
		for (i = highbuck - 1; i >= 0; i = i - 1) {
			temp = 0;
			for (j = 0; j < lengthbuck; j++) {
				if (buck[i][j].status == 'M') {
					buck[i + 1][j].status = 'M';
					buck[i][j].status = 'E';
				}
			}
		}
	}
	timee++;
	if (timee == 5) timee = 1;
	if (boy.status != 'w' && (buck[coory + 1][coorx].status == 'E')) {
		if (coory < highbuck - 1) {
			boy.y = boy.y + buckhigh;
			boy.status = 'c';
		}
	}
	else if (GetAsyncKeyState(VK_LEFT)) {
		boy.status = 'a';
		if (buck[coory][coorx - 1].status == 'E') {
			if((boy.x - bucklength)>=(lowestx+bucklength/2)) boy.x = boy.x - bucklength;
		}
		else if (buck[coory][coorx - 1].status != 'E') {
			if (buck[coory][coorx - 2].status == 'E') {
				if ((buck[coory][coorx-1].x - bucklength) >= (lowestx + bucklength / 2)) {
					boy.x = boy.x - bucklength;
					buck[coory][coorx - 2].status = 'M';
					buck[coory][coorx - 1].status = 'E';
				}
			}
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		boy.status = 'd';
		if (buck[coory][coorx + 1].status == 'E') {
			if ((boy.x + bucklength) <= (highestx + bucklength / 2)) boy.x = boy.x + bucklength;
		}
		else if (buck[coory][coorx + 1].status != 'E') {
				if (buck[coory][coorx + 2].status == 'E') {
					if ((buck[coory][coorx + 1].x + bucklength) <= (highestx - bucklength / 2)){
						boy.x = boy.x + bucklength;
						buck[coory][coorx + 2].status = 'M';
						buck[coory][coorx + 1].status = 'E';
				}
			}
		}
	}
	else if (GetAsyncKeyState(VK_UP)) {
		if (boy.status != 'w') {
			boy.status = 'w';
			if ((boy.y - buckhigh)>lowesty) {
				boy.y = boy.y - buckhigh;
			}
		}
	}
	else {
		if (buck[coory + 1][coorx].status == 'E') {
			if (coory < highbuck - 1) {
				boy.y = boy.y + buckhigh;
				boy.status = 'c';
			}
		}
		
	}
}
int checkboy(man boy,bucket buck[][lengthbuck],int buckhigh) {
	int i, j;
	i = (boy.y - starty) / buckhigh;
	j = (boy.x - (lowestx + bucklength / 2)) / bucklength;

	if(buck[i-1][j].status!='E') return 0;
	return 1;
}
void checkbucks(bucket buck[][lengthbuck],int highbuck,int &score) {
	int i, j, temp;
	for (i = highbuck-1; i >=0; i=i-1) {
		for (j = 0; j < lengthbuck; j++) {
			if (buck[i][j].status == 'M') {
				if (i == (highbuck - 1)) buck[i][j].status = 'S';
			}
			if (buck[i][j].status == 'S') {
				if (buck[i - 1][j].status != 'E') buck[i-1][j].status = 'S';
			}
		}
	}
	i = highbuck - 1;
	for (j = 0; j < lengthbuck; j++) if (buck[i][j].status != 'S') break;
	if (j == lengthbuck) {
		score = score + 1;
		for (temp = 0; temp < lengthbuck; temp++) buck[i][temp].status = 'E';
	}
	for (j = 0; j < lengthbuck; j++) {
		if (buck[i][j].status == 'E') {
			for (temp = highbuck - 2; temp >= 0; temp = temp - 1) {
				if (buck[temp][j].status != 'E') buck[temp][j].status = 'M';
			}
		}
	}
}
void border() {
	int i, j;
	for (i = lowestx-1; i <= highestx+1; i++) {
		for (j = (lowesty - 1); j <= (highesty+1); j++) {
			if (i == (lowestx-1) || i == (highestx+1)) {
				gotoxy(i, j);
				cout << "\xB2";
			}
			else {
				if (j == (lowesty - 1) || j == (highesty + 1)) {
					gotoxy(i, j);
					cout << "\xB2";
				}
			}
		}
	}
}
int newbucket() {
	int i;
	i = rand() % 10 + 1;
	return i;
}
