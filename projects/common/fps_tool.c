#include <stdio.h>
#include "fps_tool.h"
#include "glfw3.h"

unsigned fpsValue  = 30;
double   fpsDelay  = 1000. / 30.;
double   startTime = 0.0;

unsigned frames         = 0;
unsigned current_frames = 0;

void fps_set_fps(unsigned aFps)
{
    fpsValue = aFps;
    fpsDelay = (1000. / fpsValue) / 1000.;
}
//------------------------------------------------------------------------------
void fps_start()
{
    static double last   = 0.;
    static double elapsed = 0.;

    startTime = glfwGetTime();

    elapsed = startTime - last;
    if(elapsed > 1.0)
    {
        current_frames = frames / elapsed;
        last           = startTime;
        frames         = 0;

        printf("FPS:%i(%i)\n", current_frames, fpsValue);
    }
    ++frames;
}
//------------------------------------------------------------------------------
void fps_wait()
{
    while((glfwGetTime() - startTime) < fpsDelay)
        ;
}
