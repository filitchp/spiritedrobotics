//Notice, I used a subroutine to update the colors on the LEDs, since I will need to do this every loop.
//The subroutine is defined here:

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
  for(i=0;i<LEDS;i++) {
    //    color = current_color[i];
    if(i ==12 )
      TCL.sendColor(0,255,0);
    else
      TCL.sendColor(fader_color[0],fader_color[1], fader_color[2]);
  }
  TCL.sendEmptyFrame();
}

void update_orbs(int dir){
  int i;
  TCL.sendEmptyFrame();

  TCL.sendColor(0, 0, 0);
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








