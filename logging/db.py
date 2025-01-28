import serial
import json
import requests
import configparser
from datetime import datetime
import time

config = configparser.ConfigParser()
config.read('config.ini')

WIFI_SSID = config['WiFi']['ssid']
WIFI_PASSWORD = config['WiFi']['password']
FIREBASE_HOST = config['Firebase']['host']
FIREBASE_AUTH = config['Firebase']['auth']


SERIAL_PORT = "/dev/cu.usbserial-1120" 
BAUD_RATE = 9600


def send_to_firebase(data):
    timestamp_key = datetime.utcnow().strftime("%Y%m%d%H%M%S%f")
    url = f"{FIREBASE_HOST}plantData/{timestamp_key}.json?auth={FIREBASE_AUTH}"
    headers = {"Content-Type": "application/json"}

    try:
        response = requests.put(url, data=json.dumps(data), headers=headers)
        if response.status_code == 200:
            print("Data sent to Firebase:", data)
        else:
            print("Failed to send data to Firebase:", response.status_code, response.text)
    except requests.exceptions.RequestException as e:
        print("Error sending data to Firebase:", e)


def main():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")
        
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode("utf-8").strip()
                
                #Parse
                try:
                    data = json.loads(line)
                    print("Received data:", data)
                    
                    send_to_firebase(data)
                    break

                except json.JSONDecodeError:
                    print("Invalid data format:", line)
                
            time.sleep(0.1)  #prevent cpu overuse
            
    except serial.SerialException as e:
        print(f"Error connecting to serial port: {e}")
    except KeyboardInterrupt:
        print("\nExiting script.")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("Serial connection closed.")


if __name__ == "__main__":
    main()
