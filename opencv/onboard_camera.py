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
#cv2.VideoCapture()를 사용해 비디오 캡쳐 객체를 생성할 수 있습니다.                     
cap = cv2.VideoCapture(gst_str)

#while True:  특정 키를 누를때까지 무한 반복을 위해 사용했습니다. 
while True:
	'''ret, fram = cap.read() 비디오의 한 프레임씩 읽습니다. 제대로 프레임을 읽으면 ret값이 True,
	실패하면 False가 나타납니다. fram에 읽은 프레임이 나옵니다'''
	ret, fram = cap.read()
	if ret:
		cv2.imshow('video', fram)
		k = cv2.waitKey(1) & 0xFF
		if k == 27:
			break
	else:
		print('error')
		
#cap.release() 오픈한 캡쳐 객체를 해제합니다
cap.release()
cv2.destroyAllWindows()
