#include "SeaBattle.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <conio.h>
#include <string>

#define PI 3.14159265

void SeaBattleGame::startgame() {
	cout << "Welcome to the SeaBattle!\nPlease, enter first player name: ";
	getline(cin,P1.name);
	cout << "Please, enter second player name: ";
	getline(cin,P2.name);
	P1.number = Players::PLAYER1;
	P2.number = Players::PLAYER2;
	this->setgame();
	cout << "TO BATTLE!";
	system("pause");
	this->battle();

}

void SeaBattleGame::setgame() {
	Setter setg;
	system("cls");
	cout << "Give a PC to player " << P1.name << " for ship arrangement\n\n";
	system("pause");
	system("cls");
	setg.setship(P1);
	system("cls");
	cout << "Give a PC to player " << P2.name << " for ship arrangement\n\n";
	system("pause");
	system("cls");
	setg.setship(P2);
	P1.Enemy = Board();
	P2.Enemy = Board();
}

void SeaBattleGame::battle() {
	ConsoleVisualiser cvis;
	Checker check;
	int move = 1;
	int shipnumb1 = 10;
	int shipnumb2 = 10;
	while (!check.checkonwin(shipnumb1,shipnumb2)) {
		Movemaker mm;
		mm.makemove(P1, P2, move,shipnumb1,shipnumb2);
	}
	if (shipnumb1 < 1) {
		cout << "Player " << P2.name << " won!\n";
	}
	else {
		cout << "Player " << P1.name << " won!\n";
	}
	system("pause");
	cout << P1.name << "'s board: \n";
	cvis.coutboard(P1.Own);
	cout << P2.name << "'s shots: \n";
	cvis.coutboard(P2.Enemy);
	system("pause");
	cout << P2.name << "'s board: \n";
	cvis.coutboard(P2.Own);
	cout << P1.name << "'s shots: \n";
	cvis.coutboard(P1.Enemy);
	system("pause");
	system("cls");
	startgame();

}



void Setter::setship(Player &PL) {
	Checker check;
	ConsoleVisualiser cvis;
	for (int j = 4; j > 0; j--) {
		for (int i = 0; i < 5 - j; i++) {
			Shipinsetship ship = Shipinsetship(j);
			bool setted = false;
			bool correctpos = true;
			while (!setted) {
				correctpos = true;
				Board copy = PL.Own;
				if (!check.shipsetcheck(ship, PL.Own)) correctpos = false;
				placenotsettedship(ship, copy, correctpos);
				system("cls");
				cvis.coutboard(copy);
				char key = 0;
				key = _getch();
				ShipMoves a = ShipMoves::UP;
				if ((int)key != 13) {
					if (key == -32)
					{
						key = _getch();
						if ((int)key == 75) a = ShipMoves::LEFT;
						else if ((int)key == 77) a = ShipMoves::RIGHT;
						else if ((int)key == 80) a = ShipMoves::DOWN;
						moveship(ship, a);
					}
					else if ((int)key == 113) { a = ShipMoves::ROTATECOUNTERCLOCKWISE; moveship(ship, a);
					}
					else if ((int)key == 101) { a = ShipMoves::ROTATECLOCKWISE; moveship(ship, a);
					}
					
				}
				else {
					if (correctpos) {
						setted = true;
						placesettedship(ship, PL.Own);
					}
				}

			}
		}
	}
	system("cls");
}

void Setter::placenotsettedship(Shipinsetship ship, Board& copy, bool correctpos) {
	int x = ship.headx;
	int y = ship.heady;
	int sinres = (int)sin(ship.angle * PI / 180);
	int cosres = (int)cos(ship.angle * PI / 180);
	Field a = Field::NOTCORRECTLYPLACEDSHIP;
	if (correctpos) a = Field::NOTPLACEDSHIP;
	for (int i = 0; i < ship.size; i++) {
		copy.board[x][y] = a;
		x += (-1) * sinres;
		y += 1 * cosres;
	}
}

