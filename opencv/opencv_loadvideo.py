import cv2
#cv2.VideoCapture("경로")을 이용하여 동영상 파일에서 프레임을 받아옵니다.
capture = cv2.VideoCapture("./image/Clouds.mp4")

while True:
#if문을 이용하여 가장 처음 현재 프레임 개수와 총 프레임 개수를 비교합니다.
#capture.get(속성)을 이용하여 capture의 속성을 반환합니다.
#cv2.CAP_PROP_POS_FRAMES는 현재 프레임 개수를 의미합니다.
#cv2.CAP_PROP_FRAME_COUNT는 총 프레임 개수를 의미합니다.
#같을 경우, 마지막 프레임이므로, capture.open(경로)를 이용하여 다시 동영상 파일을 불러옵니다.

    if(capture.get(cv2.CAP_PROP_POS_FRAMES) == capture.get(cv2.CAP_PROP_FRAME_COUNT)):
        capture.open("image/Clouds.mp4")

    ret, frame = capture.read()
    cv2.imshow("VideoFrame", frame)


#cv2.waitkey(time)을 이용하여 33ms마다 프레임을 재생합니다.
#어떤 키라도 누를 경우, break하여 while문을 종료합니다.

    if cv2.waitKey(33) > 0: break

capture.release()
cv2.destroyAllWindows()
