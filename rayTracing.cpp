/*
 * rayTracing.cpp
 *
 *  Created on: Feb 1, 2015
 *      Author: jie
 */
#include <iostream>
#include <list>
#include <cmath>

using namespace std;

struct vec2f {
	float _x, _y;
	vec2f(float x, float y) : _x(x), _y(y){};
	vec2f() : _x(0), _y(0) {};
	vec2f operator = (vec2f& target) { vec2f origin(target._x, target._y); return origin; };
	vec2f operator - (vec2f& target) { vec2f origin(this->_x - target._x, this->_y - target._y); return origin; };
	vec2f operator * (float factor) { _x *= factor; _y *= factor; return *this;};
	vec2f operator / (float factor) { _x /= factor; _y /= factor; return *this;};
	float length() { return sqrtf( _x*_x + _y*_y ); };
};

struct vec2s {
	short _x, _y;
	vec2s(short x, short y) : _x(x), _y(y){};
};

struct vec3f {
	float _x, _y, _z;
	vec3f(float x, float y, float z) : _x(x), _y(y), _z(z){};
	vec3f() : _x(0), _y(0), _z(0) {};
	vec3f operator = (vec3f& target) { vec3f origin(target._x, target._y, target._z); return origin; };
	vec3f operator - (vec3f& target) { vec3f origin(this->_x - target._x, this->_y - target._y, this->_z - target._z); return origin; };
	vec3f operator * (float factor) { _x *= factor; _y *= factor; _z *= factor; return *this;};
	vec3f operator / (float factor) { _x /= factor; _y /= factor; _z /= factor; return *this;};
	float length() { return sqrtf( _x*_x + _y*_y + _z*_z); };
};

struct vec3s {
	short _x, _y, _z;
	vec3s(short x, short y, short z) : _x(x), _y(y), _z(z){};
};


typedef	list<vec2s> vec2slist;
typedef	list<vec3s> vec3slist;

void rayTracing_2D( vec2f start, vec2f end, vec2slist &list)
{
	float tMaxX, tMaxY, tDeltaX, tDeltaY;
	vec2f v = end - start;
	float maxT = v.length();
	int X = floor(start._x);
	int Y = floor(start._y);
	int stepX = v._x / abs(v._x);
	int stepY = v._y / abs(v._y);
	tDeltaX = v.length() / abs(v._x);
	tDeltaY = v.length() / abs(v._y);
	tMaxX = tDeltaX * (X + 0.5 - start._x);
	tMaxY = tDeltaY * (Y + 0.5 - start._y);

	list.push_back(vec2s(X,Y));

	cout << "matT: " << maxT << endl;
	while ( tMaxX <= maxT || tMaxY <= maxT )
	{
		cout << "iter: tMaxX: " << tMaxX << " and tMaxY: " << tMaxY << endl;
		if (tMaxX < tMaxY)
		{
			tMaxX = tMaxX + tDeltaX;
			X = X + stepX;
		} else {
			tMaxY = tMaxY + tDeltaY;
			Y = Y + stepY;
		}
		list.push_back(vec2s(X, Y));
	}

}

void rayTracing_3D( vec3f start, vec3f end, vec3slist &list)
{
	float tMaxX, tMaxY, tMaxZ, tDeltaX, tDeltaY, tDeltaZ;
	vec3f v = end - start;
	float maxT = v.length();
	int X = floor(start._x);
	int Y = floor(start._y);
	int Z = floor(start._z);

	int stepX = v._x / abs(v._x);
	int stepY = v._y / abs(v._y);
	int stepZ = v._z / abs(v._z);

	tDeltaX = v.length() / abs(v._x);
	tDeltaY = v.length() / abs(v._y);
	tDeltaZ = v.length() / abs(v._z);

	tMaxX = tDeltaX * (X + 0.5 - start._x);
	tMaxY = tDeltaY * (Y + 0.5 - start._y);
	tMaxZ = tDeltaZ * (Z + 0.5 - start._z);

	list.push_back(vec3s(X,Y,Z));

	cout << "matT: " << maxT << endl;
	while ( tMaxX <= maxT || tMaxY <= maxT || tMaxZ <= maxT)
	{
		cout << "iter: tMaxX: " << tMaxX << " and tMaxY: " << tMaxY << endl;

		if (tMaxX < tMaxZ)
		{
			if (tMaxX < tMaxY)
			{
				tMaxX = tMaxX + tDeltaX;
				X = X + stepX;
			} else {
				tMaxY = tMaxY + tDeltaY;
				Y = Y + stepY;
			}
		} else {
			if (tMaxZ < tMaxY)
			{
				tMaxZ = tMaxZ + tDeltaZ;
				Z = Z + stepZ;
			} else {
				tMaxY = tMaxY + tDeltaY;
				Y = Y + stepY;
			}
		}

		list.push_back(vec3s(X, Y, Z));
	}

}


int main(int argc, char* argv[])
{
	vec2f pt1(0.0, 0.0);
	vec2f pt2(0.3, 0.35);
	vec2slist list;
	rayTracing_2D(pt1, pt2, list);

	vec2slist::iterator iter;
	cout << "starting at: " << pt1._x << " , " << pt1._y;
	cout << " goes to: " << pt2._x << " , " << pt2._y << endl;

	for (iter = list.begin(); iter != list.end(); iter++)
	{
		cout << (*iter)._x << " , " << (*iter)._y << endl;
	}

	vec3f pt3_1(0.0, 0.0, 0.0);
	vec3f pt3_2(-3.0, 1.5, 1.0);
	vec3slist list3;
	rayTracing_3D(pt3_1, pt3_2, list3);

	vec3slist::iterator iter3;
	cout << "starting at: " << pt3_1._x << " , " << pt3_1._y << " , " << pt3_1._z;
	cout << " goes to: " << pt3_2._x << " , " << pt3_2._y << " , " << pt3_2._z << endl;

	for (iter3 = list3.begin(); iter3 != list3.end(); iter3++)
	{
		cout << (*iter3)._x << " , " << (*iter3)._y << " , " << (*iter3)._z << endl;
	}

	return 0;
}


