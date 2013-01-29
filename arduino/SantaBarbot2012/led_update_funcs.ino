//Notice, I used a subroutine to update the colors on the LEDs, since I will need to do this every loop.
//The subroutine is defined here:

//bright colors

int purple [3] = {255,0,255};
int lime_green[3] = {43, 255, 0};
int orange [3] = {255, 145, 0};
int baby_blue[3] = { 0, 242, 255};
int yellow[3] = {255,247,0};
int pink[3] = { 255,0 , 208};
int deep_blue[3] ={0, 64, 255};
int turquoise[3] = {0, 255, 140};

int * colors[8] = {purple, baby_blue, deep_blue, turquoise, orange, lime_green, pink, yellow};

void update_fader() {
  int i;
  int color;
  fader_color[0]+=inc_a;
  fader_color[1]+=inc_b;
  fader_color[2]+=inc_c;


  if(fader_color[0] <= 0 || fader_color[0] >= 255){

    fader_color[0]-=inc_a; 
    inc_a *= -2;
    if(abs(inc_a) > 4) // a terrible thing to do to a poor little micro...
      inc_a = random(1,4)*inc_a/abs(inc_a);
  }
  if(fader_color[1] <= 0 || fader_color[1] >= 255){
    fader_color[1]-=inc_b;
    inc_b *= -2;
    if(abs(inc_b) > 4)
      inc_b = random(1,4)*inc_b/abs(inc_b);
  }
  if(fader_color[2] <= 0 || fader_color[2] >= 255){
    fader_color[2]-=inc_c;
    inc_c *= -2; 
    if(abs(inc_c) > 4)
      inc_c = random(.1,4)*inc_c/abs(inc_c);
  }

  TCL.sendEmptyFrame();
  TCL.sendColor(debugRGB[0], debugRGB[1], debugRGB[2]);
  for(i=1;i<LEDS;i++) {
    //    color = current_color[i];
    TCL.sendColor(fader_color[0],fader_color[1], fader_color[2]);
  }
  TCL.sendEmptyFrame();
}

void update_orbs(int dir){
  int i;
  TCL.sendEmptyFrame();

  TCL.sendColor(debugRGB[0], debugRGB[1], debugRGB[2]);
  int r = random(0,255);
  int g = random(0,255);
  int b = random(0,255);

  for(i=0;i<8;i++) {
    if(i == orb_a){
      //
      TCL.sendColor(r,g,b);      
      TCL.sendColor(r,g,b);      
      TCL.sendColor(r,g,b);//(0, 30, 255);
      //      TCL.sendColor(0, 30, 255);
      //    TCL.sendColor(0, 30, 255);
      //     // delay(50);
    }
    else if(i == orb_b){
      //      TCL.sendColor(0, 30, 255);
      //      TCL.sendColor(0, 30, 255);
      //      TCL.sendColor(0, 30, 255);
      TCL.sendColor(r,g,b);      
      TCL.sendColor(r,g,b);      
      TCL.sendColor(r,g,b);
      //      
    }
    else{
      TCL.sendColor(3, 3, 3);    
      TCL.sendColor(3, 3, 3);    
      TCL.sendColor(3, 3, 3);
    }
  }
  // 

  TCL.sendEmptyFrame();
  switch (dir){
  case FORWARD:
    orb_a++;
    orb_b++;
    break;
  case BACKWARD:
    orb_a--;
    orb_b--;
    break;
  case COUNTER:
    orb_a++;
    orb_b--;
    break;
  }
  if (orb_a > 8)
    orb_a = 0;
  if (orb_b > 8)
    orb_b = 0; 
  if (orb_a < 0)
    orb_a = 8;
  if (orb_b < 0)
    orb_b = 8;    
}

void update_lit(){
  int i;
  for(i=0;i<8;i++) {
    if(i == mCur){
      //      TCL.sendColor(0, 30, 255);
      //      TCL.sendColor(0, 30, 255);
      //      TCL.sendColor(0, 30, 255);
      TCL.sendColor(colors[mCur][0], colors[mCur][1], colors[mCur][2]);
      TCL.sendColor(colors[mCur][0], colors[mCur][1], colors[mCur][2]);
      TCL.sendColor(colors[mCur][0], colors[mCur][1], colors[mCur][2]);
      //      
    }
    else{
      TCL.sendColor(3, 3, 3);    
      TCL.sendColor(3, 3, 3);    
      TCL.sendColor(3, 3, 3);
    }
  }
  
}








