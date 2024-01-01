from cvzone.FaceDetectionModule import FaceDetector
import cv2
from serial import Serial, SerialException

serial_port = 'COM5'  # Change this to your Arduino's serial port
baud_rate = 9600
arduino = Serial(serial_port, baud_rate, timeout=1)
flag = 0
cap = cv2.VideoCapture(1)  # Create Video Capture Object
detector = FaceDetector()  # Create detector instance

while True:
    success, img = cap.read()    # Get Image
    arduino.write(b'9')
    img, bboxs = detector.findFaces(img)   # Detect Face

    if bboxs:   # If boxes found,
        if not flag:
            arduino.write(b'1')
            print('I detect someone!')
            # bboxInfo - "id","bbox","score","center"
            center = bboxs[0]["center"]
            cv2.circle(img, center, 5, (255, 0, 255), cv2.FILLED)
            flag = 1
            
    else:
        arduino.write(b'0')
        flag = 0
        
    cv2.imshow("Image", img)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
