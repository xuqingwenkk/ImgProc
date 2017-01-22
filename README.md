# ImgProc
Some implement on image process

I just want to write some wrapped functions for future use though most of them have been realized in OpenCV. 

parallax:
It seems to be not a good solution for generating depth image because the method is influenced by light much.

multiview:
To remote control robot, we want a window to show the robot view. 
Since we use a 235 degree fisheye lens to broden vision, we need to unwrap the image from different views.
In this project, we can adjust in param/parameters to meet the requirement.
