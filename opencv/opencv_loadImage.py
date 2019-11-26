import cv2

image = cv2.imread("./image/cat.jpg", cv2.IMREAD_ANYCOLOR)
cv2.imshow("Cat", image)
cv2.waitKey(0)
cv2.destroyAllWindows()
