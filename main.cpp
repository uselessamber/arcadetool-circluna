#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
const float dx[] = {0.0, 0.5, 0.0, -0.5};
const float dy[] = {1.0, 0.0, -1.0, 0.0};
const string dr[] = {"sosi", "siso"};
//input
int timing_start, timing_end, count;
float center_start_x, center_start_y, center_end_x, center_end_y, radius_start, radius_end;
int color;
bool isvoid;
float x_multiplier, y_multiplier;
//output
ofstream fo("output.txt");
float cx, cy;
string s;

int m_add(int a, int b, int m){
    return (a % m + b % m) % m;
}

int m_sub(int a, int b, int m){
    return ((a % m + m) - b % m) % m;
}

void get_current_position(float &ox, float &oy, float t, int p){
    // t = [0, 1] float
    // p = [0, 3] int
    float cx = center_start_x + t * (center_end_x - center_start_x);
    float cy = center_start_y + t * (center_end_y - center_start_y);
    float cr = radius_start + t * (radius_end - radius_start);
    ox = cx + (dx[p] * x_multiplier) * cr;
    oy = cy + (dy[p] * y_multiplier) * cr;
}

int main(){
    cout << "-- Circluna by UselessAmber --\n";
    cout << "This program will allow you to interpolate circular arc around a linearly moving point.\nIts current limitation is that it only allows for 4 possible starting arc (up, right, down, left).\n";
    cout << "The program will output the set of command needed to perform the task in an output file named \"output.txt\".\nThese command are meant to work with ArcadeZero v4.\n";
    try{
        cout << "Input start timing (must be an integer): ";
        cin >> timing_start;
        cout << "Input end timing (must be an integer): ";
        cin >> timing_end;
        cout << "Input the number of full rotation (must be an integer > 0): ";
        cin >> count;
        if (count <= 0){
            cout << "Value out of bound\n";
            throw;
        }

        cout << "Input the start center location:\n";
        cout << "x = ";
        cin >> center_start_x;
        cout << "y = ";
        cin >> center_start_y;

        cout << "Input the end center location:\n";
        cout << "x = ";
        cin >> center_end_x;
        cout << "y = ";
        cin >> center_end_y;

        cout << "Input the starting radius: ";
        cin >> radius_start;
        cout << "Input the end radius: ";
        cin >> radius_end;

        cout << "Input radius multiplier for the x-axis (if the shape you are drawing is a circle and not an eclipse put 1.0): ";
        cin >> x_multiplier;

        cout << "Input radius multiplier for the y-axis (if the shape you are drawing is a circle and not an eclipse put 1.0): ";
        cin >> y_multiplier;

        int phase, rotation;
        cout << "Input the starting phase (0: Up, 1: Right, 2: Down, 3: Left): ";
        cin >> phase;
        cout << "Input rotation direction (0 for clockwise, 1 for counter-clockwise): ";
        cin >> rotation;

        cout << "Input arc color (0 for blue, 1 for red): ";
        cin >> color;
        cout << "Is the arc void? (0 for no, 1 for yes): ";
        cin >> isvoid;
        if (rotation != 0 && rotation != 1){
            cout << "Value out of bound\n";
            throw;
        }
        float ox1, oy1, ox2, oy2;
        for (int i = 0; i < 4 * count; i++){
            float t1 = (float)i / (float)(count * 4);
            float t2 = (float)(i + 1) / (float)(count * 4);
            int timing_1 = (float)timing_start + (float)t1 * (float)(timing_end - timing_start);
            int timing_2 = (float)timing_start + (float)t2 * (float)(timing_end - timing_start);
            get_current_position(ox1, oy1, t1, phase);
            if (rotation == 0)
                phase = m_add(phase, 1, 4);
            else
                phase = m_sub(phase, 1, 4);
            get_current_position(ox2, oy2, t2, phase);
            fo << setprecision(2) << fixed << "arc(" << timing_1 << "," << timing_2 << "," << ox1 << "," << ox2 << "," << dr[phase&1] << "," << oy1 << "," << oy2 << "," << color << ",none," << ((isvoid)? "true" : "false") << ");\n";
            cout << setprecision(2) << fixed << "arc(" << timing_1 << "," << timing_2 << "," << ox1 << "," << ox2 << "," << dr[phase&1] << "," << oy1 << "," << oy2 << "," << color << ",none," << ((isvoid)? "true" : "false") << ");\n";
        }
        cout << "Finish output.";
    }catch (...){
        cin >> s;
        return -1;
    }
}