import os
import sys
import glob
import random
import serial

if len(sys.argv) != 2:
    print("Usage: python3 setgame.py <folder>")
    sys.exit(1)

folder = sys.argv[1]

if not os.path.isdir(folder):
    print(f"Directory not found: {folder}")
    sys.exit(1)

# Randomly pick a .txt file
txt_files = glob.glob(os.path.join(folder, "*.txt"))

if not txt_files:
    print(f"No .txt files found in: {folder}")
    sys.exit(1)

file = random.choice(txt_files)

# Randomly pick a line from the selected .txt file
with open(file) as f:
    lines = f.readlines()
    password = random.choice(lines).strip()

# Randomly pick a number between 1 and 11
channel = random.randint(1, 11)

# Find the USB serial device
serial_devices = glob.glob("/dev/cu.usbserial*")

if not serial_devices:
    print("Serial device not found")
    sys.exit(1)

serial_device = serial_devices[0]

# Connect to the serial device and send the commands
ser = serial.Serial(serial_device, 115200)

command = f'ap -ssid "NetworkName" -password "{password}" -channel {channel}\n'
ser.write(command.encode())

print(f"Selected password: {password}")
print(f"Selected channel: {channel}")

print("Responses from the device:")

# Read the responses from the serial device in a loop
try:
    while True:
        response = ser.readline().decode()
        print(response, end="")
except KeyboardInterrupt:
    # Close the connection when Ctrl+C is pressed
    ser.close()
    print("\nConnection closed.")

