#include <iostream>
#include <cstdint>
#include <algorithm>
#include <array>
#include <cmath>
#include <random>
#include <thread>

#include "EscapeSequence.h"
#include <conio.h>

//i cant write only triangle... fuck.


struct Point2D;
typedef std::array<Point2D, 3> Triangle;

using namespace ESS;

struct Point2D {
	//double X = 0;
	//double Y = 0;
	std::intmax_t X = 0;
	std::intmax_t Y = 0;

};

bool WriteLine(double X1, double X2,double Y, char Color) {
	if (X1 > X2) { std::swap(X1, X2); }

	double A = X2 - X1;

	for (std::intmax_t i = 0; i < A; i++) {
		Locate(X1+i,Y); std::cout << Color;
	}
	return true;
}
/**/
bool WriteTriangle(Triangle X, char Color) {
	//std::sort(X.begin(), X.end(), [](auto& A, auto& B) {return A.X > B.X; });
	//std::sort(X.begin(), X.end(), [](auto& A, auto& B) {return A.Y < B.Y; });

	Locate(X[0].X, X[0].Y); std::cout << Color;
	Locate(X[1].X, X[1].Y); std::cout << (char)(Color+1);
	Locate(X[2].X, X[2].Y); std::cout << (char)(Color+2);


	double Center = X[0].X;
	double DeltaAB = X[1].Y - X[0].Y;
	double DeltaAC = X[2].Y - X[0].Y;
	double L = (std::max)(DeltaAB, DeltaAC);
	double L2 = (std::min)(DeltaAB, DeltaAC);
	double XM = (std::min)(X[1].X, X[2].X);
	double B = L / DeltaAB;
	double C = L / DeltaAC;
	std::intmax_t i=0;
	double YM = L2;
	for (i = 1; i <= L2; i++) {
	///	WriteLine(Center - (B * i), Center + (C * i), i+X[0].Y, 'A');

	} 
	double Z = (DeltaAC - DeltaAB);

	for (double j = 0; j < Z; j += 1) {
		if (X[1].Y < X[2].Y) {
	///		WriteLine(X[1].X + (X[2].X - X[1].X) / Z * j, Center + (C * (i + j)), j + i + X[0].Y, 'B');
		}
		else {
	//		WriteLine(Center + (C * (j + i)), (X[2].X - X[1].X) / Z * j, j + i + X[0].Y, 'C');
		}
	}

	return true;
}
/**/
/** /
bool WriteTriangle(Triangle X, char Color) {
	std::sort(X.begin(), X.end(), [](auto& A, auto& B) {return A.X > B.X; });
	std::sort(X.begin(), X.end(), [](auto& A, auto& B) {return A.Y < B.Y; });

	Locate(X[0].X, X[0].Y); std::cout << Color;
	Locate(X[1].X, X[1].Y); std::cout << Color+(char)1;
	Locate(X[2].X, X[2].Y); std::cout << Color+(char)2;

	double DeltaA = X[1].Y - X[0].Y;
	double DeltaB = X[2].Y - X[1].Y;
	double DeltaC = X[2].Y - X[0].Y;
	double Center = X[0].X;
	double B = (X[1].X - X[0].X) / DeltaA;
	double C = (X[2].X - X[0].X) / DeltaC;
	std::intmax_t i = 1;
	for (i = 1; i <= DeltaA; i++) {
		WriteLine(Center + (B * i), Center + (C * i), i, 'A');

	} 
	double Z = (DeltaC - DeltaA);
	double BB = X[2].X - X[1].X;
	double BBB = BB / Z;
	for (std::intmax_t j=0; j <= Z; j++) {
		WriteLine(X[1].X+(BBB*j), Center + (C * i+j), i+j, 'B');

	}

	return true;
}
/**/

bool RotOne(char C) {
	std::intmax_t X = 16;
	std::intmax_t Y = 12;
	double R=8;

	double PI = 3.14926434;
	double Rad = PI / 180.0;

	double OX = 16;
	double OY = 16;

	int k = 0;

	for (std::size_t i = 0; i < 360.0*16; i++) {
		double PX = R * std::sin(Rad * i) + OX;
		double PY = R * std::cos(Rad * i) + OY;
		Locate(PX, PY);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		ClearShow();
		std::cout << PX<<':'<<PY;
		if (_kbhit()) {
			k=_getch();
		}
		if (k == 27) { break; }
	}		
	return true;
}

bool RotateTriangle(char C) {

	Triangle T = { Point2D{0,1},Point2D{1,-1},Point2D{ -1,-1 } };
	double X = 5;
	double OX = 40;
	double OY = 10;
	Triangle T2 = T;
	double PI = 3.14926434;
	double Rad = PI / 180.0;

	for (auto& o : T2) {
		o.X *= X;
		o.Y *= X;
	}

	for (std::intmax_t i = 0; i < 360; i++) {
		auto A = T2;
		for (auto& o : A) {
			o.X = std::sin(Rad * i)*o.X;
			o.Y = std::cos(Rad * i)*o.Y;
			o.X += OX;//originX
			o.Y += OY;//originY
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(128));
		ClearShow();
		WriteTriangle(A, C);

	}
	return 0;
}

bool WriteTriangle(Point2D A, Point2D B, Point2D C, char Color) {
	return WriteTriangle({A,B,C},Color);
}

bool Test1() {
	ClearShow();
	Triangle T{Point2D{ 16,1 },{ 1,12 },{ 32,16 }};
	
	Point2D A{ 16,1 };
	Point2D B{ 1,16 };
	Point2D C{ 32,16 };

	double Q = 0xdeadbeef;

	WriteTriangle(T, 'A');

	return true;
}

bool Test2() {
	/**/
	std::mt19937 mt(1); 
	std::uniform_int_distribution<std::uint32_t> ui(0, 21);

	for (int i = 0; i < 16; i++) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		ClearShow();
		Triangle T2{ Point2D{ui(mt),ui(mt)} , Point2D{ ui(mt),ui(mt) }, Point2D{ ui(mt),ui(mt) } };
		WriteTriangle(T2, 'Q');

	}
	/**/
	return true;
}

int main() {
	SetDisplayMode();
	//HideCursor();

	//RotateTriangle('X');

	//RotOne('X');
	return 0;


}