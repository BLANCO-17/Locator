#include<iostream>
#include<math.h>

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

    void Calc(float HostLat, float HostLon, struct Positions Px)
    {
        // n = north pole
        float an = Ndist(HostLat, HostLon);
        float bn = Ndist(Px.TargetLat, Px.TargetLon);
        H = FindDist(HostLat, HostLon, Px);
        A = an-bn;
        B = sqrt(H*H - A*A);
        Angle = Todeg(acos(B/H));

        if(HostLat <= Px.TargetLat && HostLon <= Px.TargetLon)
        {
            Angle = 90-Angle;
        }
        else if(HostLat >= Px.TargetLat && HostLon <= Px.TargetLon)
        {
            Angle += 90;
        }
        else if(HostLat >= Px.TargetLat && HostLon >= Px.TargetLon)
        {
            Angle = 270-Angle;
        }
        else
        {
            Angle += 270;
        }
        //cout << A <<endl;cout << B <<endl;cout << H <<endl;cout << Angle <<endl;
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

void SetDnA(struct Positions *ptr, Triangle T)
{
    ptr->HostAngle = T.getAngle();
    ptr->HostDist = T.getDist();
}


int main()
{
    MyLat = 26.4829;
    Mylon = 74.0000;

    Positions P[3];
    P[0].TargetLat = 50.5957; P[0].TargetLon = 3.0776;
    P[1].TargetLat = 49.3995; P[1].TargetLon = -2.4985;
    P[2].TargetLat = 48.3679; P[2].TargetLon = -4.4290;

    Positions *ptrP = P;

    Triangle tn[3];

    for(int i=0; i<3; i++)
    {
        tn[i].Calc(MyLat,Mylon, P[i]);
        SetDnA(ptrP, tn[i]);
        ptrP++;
        //P[i].GetDets();
    }

    for(int i=0; i<3; i++)
    {
        cout << (int)P[i].HostAngle << " Degrees, " << (int)P[i].HostDist << " Km\n" << endl;
    }

}



float Torad(float deg)
{
    return deg * 3.14/180;
}

float Todeg(float rad)
{
    return rad * 180/3.14;
}

float FindDist(float HostLat, float HostLon, struct Positions Px)
{
    float dlat = Torad(Px.TargetLat-HostLat);
    float dlon = Torad(Px.TargetLon-HostLon);

    float r = 6371.0;
    float a = sin(dlat/2)*sin(dlat/2)+cos(Torad(HostLat)) * cos(Torad(Px.TargetLat)) * sin(dlon/2) * sin(dlon/2);
    float c = 2*atan2(sqrt(a),sqrt(1-a));
    float d = r*c;
    return d;
}

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