void Setter::placesettedship(Shipinsetship ship, Board& d) {
	int x = ship.headx;
	int y = ship.heady;
	int sinres = (int)sin(ship.angle * PI / 180);
	int cosres = (int)cos(ship.angle * PI / 180);
	Field a = Field::SHIP;
	for (int i = 0; i < ship.size; i++) {
		d.board[x][y] = a;
		x += (-1) * sinres;
		y += 1 * cosres;
	}
}

void Setter::moveship(Shipinsetship &ship,ShipMoves a) {
	int sinres = (int)sin(ship.angle * PI / 180);
	int cosres = (int)cos(ship.angle * PI / 180);
	switch (a) {
	case UP: {
		bool u1 = ship.angle == 180;
		bool u2 = ship.heady > ship.size - 1;
		bool u3 = ship.heady > 0;
		if (u1) {
			if (u2) {
				ship.heady--;
			}
		}
		else if(u3){ ship.heady--; }
		break; }
	case DOWN: {
		bool u1 = ship.angle == 0;
		bool u2 = ship.heady < 10 - ship.size;
		bool u3 = ship.heady < 9;
		if (u1) {
			if (u2) {
				ship.heady++;
			}
		}
		else if (u3) { ship.heady++; }
		break;
	}
	case LEFT: {
		bool u1 = ship.angle == 90;
		bool u2 = ship.headx > ship.size - 1;
		bool u3 = ship.headx > 0;
		if (u1) {
			if (u2) {
				ship.headx--;
			}
		}
		else if (u3) { ship.headx--; }
		break;
	}
	case RIGHT: {
		bool u1 = ship.angle == 270;
		bool u2 = ship.headx < 10 - ship.size;
		bool u3 = ship.headx < 9;
		if (u1) {
			if (u2) {
				ship.headx++;
			}
		}
		else if (u3) { ship.headx++; }
		break;
	}
	case ROTATECLOCKWISE: {
		bool canli = true;
		int angletwo = ship.angle + 90;
		switch (angletwo) {
		case 90: {
			bool u1 = ship.headx >= ship.size - 1;
			if (!u1) {
				ship.headx = ship.size - 1;
			}
			break;
		}
		case 180: {
			bool u1 = ship.heady >= ship.size - 1;
			if (!u1) {
				ship.heady = ship.size - 1;
			}
			break;
		}
		case 270: {
			bool u1  = ship.headx < 10 - ship.size;
			if (!u1) {
				ship.headx = 10 - ship.size;
			}
			break;
		}
		case 360: {
			bool u1 = ship.heady < 10 - ship.size;
			if (!u1) {
				ship.heady = 10 - ship.size;
			}
			break;
		}
		}
		if (canli) {
			ship.angle+=90;
			if (ship.angle >= 360) ship.angle -= 360;
		}
		break;
	}
	case ROTATECOUNTERCLOCKWISE: {
		bool canli = true;
		int angletwo = ship.angle - 90;
		switch (angletwo) {
		case 90: {
			bool u1 = ship.headx >= ship.size - 1;
			if (!u1) {
				ship.headx = ship.size - 1;
			}
			break;
		}
		case 180: {
			bool u1 = ship.heady >= ship.size - 1;
			if (!u1) {
				ship.heady = ship.size - 1;
			}
			break;
		}
		case -90: {
			bool u1 = ship.headx < 10 - ship.size;
			if (!u1) {
				ship.headx = 10 - ship.size;
			}
			break;
		}
		case 0: {
			bool u1 = ship.heady < 10 - ship.size;
			if (!u1) {
				ship.heady = 10 - ship.size;
			}
			break;
		}
		}
		if (canli) {
			ship.angle -= 90;
			if (ship.angle < 0) ship.angle += 360;
		}
		break;
	}
	}
}



bool Checker::shipsetcheck(Shipinsetship ship, Board d) {
	int xcheck = ship.headx;
	int ycheck = ship.heady;
	int sinres = (int)sin(ship.angle * PI / 180);
	int cosres = (int)cos(ship.angle * PI / 180);
	for (int i = 0; i < ship.size; i++) {
		bool u1 = checkonnearbyshipfield(xcheck, ycheck, d);
		if (u1) return false;
		xcheck += (-1) * sinres;
		ycheck += 1 * cosres;
	}
	return true;
}

