#include<iostream>
#include<math.h>
//gang shiz
using namespace std;

float MyLat, Mylon;

float Torad(float deg);
float Todeg(float deg);
float Ndist(float a, float b);
float FindDist(float a, float b, struct Positions p);

struct Positions
{
    float TargetLat;
    float TargetLon;
    float HostAngle;
    float HostDist;
};

class Triangle
{
private:

    float B;
    float H;
    float A;
    float Angle;

public:

    void PosAngle(float HostLat, float HostLon, struct Positions Px)
    {
        // n = north pole
        float an = Ndist(HostLat, HostLon);
        float bn = Ndist(Px.TargetLat, Px.TargetLon);
        H = FindDist(HostLat, HostLon, Px);
        A = an-bn;
        B = sqrt(H*H - A*A);
        Angle = Todeg(acos(B/H));
        //top right portion of map
        if(HostLat <= Px.TargetLat && HostLon <= Px.TargetLon)
        {
            Angle = 90-Angle;
        }//bottom right portion
        else if(HostLat >= Px.TargetLat && HostLon <= Px.TargetLon)
        {
            Angle += 90;
        }//bottom left
        else if(HostLat >= Px.TargetLat && HostLon >= Px.TargetLon)
        {
            Angle = 270-Angle;
        }//top left
        else
        {
            Angle += 270;
        }
        //cout << A <<endl;cout << B <<endl;cout << H <<endl;cout << Angle <<endl;
    }

    void ScreenAngle(float dist)
    {
      B = dist*1000;
      A = 0.1;
      H = sqrt((B*B) + (A*A));

      Angle = Todeg(acos(B/H));
    }

    float getAngle()
    {
        return Angle;
    }

    float getDist()
    {
        return H;
    }
};

void SetDnA(struct Positions *ptr, Triangle T)//dist and angle
{
    ptr->HostAngle = T.getAngle();
    ptr->HostDist = T.getDist();
}

float Torad(float deg)//to radian
{
    return deg * 3.14/180;
}
float Todeg(float rad)//to degrees
{
    return rad * 180/3.14;
}

float FindDist(float HostLat, float HostLon, struct Positions Px)
{
    float dlat = Torad(Px.TargetLat-HostLat);
    float dlon = Torad(Px.TargetLon-HostLon);

    float r = 6371.0;//avg approx.radius of the earth
    float a = sin(dlat/2)*sin(dlat/2)+cos(Torad(HostLat)) * cos(Torad(Px.TargetLat)) * sin(dlon/2) * sin(dlon/2);
    float c = 2*atan2(sqrt(a),sqrt(1-a));
    float d = r*c;//distance in km
    return d;
}

//to find distance to the north pole from host
float Ndist(float lat, float lon)
{
    float Nlon = 0.000;
    float Nlat = 90.000;

    float dlatB = Torad(lat - Nlat);
    float dlonB = Torad(lon - Nlon);

    float r = 6371.0;
    float a = sin(dlatB/2)*sin(dlatB/2)+cos(Torad(Nlat)) * cos(Torad(lat)) * sin(dlonB/2) * sin(dlonB/2);
    float c = 2*atan2(sqrt(a),sqrt(1-a));
    float d = r*c;

    return d;
}
