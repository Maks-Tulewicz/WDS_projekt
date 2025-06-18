import serial
import time
import random

def generate_frame(time_ms):
    angles = [round(random.uniform(-90, 90), 2) for _ in range(18)]
    speed = round(random.uniform(-60, -40), 2)
    packet_count = random.randint(100, 200)

    core = f"{time_ms};" + ";".join(map(str, angles)) + f";{speed};{packet_count}"
    raw_bytes = core.encode("utf-8")
    crc = sum(raw_bytes) % 256
    frame = f"<{core};{crc}>\n"
    return frame

def main():
    port = serial.Serial("/dev/pts/4", 115200)  # ← Dostosuj do używanego pseudoportu!
    t = 0
    while True:
        line = generate_frame(t)
        port.write(line.encode("utf-8"))
        t += 50
        time.sleep(0.05)

if __name__ == "__main__":
    main()
