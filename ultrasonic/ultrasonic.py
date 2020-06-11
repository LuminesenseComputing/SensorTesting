# Import Libraries
import RPi.GPIO as GPIO
import time
 
def main():
    setup()
    try:
        while True:
            dist = distance()
            print ("Measured Distance = %.1f cm" % dist)
            time.sleep(1)

    # Reset by pressing CTRL + C
    except KeyboardInterrupt:
        print("Measurement stopped by User")
        GPIO.cleanup()
    return True

def setup():
    """
    Basic setup for Raspi GPIO
    """
    # Set GPIO Mode (Board/BCM)
    GPIO.setmode(GPIO.BCM)

    # Set GPIO Pins
    GPIO_TRIGGER = 18
    GPIO_ECHO = 24

    # Set GPIO direction
    GPIO.setup(GPIO_TRIGGER, GPIO.OUT)
    GPIO.setup(GPIO_ECHO, GPIO.IN)
    
    return True

def distance():
    """
    Function: Calculates distance in cm by ultrasonic wave pulsing
    Returns: distance in cm
    """
    # clear Trigger
    GPIO.output(GPIO_TRIGGER, False)
    time.sleep(0.000002) # delay 0.002 s


    # set Trigger to HIGH got 0.01ms
    GPIO.output(GPIO_TRIGGER, True)
    time.sleep(0.00001)
 
    # set Trigger after 0.01ms to LOW
    GPIO.output(GPIO_TRIGGER, False)
 
 
    # save StartTime
    while GPIO.input(GPIO_ECHO) == 0:
        StartTime = time.time()
 
    # save time of arrival
    while GPIO.input(GPIO_ECHO) == 1:
        StopTime = time.time()
 
    # time difference between start and arrival
    TimeElapsed = StopTime - StartTime
    # multiply with the sonic speed (34300 cm/s)
    # and divide by 2, because there and back
    distance = (TimeElapsed * 34300) / 2
 
    return distance


### ======================== Calling main  ==============================
main()



### ======================== Not completed ==============================

def getDistanceMovingAvg():
    """
    Function: compute the distance base on a moving average 
    Returns: distance in cm
    """
   
    dist = 0
    dist = distance(GPIO)

    ## Error check, check if value is out of bound
    #
    #
    #

   return 

















