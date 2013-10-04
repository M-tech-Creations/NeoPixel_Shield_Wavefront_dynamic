#include <Adafruit_NeoPixel.h>

#define PIN 6
#define X 5
#define Y 8
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(40, PIN, NEO_GRB + NEO_KHZ800);

uint16_t SetElement(uint16_t, uint16_t);
int update_time = 1000;//1 sec delay

//in main, declare map matrix //6x6 map
int nothing=0;
int wall=255;
int goal=1;
int robot=254;

//declare starting robot/goal locations
int robot_x=4;
int robot_y=7;
int goal_x=0;
int goal_y=0;

//map locations
int x=0;
int y=0;

//temp variables
int temp_A=0;
int temp_B=0;
int counter=0;
int steps=0;//to determine how processor intensive the algorithm was

//when searching for a node with a lower value
int minimum_node=250;
int min_node_location=250;
int new_state=1;
int old_state=1;
int trans=50;
int reset_min=250;//anything above this number is a special item, ie a wall or robot

int count = 0;

//X is vertical, Y is horizontal
int map1[X][Y]=	{
	{0,wall,wall,wall,0,0,0,wall},
	{0,wall,wall,wall,0,wall,0,wall},
	{0,0,0,wall,0,wall,0,0},
	{wall,0,wall,wall,0,wall,0,0},
	{wall,0,0,0,0,wall,0,0}
};


//declare functions here, first
int propagate_wavefront(int robot_x, int robot_y);
void unpropagate(int robot_x, int robot_y);
int min_surrounding_node_value(int x, int y);
void print_map(void);
void LED_Print(int,int,int);//print to LED display
void object_maker();
int ran_maker();

void setup()
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  /* add setup code here */

}

void loop()
{
	
//////////////wavefront code//////////////
        while(map1[robot_x][robot_y]!=goal)
                {
					
					
					
        		//find new location to go to
        		new_state=propagate_wavefront(robot_x,robot_y);
        
        		//update new location of robot
        		if (new_state==1)
        			{
        			robot_x--;
        			//printf("x=%d y=%d\n\n",robot_x,robot_y);
        			}
        		if (new_state==2)
        			{
        			robot_y++;
        			//printf("x=%d y=%d\n\n",robot_x,robot_y);
        			}
        		if (new_state==3)
        			{
        			robot_x++;
        			//printf("x=%d y=%d\n\n",robot_x,robot_y);
        			}
        		if (new_state==4)
        			{
        			robot_y--;
        			//printf("x=%d y=%d\n\n",robot_x,robot_y);
        			}
        
        /*
        		//if not pointed in the right direction, rotate
        		if (abs(old_state - new_state) == 2)//rotate 180 degrees
        			rotate_CCW(200,200);
        		if ((old_state - new_state) == 1 || (signed int)(old_state - new_state) == -3)//rotate 90 degrees CW
        			rotate_CW(100,200);
        		if ((signed int)(old_state - new_state) == -1 || (old_state - new_state) == 3)//rotate 90 degrees CCW
        			rotate_CCW(100,200);
        		
        		//go to new location
        		straight(30,100);*/
        
        		//make new state the old state
        		old_state=new_state;
        		trans--;
				if (count==4)
				{
					object_maker();
					count=0;
				}
				count++;
                }
		//////////////////////////////////////////
	print_map();
	while(1);//stops the code

}
uint16_t SetElement(uint16_t row, uint16_t col)
{
	//array[width * row + col] = value;
	return Y * row+col;
}

void object_maker()
{
	for(int x =0;x<X;x++)
	{
		for(int y = 0;y<Y;y++)
		{
			if(map1[x][y]==goal)
			{
				break;
			}
			else if (map1[x][y]==robot)
			{
				break;
			}
			else
			{
				map1[x][y]=ran_maker();
			}
		}
	}

}
int ran_maker()
{
	int ran_temp = random(0,5);
	
	if(ran_temp==0)
	{
		return nothing;
	}
	else if (ran_temp==1)
	{
		return wall;
	}
	else if (ran_temp == 2)
	{
		return nothing;
	}
	else if (ran_temp == 3)
	{
		return wall;
	}
	else if (ran_temp == 4)
	{
		return nothing;
	}
	else
	{
		return wall;
	}
	
	
	
	return 0;	
}