#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include "roboard.h"
#include <cv.h>
#include <highgui.h>
#include <time.h>

#define width 320
#define height 240
int ch ;
int im[height][width];
int a1x=0,a1y=0,m1x=0,m1y=0,dx=0;
int sum1=0;
int centerx=145,dist=0,centery=130,disty=0;    
float dtime;
unsigned long PWM_period = 20000L;
unsigned long PWM_cw = 1580L;
unsigned long PWM_cw1 = 1580L;
unsigned long PWM_ccw = 1400L;
unsigned long PWM_ccw1 = 1430L;
unsigned long PWM_ccw2 = 1400L;
unsigned long PWM_stop = 1500L;
unsigned long PWM_camd = 2200L;
unsigned long PWM_camu = 800L;
unsigned long PWM_camcat = 1852L;
unsigned long PWM_camc = 1500L;
unsigned long PWM_ivshot = 0L;
unsigned long PWM_shot9 = 18000L;
unsigned long count;
unsigned long count2;
	
unsigned long PWM_period2 = 10000L ;
unsigned long PWM_duty_right = 1700L;
unsigned long PWM_duty_stop = 1500L;
unsigned long PWM_duty_left =1300L;
unsigned long PWM_duty_right_forward = 1600L;
unsigned long PWM_duty_left_forward =1400L;

IplImage* pFrame = NULL; 
CvCapture* pCapture = NULL;
          
IplImage* img = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,3);	
IplImage* img_gray = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
IplImage* img_hsv = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,3);
IplImage* img_ok  = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);

/*
void wait_ms(unsigned long time) 
{
	unsigned long now_time = GetTickCount();
	while((GetTickCount() - now_time) < time);
}
*/

void capinf()
{
    for(int h=0;h<height;h++)
	 {
		 unsigned char* ptr=(unsigned char*)(
    	 img_hsv->imageData + h*img_hsv->widthStep);

		 for(int w=0;w<width;w++)
         {
			if(ptr[3*w]>10 && ptr[3*w]<20 && ptr[3*w+1]>120 && ptr[3*w+1]<255 && ptr[3*w+2]>240 && ptr[3*w+2]<255)
			{
			  ptr[3*w]=0;
			  ptr[3*w+1]=0;
			  ptr[3*w+2]=0;
			}
			else
			{
			  ptr[3*w]=255;
			  ptr[3*w+1]=255;
			  ptr[3*w+2]=255;
			}
          }
	 }
}
void m()
{
	 for(int h=0;h<height;h++)
		   {
			   unsigned char* ptr=(unsigned char*)(
					 img_ok->imageData + h*img_ok->widthStep);

			   for(int w=0;w<width;w++)
             {
				 im[h][w]= ptr[w] ;		
             }
		   }
		   

          for (unsigned int y = 0; y < height; y++)
          {
              for (unsigned int x = 0; x < width; x++)
              {
                if(im[y][x]==0)
                {
                  m1x=x+m1x;
                  m1y=y+m1y;
                  sum1++;
                }
              }     
          }

           if(sum1!=0)
          {
            a1x=m1x/sum1;
            a1y=m1y/sum1;
          }
          else
         {
            a1x=0;
            a1y=0;
         }
}
void findball()
{
	      dist=a1x-centerx;
		  disty=a1y-centery;
           
		  if(dist>=10 && dist<=15)
		  {
		  count=5L;
		 
		  } 
		  else if(dist>15 && dist<=30)
		  {
		  count=10L;
		  
		  }
		  else if(dist>30 && dist<=50)
		  {
		  count=15L;
		 
		  }
		  else if(dist>50 && dist<=70)
		  {
		  count=20L;
		 
		  }
		  else if(dist>70 && dist<=90)
		  {
		  count=30L;
		
		  }
		  else if(dist>90 && dist<=110)
		  {
		  count=45L;
		  
		  }
		  else if(dist>110 && dist<=130)
		  {
		  count=65L;
		
		  }
		  else if(dist>130 && dist<=150)
		  {
		  count=85L;
		  }
		  else if(dist>150 && dist<=160)
		  {
		  count=95L;
		  }
		   else if(dist>160 && dist<=175)
		  {
		  count=100L;
		  }
		  
		  else if(dist>=(-15) && dist<=(-10))
		  {
		  count=5L;
		 
		  } 
		  else if(dist>(-30) && dist<=(-15))
		  {
		  count=10L;
		  
		  }
		  else if(dist>(-50) && dist<=(-30))
		  {
		  count=15L;
		 
		  }
		  else if(dist>(-70) && dist<=(-50))
		  {
		  count=20L;
		 
		  }
		  else if(dist>(-90) && dist<=(-70))
		  {
		  count=30L;
		
		  }
		  else if(dist>(-110) && dist<=(-90))
		  {
		  count=45L;
		  
		  }
		  else if(dist>(-130) && dist<=(-110))
		  {
		  count=65L;
		
		  }
		  else if(dist>(-145) && dist<=(-130))
		  {
		  count=85L;
		  }
		  
		  else if(disty>(-30) && disty<=(-20))
		  {
		  count=0L;
          count2=20L;		
		  }
		 else if(disty>(-50) && disty<=(-30))
		  {
		  count=0L;
          count2=50L;		
		  }
		  else if(disty>(-70) && disty<=(-50))
		  {
		  count=0L;
          count2=100L;		
		  }
		  else if(disty>(-90) && disty<=(-70))
		  {
		  count=0L;
          count2=150L;		
		  }
		   else if(disty>(-110) && disty<=(-90))
		  {
		  count=0L;
          count2=200L;		
		  }
		   else if(disty>(-120) && disty<=(-110))
		  {
		  count=0L;
          count2=250L;		
		  }
		   else
		  {
           count=0L;
		   count2=0L;
		  }


}

