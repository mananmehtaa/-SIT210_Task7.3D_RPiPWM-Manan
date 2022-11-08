import RPi.GPIO as GPIO
import time
 
distance = 0 
startTime = 0
endTime = 0
led = 12             
trig = 8
echo = 10

GPIO.setmode(GPIO.BOARD)    

GPIO.setwarnings(False)

GPIO.setup(led,GPIO.OUT)
GPIO.setup(trig, GPIO.OUT)
GPIO.setup(echo, GPIO.IN)
pwm = GPIO.PWM(led, 500)        
pwm.start(0)                        


try:
    while True:
        GPIO.output(trig, 0)
        time.sleep(0.000002)  

        GPIO.output(trig, 1)
        time.sleep(0.00001)   

        GPIO.output(trig, 0)
 
        while GPIO.input(echo) == 0:
            startTime = time.time()


        while not GPIO.input(echo) == 0:
            endTime = time.time()
        
        timee = endTime - startTime
        distance = (timee*34300)/2
 
        if distance > 0 and distance <= 40 :
            pwm.ChangeDutyCycle(((40 - distance)/40)*100)
        else:
            pwm.ChangeDutyCycle(0)

        time.sleep(0.4)

except KeyboardInterrupt:
    pwm.stop()
    GPIO.cleanup()
