#pragma once
#include <memory>
#include "Sphere.h"
#include "Cube.h"

class Fabrica {
public:
	virtual std::shared_ptr<Object> create(Vector3 v0 = { 0,0,0 }, double a = 0, Vector3 v1 = { 0,0,0 }, Vector3 v2 = { 0,0,0 }, Vector3 v3 = {0,0,0}) = 0;
};

class SphereFabrica : public Fabrica {
public:
	std::shared_ptr<Object> create(Vector3 v0 = { 0,0,0 }, double a = 0, Vector3 v1 = { 0,0,0 }, Vector3 v2 = { 0,0,0 }, Vector3 v3 = { 0,0,0 }) override {
		return std::make_shared<Sphere>(v0, a);
	}
};

class CubeFabrica : public Fabrica {
public:
	std::shared_ptr<Object> create(Vector3 v0 = { 0,0,0 }, double a = 0, Vector3 v1 = { 0,0,0 }, Vector3 v2 = { 0,0,0 }, Vector3 v3 = { 0,0,0 }) override {
		return std::make_shared<Cube>(v0 - v1 * (a/2) - v2 * (a/2) - v3 * (a/2),v0,v1,v2,v3,a);
	}
};