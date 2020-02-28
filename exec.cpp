#include<iostream>
#include<fstream>
#include<time.h>
#include"aunth.h"

using namespace std;

//Set Positions(long,lat)
void SetPosition(struct Positions *P, int n, float lat, float lon)
{
  n-=1;
  P[n].TargetLat = lat;
  P[n].TargetLon = lon;
}
//for pointer type
void SetPosition(struct Positions *P, float lat, float lon)
{
  P->TargetLat = lat;
  P->TargetLon = lon;
}

//CHeck if the target is in Infront
void CheckScreen(int hostDeg, int targetDeg)
{
  int fov = 40;//field of view
  int min = targetDeg - fov/2;
  int max = targetDeg + fov/2;

  if(hostDeg <= max && hostDeg >= min)
  {
    //cout << "on screen" <<endl;
    cout << "Object Is Infront" <<endl;
  }
  else
  {
    cout << "Object Is not Infront" <<endl;
    //cout << "not on screen" <<endl;
  }
}

int Update()//string data)
{
  int angle, a;

  ifstream file;
  file.open("hostDeg.dat");

  while(file)
  {
    file >> angle >> a;
  }
  file.close();
  return angle;
}

int exit()//stop when val=0
{
  int x;

  ifstream file;
  file.open("hostDeg.dat");

  while(file)
  {
    file >> x;
  }
  file.close();
  return x;
}

void delay(int ms)
{
  clock_t start = clock();

  while(clock() < start+ms)
    ;
}

float OnScreenAngle(float dist)
{
  Triangle t;

  t.ScreenAngle(dist);

  return t.getAngle();
}

int main()
{
  MyLat = 26.870601;
  Mylon = 75.794110;
  int data, x=0;

  Positions P;
  Positions *ptrP = &P;

  SetPosition(ptrP, 48.423366,2.345332);
  //SetPosition(P,2, 49.3995,-2.4985);
  //SetPosition(P,3, 26.3679,91.4290);

  Triangle tn;
  tn.PosAngle(MyLat,Mylon, P);
  SetDnA(ptrP, tn);
  
  for(int i=0; i<1; i++)
  {
    //  printf("%d Degrees, %.2f m\n",(int)P[i].HostAngle, (P[i].HostDist));
  }

  for(x; x<1;)
  {
    data = Update();
    CheckScreen(data,P.HostAngle);
    //cout <<  FindDist(MyLat, Mylon, P)<<endl;// OnScreenAngle(P.HostDist) <<"\n"<<
    cout << (int)P.HostAngle << " Degrees, " << (P.HostDist/1000) << "m\n" << endl;
    x = exit();
    delay(700);
  }

}