bool Checker::checkonnearbyshipfield(int x, int y, Board d) {
	for (int i = -1; i <= 1; i++) {
		if (x + i < 10 && x + i > -1) {
			for (int j = -1; j <= 1; j++) {
				if (y + j < 10 && y + j > -1) {
					if (d.board[x+i][y+j] == Field::SHIP) return true;
				}
			}
		}
	}
	return false;
}

bool Checker::checkmovepossibility(int x, int y, Board d) {
	if (x < 0 || x > 9) return false;
	else if (y < 0 || y > 9) return false;
	else if (d.board[x][y] == Field::FIRED) return false;
	else if (d.board[x][y] == Field::NOTCORRECTLYPLACEDSHIP) return false;

	return true;
}

bool Checker::checkonkill(Board B1, Board B2, int x, int y){
	for (int i = -1; i <= 1; i++) {
		if (x + i < 10 && x + i > -1) {
			for (int j = -1; j <= 1; j++) {
				if (y + j < 10 && y + j > -1) {
					bool u1 = B1.board[x + i][y + j] == Field::NOTCORRECTLYPLACEDSHIP;
					bool u2 = !(i == 0 && j == 0);
					bool y1 = B1.board[x + i][y + j] == Field::EMPTY;
					bool y2 = B2.board[x + i][y + j] == Field::SHIP;
					if (u1 && u2) {
						if (!checkonkillrecursive(B1, B2, x + i, y + j,x,y)) return false;
					}
					else if (y1 && y2)
					{
						return false;;
					}
				}
			}
		}
	}
	return true;
}

bool Checker::checkonkillrecursive(Board B1, Board B2, int x, int y, int xf, int yf) {
	for (int i = -1; i <= 1; i++) {
		if (x + i < 10 && x + i > -1) {
			for (int j = -1; j <= 1; j++) {
				if (y + j < 10 && y + j > -1) {
					bool u1 = B1.board[x + i][y + j] == Field::NOTCORRECTLYPLACEDSHIP;
					bool u2 = !(i == 0 && j == 0);
					bool u3 = (x + i != xf && y + j != yf);
					bool y1 = B1.board[x + i][y + j] == Field::EMPTY;
					bool y2 = B2.board[x + i][y + j] == Field::SHIP;
					if (u1 && u2 && u3) {
						if (!checkonkillrecursive(B1, B2, x + i, y + j,x,y)) return false;
					}
					else if (y1 && y2)
					{
						return false;;
					}
				}
			}
		}
	}
	return true;
}

bool Checker::checkonwin(int shipnumb1, int shipnumb2) {
	if (shipnumb1 < 1) {
		return true;
	}
	else if (shipnumb2 < 1) {
		return true;
	}
	return false;
}



void ConsoleVisualiser::coutboard(Board a) {
	cout << "   R E S P U B L I K A\n";
	char t = 218;
	char y = 196;
	char u = 194;
	char o = 191;

	cout << "  " << (char)218 << y << u << y << u << y << u << y << u << y << u << y << u << y << u << y << u << y << u << y << o << endl;
	for (int i = 0; i < 10; i++) {			// i - y analogy
		cout << i << " " << (char)179;
		for (int j = 0; j < 10; j++) {				// j - x analogy
			if (a.board[j][i] == Field::FIRED) cout << (char)253;
			else if (a.board[j][i] == Field::SHIP) cout << (char)219;
			else if (a.board[j][i] == Field::NOTPLACEDSHIP) cout << (char)254;
			else if (a.board[j][i] == Field::NOTCORRECTLYPLACEDSHIP) cout << (char)176;
			else cout << " ";
			cout << (char)179;
		}
		char k = 197;
		cout << endl;
		if (i < 9) {
			cout << "  " << (char)195 << y << k << y << k << y << k << y << k << y << k << y << k << y << k << y << k << y << k << y << (char)180;
		}
		else {
			k = 193;
			cout << "  " << (char)192 << y << k << y << k << y << k << y << k << y << k << y << k << y << k << y << k << y << k << y << (char)217;
		}
		cout << endl;
	}
}



