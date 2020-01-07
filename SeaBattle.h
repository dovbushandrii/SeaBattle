#pragma once
#include <vector>
#include <string>

using namespace std;

enum Field {
	EMPTY,
	FIRED,
	SHIP,
	NOTPLACEDSHIP,
	NOTCORRECTLYPLACEDSHIP
};
enum ShipMoves {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	ROTATECLOCKWISE,
	ROTATECOUNTERCLOCKWISE
};
enum Players {
	PLAYER1,
	PLAYER2
};
struct Shipinsetship {
	int headx;       // head of the ship x-coordinate 
	int heady;		 // head of the ship y-coordinate 
	int size;		 // size of the ship
	int angle;		 // ship placement angle (could be 0, 90, 180, 270)(clockwise)
	Shipinsetship(int siz) {
		headx = 0;
		heady = 0;
		size = siz;
		angle = 0;
	}
};


class Board {
public:
	Board() {
		vector<Field> a;
		for (int i = 0; i < 10; i++) {
			a.push_back(Field::EMPTY);
		}
		for (int i = 0; i < 10; i++) {
			board.push_back(a);
		}
	}
	vector<vector<Field>> board;
};	
// Board - DONE

class ConsoleVisualiser {
public:
	void coutboard(Board a);
};
// ConsoleVisualiser - DONE

class Checker {
public:
	bool shipsetcheck(Shipinsetship ship, Board d);
	bool checkonnearbyshipfield(int x, int y, Board d);
	bool checkonwin(int shipnumb1, int shipnumb2);
	bool checkmovepossibility(int x, int y, Board d);
	bool checkonkill(Board B1, Board B2, int x, int y);
	bool checkonkillrecursive(Board B1, Board B2, int x, int y, int xf,int yf);
};

struct Player {
	Players number;
	string name;
	Board Own;
	Board Enemy;
};

class SeaBattleGame {
public:
	void startgame();
private:
	void setgame();
	void battle();
	Player P1;
	Player P2;
};

class Movemaker {
public:
	void makemove(Player &P1, Player &P2, int &move , int &shipnumb1, int &shipnumb2);
private:
	string coordinateconverter(string a);
	bool doaction(Board &B1, Board B2, int x, int y, int &shipnumb);
	void dokill(Board &B1, Board B2, int x, int y);
};

class Setter {
public:
	void setship(Player &PL);
private:
	void placenotsettedship(Shipinsetship ship, Board& copy, bool correctpos);
	void placesettedship(Shipinsetship ship, Board& d);
	void moveship(Shipinsetship& ship, ShipMoves a);
};
// Setter - DONE


