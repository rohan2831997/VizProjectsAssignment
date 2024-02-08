// VizProjectsAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

std::vector<float> x, y;
float x_p, y_p;

void readInputfromFile()
{
	std::ifstream infile("input.txt");
	std::string line;

	while (std::getline(infile, line)) {

		// Range of x from 0 to 800
		// Range of y from 0 to 400

		float x0 = 0;
		float y0 = 0;

		std::string num1 = line.substr(0, line.find(','));
		std::string num2 = line.substr(line.find(',') + 1, line.size());

		x0 = stoi(num1, 0, 10);
		y0 = stoi(num2, 0, 10);

		x.push_back(x0);
		y.push_back(y0);
	}
};

void calculateDistances(float& l0l1dist, float& l2l3dist, float &distl0, float &distl1, float &distl2, float &distl3 )
{
	float diffx0 = x[0] - x[1];
	float diffx1 = x[1] - x[2];

	float diffy0 = y[0] - y[1];
	float diffy1 = y[1] - y[2];

	float slope0 = diffy0 / diffx0;
	float slope1 = diffy1 / diffx1;

	// assume line equation to be of the form ax + by + c = 0
	float a0 = slope0;
	float b0 = -1.0f;
	float c0 = (-1.0f * a0 * x[0]) + (-1.0f * b0 * y[0]);

	l0l1dist = (a0 * x[2] + b0 * y[2] + c0) / sqrt(a0 * a0 + b0 * b0);
	distl0 = (a0 * x_p + b0 * y_p + c0) / sqrt(a0 * a0 + b0 * b0);

	//
	float a1 = slope1;
	float b1 = -1.0f;
	float c1 = (-1.0f * a1 * x[1]) + (-1.0f * b1 * y[1]);

	l2l3dist = (a1 * x[3] + b1 * y[3] + c1) / sqrt(a1 * a1 + b1 * b1);
	distl1 = (a1 * x_p + b1 * y_p + c1) / sqrt(a1 * a1 + b1 * b1);

	float a2 = slope0;
	float b2 = -1.0f;
	float c2 = (-1.0f * a2 * x[2]) + (-1.0f * b2 * y[2]);

	distl2 =	(a2* x_p +  b2 * y_p +  c2) / sqrt(a2 * a2 + b2 * b2);

	float a3 = slope1;
	float b3 = -1.0f;
	float c3 = (-1.0f * a3 * x[3]) + (-1.0f * b3 * y[3]);

	distl3 = (a3 * x_p + b3* y_p + c3) / sqrt(a3 * a3+ b3 * b3);

	l0l1dist = abs(l0l1dist);
	l2l3dist = abs(l2l3dist);

	distl0 = abs(distl0);
	distl1 = abs(distl1);
	distl2 = abs(distl2);
	distl3 = abs(distl3);

}

bool pointInOrOut()
{
	// 
	float diffx0 = x[0] - x[1];
	float diffx1 = x[1] - x[2];

	float diffy0 = y[0] - y[1];
	float diffy1 = y[1] - y[2];

	float distl0 = 0.0f, distl1 = 0.0f, distl2 = 0.0f, distl3 = 0.0f;

	float l0l1dist = 0.0f, l2l3dist = 0.0f;

	// means line is parallel to y axis
	if(abs(diffx0)<0.001f || abs(diffx1) < 0.001f)
	{ 
		// means line is parallel to x axis
		if (abs(diffy0) < 0.001f || abs(diffy1) < 0.001f)
		{
			distl0 = abs(x[0] - x_p);
			distl1 = abs(x[2] - x_p);

			distl2 = abs(y[0] - y_p);
			distl3 = abs(y[2] - y_p);

			l0l1dist = abs(x[2] - x[0]);
			l2l3dist = abs(y[2] - y[0]);

				return	distl0 < l0l1dist&&
						distl1 < l0l1dist&&
						distl2 < l2l3dist&&
						distl3 < l2l3dist;
		}
	}

	calculateDistances(l0l1dist, l2l3dist, distl0, distl1, distl2, distl3);
	
	return	distl0 < l0l1dist&&
		distl2 < l0l1dist&&
		distl1 < l2l3dist&&
		distl3 < l2l3dist;

}



int main()
{
	readInputfromFile();
	x_p = 0.0f;
	y_p = 0.0f;
    std::cout << pointInOrOut();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
