#!/usr/bin/env python3
"""
Servo Data Simulator with FM Quality for Hexapod Robot

This script generates realistic servo data with FM radio quality metrics
for testing the hexapod control application.

Data format: <timestamp;angle1;angle2;...;angle18;speed;packet_count;rssi;per;crc>

Author: [Your name]
Date: [Date]
"""

import serial
import time
import random
import math
import sys

def generate_servo_frame(time_ms, frame_counter):
    """
    Generate servo frame with FM data compatible with Qt application format.
    Format: <timestamp;angle1;angle2;...;angle18;speed;packet_count;rssi;per;crc>
    
    Args:
        time_ms (int): Current timestamp in milliseconds
        frame_counter (int): Sequential frame number
        
    Returns:
        tuple: (frame_string, angles_list, rssi, per)
    """
    # Generate 18 angles (6 legs × 3 joints)
    angles = []
    
    # Simulate realistic hexapod robot movements
    for leg in range(6):
        # Hip angle: -45° to +45°
        hip_base = -30 + 60 * (leg / 5.0)  # Different base positions for legs
        hip_movement = 15 * math.sin(time_ms * 0.002 + leg * math.pi / 3)
        hip_angle = hip_base + hip_movement
        
        # Knee angle: 0° to 90°
        knee_movement = 30 * math.sin(time_ms * 0.003 + leg * math.pi / 6)
        knee_angle = 45 + knee_movement
        
        # Ankle angle: -30° to +30°
        ankle_movement = 20 * math.cos(time_ms * 0.0025 + leg * math.pi / 4)
        ankle_angle = ankle_movement
        
        angles.extend([
            round(hip_angle, 2),
            round(knee_angle, 2), 
            round(ankle_angle, 2)
        ])
    
    # Speed: simulate walking speed
    speed_variation = 10 * math.sin(time_ms * 0.001)
    speed = round(-50 + speed_variation, 2)
    
    # Packet count: increment with each frame
    packet_count = frame_counter
    
    # === FM/Radio Data Generation ===
    
    # RSSI (Received Signal Strength Indicator) - signal strength in dBm
    # Simulate realistic conditions: distance, obstacles, interference
    base_rssi = -55.0  # Base signal strength
    
    # Slow changes (robot movement, environment changes)
    slow_variation = 8 * math.sin(time_ms * 0.0008)
    
    # Fast fluctuations (interference, multipath)
    fast_noise = random.uniform(-3, 3)
    
    # Sporadic signal drops (obstacles, interference)
    if random.random() < 0.02:  # 2% chance of drop
        signal_drop = random.uniform(-15, -8)
    else:
        signal_drop = 0
    
    rssi = round(base_rssi + slow_variation + fast_noise + signal_drop, 1)
    rssi = max(-85.0, min(-25.0, rssi))  # Realistic limits
    
    # PER (Packet Error Rate) - percentage of erroneous packets
    # Depends on signal strength - weaker signal = more errors
    base_per = 2.0  # Base error level
    
    # PER increases exponentially with weaker signal
    signal_quality_factor = max(0, (-rssi - 40) / 10)  # 0 for good signals, >1 for weak
    signal_per = base_per * (1 + signal_quality_factor ** 2)
    
    # Additional fluctuations
    per_noise = random.uniform(-0.5, 1.5)
    
    per = round(signal_per + per_noise, 2)
    per = max(0.0, min(50.0, per))  # Limits 0-50%
    
    # === End FM Data ===
    
    # Assemble core string (without CRC)
    parts = [str(time_ms)] + [str(angle) for angle in angles] + [str(speed), str(packet_count), str(rssi), str(per)]
    core = ";".join(parts)
    
    # Calculate CRC as sum of bytes modulo 256
    crc = sum(core.encode("utf-8")) % 256
    
    # Assemble complete frame
    frame = f"<{core};{crc}>\n"
    
    return frame, angles, rssi, per

def main():
    """Main simulation function"""
    if len(sys.argv) > 1:
        port_path = sys.argv[1]
    else:
        port_path = "/dev/pts/2"  # Default port
    
    print(f"Servo Data Simulator with FM Quality")
    print(f"Connecting to port: {port_path}")
    print(f"Baudrate: 115200")
    print(f"Format: <timestamp;18_angles;speed;packet_count;rssi;per;crc>")
    print(f"RSSI: -85 to -25 dBm | PER: 0 to 50%")
    print("Generating data...")
    print("Press Ctrl+C to stop\n")
    
    try:
        # Open serial port
        ser = serial.Serial(port_path, 115200, timeout=1)
        
        frame_counter = 0
        start_time = int(time.time() * 1000)
        
        while True:
            # Calculate current timestamp
            current_time = int(time.time() * 1000) - start_time
            
            # Generate frame with FM data
            frame, angles, rssi, per = generate_servo_frame(current_time, frame_counter)
            
            # Send frame
            ser.write(frame.encode("utf-8"))
            
            # Log every 20 frames (1 second at 20Hz)
            if frame_counter % 20 == 0:
                print(f"Frame #{frame_counter:4d} | Time: {current_time:6d}ms")
                print(f"   Angles: Leg 1: [{angles[0]:5.1f}°, {angles[1]:5.1f}°, {angles[2]:5.1f}°]")
                print(f"   FM: RSSI={rssi:5.1f}dBm, PER={per:4.1f}%")
                print(f"   Size: {len(frame)} bytes")
            
            frame_counter += 1
            time.sleep(0.05)  # 20 Hz (50ms)
            
    except serial.SerialException as e:
        print(f"Serial port error: {e}")
        print(f"Check if port {port_path} exists and socat is running")
    except KeyboardInterrupt:
        print(f"\nStopped by user")
        print(f"Total frames sent: {frame_counter}")
    except Exception as e:
        print(f"Unexpected error: {e}")
    finally:
        try:
            ser.close()
            print("Port closed")
        except:
            pass

if __name__ == "__main__":
    main()
