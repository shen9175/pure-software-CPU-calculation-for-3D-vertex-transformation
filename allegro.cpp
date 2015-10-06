#include <allegro.h>
#include "gstransform.h"


GSVECTOR vertices[8]={
						GSVECTOR(-1,-1,-1,1),
						GSVECTOR(-1,+1,-1,1),
						GSVECTOR(+1,+1,-1,1),
						GSVECTOR(+1,-1,-1,1),
						GSVECTOR(-1,-1,+1,1),
						GSVECTOR(-1,+1,+1,1),
						GSVECTOR(+1,+1,+1,1),
						GSVECTOR(+1,-1,+1,1)
					};

GSVECTOR _2Dpoints[8]={
						GSVECTOR(-1,-1,-1,1),
						GSVECTOR(-1,+1,-1,1),
						GSVECTOR(+1,+1,-1,1),
						GSVECTOR(+1,-1,-1,1),
						GSVECTOR(-1,-1,+1,1),
						GSVECTOR(-1,+1,+1,1),
						GSVECTOR(+1,+1,+1,1),
						GSVECTOR(+1,-1,+1,1)
					};
unsigned int line_indices[][2]={{0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{3,7},{2,6},{1,5}};


GSVECTOR EyePosition=GSVECTOR(5,5,5,1);
GSVECTOR FocusPosition=GSVECTOR(0,0,0,0);
GSVECTOR UpDirection=GSVECTOR(0,1,0,0);

GSMATRIX view=GSMatrixLookAtLH(EyePosition, FocusPosition, UpDirection);
//std::cout<<"view="<<std::endl;
//std::cout<<view<<std::endl;
GSMATRIX p=GSMatrixPerspectiveFovLH(GSConvertToRadians(45),1920.0f/1200.0f,1,1000);
//std::cout<<"p="<<std::endl;
//std::cout<<p<<std::endl;


BITMAP *buffer; //This will be our temporary bitmap for double buffering

void rotateX(int a)
{
	for(unsigned int i=0;i<8;++i)
	{
		vertices[i]=GSVector3TransformCoord(vertices[i],GSMatrixRotationX(a));	
	}
}

void rotateY(int a)
{
	for(unsigned int i=0;i<8;++i)
	{
		vertices[i]=GSVector3TransformCoord(vertices[i],GSMatrixRotationY(a));	
	}
}

void rotateZ(int a)
{
	for(unsigned int i=0;i<8;++i)
	{
		vertices[i]=GSVector3TransformCoord(vertices[i],GSMatrixRotationZ(a));	
	}
}

void draw()
{



for(unsigned int i=0;i<8;++i)
{
	GSVECTOR temp=GSVector3TransformCoord(vertices[i], view);
	//std::cout<<"camera 3d="<<temp<<std::endl;
	GSVECTOR temp1=GSVector3TransformCoord(temp,p)/temp.getW();
	_2Dpoints[i]=temp1/temp1.getW();
	//std::cout<<temp.getW()<<std::endl;
	//std::cout<<_2Dpoints[i]<<std::endl;
}
/*
for(unsigned int i=0;i<8;++i)
{
	std::cout<<"X="<<static_cast<unsigned int>((_2Dpoints[i].getX()+2/2)*1920/2)<<"  Y="<<static_cast<unsigned int>((2/2-_2Dpoints[i].getY())*1200/2)<<std::endl;
}*/


acquire_screen();
clear_to_color( buffer, makecol( 255, 255, 255));
for(unsigned int i=0;i<12;++i)
{
	line(			buffer,
					static_cast<unsigned int>((_2Dpoints[line_indices[i][0]].getX()+2/2)*1920/2),
					static_cast<unsigned int>((2/2-_2Dpoints[line_indices[i][0]].getY())*1200/2),
					static_cast<unsigned int>((_2Dpoints[line_indices[i][1]].getX()+2/2)*1920/2),
					static_cast<unsigned int>((2/2-_2Dpoints[line_indices[i][1]].getY())*1200/2),
					makecol(0,0,0)
		);
				
}
draw_sprite( screen, buffer, 0, 0);
release_screen();

}

int main(){

allegro_init();
install_keyboard();
/*
install_sound (DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
MIDI *music;
music = load_midi("./99.midd");
if (!music)
    {std::cerr<<"Couldn't load background music!"<<std::endl;exit(1);}
else
	play_midi(music,1);
*/
set_gfx_mode( GFX_AUTODETECT, 1920, 1200, 0, 0);
buffer = create_bitmap( 1920, 1200); 

 while ( !key[KEY_ESC] ){
    
        clear_keybuf();
        

        
        if (key[KEY_UP]) rotateY(-2);        
        else if (key[KEY_DOWN]) rotateY(2);    
        else if (key[KEY_RIGHT]) rotateX(2);
        else if (key[KEY_LEFT]) rotateX(-2);
		else if (key[KEY_PGUP]) rotateZ(-2);
		else if (key[KEY_PGDN]) rotateZ(2);

        draw();

	}
	/*
	if(music)
	{
	stop_midi();
	destroy_midi(music);
	}
	*/
return 0;
}






        












/*
putpixel( screen, 5, 5, makecol( 128, 200, 23));
circle( screen, 20, 20, 10, makecol( 255, 0, 0));
circlefill( screen, 50, 50, 25, makecol( 0,255, 0));
rect( screen, 70, 70, 90, 90, makecol( 0, 0, 255));
rectfill( screen, 100, 100, 120, 120, makecol( 12, 34, 200));
line( screen, 130, 130, 150, 150, makecol( 255, 0, 0));
line( screen, 130, 130, 170, 130, makecol( 255, 0, 0));
line( screen, 170, 130, 150, 150, makecol( 255, 0, 0));
floodfill( screen, 140, 135, makecol( 255, 255, 0));
triangle( screen, 200, 200, 200, 220, 220, 210, makecol( 213, 79, 40));*/


//readkey();
