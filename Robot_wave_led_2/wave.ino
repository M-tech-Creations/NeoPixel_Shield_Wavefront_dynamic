//WAVEFRONT ALGORITHM





int propagate_wavefront(int robot_x, int robot_y)
	{
	//clear old wavefront
	unpropagate(robot_x, robot_y);
	
	//start location to begin scan at goal location
	map1[goal_x][goal_y]=goal;//goal at 3,3 for error
	
	print_map();

    counter=0;
    while(counter<50)//allows for recycling until robot is found
        {
        x=0;
        y=0;
    	while(x<X && y<Y)//while the map hasnt been fully scanned
    		{
    		//if this location is a wall or the goal, just ignore it
    		if (map1[x][y] != wall && map1[x][y] != goal)
    			{	
    			//a full trail to the robot has been located, finished!
    			if (min_surrounding_node_value(x, y) < reset_min && map1[x][y]==robot)
    				{
                	
                	print_map();
    				//finshed! tell robot to start moving down path
    				return min_node_location;
    				}
    			//record a value in to this node
    			else if (minimum_node!=reset_min)//if this isnt here, 'nothing' will go in the location
    				map1[x][y]=minimum_node+1;
    			}
    		
    		//go to next node and/or row
    		y++;
    		if (y==Y && x!=X)
    			{
    			x++;
    			y=0;
    			}
    		}
   		
        print_map();
   		counter++;
        }
    return 0;
	}

void unpropagate(int robot_x, int robot_y)//clears old path to determine new path
	{	
	
	print_map();
	
    //printf("Starting Unpropagate\n");

	//stay within boundary
	for (x=0; x<X; x++)
	    for (y=0; y<Y; y++)
		    if (map1[x][y] != wall && map1[x][y] != goal) //if this location is a wall or goal, just ignore it
		       map1[x][y] = nothing;//clear that space

	//old robot location was deleted, store new robot location in map
	map1[robot_x][robot_y]=robot;
	
	
	//fprintf(out, "Unpropagation Complete:\n");
	print_map();
	}

//this function looks at a node and returns the lowest value around that node
int min_surrounding_node_value(int x, int y)
	{
	minimum_node=reset_min;//reset minimum

	//down
	if(x < X-1)//not out of boundary
		if  (map1[x+1][y] < minimum_node && map1[x+1][y] != nothing)//find the lowest number node, and exclude empty nodes (0's)
		    {
			minimum_node = map1[x+1][y];
			min_node_location=3;
            }

	//up
	if(x > 0)
		if  (map1[x-1][y] < minimum_node && map1[x-1][y] != nothing)
		    {
			minimum_node = map1[x-1][y];
			min_node_location=1;
            }
	
	//right
	if(y < Y-1)
		if  (map1[x][y+1] < minimum_node && map1[x][y+1] != nothing)
		    {
			minimum_node = map1[x][y+1];
			min_node_location=2;
            }
            
	//left
	if(y > 0)
		if  (map1[x][y-1] < minimum_node && map1[x][y-1] != nothing)
		    {
			minimum_node = map1[x][y-1];
			min_node_location=4;
            }
	   
	return minimum_node;
	}

void print_map(void)
	{
	for (temp_B=0;temp_B<X;temp_B++)
		{
		for (temp_A=0;temp_A<Y;temp_A++)
			{
            if (map1[temp_B][temp_A]==wall)
				LED_Print(temp_B,temp_A,wall);
              
            else if (map1[temp_B][temp_A]==robot)
               LED_Print(temp_B,temp_A,robot);
            else if (map1[temp_B][temp_A]==goal)
               LED_Print(temp_B,temp_A,goal);
			else
               LED_Print(temp_B,temp_A,map1[temp_B][temp_A]);
		
			}
		
		
		}
	
	steps++;
	strip.show();
	delay(update_time);
	}
void LED_Print(int x,int y,int object)
{
	if(object==nothing)
	{
		strip.setPixelColor(SetElement(x,y),strip.Color(0,0,0));//off
	}
	else if(object==wall)
	{
		strip.setPixelColor(SetElement(x,y),strip.Color(100,0,0));//red
	}
	else if(object==goal)
	{
		strip.setPixelColor(SetElement(x,y),strip.Color(255,215,0));//yellow
	}
	else if(object==robot)
	{
		strip.setPixelColor(SetElement(x,y),strip.Color(0,0,100));//blue
	}
	else
	{
		strip.setPixelColor(SetElement(x,y),strip.Color(100/object*2,71/object*2,0));//yellow dim for distance
	}
}