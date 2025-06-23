#!/usr/bin/env python3
import serial
import time
import random
import math
import sys

def generate_servo_frame(time_ms, frame_counter):
    """
    Generuje ramkę danych servo zgodną z formatem oczekiwanym przez aplikację Qt.
    Format: <timestamp;angle1;angle2;...;angle18;speed;packet_count;crc>
    """
    # Generuj 18 kątów (6 nóg × 3 stawy)
    angles = []
    
    # Symuluj realistyczne ruchy robota hexapod
    for leg in range(6):
        # Hip angle (biodro): -45° do +45°
        hip_base = -30 + 60 * (leg / 5.0)  # Różne pozycje bazowe dla nóg
        hip_movement = 15 * math.sin(time_ms * 0.002 + leg * math.pi / 3)
        hip_angle = hip_base + hip_movement
        
        # Knee angle (kolano): 0° do 90°
        knee_movement = 30 * math.sin(time_ms * 0.003 + leg * math.pi / 6)
        knee_angle = 45 + knee_movement
        
        # Ankle angle (kostka): -30° do +30°
        ankle_movement = 20 * math.cos(time_ms * 0.0025 + leg * math.pi / 4)
        ankle_angle = ankle_movement
        
        angles.extend([
            round(hip_angle, 2),
            round(knee_angle, 2), 
            round(ankle_angle, 2)
        ])
    
    # Speed: symuluj prędkość chodu
    speed_variation = 10 * math.sin(time_ms * 0.001)
    speed = round(-50 + speed_variation, 2)
    
    # Packet count: zwiększaj z każdą ramką
    packet_count = frame_counter
    
    # Złóż core string (bez CRC)
    parts = [str(time_ms)] + [str(angle) for angle in angles] + [str(speed), str(packet_count)]
    core = ";".join(parts)
    
    # Oblicz CRC jako sumę bajtów modulo 256
    crc = sum(core.encode("utf-8")) % 256
    
    # Złóż kompletną ramkę
    frame = f"<{core};{crc}>\n"
    
    return frame, angles

def main():
    if len(sys.argv) > 1:
        port_path = sys.argv[1]
    else:
        port_path = "/dev/pts/2"  # Domyślny port
    
    print(f"🤖 Servo Data Simulator")
    print(f"📡 Łączenie z portem: {port_path}")
    print(f"⚙️ Baudrate: 115200")
    print(f"📊 Format: <timestamp;18_angles;speed;packet_count;crc>")
    print("🔄 Generowanie danych...")
    print("⏹️ Naciśnij Ctrl+C aby zatrzymać\n")
    
    try:
        # Otwórz port szeregowy
        ser = serial.Serial(port_path, 115200, timeout=1)
        
        frame_counter = 0
        start_time = int(time.time() * 1000)
        
        while True:
            # Oblicz aktualny timestamp
            current_time = int(time.time() * 1000) - start_time
            
            # Generuj ramkę
            frame, angles = generate_servo_frame(current_time, frame_counter)
            
            # Wyślij ramkę
            ser.write(frame.encode("utf-8"))
            
            # Loguj co 20 ramek (1 sekunda przy 20Hz)
            if frame_counter % 20 == 0:
                print(f"📤 Ramka #{frame_counter:4d} | Czas: {current_time:6d}ms")
                print(f"   Przykładowe kąty: Noga 1: [{angles[0]:5.1f}°, {angles[1]:5.1f}°, {angles[2]:5.1f}°]")
                print(f"   Rozmiar ramki: {len(frame)} bajtów")
            
            frame_counter += 1
            time.sleep(0.05)  # 20 Hz (50ms)
            
    except serial.SerialException as e:
        print(f"❌ Błąd portu szeregowego: {e}")
        print(f"💡 Sprawdź czy port {port_path} istnieje i czy socat jest uruchomiony")
    except KeyboardInterrupt:
        print(f"\n⏹️ Zatrzymano przez użytkownika")
        print(f"📊 Wysłano łącznie {frame_counter} ramek")
    except Exception as e:
        print(f"❌ Nieoczekiwany błąd: {e}")
    finally:
        try:
            ser.close()
            print("🔌 Port zamknięty")
        except:
            pass

if __name__ == "__main__":
    main()