int main()
{
    //int bar1=0,bar2=0,bar3=0,bar4=0,bar5=0,bar6=0;

	 

    roboio_SetRBVer(RB_110);
	rcservo_SetServo( 0, RCSERVO_SERVO_DEFAULT);
	rcservo_SetServo( 1, RCSERVO_SERVO_DEFAULT);
	rcservo_SetServo( 2, RCSERVO_SERVO_DEFAULT);
	rcservo_SetServo( 3, RCSERVO_SERVO_DEFAULT);
	rcservo_SetServo( 4, RCSERVO_SERVO_DEFAULT);
    rcservo_SetServo( 5, RCSERVO_SERVO_DEFAULT);

	if(rcservo_Initialize(RCSERVO_USECHANNEL0+   //DC MOTOR CW
		                  RCSERVO_USECHANNEL1+   //DC MOTOR CCW
						  RCSERVO_USECHANNEL2+   //GWS LEFT
						  RCSERVO_USECHANNEL3+   //GWS RIGHT
						  RCSERVO_USECHANNEL4+   //GWS BACK
						  RCSERVO_USECHANNEL5 )) //GWS CAM
    
	   {
	   
		  printf("Initialize is complete\n");

		  rcservo_EnterPWMMode();
         
          //===============================================



		  cvNamedWindow("camcapture", 1);
          cvMoveWindow("video", 30, 0);

		  pCapture = cvCaptureFromCAM(0);		  
        /* 
		  cvCreateTrackbar("h_min","camcapture",&bar1,180,NULL);
	      cvCreateTrackbar("h_max","camcapture",&bar2,180,NULL);
	      cvCreateTrackbar("s_min","camcapture",&bar3,255,NULL);
	      cvCreateTrackbar("s_max","camcapture",&bar4,255,NULL);
	      cvCreateTrackbar("v_min","camcapture",&bar5,255,NULL);
	      cvCreateTrackbar("v_max","camcapture",&bar6,255,NULL);


          bar1=cvGetTrackbarPos("h_min","camcapture");
          bar2=cvGetTrackbarPos("h_max","camcapture");
          bar3=cvGetTrackbarPos("s_min","camcapture");
	      bar4=cvGetTrackbarPos("s_max","camcapture");
    	  bar5=cvGetTrackbarPos("v_min","camcapture");
    	  bar6=cvGetTrackbarPos("v_max","camcapture");
          */
		 clock_t start=clock();
		 while(1)
         
		  {    
			  rcservo_SendPWM( 5, PWM_period, PWM_camcat, 100L );

			  pFrame = cvQueryFrame( pCapture );
			  cvResize(pFrame,img,CV_INTER_NN);
			 
              cvCvtColor(img, img_hsv, CV_BGR2HSV);
               
		      capinf();

              cvConvertImage(img_hsv,img_ok,0);
              cvErode(img_ok,img_ok,NULL,1);
              // cvDilate(img_ok,img_ok,NULL,1);
					   
              m();
                    
		      cvShowImage("camcapture", img_ok);
			  
			  clock_t end = clock();
	          dtime=(float)(end-start)/CLK_TCK;
     
              int key=cvWaitKey( 10 );
              if ( key == 27 )
	          {
    	         break;
	          }
     
              findball();

		      if(dtime>2)
		      { 
			   
	              printf("center x = %d   y = %d\n",a1x,a1y);	
			
	              printf("distance= %d\n",dist);
		          printf("dtime= %.3f\n",dtime);
		          start=clock();

			
                   if(dist>0 && count!=0)
		           {
		            	rcservo_SendPWMPulses(2,PWM_period2, PWM_duty_right, count);
		                rcservo_SendPWMPulses(3,PWM_period2, PWM_duty_right, count);
		              	rcservo_SendPWMPulses(4,PWM_period2, PWM_duty_right, count);
			       }
		        	else if(dist<0 && count!=0)
		          	{           
		             	rcservo_SendPWMPulses(2,PWM_period2, PWM_duty_left, count);
		                rcservo_SendPWMPulses(3,PWM_period2, PWM_duty_left, count);
		               	rcservo_SendPWMPulses(4,PWM_period2, PWM_duty_left, count);
		           	}

		           	else if(count==0 && count2!=0)
		         	{
		               rcservo_SendPWMPulses(2,PWM_period2, PWM_duty_right_forward, count2);
		               rcservo_SendPWMPulses(3,PWM_period2, PWM_duty_left_forward, count2);
			           rcservo_SendPWMPulses(4,PWM_period2, PWM_duty_stop, count2);             
			        }

		   }//if dtime

		  }//while
        rcservo_Close();

	  cvDestroyWindow("camcapture");
      cvReleaseCapture(&pCapture);

	  }//if init

    return 0;

}
