
#include"Graphics.h"
int main()
{
    olcEngine3D demo(3);
    if (demo.Construct(1080, 720, 1, 1))
        demo.Start();

    return 0;
}
