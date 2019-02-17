#ifndef STATE_INCLUDED
#define STATE_INCLUDED

using namespace std;

int camera = -1;
int quality = 0;
int frame = 0;

void clearAll()
{
   camera = -1;
   quality = 0;
   frame = 0;
}

void cacheCameraID(int id)
{
   camera = id;
}

int getCameraID()
{
   return camera;
}

void cacheQuality(int qual)
{
   quality = qual;
}

int getQuality()
{
   return quality;
}

void cacheFrame(int fr)
{
   frame = fr;
}

int getFrame()
{
   return frame;
}

#endif //STATE_INCLUDED
