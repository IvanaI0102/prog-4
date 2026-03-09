#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdio>
using namespace std;

struct Point3D {
    double x, y, z;
};

struct TransformMatrix {
    double values[3][3] = {0};
    
    Point3D apply(Point3D p) {
        return {
            values[0][0]*p.x + values[0][1]*p.y + values[0][2]*p.z,
            values[1][0]*p.x + values[1][1]*p.y + values[1][2]*p.z,
            values[2][0]*p.x + values[2][1]*p.y + values[2][2]*p.z
        };
    }
};

TransformMatrix multiplyMatrices(TransformMatrix A, TransformMatrix B) {
    TransformMatrix Result;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                Result.values[i][j] += A.values[i][k] * B.values[k][j];
    return Result;
}

int main() {
    ifstream srcFile("monkey.obj");
    ofstream dstFile("new_monkey.obj");
    string currentLine;

    if (!srcFile.is_open()) return 1;

    const double PI_VAL = 3.141592653589793;
    double thetaX = 45.0 * PI_VAL / 180.0;
    double thetaY = 27.0 * PI_VAL / 180.0;
    double thetaZ = 10.0 * PI_VAL / 180.0;

    TransformMatrix Pitch = {{{1, 0, 0}, {0, cos(thetaX), -sin(thetaX)}, {0, sin(thetaX), cos(thetaX)}}};  
    TransformMatrix Yaw = {{{cos(thetaY), 0, sin(thetaY)}, {0, 1, 0}, {-sin(thetaY), 0, cos(thetaY)}}};
    TransformMatrix Roll = {{{cos(thetaZ), -sin(thetaZ), 0}, {sin(thetaZ), cos(thetaZ), 0}, {0, 0, 1}}};
    
    TransformMatrix Resize = {{{1.5, 0, 0}, {0, -1.0, 0}, {0, 0, 1.0}}};

    TransformMatrix FinalTransform = multiplyMatrices(Resize, multiplyMatrices(Roll, multiplyMatrices(Yaw, Pitch)));

    while (getline(srcFile, currentLine)) {
      
        if (currentLine.size() > 2 && currentLine[0] == 'v' && currentLine[1] == ' ') {
            Point3D vertex;
            
            if (sscanf(currentLine.c_str(), "v %lf %lf %lf", &vertex.x, &vertex.y, &vertex.z) == 3) {
                
                Point3D processedVertex = FinalTransform.apply(vertex);

                dstFile << "v " << fixed << setprecision(4)
                            << processedVertex.x << " " << processedVertex.y << " " << processedVertex.z << "\n";
            }
        } else {
            dstFile << currentLine << "\n";
        }
    }

    srcFile.close();
    dstFile.close();
    return 0;
}