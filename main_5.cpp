#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <float.h>
#include <fstream>
#include "CImg.h"
#include "Fabrica.h"
using namespace std;

#define PI 3.1415926

int main() {
	Fabrica* SFabrika = new SphereFabrica();
	Fabrica* CFabrika = new CubeFabrica();
	vector<std::shared_ptr<Object>> objs;
	double fov;
	int x, y;
	ifstream in("conf.txt");
	in >> fov >> x >> y;
	if (x % 2 != 0) {
		x++;
	}
	if (y % 2 != 0) {
		y++;
	}
    cimg_library::CImg<unsigned char> image(x,y,1,3,0);
    cimg_library::CImgDisplay display(image, "raytracing");
	double scry = sqrt(static_cast<double>(x * x) / (2 * (1 - cos(fov / 180 * PI))) - static_cast<double>(x * x) / 4);
	while (!in.eof()) {
		std::string name;
		in >> name;
		if (name == "sphere") {
			double x0, y0, z0, r;
			in >> x0 >> y0 >> z0 >> r;
			Vector3 v0 = Vector3(x0,y0,z0);
			if (v0.length() > maxDist) {
			    maxDist = v0.length();
            }
			if (v0.length() < minDist) {
			    minDist = v0.length();
			}
			objs.push_back(SFabrika->create(v0, r));
		}
		else if (name == "cube") {
			double x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, a;
			in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3 >> x4 >> y4 >> z4 >> a;
			Vector3 v0;
			v0 = Vector3(x1, y1, z1) - Vector3(x2, y2, z2) * (a / 2) - Vector3(x3, y3, z3) * (a / 2) - Vector3(x4, y4, z4) * (a / 2);
            if (v0.length() > maxDist) {
                maxDist = v0.length();
            }
            if (v0.length() < minDist) {
                minDist = v0.length();
            }
			objs.push_back(CFabrika->create(Vector3(x1, y1, z1),a, Vector3(x2, y2, z2), Vector3(x3, y3, z3), Vector3(x4,y4,z4)));
		}
	}
	for (auto o : objs) {
        double shade;
        if (maxDist == minDist) {
            shade = 0;
        } else {
            shade = ((255.0 / (maxDist - minDist))) * o->getCenter().length() -
                             (255.0 * minDist) / (maxDist - minDist);
        }
        if (shade < 0) shade = 0;
		if (shade > 255) shade = 255;
        Color c(255 - shade, shade, 0);
        o->setColor(c);
	}
	std::cout << "Minimum distance: " << minDist << std::endl;
	std::cout << "Maximum distance: " << maxDist << std::endl;
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
#pragma omp parallel for
	for (int i = -y / 2; i < y / 2; i++) {
#pragma omp parallel for
		for (int j = -x / 2; j < x / 2; j++) {
			bool pixelSet = false;
			double cury = DBL_MAX;
			for (auto o : objs) {
				double yx;
				bool tch;
				int col = 0;
				if (o->intersect(j, scry, i, 0, 0, 0, yx, tch, col)) {
					if (yx < cury) {
						cury = yx;
						Color c = o->pixelColor(static_cast<double>(j) * yx / scry, yx, static_cast<double>(i) * yx / scry, col);
						unsigned char color[3] = { (unsigned char)c.red,(unsigned char)c.green,(unsigned char)c.blue };
						image.draw_point(x / 2 + j, y / 2 + i, color);
						pixelSet = true;
					}
				}
			}
			if (!pixelSet) {
                unsigned char color[3] = {(unsigned char)0,(unsigned char)0,(unsigned char)0};
                image.draw_point(x / 2 + j, y / 2 + i, color);
			}
		}
	}
	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	int elapsed_ms = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
	std::cout << "Render took: " << elapsed_ms << " ms\n";
    display.display(image);
    image.save("test.bmp");
	while (!display.is_closed())
        display.wait();
}