void Movemaker::makemove(Player &P1, Player &P2, int &move, int& shipnumb1, int& shipnumb2) {
	if (move % 2 == 0) {
		cout << "Give PC to " << P2.name << " for shooting!";
		system("pause");
	}
	else {
		cout << "Give PC to " << P1.name << " for shooting!";
		system("pause");
	}
	if (move % 2 == 0) {
		while (move % 2 == 0 && shipnumb1 > 0) {
			ConsoleVisualiser cvis;
			Checker check;
			cvis.coutboard(P2.Enemy);
			cout << "Enter coordinates to shoot (R0,S5,r0,s5): ";
			bool acception = false;
			int x, y;
			while (!acception) {
				cin.ignore();
				string s;
				cin >> s;
				s = coordinateconverter(s);
				x = s[0] - '0';
				y = s[1] - '0';
				if (check.checkmovepossibility(x, y, P2.Enemy)) {
					acception = true;
				}
				else { cout << "Invalid coordinates, try again: "; }
			}
			if (doaction(P2.Enemy, P1.Own, x, y, shipnumb1)) {
				cvis.coutboard(P2.Enemy);
				system("pause");
				move++;
			}
			system("cls");
		}
	}
	else {
		while (move % 2 == 1 && shipnumb2 > 0) {
			ConsoleVisualiser cvis;
			Checker check;
			cvis.coutboard(P1.Enemy);
			cout << "Enter coordinates to shoot (R0,S5,r0,s5): ";
			bool acception = false;
			int x, y;
			while (!acception) {
				cin.ignore();
				string s;
				cin >> s;
				s = coordinateconverter(s);
				x = s[0] - '0';
				y = s[1] - '0';
				if (check.checkmovepossibility(x, y, P1.Enemy)) {
					acception = true;
				}
				else { cout << "Invalid coordinates, try again: "; }
			}
			if (doaction(P1.Enemy, P2.Own, x, y, shipnumb2)) {
				cvis.coutboard(P1.Enemy);
				system("pause");
				move++;
			}
			system("cls");
		}
	}
}

string Movemaker::coordinateconverter(string a) {
	string res;
	switch (a[0]) {
	case 'r': res += '0'; break;
	case 'R': res += '0'; break;
	case 'e': res += '1'; break;
	case 'E': res += '1'; break;
	case 's': res += '2'; break;
	case 'S': res += '2'; break;
	case 'p': res += '3'; break;
	case 'P': res += '3'; break;
	case 'u': res += '4'; break;
	case 'U': res += '4'; break;
	case 'b': res += '5'; break;
	case 'B': res += '5'; break;
	case 'l': res += '6'; break;
	case 'L': res += '6'; break;
	case 'i': res += '7'; break;
	case 'I': res += '7'; break;
	case 'k': res += '8'; break;
	case 'K': res += '8'; break;
	case 'a': res += '9'; break;
	case 'A': res += '9'; break;
	default: res += 'f'; break;
	}
	res += a[1];
	return res;
}

bool Movemaker::doaction(Board &B1, Board B2, int x, int y, int& shipnumb) {
	if (B2.board[x][y] == Field::EMPTY) {
		B1.board[x][y] = Field::FIRED;
		return true;
	}
	else {
		Checker check;
		B1.board[x][y] = Field::NOTCORRECTLYPLACEDSHIP;
		if(check.checkonkill(B1,B2,x,y)){
			B1.board[x][y] = Field::SHIP;
			shipnumb--;
			dokill(B1, B2, x, y);
		}
		return false;
	}
}

void Movemaker::dokill(Board &B1, Board B2, int x, int y) {
	for (int i = -1; i <= 1; i++) {
		if (x + i < 10 && x + i > -1) {
			for (int j = -1; j <= 1; j++) {
				if (y + j < 10 && y + j > -1) {
					if (B2.board[x + i][y + j] == Field::SHIP && B1.board[x + i][y + j] == Field::NOTCORRECTLYPLACEDSHIP){
						B1.board[x + i][y + j] = Field::SHIP;
						dokill(B1, B2, x + i, y + j);
					}
					else {
						if (i == 0 && j == 0) {
							B1.board[x + i][y + j] = Field::SHIP;
						}
						else if(B1.board[x + i][y + j] != Field::SHIP) B1.board[x + i][y + j] = Field::FIRED;
					}
				}
			}
		}
	}
}
