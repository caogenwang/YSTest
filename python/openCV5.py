#-*-coding: utf-8 -*-
import cv2 as cv
import numpy as np
# img = cv.imread(cv.samples.findFile('/Users/yangsen/book/sudu.jpg'))
# gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)
# edges = cv.Canny(gray,50,150,apertureSize = 3)
# lines = cv.HoughLines(edges,1,np.pi/180,200)
# for line in lines:
#     rho,theta = line[0]
#     print(rho,theta)
#     a = np.cos(theta)
#     b = np.sin(theta)
#     x0 = a*rho
#     y0 = b*rho
#     x1 = int(x0 + 2000*(-b))
#     y1 = int(y0 + 2000*(a))
#     x2 = int(x0 - 2000*(-b))
#     y2 = int(y0 - 2000*(a))
#     cv.line(img,(x1,y1),(x2,y2),(0,0,255),2)
# cv.imwrite('/Users/yangsen/book/houghlines3.jpg',img)

# import cv2 as cv
# import numpy as np
# img = cv.imread(cv.samples.findFile('/Users/yangsen/book/sudu.jpg'))
# gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)
# edges = cv.Canny(gray,50,150,apertureSize = 3)
# lines = cv.HoughLinesP(edges,1,np.pi/180,100,minLineLength=100,maxLineGap=10)
# for line in lines:
#     x1,y1,x2,y2 = line[0]
#     cv.line(img,(x1,y1),(x2,y2),(0,255,0),2)
# cv.imwrite('houghlines5.jpg',img)
a = 3
x = np.linspace(1, 10, num=50, endpoint=True, retstep=False, dtype=None)
b = 5
y = a * x + b

thetas = np.linspace(1, 180, num=180, endpoint=True, retstep=False, dtype=None)
thetas = np.pi/thetas

for (x0,y0) in zip(x,y):
    for theta in thetas:
        tho = x0 * np.cos(theta) + y0 * np.sin(theta)
        print(tho,theta)
