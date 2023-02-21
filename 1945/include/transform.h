#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<iostream>

#include "Vector2D.h"

using namespace std;


class Transform
{
    public:
        float X, Y;

    public:
        Transform(float x=0, float y=0)
        :X(x) , Y(y)
        {

        }

        void Log(string msg = ""){
            cout << msg << "(X Y) = (" << X << " " << Y << ")" << endl;
        }


    private:                                                        //(dich. chuyen object)
        inline void TranslateX(float x){X += x;}                    //phep' dich. chuyen truc. x
        inline void TranslateY(float y){Y += y;}                    //phep' dich. chuyen truc. y
        inline void TranslateVec(Vector2D v){X += v.X; Y += v.Y;}     //vecto dich chuyen 2D
};

#endif // TRANSFORM_H
