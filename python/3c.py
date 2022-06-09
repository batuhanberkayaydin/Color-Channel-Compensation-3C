from skimage.color import rgb2lab,rgb2gray,lab2rgb
import numpy as np
import cv2

def three_c(img_rgb):

    
    img_lab = rgb2lab(img_rgb)
    img_gray = rgb2gray(img_rgb)
    img_gray[img_gray > 216] = 0
    img_gray[img_gray <= 216] = 1
    
    gray_gauss = cv2.GaussianBlur(img_gray,(0,0),5)
    ch1,ch2,ch3 = cv2.split(img_lab)
    ch2_gauss = cv2.GaussianBlur(ch2,(0,0),100)
    img_lab[:,:,1]=np.subtract(ch2,np.multiply(gray_gauss,ch2_gauss))
    
    ch3_gauss = cv2.GaussianBlur(ch3,(0,0),100)
    img_lab[:,:,2]=np.subtract(ch3,np.multiply(gray_gauss,ch3_gauss))
    
    new=lab2rgb(img_lab)
    
    return 255*new

if __name__ == '__main__':

    img_rgb= cv2.imread("../inputs/test_image.jpg")
    compensated_image = three_c(img_rgb)
    cv2.imwrite("../results/result.png",compensated_image)
