# pure-software-CPU-calculation-for-3D-vertex-transformation
To get better understanding the math behind the 3D graphic,
I wrote a CPU based matrix transformation math library using homebrew generalized matrix class

This matrix class is very generic template and it can be used in any dimension matrix
by using all classic math text book method to implement matrix ADD/SUB/MUL/Reverse/Transpose etc operations.
I call it general slow matrix class, since it is only for fun. 
Only use 1 cpu thread, no hardware vector processor optimized(no SSE/SSE2) and only use math text book of human method.
and I did not use fancy strassen matrix algorithm, just linear algebra class human method.

The 3D verex transformation part is the normal 3D graphic vertex shader stage. But this is in CPU software implementation in
GPU hardware. 3D local view system-> world view system + 3D camera view -> 2D clipping view.

The output is using linux allegro library to draw 2D lines connect 8 points to 3D cube. And use keyboard arrow key
to rotate the 3D cube.

The realtime rotation is done by the slow generalize matrix class calculation through the 3D vertex pipeline.


