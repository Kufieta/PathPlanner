#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
 
int main( )
{    
  // Create black empty images
  Mat image = Mat::zeros( 400, 400, CV_8UC3 );
   
  // Draw a ellipse 
  ellipse( image, Point( 200, 200 ), Size( 100.0, 160.0 ), 45, 0, 360, Scalar( 255, 0, 0 ), 1, 8 );
  ellipse( image, Point( 200, 200 ), Size( 100.0, 160.0 ), 135, 0, 360, Scalar( 255, 0, 0 ), 10, 8 );
  ellipse( image, Point( 200, 200 ), Size( 150.0, 50.0 ), 135, 0, 360, Scalar( 0, 255, 0 ), 1, 8 );
  imshow("Image",image);
 
  waitKey( 0 );
  return(0);
}
