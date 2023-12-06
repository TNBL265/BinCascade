# import RPi.GPIO as GPIO
import time
import paho.mqtt.client as mqtt
import ssl

# Define the GPIO pins for step and direction
# step_pin = 23  # GPIO23 (Pin 16)
# dir_pin = 24   # GPIO24 (Pin 18)
#
# # Set the GPIO mode and initial setup
# GPIO.setmode(GPIO.BCM)
# GPIO.setup(step_pin, GPIO.OUT)
# GPIO.setup(dir_pin, GPIO.OUT)

# motor_moving = False

# Function to move the stepper motor
# def move_motor(steps):
#     global motor_moving
#     motor_moving = True
#
#     if steps > 0:
#         GPIO.output(dir_pin, GPIO.HIGH)  # Clockwise rotation
#     else:
#         GPIO.output(dir_pin, GPIO.LOW)   # Anti-clockwise rotation
#         steps = -steps  # Make steps positive for the loop
#
#     for _ in range(steps):
#         GPIO.output(step_pin, GPIO.HIGH)
#         time.sleep(0.0005)  # Adjust the delay as needed for your motor
#         GPIO.output(step_pin, GPIO.LOW)
#         time.sleep(0.0005)  # Adjust the delay as needed for your motor

# MQTT callback functions
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print(client, userdata, flags, rc)
        print("Connected to MQTT Broker!")
        client.subscribe("Waste/Detect")
        print("Subscribed to Topic: Waste/Detect!")
    else:
        print("Failed to connect, return code %d\n", rc)

def on_message(client, user, data, msg):
    print("On message function")
    global motor_moving
    print("Motor moving is " + str(motor_moving))
    if not motor_moving:
        try:
            value = int(msg.payload.decode())  # Directly converting payload to integer
            print("Value" + str(value))

            # if value == 1:
            #     print("Moving motor: Organic Waste")
            #     move_motor(2500)
            #     time.sleep(2)
            #     print("Moving motor: Back to Center")
            #     move_motor(-2500)
            # elif value == 2:
            #     print("Moving motor: Inorganic Waste")
            #     move_motor(-2500)
            #     time.sleep(2)
            #     print("Moving motor: Back to Center")
            #     move_motor(2500)

        except ValueError:
            print("Received non-integer value")
        except Exception as e:
            print(f"Error processing message: {e}")

# MQTT client configuration
mqtt_client = mqtt.Client()
mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message

# Set the security options - Change these to your certificate files
ca = "root_cert_auth.crt"
cert = 'client.crt'
private = 'client.key'

mqtt_client.tls_set(ca_certs=ca, certfile=cert, keyfile=private, cert_reqs=ssl.CERT_REQUIRED, tls_version=ssl.PROTOCOL_TLSv1_2, ciphers=None)
mqtt_client.tls_insecure_set(False)

# Connect to AWS IoT Core - Replace with your endpoint
mqtt_endpoint = "adjvq7uqn9pv1-ats.iot.us-east-1.amazonaws.com"  # Replace with your AWS IoT Core endpoint
mqtt_client.connect(mqtt_endpoint, 8883, 60)

try:
    mqtt_client.loop_start()
    while True:
        # Keep the script running
        time.sleep(1)
except KeyboardInterrupt:
    print("Script interrupted by user")
except Exception as e:
    print(f"An error occurred: {e}")
finally:
    mqtt_client.loop_stop()
    mqtt_client.disconnect()
    # GPIO.cleanup()
    print("Script terminated and resources cleaned up")