import cv2
width = 1280
height = 720


gst_str = ('nvarguscamerasrc ! '
                   'video/x-raw(memory:NVMM), '
                   'width=(int)1920, height=(int)1080, '
                   'format=(string)NV12, framerate=(fraction)30/1 ! '
                   'nvvidconv flip-method=0 ! '
                   'video/x-raw, width=(int){}, height=(int){}, '
                   'format=(string)BGRx ! '
                   'videoconvert ! appsink').format(width, height)
                   
cap = cv2.VideoCapture(gst_str)

while True:
	ret, fram = cap.read()
	if ret:
		cv2.imshow('video', fram)
		k = cv2.waitKey(1) & 0xFF
		if k == 27:
			break
	else:
		print('error')
		

cap.release()
cv2.destroyAllWindows()
