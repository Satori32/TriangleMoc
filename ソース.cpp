#include <iostream>
#include <cstdint>
#include <algorithm>
#include <array>
#include <cmath>
#include <random>
#include <thread>

#include "EscapeSequence.h"

struct Point2D;
typedef std::array<Point2D, 3> Triangle;

using namespace ESS;

struct Point2D {
	//double X = 0;
	//double Y = 0;
	std::uintmax_t X = 0;
	std::uintmax_t Y = 0;

};

bool WriteLine(double X1, double X2,double Y, char Color) {
	if (X1 > X2) { std::swap(X1, X2); }

	for (std::intmax_t i = 0; i < X2-X1; i++) {
		Locate(X1+i,Y); std::cout << Color;
	}
	return true;
}


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
	for (std::intmax_t j=0; j <= Z; j++) {
		WriteLine(Center-Center+j*Z, Center + (C * i+j), i+j, 'A');

	}

	return true;
}

bool WriteTriangle(Point2D A, Point2D B, Point2D C, char Color) {
	return WriteTriangle({A,B,C},Color);
}
int main() {
	SetDisplayMode();
	//HideCursor();
	ClearShow();
	Triangle T{Point2D{ 16,1 },{ 1,12 },{ 32,16 }};
	
	Point2D A{ 16,1 };
	Point2D B{ 1,16 };
	Point2D C{ 32,16 };

	WriteTriangle(T, 'A');

	std::mt19937 mt(1);
	std::uniform_int_distribution<uintmax_t> ui(21, 21);
	Triangle T2{ Point2D{ui(mt),ui(mt)} , Point2D{ ui(mt),ui(mt) }, Point2D{ ui(mt),ui(mt) } };

	for (int i = 0; i < 16; i++) {


		ClearShow();
		std::this_thread::sleep_for(std::chrono::seconds(2));
		WriteTriangle(T2, 'X');

	}
	return 0;


}