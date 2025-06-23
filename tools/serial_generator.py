import serial
import time
import random

def generate_frame(packet_count):
    timestamp = int(time.time() * 1000) % 1000000
    angles = [round(random.uniform(-90, 90), 2) for _ in range(18)]
    speed = 9600
    parts = [str(timestamp)] + [str(a) for a in angles] + [str(speed), str(packet_count)]
    core = ";".join(parts)
    crc = sum(bytearray(core.encode("utf-8"))) % 256
    frame = f"<{core};{crc}>"
    return frame

def main():
    port = "/dev/pts/2"  # lub inny port
    baud = 115200
    s = serial.Serial(port, baud, timeout=1)
    packet_count = 0
    try:
        while True:
            frame = generate_frame(packet_count)
            s.write((frame + "\n").encode("utf-8"))
            print("Wysłano:", frame)
            packet_count += 1
            time.sleep(0.05)  # 20 Hz
    except KeyboardInterrupt:
        print("Przerwano przez użytkownika")
    finally:
        s.close()

if __name__ == "__main__":
    main()
