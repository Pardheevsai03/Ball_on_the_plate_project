import cv2 as cv
import numpy as np


cap =cv.VideoCapture(1)
while True:
    _,frame2 =cap.read()
    gray_img = cv.cvtColor(frame2, cv.COLOR_BGR2GRAY)
    blur_img = cv.GaussianBlur(gray_img,(5,5),1 )

    canny_img = cv.Canny(blur_img, 0, 200,-1)
    
    find_countours, _ = cv.findContours(canny_img, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    cv.drawContours(image= frame2, contours = find_countours ,contourIdx=-1, color=(255,0,0) ,thickness =2)
    #finding and cropping plate
    max_area = 0
    max_contour = None
    for contour in find_countours:
      area = cv.contourArea(contour)
      if area > max_area:
         max_area = area
         max_contour = contour
    x, y, w, h = cv.boundingRect(max_contour)
    print("--------",x,y,w,h,"------------")
    x_center =x+(w)/2
    y_center = (y+h)/2
    print("--------",x_center,y_center,"------------")

    image = cv.circle(frame2,[int((x+(w)/2)),int(y+(h)/2)],1,(0,0,255),10)
    
    
    #print(find_countours, len(find_countours[0]),len(find_countours[1]),'------------------------------------------------------------')

    

    cv.waitKey(1)

    detected_circles = cv.HoughCircles(blur_img,cv.HOUGH_GRADIENT,1,50,param1 =50, param2 = 30, minRadius = 1,maxRadius=40)
    if detected_circles is not None:
        detected_circles = np.uint16(np.around(detected_circles))
  
        for pt in detected_circles[0, :]:
           a =0
           a, b, r = pt[0], pt[1], pt[2]
           image = cv.circle(frame2,[int(a),int(b)],1,(0,0,255),10)
           image = cv.circle(frame2,[int(a),int(b)],r,(0,0,255),10)
    cv.imshow("cam", frame2)
   
