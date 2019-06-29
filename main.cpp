#define OLC_PGE_APPLICATION

#include <iostream>
#include "olcPixelGameEngine.h"
#include <complex>

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
const int SCREEN_RATIO = 1;

const float xMin = -2;
const float xMax = 2;

const float yMin = -2;
const float yMax = 2;

class Application : public olc::PixelGameEngine {
private:
	const int MAX_ITERATION_AMNT = 50;
	const double VALUE_OF_INFINITY = 2.0;
public:
	Application() {
		sAppName = "Fractals";
	}

	bool OnUserCreate() override{
			
		Calculate();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override{

		return true;
	}

private:

	void DrawPixel(int x, int y, float val) {
		olc::Pixel p;
		p.r = Map(val, 0, MAX_ITERATION_AMNT, 0, 255);
		p.g = 0;
		p.b = 0;;
		p.a = 255;

		Draw(x, y, p);
	}

	void Calculate() {
		for (int x = 0; x < ScreenWidth(); ++x) {
			for (int y = 0; y < ScreenHeight(); ++y) {
				std::complex<double> c(Map(x, 0, ScreenWidth(), xMin, xMax), Map(y, 0, ScreenHeight(), yMin, yMax));
				std::complex<double> z(0.0, 0.0);

				int iteration = 0;

				while (iteration < MAX_ITERATION_AMNT)
				{
					z = z * z + c;
					if (std::abs(z) > VALUE_OF_INFINITY) {
						break;
					}
					++iteration;
				}

				DrawPixel(x, y, iteration);
			}
		}
	}

	//MAP VALUES
	double Map(double valToMap, double valMin, double valMax, double mapMin, double mapMax) {
		double ratio = (mapMax - mapMin) / (valMax - valMin);
		return((valToMap - valMin) * ratio + mapMin);
	}
};


int main(int argc, char* argv[]) {

	Application myApplication;
	if (myApplication.Construct(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_RATIO, SCREEN_RATIO)) {
		myApplication.Start();
	}


	return 0;
}
