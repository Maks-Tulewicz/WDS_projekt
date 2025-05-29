#!/usr/bin/env python3
import numpy as np, random

num_frames = 200
time_step = 50
num_servos = 18
min_a, max_a = 30, 150
base = (max_a + min_a)/2
amp  = (max_a - min_a)/4

def compute_crc(s: str) -> int:
    return sum(s.encode('utf-8')) % 256

with open("servo_test_data_comm.txt", "w") as f:
    for i in range(num_frames):
        ts = i * time_step
        angles = [int(base + amp * np.sin(2*np.pi*0.1*(i + j*5)))
                  for j in range(num_servos)]
        speed   = random.uniform(100.0, 1000.0)
        packets = i
        payload = f"{ts};" + ";".join(map(str, angles)) + f";{speed:.1f};{packets}"
        crc     = compute_crc(payload)
        f.write(f"<{payload};{crc}>\n")
