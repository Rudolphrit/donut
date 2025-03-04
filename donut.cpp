#include <set>
#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <map>
#include <unistd.h>
#include <thread>
#include <chrono>

#include <unordered_map>
#include <stack>
#include <string>
#include <stdio.h>
using namespace std;
float R1 = 1;
float R2 = 2;
float K1 = 13;
float K2 = 5;
float pi = 3.14159;
int screenwidth = 40;
int screenheight = 40;
string brightness = ".,-~:;=!*#$@";
int main()
{
    float A = 0;
    float B = 0;
    while (true)
    {

        vector<vector<char> >  output(40, vector<char>(40, ' '));
        vector<vector<float> > zbuffer(40, vector<float>(40, 0));

        for (float theta = 0; theta < 2 * pi; theta += 0.07)
        {
            float cosTheta = cos(theta);
            float sinTheta = sin(theta);
            for (float phi = 0; phi < 2 * pi; phi += 0.04)
            {
                float sinPhi = sin(phi);
                float cosPhi = cos(phi);
                float x = R2 + R1 * cosTheta;
                float y = R1 * sinTheta;
                float rotationx = x * (cos(B) * cosPhi + sin(A) * sin(B) * sinPhi) - y * cos(A) * sin(B);
                float rotationy = x * (sin(B) * cosPhi - sin(A) * cos(B) * sinPhi) + y * cos(A) * cos(B);
                float rotationz = K2 + x * cos(A) * sinPhi + y * sin(A);
                float zinverse = 1 / rotationz;
                int projx = (screenwidth / 2 + K1 * rotationx * zinverse);
                int projy = (screenheight / 2 - K1 * rotationy * zinverse);
                float luminance = cosPhi * cosTheta * sin(B) - cos(A) * cosTheta * sinPhi - sin(A) * sinTheta + cos(B) * (sinTheta * cos(A) - sinPhi * cosTheta * sin(A));

                if (luminance > 0)
                {
                    if (zinverse > zbuffer[projx][projy])
                    {
                        zbuffer[projx][projy] = zinverse;
                        int lIndex = luminance * 8;
                        output[projx][projy] = brightness[lIndex];
                    }
                }
            }
        }

        for (int i = 0; i < screenwidth; i++)
        {
            for (int j = 0; j < screenheight; j++)
            {
                cout << (output[i][j]) << " ";
            }
            cout << endl;
        }
        A += 0.04;
        B += 0.02;
        this_thread::sleep_for(
            chrono::milliseconds(15));
        system("clear");
    }
}
