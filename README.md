Ultrasonic Distance Measurement System (ATmega32)

🚀 Features

- Measure distance using Ultrasonic Sensor (HC-SR04)
- Real-time distance display on LCD
- High accuracy using Timer Input Capture
- Continuous distance monitoring
- Works in cm range

🛠️ Components Used

- ATmega32
- Ultrasonic Sensor (HC-SR04)
- LCD Display
- Resistors & Wires
- Buzzer

⚙️ Drivers Implemented

- GPIO
- Timer (Input Capture Unit - ICU)
- LCD

📂 Project Structure

- MCAL (GPIO, Timer/ICU)
- HAL (Ultrasonic, LCD)
- Application Layer

▶️ How it Works

1. Trigger pin sends a pulse to the ultrasonic sensor
2. Sensor emits ultrasonic waves
3. Echo pin receives the reflected signal
4. Timer measures the time between sending and receiving
5. Distance is calculated using:
   Distance = (Time × Speed of Sound) / 2
6. Result is displayed on LCD

📏 Calculation

- Speed of sound ≈ 340 m/s
- Distance (cm) = Time (µs) / 58

⏱️ Timing Technique

- Uses Timer1 Input Capture Unit (ICU)
- Measures rising and falling edges of Echo signal

🎯 Learning Outcomes

- Working with Input Capture Unit (ICU)
- Accurate time measurement
- Interfacing sensors with microcontroller
- Real-time embedded processing
